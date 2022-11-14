//
// Created by aziz on 23.08.21.
//

#ifndef EVENT_MANAGER_MODBUS_H
#define EVENT_MANAGER_MODBUS_H
#include <modbuspp.h>
#include <string>
#include "../ErrorManager/ErrorManager.h"
extern ERROR::ErrorManager errorManager;

namespace ModBUS
{

struct stNet {
    std::string strNet{"null"};
    std::string strConnection{"null"};
    std::string strSettings{"null"};
};

template<class Node_Type>
class ModBus
{
protected:
    virtual void Init() {};
    Node_Type Node{};
public:

    ModBus();
    virtual	~ModBus();
    stNet Backend ()
    {
        return stNet{};
    };
    bool bSetBackend (const std::string &net, const std::string &connection, const std::string &setting);
    std::string strConnection () const;
    bool bDebug() const;
    int iFlush();
    bool bIsConnected () const;

    bool bIsValid () const;
    std::string strNet () const;
    bool bSetConfig (const std::string &jsonfile, const std::string &key= std::string());
    bool bSetDebug (bool debug=true);

    std::string strSettings () const;

    virtual void Close ();
    virtual bool IsOpen () const;
    virtual bool open();
    virtual void Run() {};
};

}

#endif //EVENT_MANAGER_MODBUS_H
