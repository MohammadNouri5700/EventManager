//
// Created by aziz on 23.08.21.
//

#include "S7Client.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <zconf.h>

void Snap7::S7Client::Run()
{
    while (iResultCon == 0 && !bStopThread)
    {
//        std::cerr << "void Snap7::S7Client::Run() Run" << std::endl;
        if (Connected())
        {
            Act();
            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_S7));
        }
        else
        {

            if (ConnectTo(strAddress.c_str(), iRack, iSlot))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_S7));
            }
        }
    }
//    std::cerr << "void Snap7::S7Client::Run() stopped" << std::endl;
    Disconnect();
}
bool GetBit(byte byt, int index)
{
    if (index < 0 || index > 7)
        throw std::exception();
    byte bitMask = (byte)(1 << index);
    byte masked = (byte)(byt & bitMask);
    return masked != 0;
}


void Snap7::S7Client::Init()
{
    iResultCon = ConnectTo(strAddress.c_str(), iRack, iSlot);
    std::cout << "\nConnected to   : " << strAddress.c_str() << " (iRack=" << iRack << ",iSlot=" << iSlot << ")\n"
              << "Pdu Requested  : " << PDURequested() << " bytes\n"
              << "Pdu Negotiated : " << PDULength() << " bytes" << std::endl;
    if (Connected())
    {
        std::cout << "\nConnected to   : " << strAddress << " (iRack=" << iRack << ",iSlot=" << iSlot << ")\n"
                  << "Pdu Requested  : " << PDURequested() << " bytes\n"
                  << "Pdu Negotiated : " << PDULength() << " bytes" << std::endl;
        // OrderCode();
        // CpuInfo();
        // CpInfo();
        // UnitStatus();

//        int rec = ReadArea(S7AreaMK, 0, 801, 1,S7WLBit, Buffer);
//        PS7BlockInfo pUsrData;

//        byte MBRead[1];



//        byte MB4['\001']; // 16 Merker bytes
//        uint8_t b0=1;
//        byte MB3[b0]; // 16 Merker bytes




//        GetAgBlockInfo(Block_FC,801,pUsrData);
//        WriteArea(S7AreaMK,0,801,1,1,pUsrData);
//        byte Buffer[pUsrData->MC7Size];
//        ReadArea(S7AreaPE,0,801,1,S7WLByte,&MB1);
//        ReadArea(S7AreaPA,0,801,1,S7WLByte,&MB2);
//        ReadArea(S7AreaMK,0,801,1,S7WLByte,&MB3);
//        WriteArea(S7AreaMK,0,801,1,S7WLByte,&MB2);

//        ReadArea(S7AreaMK,0,801,1,S7WLByte, &MBRead);
//        std::string startFD = std::to_string(GetBit(MBRead[0],0));
//        std::string stopFD = std::to_string(GetBit(MBRead[0],1));

//bool bool_val = true;
//        WriteArea(S7AreaMK,0,801,1,S7WLBit, &bool_val);


//        ReadArea(S7AreaDB,0,801,1,S7WLByte,&MB4);
//        ReadArea(S7AreaCT,0,801,1,S7WLByte,&MB5);
//        ReadArea(S7AreaTM,0,801,1,S7WLByte,&MB6);


//        int w = 4;


    }
    else
    {
        std::cerr << ""
                     "error Connect s7" << std::endl;
        ErrCallBack("error Connect s7");
    }
}

void Snap7::S7Client::Act()
{
    S7Callback();
}

void Snap7::S7Client::Stop()
{
    std::cerr << "void Snap7::S7Client::Stop()" << std::endl;
    bStopThread = true;
}

void Snap7::S7Client::SetAddress(const std::string &address)
{
    strAddress = address;
}

void Snap7::S7Client::SetRack(int rack)
{
    iRack = rack;
}

void Snap7::S7Client::SetSlot(int slot)
{
    iSlot = slot;
}

Snap7::S7Client::~S7Client()
{
    Disconnect();
}

bool Snap7::S7Client::Check(int Result, std::string function)
{

    std::cout << "\n+-----------------------------------------------------"
              << "\n|  " << function << " "
              << "\n+-----------------------------------------------------";
    if (Result == 0)
    {
        std::cout << "\n| aResultCon         : OK"
                  << "\n| Execution time : " << ExecTime() << " ms"
                  << "\n+-----------------------------------------------------\n";
    }
    else
    {
        std::cout << "| ERROR !!! \n";
        if (Result < 0)
            std::cout << "| Library Error (-1)\n";
        else
            std::cout << "| " << CliErrorText(Result);
        std::cout << "\n+-----------------------------------------------------\n";
    }
    return Result == 0;
}

void Snap7::S7Client::OrderCode()
{
    TS7OrderCode Info;
    if (Check(GetOrderCode(&Info), "Catalog"))
    {
        std::cout << "  Order Code : " << Info.Code << std::endl;
        std::cout << "  Version    : " << int{Info.V1} << "." << int{Info.V2} << "." << uint{Info.V3} << std::endl;
    };
}

void Snap7::S7Client::UnitStatus()
{

    int Status = PlcStatus();
    if (Check(iResultCon, "CPU Status"))
    {
        switch (Status)
        {
        case S7CpuStatusRun:
            std::cout << "  RUN\n";
            break;
        case S7CpuStatusStop:
            std::cout << "  STOP\n";
            break;
        default:
            std::cout << "  UNKNOWN\n";
            break;
        }
    };
}

void Snap7::S7Client::CpInfo()
{
    TS7CpInfo Info;
    if (Check(GetCpInfo(&Info), "Communication processor Info"))
    {

        std::cout << "  Max Pdu Length   : " << Info.MaxPduLengt << " bytes\n"
                  << "  Max Connections  : " << Info.MaxConnections << " \n"
                  << "  Max MPI Rate     : " << Info.MaxMpiRate << " bps\n"
                  << "  Max Bus Rate     : " << Info.MaxBusRate << " bps\n";
    };
}

void Snap7::S7Client::CpuInfo()
{
    TS7CpuInfo Info;
    if (Check(GetCpuInfo(&Info), "Unit Info"))
    {
        std::cout << "\n  Module Type Name : " << Info.ModuleTypeName
                  << "\n  Serial Number    : " << Info.SerialNumber
                  << "\n  AS Name          : " << Info.ASName
                  << "\n  Module Name      : " << Info.ModuleName << std::endl;
    };
}

void Snap7::S7Client::SetS7Cb(const HandlrS7 &Cb)
{
    S7Callback = Cb;
}

void Snap7::S7Client::setErrCallBack(const ErrHandler &errCallBack)
{
    ErrCallBack = errCallBack;
}
