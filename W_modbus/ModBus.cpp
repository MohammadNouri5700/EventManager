//
// Created by aziz on 23.08.21.
//

#include "ModBus.h"
#include <modbuspp.h>

using namespace ModBUS;
template class ModBUS::ModBus<Modbus::Master>;
template class ModBUS::ModBus<Modbus::Server>;

template<class NodeType>
ModBUS::ModBus<NodeType>::ModBus()
{

}
template<class NodeType>
ModBUS::ModBus<NodeType>::~ModBus()
{

}

template<class NodeType>
std::string ModBUS::ModBus<NodeType>::strSettings ()const
{
    return Node.settings();
}

template<class NodeType>
std::string ModBUS::ModBus<NodeType>::strNet () const
{
    return (Node.net() == Modbus::Rtu ? "Rtu" : "Tcp");
}

template<class NodeType>
std::string ModBUS::ModBus<NodeType>::strConnection() const
{
    return Node.connection();
}

template<class NodeType>bool ModBUS::ModBus<NodeType>::bSetBackend (const std::string &net, const std::string &connection, const std::string &setting)
{
    Modbus::Net n = (net == "Rtu" ? Modbus::Rtu : Modbus::Tcp);
    if(n==Modbus::Rtu)
    {
        //Node.rtu().setRts(MODBUS_RTU_RTS_DOWN);
        //Node.rtu().setSerialMode(Rs485);
    }

    return Node.setBackend(n, connection, setting);
    
}

template<class NodeType>
bool ModBUS::ModBus<NodeType>::bDebug() const
{
    return Node.debug();
}
template<class NodeType>
int ModBUS::ModBus<NodeType>::iFlush()
{
    return Node.flush();
}
template<class NodeType>
bool ModBUS::ModBus<NodeType>::bIsConnected () const
{
    return Node.isConnected();
}
template<class NodeType>
bool ModBUS::ModBus<NodeType>::bIsValid () const
{
    return Node.isValid();
}

template<class NodeType>
bool ModBUS::ModBus<NodeType>::bSetConfig (const std::string &jsonfile, const std::string &key)
{
    return Node.setConfig(jsonfile, key);
}
template<class NodeType>
bool ModBUS::ModBus<NodeType>::bSetDebug (bool debug)
{
    return Node.setDebug(debug);
}

template<>
void ModBUS::ModBus<Modbus::Master>::Close ()
{
    Node.close();
}
template<>
bool ModBUS::ModBus<Modbus::Master>::IsOpen () const
{
    return Node.isOpen();
}
template<>
bool ModBUS::ModBus<Modbus::Master>::open()
{
    return Node.open();
}

template<>
void ModBUS::ModBus<Modbus::Server>::Close ()
{
    Node.close();
}
template<>
bool ModBUS::ModBus<Modbus::Server>::IsOpen () const
{
    return Node.isOpen();
}
template<>
bool ModBUS::ModBus<Modbus::Server>::open()
{
    return Node.open();
}
