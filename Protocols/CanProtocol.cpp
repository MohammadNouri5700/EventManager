//
// Created by aziz on 03.08.21.
//

#include "CanProtocol.h"
#include "../GateWay/Connection/ConnectionCan.h"

ProtocolS::CAN::CANProtocol::CANProtocol()
{
}

ProtocolS::CAN::CANProtocol::CANProtocol(ConnectionCAN *Conn)
{
    std::cout << "CAN..########################" << std::endl;
    conn = Conn;
    CanClient = new ::CAN::CanController(Conn->Address.Value);
   // if()
    ReadCallback cb = [this](canid_t can_id, const std::vector<unsigned char> &msg)
    {
        auto f = [can_id, msg](CANTag *t) -> bool
        {
            ConnectionCAN *c = (ConnectionCAN *)t->conn;
            return (t->CANID.Value == can_id);
        };
        for (auto i : Observer)
        {
            auto m = reinterpret_cast<CANTag *>(i);
            bool b = f(m);
            if (b)
            {
                std::stringstream result;
                std::copy(msg.begin(), msg.end(), std::ostream_iterator<int>(result," "));
                std::cout << result.str() << std::endl;
                auto str = result.str();
                m->setValue((void*)str.c_str(),strlen(str.c_str()));
            }
        }
    };
    CanClient->set_read_callback(cb);
}

ProtocolS::CAN::CANProtocol::~CANProtocol()
{
}
void ProtocolS::CAN::CANProtocol::Listen()
{
    if(!conn->Disabled)
        CanClient->start();
}

void ProtocolS::CAN::CANProtocol::Create(Connection *Conn)
{
    (void)Conn; // TODO
}

void ProtocolS::CAN::CANProtocol::Open(Connection *Conn)
{
    ConnectionCAN *c = (ConnectionCAN *)Conn;
    ::CAN::CanController::setup(c->ID.Value, c->BitRate.Value);
}

void ProtocolS::CAN::CANProtocol::Close()
{
}

void ProtocolS::CAN::CANProtocol::KeepAlive()
{
}

bool ProtocolS::CAN::CANProtocol::isOK()
{
    return true;
}

void ProtocolS::CAN::CANProtocol::Reconnect()
{
}

void ProtocolS::CAN::CANProtocol::hasError()
{
}

void ProtocolS::CAN::CANProtocol::DataReceived()
{
}

void ProtocolS::CAN::CANProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

int ProtocolS::CAN::CANProtocol::Size(std::string str)
{
    if (!strcmp(str.c_str(), "float"))
        return 4;
    else if (!strcmp(str.c_str(), "int16"))
        return 2;
    else if (!strcmp(str.c_str(), "int"))
        return 4;
    else if (!strcmp(str.c_str(), "bool"))
        return 1;
    return 0;
}


void ProtocolS::CAN::CANProtocol::Write(Data *data, Tag *tag)
{
    if(conn->Disabled)
        return;
    Protocol::Write(data, tag);
    ProtocolS::CANTag *tag_ = (ProtocolS::CANTag *)tag;
    auto size = Size(tag->ValueType.Value);
    int16_t temp = atoi(data->GetString().c_str());
    std::cout << "++++++ write can ++++++" << std::endl;
    //------------------------------DUMMY DATA
    std::vector<unsigned char> data_;
    
    data_.push_back('1');
    data_.push_back('A');
    data_.push_back('B');
    data_.push_back('C');
    //------------------------------
    canid_t temp1 =  static_cast< canid_t>(tag_->CANID.Value);
    CanClient->send(temp1, data_ );
}

void ProtocolS::CAN::CANProtocol::Stop()
{
    CanClient->stop();
}
