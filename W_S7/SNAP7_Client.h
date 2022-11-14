//
// Created by aziz on 23.08.21.
//

#ifndef EVENT_MANAGER_SNAP7_CLIENT_H
#define EVENT_MANAGER_SNAP7_CLIENT_H
#include "snap7.h"
#include <string>
namespace Snap7
{
class SNAP7_Client
{
private:
    S7Object Client;
public:
    SNAP7_Client();
    virtual ~SNAP7_Client();
    // Control functions
    int Connect();
    int ConnectTo(const std::string &RemAddress, int Rack, int Slot);
    int SetConnectionParams(const std::string &RemAddress, word LocalTSAP, word RemoteTSAP);
    int SetConnectionType(word ConnectionType);
    int Disconnect();
    int GetParam(int ParamNumber, void *pValue);
    int SetParam(int ParamNumber, void *pValue);
    // Data I/O Main functions
    int ReadArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
    int WriteArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
    int ReadMultiVars(PS7DataItem Item, int ItemsCount);
    int WriteMultiVars(PS7DataItem Item, int ItemsCount);
    // Data I/O Lean functions
    int DBRead(int DBNumber, int Start, int Size, void *pUsrData);
    int DBWrite(int DBNumber, int Start, int Size, void *pUsrData);
    int MBRead(int Start, int Size, void *pUsrData);
    int MBWrite(int Start, int Size, void *pUsrData);
    int EBRead(int Start, int Size, void *pUsrData);
    int EBWrite(int Start, int Size, void *pUsrData);
    int ABRead(int Start, int Size, void *pUsrData);
    int ABWrite(int Start, int Size, void *pUsrData);
    int TMRead(int Start, int Amount, void *pUsrData);
    int TMWrite(int Start, int Amount, void *pUsrData);
    int CTRead(int Start, int Amount, void *pUsrData);
    int CTWrite(int Start, int Amount, void *pUsrData);
    // Directory functions
    int ListBlocks(PS7BlocksList pUsrData);
    int GetAgBlockInfo(int BlockType, int BlockNum, PS7BlockInfo pUsrData);
    int GetPgBlockInfo(void *pBlock, PS7BlockInfo pUsrData, int Size);
    int ListBlocksOfType(int BlockType, TS7BlocksOfType *pUsrData, int *ItemsCount);
    // Blocks functions
    int Upload(int BlockType, int BlockNum, void *pUsrData, int *Size);
    int FullUpload(int BlockType, int BlockNum, void *pUsrData, int *Size);
    int Download(int BlockNum, void *pUsrData, int Size);
    int Delete(int BlockType, int BlockNum);
    int DBGet(int DBNumber, void *pUsrData, int *Size);
    int DBFill(int DBNumber, int FillChar);
    // Date/Time functions
    int GetPlcDateTime(tm *DateTime);
    int SetPlcDateTime(tm *DateTime);
    int SetPlcSystemDateTime();
    // System Info functions
    int GetOrderCode(PS7OrderCode pUsrData);
    int GetCpuInfo(PS7CpuInfo pUsrData);
    int GetCpInfo(PS7CpInfo pUsrData);
    int ReadSZL(int ID, int Index, PS7SZL pUsrData, int *Size);
    int ReadSZLList(PS7SZLList pUsrData, int *ItemsCount);
    // Control functions
    int PlcHotStart();
    int PlcColdStart();
    int PlcStop();
    int CopyRamToRom(int Timeout);
    int Compress(int Timeout);
    // Security functions
    int GetProtection(PS7Protection pUsrData);
    int SetSessionPassword(char *Password);
    int ClearSessionPassword();
    // Properties
    int ExecTime();
    int LastError();
    int PDURequested();
    int PDULength();
    int PlcStatus();
    bool Connected();
    // Async functions
    int SetAsCallback(pfn_CliCompletion pCompletion, void *usrPtr);
    bool CheckAsCompletion(int *opResult);
    int WaitAsCompletion(longword Timeout);
    int AsReadArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
    int AsWriteArea(int Area, int DBNumber, int Start, int Amount, int WordLen, void *pUsrData);
    int AsListBlocksOfType(int BlockType, PS7BlocksOfType pUsrData, int *ItemsCount);
    int AsReadSZL(int ID, int Index, PS7SZL pUsrData, int *Size);
    int AsReadSZLList(PS7SZLList pUsrData, int *ItemsCount);
    int AsUpload(int BlockType, int BlockNum, void *pUsrData, int *Size);
    int AsFullUpload(int BlockType, int BlockNum, void *pUsrData, int *Size);
    int AsDownload(int BlockNum, void *pUsrData,  int Size);
    int AsCopyRamToRom(int Timeout);
    int AsCompress(int Timeout);
    int AsDBRead(int DBNumber, int Start, int Size, void *pUsrData);
    int AsDBWrite(int DBNumber, int Start, int Size, void *pUsrData);
    int AsMBRead(int Start, int Size, void *pUsrData);
    int AsMBWrite(int Start, int Size, void *pUsrData);
    int AsEBRead(int Start, int Size, void *pUsrData);
    int AsEBWrite(int Start, int Size, void *pUsrData);
    int AsABRead(int Start, int Size, void *pUsrData);
    int AsABWrite(int Start, int Size, void *pUsrData);
    int AsTMRead(int Start, int Amount, void *pUsrData);
    int AsTMWrite(int Start, int Amount, void *pUsrData);
    int AsCTRead(int Start, int Amount, void *pUsrData);
    int AsCTWrite(int Start, int Amount, void *pUsrData);
    int AsDBGet(int DBNumber, void *pUsrData, int *Size);
    int AsDBFill(int DBNumber, int FillChar);
};
std::string CliErrorText(int Error);
}

#endif //EVENT_MANAGER_SNAP7_CLIENT_H
