//
// Created by aziz on 11.08.21.
//

#include "SnmpAgent.h"
#include <iostream>
#include <chrono>
#include <thread>

SNMP::SnmpAgent::SnmpAgent()
{
    SNMPpp::netsnmpLogSyslog();
    SNMPpp::netsnmpLogStdErr();
}

SNMP::SnmpAgent::~SnmpAgent()
{
}

void SNMP::SnmpAgent::Init(void)
{
}

void SNMP::SnmpAgent::Run(void)
{

    try {
        SNMPpp::openSession(aSessionCallback);
        bool session_valid = aSessionCallback != nullptr ;
        while (session_valid) {
            SNMPpp::PDU pdu(Type );
            PduCallback(pdu);
            ActCallback(pdu, aSessionCallback);
            std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_SNMP));
            pdu.free();
        }
        SNMPpp::closeSession(aSessionCallback );
    } catch (std::exception & e) {
        std::cout << "\nerr in agent" << e.what() << std::endl;
    }



}


void SNMP::SnmpAgent::Inform(void)
{
}

void SNMP::SnmpAgent::SetName(const std::string &name)
{
    strName = name;
}

void SNMP::SnmpAgent::SetPduCb(const HandlrPdu &pduCb)
{
    PduCallback = pduCb;
}

void SNMP::SnmpAgent::SetServerAddress(const std::string &server)
{
    SnmpAgent::strServerAddress = server;
}

void SNMP::SnmpAgent::SetCommunity(const std::string &community)
{
    strCommunity = community;
}

void SNMP::SnmpAgent::SetActCallback(const HandlrAct &Cb)
{
    ActCallback = Cb;
}



void SNMP::SnmpAgent::SetType(SNMPpp::PDU::EType type)
{
    this->Type = type;
}

void SNMP::SnmpAgent::Off(void)
{
    SNMPpp::shutdownNetSnmpAgent();
}

template<class T>
void SNMP::SnmpAgent::Trap(const T o)
{
    SNMPpp::sendV2Trap( o );
}


