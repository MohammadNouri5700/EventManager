//
// Created by behrang on 12/18/21.
//

#include "setting.h"

setting::setting()
{


}

setting::~setting()
{


}

void settingEntity::extract(nlohmann::json j)
{
    i_settingId = j.at("settingId").get<int>();
    i_itemsRef = j.at("itemsRef").get<int>();
    //dt_itemsDate = j.at("itemsDate").get<date>();
    b_isDeleted = j.at("isDeleted").get<bool>();
    //dt_dateTime = j.at("dateTime").get<date>();
}

void settingEntity::print()
{

}

void setting::addSetting(settingEntity aSetting)
{
    lst_settingList.push_back(aSetting);
}

//settingEntity setting::getSettingAt(int at) {
//
//    return settingentity();
//}
