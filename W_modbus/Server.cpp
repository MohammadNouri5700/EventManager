//
// Created by aziz on 23.08.21.
//

#include "Server.h"
ModBUS::Server::Server()
{

}

ModBUS::Server::~Server()
{

}

void ModBUS::Server::Run()
{
    try {
        ActCb(Node);
    } catch (std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unattended exception !" << std::endl;
    }
}