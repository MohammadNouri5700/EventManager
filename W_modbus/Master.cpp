//
// Created by aziz on 23.08.21.
//

#include "Master.h"


ModBUS::Master::Master()
{

}

ModBUS::Master::~Master()
{

}

void ModBUS::Master::Run()
{
    if( bStopThread )
        return;

    try {
        
        if (Node.open()) {
            std::cout << "void ModBUS::Master::Run()" << Node.isValid() << std::endl;
            ActCb();
            Node.close();
        } else {
            std::cerr << "Unable to open MODBUS aConnection to " << Node.connection() << std::endl;
            ERROR::Error err{ERR_MODBUS, "not found Modbus::master", "debug modbus::master", ERROR::ErrorType::RUN_TIME, 5};
            errorManager.AddError(err);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unattended exception !" << std::endl;
    }

}

void ModBUS::Master::Stop()
{
    std::cerr << "void Snap7::S7Client::Stop()" << std::endl;
    bStopThread = true;
}
