//
// Created by aziz on 24.08.21.
//

#include "S7Protocol.h"
#include "../GateWay/Node/S7Tag.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex mtxs7;
extern std::vector<Connection *> ConnectionS;

void ProtocolS::S7::S7Protocol::ReverseBytes(void *start, int size) {
    char *istart = (char *) start, *iend = istart + size;
    std::reverse(istart, iend);
}

int ProtocolS::S7::S7Protocol::Size(std::string str) {
    if (!strcmp(str.c_str(), "float"))
        return 4;
    else if (!strcmp(str.c_str(), "int16"))
        return 2;
    else if (!strcmp(str.c_str(), "int"))
        return 4;
    else if (!strcmp(str.c_str(), "bool"))
        return 1;
    return 0;
}

ProtocolS::S7::S7Protocol::S7Protocol() {
}

ProtocolS::S7::S7Protocol::~S7Protocol() {
    std::cerr << "ProtocolS::S7::S7Protocol::~S7Protocol()" << std::endl;
}

void ProtocolS::S7::S7Protocol::Listen() {
    Run();
}

byte get_bits(byte n, int bitswanted) {
    byte mask = 1;
    mask <<= bitswanted;
    return n & mask ? 1 : 0;
}


void ProtocolS::S7::S7Protocol::Create(Connection *Conn) {
    auto cS7 = reinterpret_cast<ConnectionS7 *>(Conn);
    SetAddress(cS7->Address.Value);
    SetRack();
    SetSlot();
    Init();
    auto cb = [this]() -> bool {
        mtxs7.lock();
        int plcStatusCode = PlcStatus();
        if (plcStatusCode != 8) {
            std::cerr << "\n\n\n\n PLC has error try to establish \n\n\n\n\n" << std::endl;
            SetRack();
            SetSlot();
            Init();
        }



        // std::ofstream outFile;
        // outFile.open("log_s7.txt", std::ios_base::app);
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        for (auto it = Observer.begin(); it != Observer.end(); it++) {
            auto tag = reinterpret_cast<S7Tag *>(*it);

            auto size = Size(tag->ValueType.Value);
            byte db[size];
            byte a = 0;


            int ii = -99;
            float ff = -99.9;
            bool ss = false;

            if (PlcStatus() != 8) {
                if (strcmp(tag->ValueType.Value.c_str(), "bool") == 0) {
                    (*it)->setValue(&ss, size * sizeof(db));
                } else if (strcmp(tag->ValueType.Value.c_str(), "float") == 0) {
                    (*it)->setValue(&ff, size * sizeof(db));
                } else if (strcmp(tag->ValueType.Value.c_str(), "int") == 0) {
                    (*it)->setValue(&ii, size * sizeof(db));
                } else if (strcmp(tag->ValueType.Value.c_str(), "int16") == 0) {
                    (*it)->setValue(&ii, size * sizeof(db));
                } else {
                    (*it)->setValue((bool *) false, size * sizeof(db));
                }
            } else {
                switch (tag->s7tagType) {
                    case S7TagType::DATABLOCKTAG:


                        // std::cerr << "tag->getDBNumber() " << tag->getDBNumber() << " tag->getBitNumber() " << tag->getBitNumber() << " tag->getStartingAddress() "
                        //           << tag->getStartingAddress() << " tag->ValueType.Value " << tag->ValueType.Value << " Size : " << size << std::endl;
                        // outFile << "tag->getDBNumber() " << tag->getDBNumber() << " tag->getBitNumber() " << tag->getBitNumber() << " tag->getStartingAddress() "
                        //           << tag->getStartingAddress() << " tag->ValueType.Value " << tag->ValueType.Value << " Size : " << size << "Time : " << std::ctime(&now);
                        if (!strcmp(tag->ValueType.Value.c_str(), "bool")) {
                            DBRead(tag->getDBNumber(), tag->getStartingAddress(), 1, db);
                            a = db[0];
                            byte bits = get_bits(a, tag->getBitNumber());
                            (*it)->setBitValue(bits);
//                     std::cerr << "&&&&&&& "<< (int)bits << std::endl;
                            //  outFile << (int)bits << std::endl;
                        } else {
                            DBRead(tag->getDBNumber(), tag->getStartingAddress(), size, db);
                            ReverseBytes(db, size);
                            (*it)->setValue(db, size * sizeof(byte));
                            if (!strcmp(tag->ValueType.Value.c_str(), "float")) {
                                float value = 0;
                                memcpy(&value, db, 4);
                                //outFile << value << std::endl;
                            }

                        }

                        break;

                    case S7TagType::IOTAGOUT:
                        if (!strcmp(tag->ValueType.Value.c_str(), "bool")) {
                            ABRead(tag->getDBNumber(), 1, db);
                            // memcpy(&a, db, sizeof(1));
                            a = db[0];
                            byte bits = get_bits(a, tag->getStartingAddress());
                            (*it)->setValue(&bits, 1);
                        } else {
                            ABRead(tag->getDBNumber(), size, db);
                            ReverseBytes(db, size);
                            (*it)->setValue(db, size * sizeof(byte));
                        }
                        break;
                    case S7TagType::IOTAGIN:
                        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<IOTAGIN>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
                        if (!strcmp(tag->ValueType.Value.c_str(), "bool")) {
                            EBRead(tag->getDBNumber(), 2, db);
                            memcpy(&a, db, sizeof(2));
                            int bits = get_bits(a, tag->getStartingAddress());
                            printf("%d\n", a);
                            (*it)->setValue(&bits, 2);
                        } else {
                            EBRead(tag->getDBNumber(), size, db);
                            ReverseBytes(db, size);
                            (*it)->setValue(db, size * sizeof(byte));
                        }
                        break;
                    case S7TagType::MEMORYTAG: {

                        if (strcmp(tag->ValueType.Value.c_str(), "bool")==0) {
                            MBRead(tag->getDBNumber(), size, db);
                            memcpy(&a, db, size);
                            int bits = get_bits(a, tag->getStartingAddress());
                            ReverseBytes(db, size);
                            (*it)->setValue(&bits, 2);
                        } else {
                            MBRead(tag->getDBNumber(), size, db);
                            ReverseBytes(db, size);
                            (*it)->setValue(db, size * sizeof(byte));
                        }


//                        MBRead(tag->getDBNumber(), size, dbs);

                        break;
                    }


                    default:
                        DBRead(tag->getDBNumber(), tag->getStartingAddress(), size, db);
                        ReverseBytes(db, size);
                        (*it)->setValue(db, size * sizeof(byte));
                        break;
                }
            }


        }
        if (plcStatusCode == 8)
            std::cerr << "PLC TAGS updated successfully" << std::endl;
        mtxs7.unlock();
        return true;
    };
    SetS7Cb(cb);

}

// void ProtocolS::S7::S7Protocol::CreateAndWrite(Connection *Conn, Data* data)
// {
//     auto cS7 = reinterpret_cast<ConnectionS7 *>(Conn);
//     SetAddress(cS7->Address.Value);
//     SetRack();
//     SetSlot();
//     Init();

// }

// ProtocolS::S7Tag *ProtocolS::S7::S7Protocol::FindS7Tag(std::string name)
// {
//     for (auto p : ConnectionS)
//         if (p->IProtocol == ProtocolIIOT::S7)
//             for (auto n : p->NodeS){
//                  auto mq = reinterpret_cast<xmlS7*>(n);
//                 ProtocolS::S7Tag* mn{new ProtocolS::S7Tag(mq)};
//                  if (strcmp(mn->Name.Value.c_str(), name.c_str()) == 0)
//                     return mn;
//             }

//     std::cout << "S7 Tag :Not Found" << std::endl;
//     return nullptr;
// }

void ProtocolS::S7::S7Protocol::Open(Connection *Conn) {
    Connect();
}

void ProtocolS::S7::S7Protocol::Close() {
//    Disconnect();
}

void ProtocolS::S7::S7Protocol::KeepAlive() {
}

bool ProtocolS::S7::S7Protocol::isOK() {
    return Connected();
}

void ProtocolS::S7::S7Protocol::Reconnect() {
}

void ProtocolS::S7::S7Protocol::hasError() {
}

void ProtocolS::S7::S7Protocol::DataReceived() {
}

void ProtocolS::S7::S7Protocol::UpdateTag(ProtocolS::Tag *tag) {
    Protocol::UpdateTag(tag);
}


void ProtocolS::S7::S7Protocol::Write(Data *data, Tag *tag) {
    Protocol::Write(data, tag);
    ProtocolS::S7Tag *tag_ = (ProtocolS::S7Tag *) tag;
    auto size = Size(tag->ValueType.Value);
    byte db[size];
    int16_t temp = atoi(data->GetString().c_str());
    memcpy(db, &temp, sizeof(temp));
    boost::posix_time::time_duration td;
    std::cout << "++++++ write S7 ++++++" << std::endl;
    switch (tag_->s7tagType) {
        case S7TagType::DATABLOCKTAG:
            ReverseBytes(db, size);
            std::cout << temp << "++++++ write S7 DATABLOCKTAG++++++" << std::endl;
            DBWrite(tag_->getBitNumber(), tag_->getStartingAddress(), size, db);
            tag_->outputTime = boost::posix_time::microsec_clock::local_time();
            td = tag_->outputTime - tag_->inputTime;
            std::cout << "time : " << td.total_milliseconds() << std::endl
                      << std::endl;
            break;

        case S7TagType::IOTAGOUT:
            if (!strcmp(tag_->ValueType.Value.c_str(), "bool")) {
                uint16_t a = 0;
                ABRead(tag_->getBitNumber(), 2, db);
                memcpy(&a, db, sizeof(2));
                if (!strcmp(data->GetString().c_str(), "true")) {
                    a |= 1UL << tag_->getStartingAddress();
                } else {
                    a &= ~(1UL << tag_->getStartingAddress());
                }
                std::cout << temp << "++++++ write S7 IOTAGOUT++++++" << std::endl;
                ABWrite(tag_->getBitNumber(), 2, &a);
            } else {
                ReverseBytes(db, size);
                std::cout << temp << "++++++ write S7 IOTAGOUT++++++" << std::endl;
                ABWrite(tag_->getBitNumber(), size, db);
            }
            tag_->outputTime = boost::posix_time::microsec_clock::local_time();
            td = tag_->outputTime - tag_->inputTime;
            std::cout << "time : " << td.total_milliseconds() << std::endl
                      << std::endl;
            break;

        case S7TagType::MEMORYTAG: {
            if (!strcmp(tag_->ValueType.Value.c_str(), "bool")) {
                byte db_helper[1];
                if (strcmp(data->GetString().c_str(), std::string("true").c_str()) == 0) {
                    SetBitAt(db_helper, 0, tag_->getStartingAddress(), true);
                    MBWrite(tag_->getDBNumber(), size, &db_helper);
                } else {
                    SetBitAt(db_helper, 0, tag_->getStartingAddress(), false);
                    MBWrite(tag_->getDBNumber(), size, &db_helper);
                }


            } else {

                if (size==4){
                    byte Ndb[size];
                    float tempn = std::stof(data->GetString());
                    memcpy(Ndb, &tempn, sizeof(tempn));
                    ReverseBytes(Ndb, 4);
                    MBWrite(tag_->getDBNumber(), 4, Ndb);
                }else{
                    ReverseBytes(db, size);
                    std::cout << temp << "++++++ write S7 MEMORYTAG++++++" << std::endl;
                    MBWrite(tag_->getDBNumber(), size, db);
                }

            }


            break;
        }

        default:
            std::cout << "++++++ write S7 function error ++++++" << db << std::endl;
            // ReverseBytes(db, size);
            // DBWrite(tag_->getBitNumber(), tag_->getStartingAddress(), size, db);
            break;
    }
}

void ProtocolS::S7::S7Protocol::Stop() {
    Snap7::S7Client::Stop();
}

void ProtocolS::S7::S7Protocol::SetBitAt(byte *buffer, int Pos, int Bit, bool Value) {
    byte Mask[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    if (Bit < 0) Bit = 0;
    if (Bit > 7) Bit = 7;

    if (Value) {
        buffer[Pos] = (byte) (buffer[Pos] | Mask[Bit]);
    } else {
        buffer[Pos] = (byte) (buffer[Pos] & ~Mask[Bit]);
    }
}
