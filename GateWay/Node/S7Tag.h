//
// Created by aziz on 11.10.21.
//

#ifndef EVENT_MANAGER_S7TAG_H
#define EVENT_MANAGER_S7TAG_H

#include "Tag.h"
#include "../Connection/ConnectionS7.h"
namespace ProtocolS
{
    
class S7Tag: public Tag
{

private:
    u16Tag StartingAddress;
    u16Tag BitNumber;
    u16Tag DBNumber;
    bTag SignalState;
    struct IoTag {
            std::string tagName;
            std::string tagId;
            std::string tagType;
            std::string ioType;
            int32_t startAddress;
            int32_t varSize;
            int32_t byteCount;
        } ioTag;
    struct {
            std::string tagName;
            std::string tagId;
            std::string functionCode;
            int32_t dBNumber;
            int32_t startAddress;
            int32_t varSize;
        } dataBlockTag;
    struct {
            std::string tagName;
            std::string tagId;
            std::string functionCode;
            int32_t startAddress;
            int32_t varSize;
        } memoryTag;
public:
    S7TagType s7tagType;
    void setSubject(Protocol *subject) override;
    void SendEvent() override;
    void Print() override;
    void UpdateValue() override;
    int GetType() override;
    S7Tag(xmlS7 *nS7);
    ~S7Tag() override;
    uint16_t getStartingAddress() const;
    uint16_t getBitNumber() const;
    bool getSignalState() const;

    uint16_t  getDBNumber() const;

    virtual bool compare(Tag *t)
    {
        auto tag = dynamic_cast<S7Tag*>(t);
        if (tag == NULL) {
            return false;
        }
        return this->conn->Address.Value == tag->conn->Address.Value;
    }
};
}



#endif //EVENT_MANAGER_S7TAG_H
