//
// Created by aziz on 19.09.21.
//

#include "ErrorManager.h"
#include "../GateWay/Event.h"
extern std::queue<Event> EventList;
void ERROR::ErrorManager::AddError(Error e)
{
    ErrorS.push_back(e);
    Event ev{new ErrorData{e}, TYPE::ERROR};
    EventList.push(std::move(ev));
}

void ERROR::ErrorManager::Clean()
{
    ErrorS.clear();
}

void ERROR::ErrorManager::Remove()
{
    ErrorS.pop_front();
}

bool ERROR::ErrorManager::bState()
{
    return ErrorS.empty();
}

ERROR::ErrorManager::ErrorManager() {}

ERROR::ErrorManager::~ErrorManager() {}

