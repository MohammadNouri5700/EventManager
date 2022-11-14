//
// Created by aziz on 19.09.21.
//

#ifndef ERRORMANAGER_ERRORMANAGER_H
#define ERRORMANAGER_ERRORMANAGER_H
#include "Error.h"
#include <deque>
#include "../GateWay/SignalS.h"
#include <list>

namespace ERROR
{
class ErrorManager
{
private:
    std::deque<Error> ErrorS{};
public:
    void AddError( Error e);
    void Clean();
    void Remove();
    bool bState();

    ErrorManager();

    virtual ~ErrorManager();
};
}

#endif //ERRORMANAGER_ERRORMANAGER_H
