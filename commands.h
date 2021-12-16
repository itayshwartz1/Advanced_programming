

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <utility>
#include <vector>
#include "HybridAnomalyDetector.h"


using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here

};

// you may add here helper classes
class StandardIo : public DefaultIO {
    virtual string read() override {
        string result;
        getline(cin, result);
        return result;
    }

    virtual void write(string text) override {
        cout << text;
    }

    virtual void write(float f) override {
        cout << f;
    }

    //need to check
    virtual void read(float *f) override {
        cout << f;
    }
};

class Client {
    string train_path;
    string test_path;
    double correlation;
    int test_line_size;
    int csv_lines;
    vector<AnomalyReport> *anomaly_report;
public:
    Client() {}

    void setTrainPath(string path) {
        train_path = path;
    }

    int getCsvLines() {
        return csv_lines;
    }

    void setCsvLines(int n) {
        csv_lines = n;
    }

    string getTrainPath() {
        return train_path;
    }

    void setTestPath(string path) {
        test_path = path;
    }

    string getTestPath() {
        return test_path;
    }

    void setCorrelation(double corr) {
        correlation = corr;
    }

    double getCorrelation() {
        return correlation;
    }

    void setTestLineSize(int size) {
        test_line_size = size;
    }

    int getTestLineSize() {
        return test_line_size;
    }

    const vector<AnomalyReport> *getAnomalyReport() {
        return anomaly_report;
    }

    void setAnomalyReport(vector<AnomalyReport> *ar) {
         anomaly_report = ar;
    }
};

// you may edit this class
class Command {
    string description;
    Client *client;
    DefaultIO *dio;
public:
    Command(DefaultIO *dio) : dio(dio) {}

    Command(DefaultIO *dio, string description, Client *client) : dio(dio), description(std::move(description)),
                                                                  client(client) {}


    virtual void execute() = 0;

    virtual ~Command() {}

    void setDescription(string &desc) {
        description = desc;
    }

    void setClient(Client *client) {
        client = client;
    }

    string getDescription() {
        return description;
    }

    Client &getClient() {
        return *client;
    }

    DefaultIO *getDefaultIO() {
        return dio;
    }
};

// implement here your command classes
class UploadAndAnalyze : public Command {
public:
    UploadAndAnalyze(DefaultIO *dio, Client *client) : Command(dio, "UploadAndAnalyze command", client) {}

    DefaultIO *dio = getDefaultIO();

    virtual void execute() override {
        vector<pair<int, int>> compressed_report = compressReport(*getClient().getAnomalyReport());
        vector<pair<int, int>> real_report = initRealReport();
        int FP = 0, TP = 0;
        if ((int) compressed_report.size() == 0) {
            FP = (int) real_report.size();
        }
        if ((int) real_report.size() == 0) {
            FP = (int) compressed_report.size();
        }
        int i = 0;
        int j = 0;
        while (i < compressed_report.size() || j < real_report.size()) {
            if (isContained(compressed_report[i], real_report[j])) {
                TP++;
                if (compressed_report[i].second >= real_report[j].second)
                    j++;
                else i++;
            } else {
                FP++;
            }
        }
        string TP_result = to_string((double) ((double) TP / (double) real_report.size()));
        string FP_result = to_string((double) FP / (double) getClient().getCsvLines());
        dio->write("True Positive Rate: \n" + TP_result);
        dio->write("False Positive Rate: \n" + FP_result);

    }

    bool isContained(pair<int, int> a, pair<int, int> b) {
        if ((a.first >= b.first && a.first <= b.second) || (b.first <= a.second && b.first >= a.first)) {
            return true;
        }
        return false;
    }

    vector<pair<int, int>> initRealReport() const {
        vector<pair<int, int>> result = {};
        string line = dio->read();
        //splitting
        int indx = line.find(',');
        int start, end;
        while (line != "done") {
            start = stoi(line.substr(0, indx - 1));
            end = stoi(line.substr(indx + 1, line.size() - 1));
            result.emplace_back(start, end);
            line = dio->read();
        }
        return result;
    }

    static vector<pair<int, int>> compressReport(const vector<AnomalyReport> &ar) {

        vector<pair<int, int>> ret = {};
        if (ar.empty()) {
            return ret;
        }
        const AnomalyReport *start = &ar[0];
        for (int i = 1; i < ar.size(); i++) {
            if (ar[i - 1].description == ar[i].description && ar[i - 1].timeStep + 1 == ar[i].timeStep) {
                continue;
            }
            ret.emplace_back(start->timeStep, ar[i - 1].timeStep);
            start = &ar[i];
        }
        return ret;
    }
};

class MenuCommand : public Command {
public:
    MenuCommand(DefaultIO *dio, Client *client) : Command(dio, "Menu Command", client) {}

    DefaultIO *dio = getDefaultIO();

    virtual void execute() override {
        dio->write("Welcome to the Anomaly Detection Server.\n"
                   "Please choose an option:\n"
                   "1. upload a time series csv file\n"
                   "2. algorithm settings\n"
                   "3. detect anomalies\n"
                   "4. display results\n"
                   "5. upload anomalies and analyze results\n"
                   "6. exit\n");
    }
};

class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO *dio, Client *client) : Command(dio, "Upload command", client) {}

    DefaultIO *dio = getDefaultIO();

    virtual void execute() override {
        dio->write("Please upload your local train CSV file.\n");
        string test_path="C:\\Users\\yhood\\CLionProjects\\Advanced_programming\\server\\anomalyTest.csv";
        string train_path="C:\\Users\\yhood\\CLionProjects\\Advanced_programming\\server\\anomalyTrain.csv";
        getClient().setTestPath(test_path);
        getClient().setTrainPath(train_path);
        getCSV(test_path, true);
        dio->write("Please upload your local test CSV file.\n");
        getCSV(train_path, false);

    }

    /**
     * 
     * @param path the path of the file
     * @param update_csv_len if we add anomalyTest we want to count number of lines
     */
    void getCSV(string path, bool update_csv_len) {
        fstream myfile;
        int counter = 0;
        myfile.open(path, ios::out);
        if (!myfile) {
            cout << "file didnt create";
        }
        string data;
        data = dio->read();
        while (data != "done") {
            counter++;
            myfile << data + "\n";
            data = dio->read();
        }
        myfile.close();
        if (update_csv_len) {
            getClient().setCsvLines(counter);
        }
        dio->write("Upload complete.\n");
    }
};

class Exit : public Command {
public:
    Exit(DefaultIO *dio, Client *client) : Command(dio, "Exit", client) {}

    void execute() override {
        string testPath = getClient().getTestPath();
        string trainPath = getClient().getTrainPath();
        remove(testPath.c_str());
        remove(trainPath.c_str());
        getClient().setCorrelation(0);
        getClient().setTestLineSize(0);
    }
};

class DisplayResults : public Command {
public:
    DisplayResults(DefaultIO *dio, Client *client) : Command(dio, "DisplayResults", client) {}

    void execute() override {
        vector<AnomalyReport> ar = *getClient().getAnomalyReport();
        for (auto &element: ar) {
            getDefaultIO()->write(to_string(element.timeStep) + "\t" + element.description);
        }
        getDefaultIO()->write("Done.");
    }
};

class DetectAnomaly : public Command {
public:
    DetectAnomaly(DefaultIO *dio, Client *client) : Command(dio, "DetectAnomaly", client) {}

    void execute() override {
        string train_path = getClient().getTrainPath();
        TimeSeries ts(train_path.c_str());
        HybridAnomalyDetector ad;
        ad.learnNormal(ts);

        string test_path = getClient().getTestPath();
        TimeSeries ts2(test_path.c_str());
        vector<AnomalyReport> report = ad.detect(ts2);

        getClient().setAnomalyReport(&report);
        getDefaultIO()->write("anomaly detection complete.\n");
    }
};

class AlgorithmSetting : public Command {
public:
    AlgorithmSetting(DefaultIO *dio, Client *client) : Command(dio, "AlgorithmSetting", client) {}

    void execute() override {
        float corr;
        while (true) {
            getDefaultIO()->write("The current correlation threshold is " +
                                  to_string(getClient().getCorrelation()) + "\n");
            corr = std::stof((getDefaultIO()->read()));
            if (corr <= 1 && corr >= 0) {
                break;
            }
            getDefaultIO()->write("please choose a value between 0 and 1.\n");

        }
        getClient().setCorrelation(corr);

    }
};


#endif /* COMMANDS_H_ */
