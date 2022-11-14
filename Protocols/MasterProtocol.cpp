//
// Created by aziz on 16.08.21.
//

#include "MasterProtocol.h"
#include "../GateWay/Node/ModBusTag.h"
#include "../GateWay/Node/NodeList.h"
#include <boost/tokenizer.hpp>
#include <string>

extern std::vector<Connection*> ConnectionS;
void ProtocolS::ModBus::MasterProtocol::Listen()
{
    std::cout << "Run..."<<std::endl;
    Run();
}

ProtocolS::ModBus::MasterProtocol::MasterProtocol()
{
}

ProtocolS::ModBus::MasterProtocol::~MasterProtocol()
{
}

void ProtocolS::ModBus::MasterProtocol::Create(Connection *Conn)
{
    Conn_Modbus_.reset(reinterpret_cast<ConnectionModbus* >(Conn));
    std::string strPro = (ConnectionType::RTU == Conn_Modbus_->Type) ? "Rtu":"Tcp";
    std::cout << "Address : "<<Conn_Modbus_->Address.Value.c_str()<< std::endl;
    boost::char_separator<char> sep(":");
    boost::tokenizer tok(Conn_Modbus_->Address.Value,sep);
    auto it = tok.begin();
    auto it1 = ++tok.begin();
    std::cout << *it << "*********************" << *it1<<std::endl;
    bSetBackend(strPro, *it, *it1);
    
    slv = &Node.addSlave(1);
    ////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////    
    ModBUS::mHandlerAct cb = [this]() -> bool
    {
        
        while (slv->isOpen() &&!bStopThread)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MODBUS));
            for (auto it = Observer.begin(); it != Observer.end(); it++)
            {
                auto tag = reinterpret_cast<ModBusTag *>(*it);
                int size = 1;//tag->getNumberOfRegisters();
                uint16_t *int_values = new uint16_t[size];
                bool *bool_values = new bool[size];
                std::cout << tag->getStartingAddress() << "************Modbus*************" << std::endl<< 
                            "Is Open : " << slv->isOpen() << "    Size is " << size << std::endl;
                tag->setFunction(FunctionCode::ReadInputRegisters) ;
                std::cout << "*Function : " <<tag->getFunction() << std::endl ;
                switch (tag->getFunction())
                {
                case FunctionCode::ReadCoil: 
                    if ( slv->readCoils(tag->getStartingAddress(), bool_values, size)== size)
                        {
                            tag->setValue(bool_values, size * sizeof(bool));
                            std::cout << "*Value : " << (bool_values[0]? "true" : "false")  << std::endl ;
                        }
                    break;

                case FunctionCode::ReadDiscreteInputs:
                    break;

                case FunctionCode::ReadMultipleHoldingRegisters:
                    if (slv->readRegisters(tag->getStartingAddress(), int_values, size) == size)
                    {
                        tag->setValue(int_values, size * sizeof(uint16_t));
                        std::cout << "*Value : " << int_values[0] << std::endl ;
                    }
                    break;

                case FunctionCode::ReadInputRegisters:
                {
                    int b = slv->readInputRegister(tag->getStartingAddress()+1, int_values[0]);
                    if (b == size)
                    {
                        tag->setValue(int_values, size * sizeof(uint16_t));
                        int a = 0;
                        memcpy(&a, int_values, sizeof(int));
                        std::cout << "<<<<<< Value : " << a << std::endl;
                    }
                    else
                    {
                        std::cout << "<<<<<< Error : " << b << std::endl;
                    }
                  
                }
                break;

                default:
                    break;
                }
            }
        }
        return true;
    };
    SetAct(cb);
}

ProtocolS::ModBusTag *ProtocolS::ModBus::MasterProtocol::FindModbusTag(std::string name)
{
    for (auto p : ConnectionS)
        if (p->IProtocol == ProtocolIIOT::MODBUS)
            for (auto n : p->NodeS){
                 auto mq = reinterpret_cast<xmlModBus*>(n);
                ProtocolS::ModBusTag* mn{new ProtocolS::ModBusTag(mq)};
                 if (strcmp(mn->Name.Value.c_str(), name.c_str()) == 0)
                    return (ProtocolS::ModBusTag*) mn;
            }
               
    std::cout << "Modbus Tag :Not Found" << std::endl;
    return nullptr;
}

void ProtocolS::ModBus::MasterProtocol::OpenAndWrtie(Connection* Conn , Data* data)
{
    Conn_Modbus_.reset(reinterpret_cast<ConnectionModbus *>(Conn));
    std::string strPro = (ConnectionType::RTU == Conn_Modbus_->Type) ? "Rtu" : "Tcp";
    boost::char_separator<char> sep(":");
    boost::tokenizer tok(Conn_Modbus_->Address.Value, sep);
    auto it = tok.begin();
    auto it1 = ++tok.begin();
    std::cout << *it << "*********************" << *it1;

    bSetBackend(strPro, *it, *it1);
    slv = &Node.addSlave(1);
    Node.open();
}

void ProtocolS::ModBus::MasterProtocol::Open(Connection *Conn)
{
    Conn_Modbus_.reset(reinterpret_cast<ConnectionModbus *>(Conn));
    std::string strPro = (ConnectionType::RTU == Conn_Modbus_->Type) ? "Rtu" : "Tcp";
    boost::char_separator<char> sep(":");
    boost::tokenizer tok(Conn_Modbus_->Address.Value, sep);
    auto it = tok.begin();
    auto it1 = ++tok.begin();
    std::cout << *it << "*********************" << *it1;

    bSetBackend(strPro, *it, *it1);
    slv = &Node.addSlave(1);
    Node.open();
}

void ProtocolS::ModBus::MasterProtocol::Close()
{
    Node.close();
}

void ProtocolS::ModBus::MasterProtocol::KeepAlive()
{
}

bool ProtocolS::ModBus::MasterProtocol::isOK()
{
    return Node.isConnected();
}

void ProtocolS::ModBus::MasterProtocol::Reconnect()
{
    if (!isOK())
    {
        Node.connection();
    }
}

void ProtocolS::ModBus::MasterProtocol::hasError()
{
    std::cerr << Node.lastError() << std::endl;
}

void ProtocolS::ModBus::MasterProtocol::DataReceived()
{
}

void ProtocolS::ModBus::MasterProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::ModBus::MasterProtocol::Write(Data* data,Tag* _tag)
{
    if (slv->isOpen())
    {
        ProtocolS::ModBusTag *tag = (ProtocolS::ModBusTag *)_tag;
        int size = tag->getNumberOfRegisters();
        uint16_t values[size];
        bool boolvalues[size];
        switch (tag->getFunction())
        {
        case FunctionCode::WriteSingleCoil:
            memcpy(boolvalues, data->data, size * sizeof(bool));
            if (slv->writeCoil(tag->getStartingAddress(), boolvalues[0]) == size)
            {
                std::cout << "++++++ write modbus WriteSingleCoil++++++" << std::endl;
            }
            tag->outputTime = boost::posix_time::microsec_clock::local_time();
            break;
        case FunctionCode::WritesingleHoldingRegister:
            memcpy(values, data->data, size * sizeof(uint16_t));
            if (slv->writeRegisters(tag->getStartingAddress(), values, size) == size)
            {
                std::cout << "++++++ write modbus WritesingleHoldingRegister++++++" << values[0] << std::endl;
            }
            tag->outputTime = boost::posix_time::microsec_clock::local_time();
            break;
        case FunctionCode::WriteMultipleCoils:
            memcpy(boolvalues, data->data, size * sizeof(bool));
            if (slv->writeCoils(tag->getStartingAddress(), boolvalues, size) == size)
            {
                std::cout << "++++++ write modbus  WriteMultipleCoils++++++" << std::endl;
            }
            tag->outputTime = boost::posix_time::microsec_clock::local_time();
            break;
        default:
            std::cout << "##Cant find function :" << tag->getFunction() << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "Error open modbus to write ....." << std::endl;
    }
}


void ProtocolS::ModBus::MasterProtocol::Stop()
{
    bStopThread = true;
    ModBUS::Master::Stop();
}
