//
// Created by behrang on 12/18/21.
//

#ifndef EVENT_MANAGER_SETTING_H
#define EVENT_MANAGER_SETTING_H
#include <boost/date_time/gregorian/greg_date.hpp>
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"
#include <list>
using namespace boost::gregorian;


struct settingEntity:public JsonMessage {
    int i_settingId;
    int i_itemsRef;
    date dt_itemsDate;
    bool b_isDeleted;
    date dt_dateTime;

    void extract(nlohmann::json j) override;
    void print() override;
};

class setting
{
public:
    setting();
    virtual ~setting();
    void addSetting(settingEntity aSetting);
    settingEntity getSettingAt(int at);

private:
    std::list<settingEntity> lst_settingList{};

};


#endif //EVENT_MANAGER_SETTING_H
