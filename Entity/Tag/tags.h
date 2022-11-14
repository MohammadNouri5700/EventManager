//
// Created by behrang on 12/18/21.
//

#ifndef EVENT_MANAGER_TAGS_H
#define EVENT_MANAGER_TAGS_H
#include <iostream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include "../JsonMessage.h"

struct tagsEntity:public JsonMessage {
    int tagId{0};
    std::string tagName{""};
    int tagType{0};
    size_t tagSize{0};
    int settingRef{0};
    bool read{false};
    bool write{false};
    void  *tagValue{nullptr};

    tagsEntity(int tagId, const std::string &tagName, int tagType, size_t tagSize, int settingRef, bool read, bool write,
               void *tagValue);

    tagsEntity(const tagsEntity& te)
    {
        tagId = te.tagId;
        tagName = te.tagName;
        tagType = te.tagType;
        tagSize = te.tagSize;
        settingRef = te.settingRef;
        read = te.read;
        write = te.write;
        tagValue = te.tagValue;
    }
    tagsEntity& operator=(const tagsEntity&) = delete;

    void extract(nlohmann::json j) override;
    void print() override;

    json toJson() override;
};

class tags
{
public:
    tags();
    virtual ~tags();
private:

};


#endif //EVENT_MANAGER_TAGS_H
