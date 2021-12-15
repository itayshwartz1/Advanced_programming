#include "CLI.h"

/**
 *
 *
 */
CLI::CLI(DefaultIO *dio) {
}

void CLI::start() {
    string choice;
    dio= new StandardIo();
    /**
   * DO NOT FORGET TO DELETE ALL NEW COMMANDS
   */
    /**
      * DO NOT FORGET TO DELETE
      * we will modify client object for each client.
      */
    auto *client = new Client();
    client->setCorrelation(0.9);
    //initialize only once and change it.
    initializeCommandMap(client);
    //accept
    while (true) {
        do {
            command_map["0"]->execute();
            choice = dio->read();
            command_map[choice]->execute();
        } while (choice != "6");
    }
    //removing all allocations.
    deleteCommandMap();
}


CLI::~CLI() {
}

void CLI::initializeCommandMap(Client *client) {
    command_map.insert({"0", new MenuCommand(dio, client)});
    command_map.insert({"1", new UploadCommand(dio, client)});
    command_map.insert({"2", new AlgorithmSetting(dio, client)});
    command_map.insert({"3", new DetectAnomaly(dio, client)});
    command_map.insert({"4", new DisplayResults(dio, client)});
    command_map.insert({"5", new UploadAndAnalyze(dio, client)});
    command_map.insert({"6", new Exit(dio, client)});
}

void CLI::deleteCommandMap() {
    for (auto &key: command_map) {
        delete[]key.second;
    }
}

