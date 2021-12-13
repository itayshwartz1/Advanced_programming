

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
public:
    Client();
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
    DefaultIO* getDio(){
        return dio;
    }
};

// implement here your command classes
class UploadCommand:public Command{
public:
    UploadCommand(DefaultIO* dio,Client* client): Command(dio,"Upload command",client){}
    DefaultIO* dio=getDio();
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



#endif /* COMMANDS_H_ */
