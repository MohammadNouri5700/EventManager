//
// Created by aziz on 23.08.21.
//

#include "SNAP7_Client.h"

Snap7::SNAP7_Client::SNAP7_Client() :
    Client(Cli_Create())
{
}
//---------------------------------------------------------------------------
Snap7::SNAP7_Client::~SNAP7_Client()
{
    Cli_Destroy(&Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::Connect()
{
    return Cli_Connect(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ConnectTo(const std::string &RemAddress, int Rack, int Slot)
{
    return Cli_ConnectTo(Client, RemAddress.c_str(), Rack, Slot);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetConnectionParams(const std::string &RemAddress, word LocalTSAP, word RemoteTSAP)
{
    return Cli_SetConnectionParams(Client, RemAddress.c_str(), LocalTSAP, RemoteTSAP);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetConnectionType(word ConnectionType)
{
    return Cli_SetConnectionType(Client, ConnectionType);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::Disconnect()
{
    return Cli_Disconnect(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetParam(int ParamNumber, void *pValue)
{
    return Cli_GetParam(Client, ParamNumber, pValue);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetParam(int ParamNumber, void *pValue)
{
    return Cli_SetParam(Client, ParamNumber, pValue);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ReadArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData)
{
    return Cli_ReadArea(Client, Area, DBNumber, Start, Amount, WordLen, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::WriteArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData)
{
    return Cli_WriteArea(Client, Area, DBNumber, Start, Amount, WordLen, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ReadMultiVars(PS7DataItem Item, int ItemsCount)
{
    return Cli_ReadMultiVars(Client, Item, ItemsCount);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::WriteMultiVars(PS7DataItem Item, int ItemsCount)
{
    return Cli_WriteMultiVars(Client, Item, ItemsCount);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::DBRead(int DBNumber, int Start, int Size, void *pUsrData)
{
    return Cli_DBRead(Client, DBNumber, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::DBWrite(int DBNumber, int Start, int Size, void *pUsrData)
{
    return Cli_DBWrite(Client, DBNumber, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::MBRead(int Start, int Size, void *pUsrData)
{
    return Cli_MBRead(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::MBWrite(int Start, int Size, void *pUsrData)
{
    return Cli_MBWrite(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::EBRead(int Start, int Size, void *pUsrData)
{
    return Cli_EBRead(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::EBWrite(int Start, int Size, void *pUsrData)
{
    return Cli_EBWrite(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ABRead(int Start, int Size, void *pUsrData)
{
    return Cli_ABRead(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ABWrite(int Start, int Size, void *pUsrData)
{
    return Cli_ABWrite(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::TMRead(int Start, int Amount, void *pUsrData)
{
    return Cli_TMRead(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::TMWrite(int Start, int Amount, void *pUsrData)
{
    return Cli_TMWrite(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::CTRead(int Start, int Amount, void *pUsrData)
{
    return Cli_CTRead(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::CTWrite(int Start, int Amount, void *pUsrData)
{
    return Cli_CTWrite(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ListBlocks(PS7BlocksList pUsrData)
{
    return Cli_ListBlocks(Client, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetAgBlockInfo(int BlockType, int BlockNum, PS7BlockInfo pUsrData)
{
    return Cli_GetAgBlockInfo(Client, BlockType, BlockNum, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetPgBlockInfo(void *pBlock, PS7BlockInfo pUsrData, int Size)
{
    return Cli_GetPgBlockInfo(Client, pBlock, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ListBlocksOfType(int BlockType, TS7BlocksOfType *pUsrData, int *ItemsCount)
{
    return Cli_ListBlocksOfType(Client, BlockType, pUsrData, ItemsCount);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::Upload(int BlockType, int BlockNum, void *pUsrData, int *Size)
{
    return Cli_Upload(Client, BlockType, BlockNum, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::FullUpload(int BlockType, int BlockNum, void *pUsrData, int *Size)
{
    return Cli_FullUpload(Client, BlockType, BlockNum, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::Download(int BlockNum, void *pUsrData, int Size)
{
    return Cli_Download(Client, BlockNum, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::Delete(int BlockType, int BlockNum)
{
    return Cli_Delete(Client, BlockType, BlockNum);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::DBGet(int DBNumber, void *pUsrData, int *Size)
{
    return Cli_DBGet(Client, DBNumber, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::DBFill(int DBNumber, int FillChar)
{
    return Cli_DBFill(Client, DBNumber, FillChar);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetPlcDateTime(tm *DateTime)
{
    return Cli_GetPlcDateTime(Client, DateTime);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetPlcDateTime(tm *DateTime)
{
    return Cli_SetPlcDateTime(Client, DateTime);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetPlcSystemDateTime()
{
    return Cli_SetPlcSystemDateTime(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetOrderCode(PS7OrderCode pUsrData)
{
    return Cli_GetOrderCode(Client, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetCpuInfo(PS7CpuInfo pUsrData)
{
    return Cli_GetCpuInfo(Client, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetCpInfo(PS7CpInfo pUsrData)
{
    return Cli_GetCpInfo(Client, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ReadSZL(int ID, int Index, PS7SZL pUsrData, int *Size)
{
    return Cli_ReadSZL(Client, ID, Index, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ReadSZLList(PS7SZLList pUsrData, int *ItemsCount)
{
    return Cli_ReadSZLList(Client, pUsrData, ItemsCount);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::PlcHotStart()
{
    return Cli_PlcHotStart(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::PlcColdStart()
{
    return Cli_PlcColdStart(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::PlcStop()
{
    return Cli_PlcStop(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::CopyRamToRom(int Timeout)
{
    return Cli_CopyRamToRom(Client, Timeout);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::Compress(int Timeout)
{
    return Cli_Compress(Client, Timeout);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::GetProtection(PS7Protection pUsrData)
{
    return Cli_GetProtection(Client, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetSessionPassword(char *Password)
{
    return Cli_SetSessionPassword(Client, Password);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ClearSessionPassword()
{
    return Cli_ClearSessionPassword(Client);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::ExecTime()
{
    int Time;
    int Result = Cli_GetExecTime(Client, &Time);
    if (Result==0)
        return Time;
    else
        return Result;
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::LastError()
{
    int LastError;
    int Result =Cli_GetLastError(Client, &LastError);
    if (Result==0)
        return LastError;
    else
        return Result;
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::PDULength()
{
    int Requested, Negotiated;
    if (Cli_GetPduLength(Client, &Requested, &Negotiated)==0)
        return Negotiated;
    else
        return 0;
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::PDURequested()
{
    int Requested, Negotiated;
    if (Cli_GetPduLength(Client, &Requested, &Negotiated)==0)
        return Requested;
    else
        return 0;
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::PlcStatus()
{
    int Status;
    int Result = Cli_GetPlcStatus(Client, &Status);
    if (Result==0)
        return Status;
    else
        return Result;
}
//---------------------------------------------------------------------------
bool Snap7::SNAP7_Client::Connected()
{
    int ClientStatus;
    if (Cli_GetConnected(Client, &ClientStatus)==0)
        return ClientStatus!=0;
    else
        return false;
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::SetAsCallback(pfn_CliCompletion pCompletion, void *usrPtr)
{
    return Cli_SetAsCallback(Client, pCompletion, usrPtr);
}
//---------------------------------------------------------------------------
bool Snap7::SNAP7_Client::CheckAsCompletion(int *opResult)
{
    return Cli_CheckAsCompletion(Client, opResult)==JobComplete;
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::WaitAsCompletion(longword Timeout)
{
    return Cli_WaitAsCompletion(Client, Timeout);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsReadArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData)
{
    return Cli_AsReadArea(Client, Area, DBNumber, Start, Amount, WordLen, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsWriteArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData)
{
    return Cli_AsWriteArea(Client, Area, DBNumber, Start, Amount, WordLen, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsListBlocksOfType(int BlockType,  PS7BlocksOfType pUsrData, int *ItemsCount)
{
    return Cli_AsListBlocksOfType(Client, BlockType,  pUsrData, ItemsCount);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsReadSZL(int ID, int Index,  PS7SZL pUsrData, int *Size)
{
    return Cli_AsReadSZL(Client, ID, Index, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsReadSZLList(PS7SZLList pUsrData, int *ItemsCount)
{
    return Cli_AsReadSZLList(Client, pUsrData, ItemsCount);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsUpload(int BlockType, int BlockNum, void *pUsrData, int *Size)
{
    return Cli_AsUpload(Client, BlockType, BlockNum, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsFullUpload(int BlockType, int BlockNum, void *pUsrData, int *Size)
{
    return Cli_AsFullUpload(Client, BlockType, BlockNum, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsDownload(int BlockNum, void *pUsrData, int Size)
{
    return Cli_AsDownload(Client, BlockNum, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsCopyRamToRom(int Timeout)
{
    return Cli_AsCopyRamToRom(Client, Timeout);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsCompress(int Timeout)
{
    return Cli_AsCompress(Client, Timeout);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsDBRead(int DBNumber, int Start, int Size, void *pUsrData)
{
    return Cli_AsDBRead(Client, DBNumber, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsDBWrite(int DBNumber, int Start, int Size, void *pUsrData)
{
    return Cli_AsDBWrite(Client, DBNumber, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsMBRead(int Start, int Size, void *pUsrData)
{
    return Cli_AsMBRead(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsMBWrite(int Start, int Size, void *pUsrData)
{
    return Cli_AsMBWrite(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsEBRead(int Start, int Size, void *pUsrData)
{
    return Cli_AsEBRead(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsEBWrite(int Start, int Size, void *pUsrData)
{
    return Cli_AsEBWrite(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsABRead(int Start, int Size, void *pUsrData)
{
    return Cli_AsABRead(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsABWrite(int Start, int Size, void *pUsrData)
{
    return Cli_AsABWrite(Client, Start, Size, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsTMRead(int Start, int Amount, void *pUsrData)
{
    return Cli_AsTMRead(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsTMWrite(int Start, int Amount, void *pUsrData)
{
    return Cli_AsTMWrite(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsCTRead(int Start, int Amount, void *pUsrData)
{
    return Cli_AsCTRead(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsCTWrite(int Start, int Amount, void *pUsrData)
{
    return Cli_AsCTWrite(Client, Start, Amount, pUsrData);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsDBGet(int DBNumber, void *pUsrData, int *Size)
{
    return Cli_AsDBGet(Client, DBNumber, pUsrData, Size);
}
//---------------------------------------------------------------------------
int Snap7::SNAP7_Client::AsDBFill(int DBNumber, int FillChar)
{
    return Cli_AsDBFill(Client, DBNumber, FillChar);
}

std::string Snap7::CliErrorText(int Error)
{
    char text[1024];
    Cli_ErrorText(Error, text, 1024);
    return std::string(text);
}

