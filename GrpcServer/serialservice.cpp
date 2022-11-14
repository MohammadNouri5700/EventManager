#include "serialservice.h"
#include <iostream>
#include "../GateWay/Node/NodeList.h"
#include "../GateWay/SimpleSerial.h"
#include "../GateWay/ConvertS/OutputNode.h"
using namespace grpc;
extern std::vector<OutputNode *> OutnodeS;

SystemSerialConfigService::SystemSerialConfigService(CONNECTION::ConnectionManager *ConnMan)
{
    // connMan = ConnMan;
}

::grpc::Status SystemSerialConfigService::SendSystemSerialConfig(::grpc::ServerContext *context, const ::SerialConfig *request, ::SerialResponse *response)
{

    std::cout << "Received Serial Config request" << std::endl;       
    rs232Config.dataBit = request->rs232config().databit();
    rs232Config.enabled = request->rs232config().enabled();
    rs232Config.endBit = request->rs232config().endbit();
    rs232Config.serialBaudRate = request->rs232config().serialbaudrate();
    std::cout << "Received baud 232" << rs232Config.serialBaudRate<< std::endl;  
    rs232Config.serialParity = request->rs232config().serialparity();

    rs485Config.dataBit = request->rs485config().databit();
    rs485Config.enabled = request->rs485config().enabled();
    rs485Config.endBit = request->rs485config().endbit();
    rs485Config.serialBaudRate = request->rs485config().serialbaudrate();
     std::cout << "Received baud 485 " << rs485Config.serialBaudRate<< std::endl; 
    rs485Config.serialParity = request->rs485config().serialparity();

    try
    {

        SimpleSerial serial("/dev/ttyO2", EnumToNumberBaud(rs232Config.serialBaudRate),
            EnumToNumberParity(rs232Config.serialParity),rs232Config.dataBit , rs232Config.endBit);

                std::cout << "Baud: "<<  EnumToNumberBaud(rs232Config.serialBaudRate)
                << "Parity : "<<  EnumToNumberParity(rs232Config.serialParity) 
                << "Data : "<< rs232Config.dataBit   
                << "Stop :" << rs232Config.endBit << 
                "Enabled : " << rs232Config.enabled << std::endl;

                std::cout << "Baud: "<<  EnumToNumberBaud(rs485Config.serialBaudRate)
                << "Parity : "<<  EnumToNumberParity(rs485Config.serialParity) 
                << "Data : "<< rs485Config.dataBit   
                << "Stop :" << rs485Config.endBit << 
                "Enabled : " << rs485Config.enabled << std::endl;
        if(rs232Config.enabled == true)
            serial.writeString("Hello world2\n");
        //std::cout << serial.readLine() << std::endl;
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return Status::OK;
}

u_int32_t SystemSerialConfigService::EnumToNumberBaud(SerialBaudRate serialBaudRate)
{
    u_int32_t BaudRate = 0;
    switch (serialBaudRate)
    {
    case SerialBaudRate::BS300:
        BaudRate = 300;
        break;

    case SerialBaudRate::BS600:
        BaudRate = 600;
        break;

    case SerialBaudRate::BS1200:
        BaudRate = 1200;
        break;

    case SerialBaudRate::BS2400:
        BaudRate = 2400;
        break;

    case SerialBaudRate::BS4800:
        BaudRate = 4800;
        break;

    case SerialBaudRate::BS9600:
        BaudRate = 9600;
        break;
    case SerialBaudRate::BS14400:
        BaudRate = 14400;
        break;

    case SerialBaudRate::BS19200:
        BaudRate = 19200;
        break;

    case SerialBaudRate::BS38400:
        BaudRate = 38400;
        break;
    case SerialBaudRate::BS57600:
        BaudRate = 57600;
        break;

    case SerialBaudRate::BS115200:
        BaudRate = 115200;
        break;

    case SerialBaudRate::BS230400:
        BaudRate = 230400;
        break;

    case SerialBaudRate::BS460800:
        BaudRate = 460800;
        break;

    case SerialBaudRate::BS921600:
        BaudRate = 921600;
        break;

    case SerialBaudRate::BS1843000:
        BaudRate = 1843000;
        break;
    }

    return BaudRate;
}

u_int32_t SystemSerialConfigService::EnumToNumberParity(SerialParity serialParity)
{
    u_int32_t Parity = 0;
    switch (serialParity)
    {
    case SerialParity::SerialNone:
        Parity = 0;
        break;

    case SerialParity::SerialEven:
        Parity = 1;
        break;

    case SerialParity::SerialODD:
        Parity = 2;
        break;
    }
    return Parity;
}