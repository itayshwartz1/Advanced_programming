

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
    void local_download(string path){}

};

// you may add here helper classes
class StandardIo:public DefaultIO{
    virtual string read() override{
        string result;
        cin>>result;
        return result;
    }
    virtual void write(string text) override{
        cout<<text;
    }
    virtual void write(float f) override{
        cout<<f;
    }
    //need to check
    virtual void read(float* f) override{
        cout<<f;
    }
};
class Client {
    string train_path;
    string test_path;
    double correlation;
    int test_line_size;
    vector<AnomalyReport> anomaly_report;
public:
    Client();

    void setTrainPath(string path) {
        train_path = path;
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

    vector<AnomalyReport> getAnomalyReport() {
        return anomaly_report;
    }

    void setAnomalyReport(vector<AnomalyReport> ar) {
        anomaly_report = ar;
    }
};

// you may edit this class
class Command{
    string description;
    Client* client;
	DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio),description(nullptr){}
    Command(DefaultIO* dio,string description,Client* client):dio(dio),description(description),client(client){}
	virtual void execute()=0;
	virtual ~Command(){}
    void setDescription(string desc){
        description=desc;
    }
    void setClient(Client* client){
        client = client;
    }
    string getDescription(){
        return description;
    }
    Client* getClient(){
        return client;
    }

    DefaultIO *getDefaultIO() {
        return dio;
    }
};

// implement here your command classes
class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO* dio,Client* client): Command(dio,"Upload command",client){}
    DefaultIO* dio=getDefaultIO();
    virtual void execute() override{
        dio->write("Please upload your local train CSV file.");
        getCSV("anomalyTest.csv");
        dio->write("Please upload your local test CSV file.");
        getCSV("anomalyTrain.csv");

    }
    void getCSV(string path){
        fstream myfile;
        myfile.open(path,ios::in);
        string data;
        data=dio->read();
        while(data!="done"){
            myfile<<data;
            data=dio->read();
        }
        myfile.close();
        dio->write("Upload complete.");
    }
};

class Exit : public Command {
public:
    Exit(DefaultIO *dio, Client *client) : Command(dio, "Exit", client) {}

    void execute() override {
        string testPath = getClient()->getTestPath();
        string trainPath = getClient()->getTrainPath();
        remove(testPath.c_str());
        remove(trainPath.c_str());
        getClient()->setCorrelation(0);
        getClient()->setTestLineSize(0);
    }
};

class DisplayResults : public Command {
public:
    DisplayResults(DefaultIO *dio, Client *client) : Command(dio, "DisplayResults", client) {}

    void execute() override {
        vector<AnomalyReport> ar = getClient()->getAnomalyReport();
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
        string train_path = getClient()->getTrainPath();
        TimeSeries ts(train_path.c_str());
        HybridAnomalyDetector ad;
        ad.learnNormal(ts);

        string test_path = getClient()->getTestPath();
        TimeSeries ts2(test_path.c_str());
        vector<AnomalyReport> report = ad.detect(ts2);

        getClient()->setAnomalyReport(report);
        getDefaultIO()->write("anomaly detection complete.");
    }
};

class AlgorithmSetting : public Command {
public:
    AlgorithmSetting(DefaultIO *dio, Client *client) : Command(dio, "AlgorithmSetting", client) {}

    void execute() override {
        float corr;
        while (true) {
            getDefaultIO()->write("The current correlation threshold is " + to_string(getClient()->getCorrelation()));
            corr = std::stof((getDefaultIO()->read()));
            if (corr <= 1 && corr >= 0) {
                break;
            }
            getDefaultIO()->write("please choose a value between 0 and 1.");

        }
        getClient()->setCorrelation(corr);

    }
};


#endif /* COMMANDS_H_ */
