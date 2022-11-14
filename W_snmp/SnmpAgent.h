//
// Created by aziz on 11.08.21.
//

#ifndef SNMP3_SNMP_AGENT_H
#define SNMP3_SNMP_AGENT_H
#include <SNMPpp/SNMPpp.hpp>
#include <stdexcept>
#include <cassert>
#include <string>
#include <functional>
#define SLEEP_SNMP 5000

namespace SNMP
{

using HandlrPdu =   std::function<void(SNMPpp::PDU&)>;
using HandlrAct =   std::function<void (SNMPpp::PDU&, SNMPpp::SessionHandle&)>;

class SnmpAgent
{
private:
    std::string strName{"snmppp"};
    std::string strServerAddress{"udp:127.0.0.1:161"};
    std::string strCommunity {"public"};
    SNMPpp::PDU::EType Type{};
    HandlrPdu PduCallback{};
    HandlrAct ActCallback{};
    SNMPpp::SessionHandle aSessionCallback {nullptr};
public:
    void SetType(SNMPpp::PDU::EType type);
    void SetActCallback(const HandlrAct &Cb);
    void SetServerAddress(const std::string &server);
    void SetCommunity(const std::string &community);
    void SetName(const std::string &name);
    void SetPduCb(const HandlrPdu &pduCb);
    template<class T>
    void Trap(const T o);
    void Off(void);
    void Inform(void);
    SnmpAgent();
    virtual ~SnmpAgent();
    SnmpAgent(const SnmpAgent&) = delete;
    SnmpAgent operator=(const SnmpAgent&) = delete;
    void Init(void);
    void Run(void);
    void GetResponse();
    void SetResponse();
    void SetSessionHandle(const std::string & Str_ss);
};
}


#endif //SNMP3_SNMP_AGENT_H
