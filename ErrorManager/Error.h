//
// Created by aziz on 19.09.21.
//

#ifndef ERRORMANAGER_ERROR_H
#define ERRORMANAGER_ERROR_H
#include <string>
#include <cstdint>
#include <iostream>
#include <map>

namespace ERROR
{
///Error Code Define
#define ERR_GPS -1
#define ERR_MQTT -2
#define ERR_MODBUS -3
#define ERR_S7 -4
#define ERR_SNMP -5
#define ERR_HARDWARE -6
#define ERR_SOFTWARE -7
#define ERR_CONNECTION -8

enum struct ErrorType {RUN_TIME, LOGICAL, RESOURCE};

class Error
{
    friend std::ostream & operator << (std::ostream &out, const Error &c);
public:
    Error(int iCode, const std::string &strMessage, const std::string &strDescription, ErrorType errType,
          uint8_t u8Severity);
    Error();
    //private:
    int iCode{0};
    std::string strMessage{""};
    std::string strDescription{""};
    ErrorType errType{ErrorType::RUN_TIME};
    uint u8Severity{10};
};

std::ostream & operator << (std::ostream &out, const Error &e);

}

#endif //ERRORMANAGER_ERROR_H
