
#ifndef XML_OUTPUTNODE_H
#define XML_OUTPUTNODE_H
#include <pugixml.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <map>
#include <vector>
#include "../Connection/XmlTag.h"
#include "../Node/Tag.h"
#include <atomic>
#include <thread>

using strTag = XmlTag<std::string>;
using u16Tag = XmlTag<uint16_t>;
using Second = XmlTag<size_t>;

class TagCell
{
public:
    std::string Name{};
    std::string Alternative{};
    ProtocolS::Tag *tag;
    std::string att;
};

class OutputNode : public ProtocolS::Tag
{
    std::atomic_bool start;
    std::thread* thread;
public:
    strTag Name{};
    strTag OutputNodeID{};
    strTag ConnectionName{};
    strTag ParentShell{};
    Connection* Conn;
    Second Timer{};
    strTag Topic{};
    std::vector<TagCell> TagList{};
    void GeneralInfo(pugi::xml_node &OutnodeGeneral);
    void TagsListInfo(pugi::xml_node &OutnodeTags);
    void SpecialInfo(pugi::xml_node &OutnodeSpecial);
    void print();
    void SetData(pugi::xml_node &outputnode);
    OutputNode();
    void SendMQTTEvent();
    std::string CreateMQTTPayload();

    virtual ~OutputNode();

    void run(int interval_sec);
    void async_run(int interval_sec);
    void stop();
    void task();
    virtual void SendEvent(){}

    virtual bool compare(Tag *t)
    {
        auto tag = dynamic_cast<OutputNode*>(t);
        if (tag == NULL) {
            return false;
        }
        return this->conn->Address.Value == tag->conn->Address.Value;
    }
};
#endif // XML_CONNECTION_H
