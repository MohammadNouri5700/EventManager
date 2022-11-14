//
// Created by aziz on 30.08.21.
//

#include "SignalS.h"
#include "Event.h"
#include "../Protocols/MasterProtocol.h"
#include "../Protocols/S7Protocol.h"
#include "../Protocols/CanProtocol.h"
#include <fstream>
#include "../wireless/wifi.h"
#include "Node/NodeList.h"
#include "config/config.h"
#include "Node/Tag.h"
#include "Node/MqttTag.h"
#include <map>

extern std::queue<Event> EventList;
extern std::vector<Connection *> ConnectionS;

FunctionType Updater = [](Data *data, auto)
{
    std::cout << "Updater" << std::endl;
    auto tag = dynamic_cast<TagData *>(data)->tag_;
    tag->UpdateValue();
};

FunctionType message01 = [](Data *data, auto)
{
    std::cout << "message01" << std::endl;
    std::string str;

    auto err = dynamic_cast<ErrorData *>(data)->errData;
    str += std::string{"zenity "};
    str += (err.u8Severity == 0 ? "--error" : "--warning");
    str += " --text=";
    str += "\"" + err.strMessage + "\"";
    std::cerr << str << "\n";
    system(str.c_str());
};

std::map<std::string, MqTT::NewPublisher *> mqttBrokers;
std::mutex myMutex;

FunctionType MqttCB01 = [](Data *data, ProtocolS::Tag *dest)
{
    
    myMutex.lock();
    std::cout << "MqttCB01" << std::endl;

    MqTT::NewPublisher *Npub;
    if (mqttBrokers.find(dest->conn->Address.Value) != mqttBrokers.end())
    {
        Npub = mqttBrokers[dest->conn->Address.Value];
        std::cout << "*************** found mqtt  ******************" << dest->conn->Address.Value << std::endl;
    }
    else
    {
        ProtocolS::MqttTag *temp = (ProtocolS::MqttTag *)dest;
        std::cout << "*************** new mqtt  ******************" << dest->conn->Address.Value << std::endl;

        Npub = new MqTT::NewPublisher(dest->conn->Address.Value, ((ConnectionMqtt *)temp->conn)->getID().Value);
        mqttBrokers[dest->conn->Address.Value] = Npub;

        std::cout << "*************** new mqtt  ******************" << temp->Topic.Value << std::endl;
        Npub->SetTopic(temp->Topic.Value);
        // size_t i = 0;
        // p.push_back(std::to_string(i++));
    }


//-------------------------------------------------
//create payload
//------------------------------------------------
    std::string temp;
    temp = "{\n\"deviceTwinDocument\":{ \n \"attributes\":{ \n \"reported\":" + data->GetJson() +  " \n} \n} \n}";
//----------------------------------------------
    std::vector<std::string> p;
    p.clear();
    p.push_back(temp);
    Npub->SetPayload(p);
    std::cout << "*************** run mqtt  ******************" << data->GetString() << std::endl;
    //dest->Value = new std::string(data->GetString());    
    Npub->Run();
    myMutex.unlock();
};

FunctionTypeNode MqttCB02 = [](Data *data, OutputNode *dest_)
{
     myMutex.lock();
    auto dest = dynamic_cast<OutputNode*>(dest_);
    std::cout << "MqttCB02" << std::endl;

    MqTT::NewPublisher *Npub;
    if (mqttBrokers.find(dest->Conn->Name.Value) != mqttBrokers.end())
    {
        Npub = mqttBrokers[dest->Conn->Name.Value];
        std::cout << "*************** found mqtt node ******************" << dest->Conn->Name.Value << std::endl;
    }
    else
    {
        std::cout << "*************** new mqtt node  ******************" << dest->Conn->Name.Value << std::endl;

        Npub = new MqTT::NewPublisher(dest->Conn->Address.Value, ((ConnectionMqtt *)dest->Conn)->getID().Value);
        mqttBrokers[dest->Conn->Name.Value] = Npub;

        std::cout << "*************** new mqtt node2 ******************" << dest->Topic.Value << std::endl;
        Npub->SetTopic(dest->Topic.Value);
        // size_t i = 0;
        // p.push_back(std::to_string(i++));
    }

    std::vector<std::string> p;
    p.clear();
    p.push_back(data->GetString());
    Npub->SetPayload(p);
    Npub->Run();
    myMutex.unlock();
};

std::map<std::string, ProtocolS::ModBus::MasterProtocol *> modbusMasters;

FunctionType ModbusCB01 = [](Data *data, ProtocolS::Tag *dest)
{
    std::cout << "ModbusCB01" << std::endl;
    ProtocolS::ModBus::MasterProtocol *master;
    if (modbusMasters.find(dest->conn->Address.Value) != modbusMasters.end())
    {
        master = modbusMasters[dest->conn->Address.Value];
    }
    else
    {
        master = new ProtocolS::ModBus::MasterProtocol();
        modbusMasters[dest->conn->Address.Value] = master;
        master->Open(dest->conn);
    }
    master->Write(data, dest);
};

std::map<std::string, ProtocolS::S7::S7Protocol *> S7s;

FunctionType S7CB01 = [](Data *data, ProtocolS::Tag *dest)
{
    std::cout << "S7CB01" << std::endl;
    ProtocolS::S7::S7Protocol *s7;
    if (S7s.find(dest->conn->Address.Value) != S7s.end())
    {
        s7 = S7s[dest->conn->Address.Value];
    }
    else
    {
        s7 = new ProtocolS::S7::S7Protocol();
        s7->Create(dest->conn);
        S7s[dest->conn->Address.Value] = s7;
    };
    std::cout << "*************** here S7  ******************" << dest->conn->Address.Value << std::endl;
    s7->Write(data, dest);
};

std::map<std::string, ProtocolS::CAN::CANProtocol *> Cans;

FunctionType CANCB01 = [](Data *data, ProtocolS::Tag *dest)
{
    std::cout << "CANCB01" << std::endl;
    ProtocolS::CAN::CANProtocol *can;
    if (Cans.find(dest->conn->Address.Value) != Cans.end())
    {
        can = Cans[dest->conn->Address.Value];
    }
    else
    {
        can = new ProtocolS::CAN::CANProtocol((ConnectionCAN*)dest->conn);
        //can->Create(dest->conn);
        Cans[dest->conn->Address.Value] = can;
    };
    std::cout << "*************** here can  ******************" << dest->conn->Address.Value << std::endl;
    can->Write(data, dest);
};

FunctionType PrintCB01 = [](Data *data, auto)
{
    std::cout << "FunctionType PrintCB01 = [](Data *data, auto)" << std::endl;
    std::cout << data->GetString() << '\n';
};

FunctionType Notyfy01 = [](Data *data, auto)
{
    std::string str = "notify-send -t 1 " + std::string{"ERROR"} + " \"" + dynamic_cast<ErrorData *>(data)->errData.strMessage + "\"";
    // system(str.c_str());
};
