//
// Created by behrang on 12/18/21.
//

#include "tags.h"

tags::tags()
{

}

tags::~tags()
{

}

void tagsEntity::extract(nlohmann::json j)
{
    tagId = j.at("tagId").get<int>();
    tagName = j.at("tagName").get<std::string>();
    tagType = j.at("tagType").get<int>();
    tagSize = j.at("tagSize").get<int>();
    settingRef = j.at("settingRef").get<int>();
    read = j.at("read").get<bool>();
    write = j.at("write").get<bool>();
    //tagValue = j.at("tagValue").get<int>();
}

void tagsEntity::print()
{
}

tagsEntity::tagsEntity(int tagId, const std::string &tagName, int tagType, size_t tagSize, int settingRef, bool read,
                       bool write, void *tagValue) : tagId(tagId), tagName(tagName), tagType(tagType), tagSize(tagSize),
    settingRef(settingRef), read(read), write(write),
    tagValue(tagValue) {}

json tagsEntity::toJson()
{
    json j;
    j["tagId"] = tagId;
    j["tagName"]= tagName;
    j["tagType"] = tagType;
    j["tagSize"] = tagSize;
    j["settingRef"] = settingRef;
    j["read"] = read;
    j["write"] = write;
    j["tagValue"] = nullptr;//tagValue;
    return j;
}
