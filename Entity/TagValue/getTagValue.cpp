//
// Created by behrang on 12/20/21.
//

#include "getTagValue.h"
#include <iostream>


gettagvalue::~gettagvalue()
{

}

void gettagvalue::toJson()
{

}


void gettagValueEntity::extract(nlohmann::json j)
{
    try {
        tagId = j.at("tagId").get<int>();
        tagsRef = j.at("tagsRef").get<int>();
        dateTime = j.at("dateTime").get<std::string>();
        tagsValue = j.at("tagsValue").get<std::string>();
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}

void gettagValueEntity::print()
{
}

json gettagValueEntity::toJson()
{

    json j;
    j["tagId"] = tagId;
    j["tagsRef"] = tagsRef;
    j["dateTime"]= dateTime;
    j["tagsValue"] = tagsValue;
    return j;

}

gettagValueEntity::gettagValueEntity(int tagId, int tagsRef, const std::string &dateTime,
                                     const std::string &tagsValue) : tagId(tagId), tagsRef(tagsRef), dateTime(dateTime),
    tagsValue(tagsValue) {}

