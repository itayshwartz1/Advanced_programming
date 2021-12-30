

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
class SocketIO: public DefaultIO{

    virtual string read() override {

    }
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

struct Client {
    string train_path;
    string test_path;
    float correlation;
    int csv_lines;
    int N;
    vector<AnomalyReport> anomaly_report;
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

    virtual ~UploadAndAnalyze() {}

    DefaultIO *dio = getDefaultIO();

    virtual void execute() override {
        dio->write("Please upload your local anomalies file.\n");
        vector<pair<int, int>> compressed_report = compressReport(getClient().anomaly_report);
        vector<pair<int, int>> real_report = initRealReport(&getClient());
        float FP = 0, TP = 0;
        bool flag = false;
        for (auto &comp_res: compressed_report) {
            for (auto &real_rep: real_report) {
                if ((comp_res.first >= real_rep.first && comp_res.first <= real_rep.second) ||
                    (real_rep.first >= comp_res.first && real_rep.first <= comp_res.second)) {
                    TP++;
                    flag = true;
                }

            }
            if (!flag) {
                FP++;
            }
            flag = false;
        }
        string TP_result = toStringCase(TP, (float) real_report.size());
        string FP_result = toStringCase(FP, (float) getClient().N);
        dio->write("True Positive Rate: " + TP_result + "\n");
        dio->write("False Positive Rate: " + FP_result + "\n");
    }

/**
 * NEED TO DEBUG AND CHECK IT!
 */
    string toStringCase(float result, float size) {
        float temp = result / size;
        string str_temp = to_string(temp);
        str_temp = str_temp.substr(0, 5);
        while ((str_temp.at(str_temp.size() - 1) == '0' && str_temp.size() > 1) ||
               str_temp.at(str_temp.size() - 1) == '.') {
            str_temp = str_temp.substr(0, str_temp.size() - 1);
        }
        return str_temp;
    }

    bool isContained(pair<int, int> a, pair<int, int> b) {
        if ((a.first > b.first && a.first < b.second) || (b.first < a.second && b.first > a.first)) {
            return true;
        }
        return false;
    }

    vector<pair<int, int>> initRealReport(Client *client) const {
        vector<pair<int, int>> result = {};
        string line = dio->read();
        //splitting
        int indx;
        int start, end;
        int N = client->csv_lines;
        while (line != "done") {
            indx = line.find(',');
            start = stoi(line.substr(0, indx));
            end = stoi(line.substr(indx + 1, line.size() - 1));
            result.emplace_back(start, end);
            line = dio->read();
            N -= (end - start) + 1;
        }
        client->N = N;
        dio->write("Upload complete.\n");
        return result;
    }

    static vector<pair<int, int>> compressReport(const vector<AnomalyReport> &ar) {

        vector<pair<int, int>> ret = {};
        if (ar.empty()) {
            return ret;
        }
        const AnomalyReport *start = &ar[0];
        int i;
        for (i = 1; i < ar.size(); i++) {
            if (ar[i - 1].description == ar[i].description && ar[i - 1].timeStep + 1 == ar[i].timeStep) {
                continue;
            }
            ret.emplace_back(start->timeStep, ar[i - 1].timeStep);
            start = &ar[i];
        }
        ret.emplace_back(start->timeStep, ar[i - 1].timeStep);
        return ret;
    }
};

class MenuCommand : public Command {
public:
    MenuCommand(DefaultIO *dio, Client *client) : Command(dio, "Menu Command", client) {}

    virtual ~MenuCommand() {}

    DefaultIO *dio = getDefaultIO();

    virtual void execute() override {
        dio->write("Welcome to the Anomaly Detection Server.\n"
                   "Please choose an option:\n"
                   "1.upload a time series csv file\n"
                   "2.algorithm settings\n"
                   "3.detect anomalies\n"
                   "4.display results\n"
                   "5.upload anomalies and analyze results\n"
                   "6.exit\n");
    }
};

class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO *dio, Client *client) : Command(dio, "Upload command", client) {}

    virtual ~UploadCommand() {}

    DefaultIO *dio = getDefaultIO();

    virtual void execute() override {
        dio->write("Please upload your local train CSV file.\n");
        string test_path = "anomalyTest.csv";
        string train_path = "anomalyTrain.csv";
        getClient().train_path = train_path;
        getClient().test_path = test_path;
        getCSV(train_path, true);
        dio->write("Please upload your local test CSV file.\n");
        getCSV(test_path, false);

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
            getClient().csv_lines = counter - 1;
        }
        dio->write("Upload complete.\n");
    }
};

class Exit : public Command {
public:
    Exit(DefaultIO *dio, Client *client) : Command(dio, "Exit", client) {}

    virtual ~Exit() {}

    void execute() override {
        string testPath = getClient().test_path;
        string trainPath = getClient().train_path;
        remove(testPath.c_str());
        remove(trainPath.c_str());
        getClient().correlation = 0;
    }
};

class DisplayResults : public Command {
public:
    DisplayResults(DefaultIO *dio, Client *client) : Command(dio, "DisplayResults", client) {}

    virtual ~DisplayResults() {}

    void execute() override {
        const vector<AnomalyReport> &ar = getClient().anomaly_report;
        for (auto &element: ar) {
            getDefaultIO()->write(to_string(element.timeStep) + "\t" + element.description + "\n");
        }
        getDefaultIO()->write("Done.\n");
    }
};

class DetectAnomaly : public Command {
public:
    DetectAnomaly(DefaultIO *dio, Client *client) : Command(dio, "DetectAnomaly", client) {}

    virtual ~DetectAnomaly() {}

    void execute() override {
        string train_path = getClient().train_path;
        TimeSeries ts(train_path.c_str());
        HybridAnomalyDetector ad(getClient().correlation);
        ad.learnNormal(ts);

        string test_path = getClient().test_path;
        TimeSeries ts2(test_path.c_str());
        getClient().anomaly_report=ad.detect(ts2);
        getDefaultIO()->write("anomaly detection complete.\n");
    }
};

class AlgorithmSetting : public Command {
public:
    AlgorithmSetting(DefaultIO *dio, Client *client) : Command(dio, "AlgorithmSetting", client) {}

    virtual ~AlgorithmSetting() {}

    void execute() override {
        float corr;
        while (true) {
            float corrolation = getClient().correlation;
            getDefaultIO()->write("The current correlation threshold is " +
                                  to_string(corrolation).substr
                                          (0, to_string(corrolation).find(".") + 2) + "\n");
            getDefaultIO()->write("Type a new threshold\n");
            corr = std::stof((getDefaultIO()->read()));
            if (corr <= 1 && corr >= 0) {
                break;
            }
            getDefaultIO()->write("please choose a value between 0 and 1.\n");

        }
        getClient().correlation = corr;

    }
};


#endif /* COMMANDS_H_ */
