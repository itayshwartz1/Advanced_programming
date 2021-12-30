

#include "Server.h"

Server::Server(int port) throw(const char *){
    stopped=false;
    if (server_fd = socket(AF_INET, SOCK_STREAM, 0) == 0) {
        throw "socket failed";
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        throw "bind failed";
    }
    if (listen(server_fd, 3) < 0) {
        throw "listen failure";
    }
}

void Server::start(ClientHandler &ch) throw(const char *) {
    //openning a new server in a new thread
    t = new thread([&ch, this]() {
        //Accept loop,for each client
        while(!stopped){
        cout << "waiting for client" << endl;
        socklen_t client_size = sizeof(client);
        //if there is no movment in the thread for max 2 seconds, close the thread.
        alarm(2);
        int a_client = accept(server_fd, (struct sockaddr *) &client, &client_size);
            if (a_client < 0)
                throw "accept failure";
            //debugging print
            cout << "client connected" << endl;
            //if we want different threads need to add here new thread
            ch.handle(a_client);
            close(a_client);
            close(server_fd);
        }
    });

}

void Server::stop() {
    stopped=true;
    t->join(); // do not delete this!
}

Server::~Server() {
}

