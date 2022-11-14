//
// Created by behrang on 12/20/21.
//

#include "tagValue.h"

tagvalue::tagvalue()
{

}

tagvalue::~tagvalue()
{

}

void tagvalue::toJson()
{

}


void tagValueEntity::extract(nlohmann::json j)
{
    tagId = j.at("tagId").get<int>();
    tagsRef = j.at("tagsRef").get<std::string>();
    dateTime = j.at("dateTime").get<std::string>();
    tagsValue = j.at("tagsValue").get<std::string>();
}

void tagValueEntity::print()
{
}
