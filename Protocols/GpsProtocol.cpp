//
// Created by aziz on 07.09.21.
//

#include "GpsProtocol.h"

void ProtocolS::GPS::GpsProtocol::Listen()
{
   parsergps.fetchNMEA();
}
ProtocolS::GPS::GpsProtocol::GpsProtocol(){}


ProtocolS::GPS::GpsProtocol::~GpsProtocol()
{
}

void ProtocolS::GPS::GpsProtocol::Create(Connection *Conn)
{
    // (void)Conn;//TODO
    auto cS7 = reinterpret_cast<ConnectionGPS *>(Conn);



    conn =cS7;

//    for (auto n : conn->NodeS) {
//        auto mq = reinterpret_cast<xmlGPS *>(n);
//        ProtocolS::GPSTag *mn{new ProtocolS::GPSTag(mq)};
//        std::cout << mn->Name.Value << std::endl;
//    }
//        GpsMessagesParser msg = GpsMessagesParser("/dev/ttyUSB0",9600);
//        msg.start=true;
    auto func = [this](json_t stringval, json_t lat, json_t lon, json_t d3, double d4 , double d5, double d6){
        for (auto i : Observer)
        {
            auto m = reinterpret_cast<GPSTag *>(i);
            if (m->Units.Value == "String"){
                m->setValue((void*)stringval.c_str(),strlen(stringval.c_str()));
            }else if (m->Units.Value == "Latitude"){
                m->setValue((void*)lat.c_str(),strlen(lat.c_str()));
            } else if (m->Units.Value == "Longitude"){
                m->setValue((void*)lon.c_str(),strlen(lon.c_str()));
            }
        }
    };
    parsergps.setGpsCb(func);
}

void ProtocolS::GPS::GpsProtocol::Open(Connection * Conn)
{
     std::cout<<"Conn->Address.Open"<<std::endl;

}

void ProtocolS::GPS::GpsProtocol::Close()
{
}

void ProtocolS::GPS::GpsProtocol::KeepAlive()
{
}

bool ProtocolS::GPS::GpsProtocol::isOK()
{
return true;
}

void ProtocolS::GPS::GpsProtocol::Reconnect()
{
}

void ProtocolS::GPS::GpsProtocol::hasError()
{
}

void ProtocolS::GPS::GpsProtocol::DataReceived()
{
}
// void mee (json_t d, json_t d1, json_t d2, json_t d3, double d4 , double d5, double d6 ){
//  std::cout << "GPS Protocol Recived Data" << std::endl;
// }

ProtocolS::GPS::GpsProtocol::GpsProtocol(ConnectionGPS *Conn)
{
    std::cout << "GPS Protocol called..########################" << std::endl;
    conn =Conn;



//             for (auto n : conn->NodeS) {
//                 auto mq = reinterpret_cast<xmlGPS *>(n);
//                 ProtocolS::GPSTag *mn{new ProtocolS::GPSTag(mq)};
//                 std::cout << mn->Name.Value << std::endl;
//             }
//               msg.fetchNMEA();


}

void ProtocolS::GPS::GpsProtocol::UpdateTag(ProtocolS::Tag *tag)
{
    Protocol::UpdateTag(tag);
}

void ProtocolS::GPS::GpsProtocol::Write(Data * data, Tag * tag)
{
}

void ProtocolS::GPS::GpsProtocol::Stop()
{
    std::cout << "stop gps" << std::endl;

    // msg.start=false;
}
