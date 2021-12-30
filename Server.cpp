
#include "Server.h"

Server::Server(int port)throw (const char*) {

}

void Server::start(ClientHandler& ch)throw(const char*){
    //Accept loop,for each client.

}

void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}

