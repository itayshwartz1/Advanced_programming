#include "CLI.h"
/**
 * TODO:
 * Create Command map.
 * Initialize Client
 * Check if we send Client by &.
 * run maintrain.
 *
 *
 */
CLI::CLI(DefaultIO *dio) {
}

void CLI::start() {
    string choice;
    //accept
    /**
     * DO NOT FORGET TO DELETE
     */
    auto* client=new Client();
    /**
     * Need to create commands_array
     */

    while (true) {
        command_map["0"].execute();
        choice = dio->read();
        command_map[choice].execute();
    }
}


CLI::~CLI() {
}
void CLI::initializeCommandMap(Client& client) {
    command_map.insert(make_pair("0",new MenuCommand(dio,client)))

}
