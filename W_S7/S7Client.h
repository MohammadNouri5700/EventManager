//
// Created by aziz on 23.08.21.
//

#ifndef EVENT_MANAGER_S7CLIENT_H
#define EVENT_MANAGER_S7CLIENT_H
#include "SNAP7_Client.h"
#include <functional>
#include <atomic>
#define SLEEP_S7 1000

namespace Snap7
{
using ErrHandler = std::function<void(std::string)>;
using HandlrS7 = std::function<bool()>;
class S7Client: public SNAP7_Client
{
    std::string strAddress{};
    int iRack {0};
    int iSlot {2};
    int iResultCon{0};
    std::atomic_bool bStopThread{false};
    HandlrS7 S7Callback{};
    ErrHandler ErrCallBack{};
public:
    void setErrCallBack(const ErrHandler &errCallBack);
    void SetS7Cb(const HandlrS7 &Cb);
    void Init();
    void Run();
    void Act();
    void Stop();

    void SetAddress(const std::string &address = "192.168.0.59");
    bool Check(int Result, std::string function);
    void OrderCode();
    void UnitStatus();
    void CpInfo();
    void CpuInfo();

    void SetRack(int rack=0);
    void SetSlot(int slot=2);
    virtual ~S7Client();


};
}

#endif //EVENT_MANAGER_S7CLIENT_H
