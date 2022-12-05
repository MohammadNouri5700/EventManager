//
// Created by aziz on 07.09.21.
//

#ifndef EVENT_MANAGER_GPSPROTOCOL_H
#define EVENT_MANAGER_GPSPROTOCOL_H
#include "Protocol.h"
#include "../W_gps/GpsMessagesParser.h"
#include "../GateWay/Connection/ConnectionGPS.h"
#include "../GateWay/Node/GpsTag.h"
namespace ProtocolS::GPS
{

    
class GpsProtocol: public ProtocolS::Protocol
{
    
public:
    // GpsProtocol(const string &port, unsigned int baudRate);
    // GpsProtocol(ConnectionGPS *Conn);
    
        
        GpsMessagesParser parsergps ;
        ConnectionGPS *conn;
        GpsProtocol();
        GpsProtocol(ConnectionGPS *Conn);
        
        virtual ~GpsProtocol();
        void Listen() override;
        void Create(Connection *Conn) override;
        void Open(Connection *Conn) override;
        void Close() override;
        void KeepAlive() override;
        bool isOK() override;
        void Reconnect() override;
        void hasError() override;
        void DataReceived() override;
        void UpdateTag(Tag *tag) override;
        void Write(Data *data, Tag *tag) override;
        void Stop();
        
};
}


#endif //EVENT_MANAGER_GPSPROTOCOL_H
