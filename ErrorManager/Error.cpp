//
// Created by aziz on 19.09.21.
//

#include "Error.h"

ERROR::Error::Error(int iCode, const std::string &strMessage, const std::string &strDescription, ErrorType errType,
                    uint8_t u8Severity) : iCode(iCode), strMessage(std::move(strMessage)), strDescription(std::move(strDescription)),
    errType(errType), u8Severity(u8Severity) {}

std::ostream &ERROR::operator<<(std::ostream &out, const ERROR::Error &e)
{
    std::map<ErrorType, std::string> strErrorType{{ErrorType::RUN_TIME, "RUN_TIME"}, {ErrorType::RESOURCE, "RESOURCE"}, {ErrorType::LOGICAL, "LOGICAL"}};
    out << "\n<Error> "
        << "\nCode : " << e.iCode
        << "\nMessage : " << e.strMessage
        << "\nDescription : " << e.strDescription
        << "\nType : " << strErrorType.at(e.errType)
        << "\nSeverity : " << e.u8Severity;
    return out;
}


