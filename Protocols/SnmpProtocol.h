//
// Created by aziz on 14.08.21.
//

#ifndef EVENT_MANAGER_SNMPPROTOCOL_H
#define EVENT_MANAGER_SNMPPROTOCOL_H
#include "../W_snmp/SnmpAgent.h"
#include "Protocol.h"
#include "../GateWay/Connection/ConnectionSnmp.h"
namespace ProtocolS::SnMP
{
class SnmpProtocol: public Protocol, public SNMP::SnmpAgent
{
public:
    SnmpProtocol();
    virtual ~SnmpProtocol();
    void Listen() override;
    void Create(Connection *Conn) override;

};
}
#endif //EVENT_MANAGER_SNMPPROTOCOL_H
