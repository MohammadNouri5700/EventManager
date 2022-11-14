//
// Created by aziz on 29.09.21.
//

#include "Tag.h"
#include "../../Protocols/Protocol.h"



using Byte = uint8_t;
ProtocolS::Tag::~Tag()
{

}

void ProtocolS::Tag::setName(const std::string &strName)
{
    Tag::Name.Value = strName;
}

void ProtocolS::Tag::setSubject(Protocol *subject)
{
    Tag::subject = subject;
    this->subject->Attach(this);
    //Tag::static_number++;
    //this->number = Tag::static_number;
}

void ProtocolS::Tag::RemoveFromTheList()
{
    subject->Detach(this);
    //std::cout << "Observer \"" << number << "\" removed from the list.\n";
}

void ProtocolS::Tag::Print()
{
    std::cout << "Tag\n"
              << "name : " << Name.Value << "\n"
              << "unit : " << Units.Value << "\n"
              << "ReadWrite : " << ReadWrite.Value << "\n"
              << "Disable : " << Disable.Value << "\n"
              << "Notes : " << Notes.Value << "\n"
              << "ValueType : "<< ValueType.Value << "\n";
}

ProtocolS::Tag::Tag(const strTag &name, const strTag &units, const strTag &valueType, const strTag &notes,
                    const bTag &readWrite, const bTag &disable, const Second &time) : Name(name), Units(units), ValueType(valueType),
    Notes(notes), ReadWrite(readWrite),
    Disable(disable), Timer(time) {}

ProtocolS::Tag::Tag(xmlNode * node) :Name(node->Name), Units(node->Units), ValueType(node->ValueType),
    Notes(node->Notes), ReadWrite(node->ReadWrite), Disable(node->Disable), Timer(node->Timer)
{

}

void ProtocolS::Tag::setValue(void *value, size_t Size)
{
    Value = malloc(Size+1);
    SizeValue = Size;
    memset(Value, 0, Size+1);
    //if (memcmp((Byte*)Value, (Byte*)value, Size) != 0) {
    memmove(Value, value, Size);

    SendEvent();
    //}
    inputTime = boost::posix_time::microsec_clock::local_time();
}

void ProtocolS::Tag::setBitValue(bool value)
{
    Value = malloc(2);
    int16_t temp = value;
    memset(Value, 0, 2);
    memmove((Byte*)Value, (Byte*)&temp, 2);
    SendEvent();
    inputTime = boost::posix_time::microsec_clock::local_time();
}


void ProtocolS::Tag::UpdateValue()
{
    std::cout << "update :"<< strGetName() <<std::endl;
    subject->UpdateTag(this);
}

