
#include "OutputNode.h"
#include "../Node/NodeList.h"
#include "../Event.h"
#include <iostream>
#include "atomic_queue/atomic_queue.h"

using Queue = atomic_queue::AtomicQueueB2<Event>; // Use heap-allocated buffer.
extern Queue EventList;
OutputNode::OutputNode() : ProtocolS::Tag()
{
}

OutputNode::~OutputNode()
{
    stop();
}

void OutputNode::run(int interval_sec)
{

    start = true;
    while (start) {
        if (Name.Value.length() > 2)
            task();
        sleep(interval_sec);
    }
}

void OutputNode::async_run(int interval_sec)
{
    start = true;
    thread = new std::thread(&OutputNode::run, this, interval_sec);
}

void OutputNode::stop()
{
    start = false;
    if (thread->joinable())
        thread->join();
}

void OutputNode::task()
{
    std::cout << "Sending Node :" << Name.Value << std::endl;
    if (Conn == NULL)
        return;
    switch (Conn->IProtocol) {
    case ProtocolIIOT::MQTT:
        SendMQTTEvent();
        break;

    case ProtocolIIOT::MODBUS:
        /* code */
        break;
    case ProtocolIIOT::S7:
        /* code */
        break;
    }
}

void OutputNode::GeneralInfo(pugi::xml_node &OutnodeGeneral)
{
    // if(Name.Value == "")
    //     return;
    Name.Value = OutnodeGeneral.child("Name").child_value();
    OutputNodeID.Value = OutnodeGeneral.child("OutputNodeID").child_value();
    ConnectionName.Value = OutnodeGeneral.child("ConnectionName").child_value();
    Conn = findConnection(ConnectionName.Value);
    ParentShell.Value = OutnodeGeneral.child("ParentShell").child_value();
    std::string temp = OutnodeGeneral.child("Timer").child_value();
    Timer.Value = temp.empty() ? 0 : std::stoull(temp);
}

void OutputNode::TagsListInfo(pugi::xml_node &OutnodeTags)
{
    for (pugi::xml_node t : OutnodeTags.children("Dist")) {
        TagCell tagcell;
        tagcell.att = t.child("TagName").attribute("att").as_string();
        tagcell.Name = t.child("TagName").child_value();
        tagcell.Alternative = t.child("Alternative").child_value();
        tagcell.tag = findTag(tagcell.Name);
        if (!tagcell.tag->OnlyNode)
            tagcell.tag->OnlyNode = (tagcell.att == "public" ? false : true );
        TagList.push_back(tagcell);
    }
}

void OutputNode::SpecialInfo(pugi::xml_node &OutnodeSpecial)
{
    switch (Conn->IProtocol) {
    case ProtocolIIOT::MQTT:
        Topic.Value = OutnodeSpecial.child("Topic").child_value();
        break;

    default:
        break;
    }
}

void OutputNode::print()
{
    std::cout << "Name: " << Name.Value << std::endl;
    std::cout << "OutputNodeID: " << OutputNodeID.Value << std::endl;
    std::cout << "ConnectionName: " << ConnectionName.Value << "--" << Conn->Name.Value << std::endl;
    std::cout << "ParentShell: " << ParentShell.Value << std::endl;
    std::cout << "Topic: " << Topic.Value << std::endl;
    for (TagCell &i : TagList) {
        std::cout << "Name: " << i.Name << std::endl;
        std::cout << "Tag: " << i.tag->Name.Value << std::endl;
        std::cout << "att: " << i.att << std::endl;
        std::cout << "OnlyNode: " << (i.tag->OnlyNode ? "true" : "false") << std::endl;
    }
}

void OutputNode::SetData(pugi::xml_node &outputnode)
{
    auto General = outputnode.child("General");
    auto TagList = outputnode.child("TagList");
    auto Special = outputnode.child("Special");

    GeneralInfo(General);
    TagsListInfo(TagList);
    SpecialInfo(Special);
}

void OutputNode::SendMQTTEvent()
{
    std::string v;
    Event b;
    void *Value{nullptr};

    Event e{new ProtocolData{v, nullptr, Name.Value}, TYPE::PRINT};
    EventList.push(std::move(e));
    v = CreateMQTTPayload();
    b = Event(new ProtocolData{v, Value, Name.Value}, TYPE::MQTTNODE, this);
    EventList.push(std::move(b));
}

std::string OutputNode::CreateMQTTPayload()
{
    std::string Reported, vTemp;
    bool firstline=true;


    for (auto t : TagList) {

        if (t.tag->Value==0) continue;
        if (!firstline)
            Reported+= "," ;

//        if (t.tag->Name.Value=="PT102"){
//            std::string *str = new std::string((char *)0);
//            vTemp = *str;
//        }

        if (t.tag->Value !=NULL && t.tag->Value != "") {
            std::string *str = new std::string((char *)t.tag->Value);
            vTemp = *str;
        } else{
            continue;
        }


        firstline  = false;
        Reported += "\"" + t.Alternative + "\":\"" + vTemp +"\"\n";


    }

    std::string ReturnValue = "{\n\"deviceTwinDocument\":{ \n \"attributes\":{ \n \"reported\":{ \n" + Reported + "} \n} \n} \n}";
    return ReturnValue;
}
