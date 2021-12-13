

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

};

// you may add here helper classes
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
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
    void setDescription(string desc){
        description=desc;
    }
    void setClient(Client* client){
        client=client;
    }
    string getDescription(){
        return description;
    }
    Client* getClient(){
        return client;
    }
};

// implement here your command classes
class UploadCommand:public Command{
public:

};



#endif /* COMMANDS_H_ */
