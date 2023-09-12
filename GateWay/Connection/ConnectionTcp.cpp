//
// Created by user on 7/25/23.
//


#include <arpa/inet.h>
#include "ConnectionTcp.h"
#include "nlohmann/json.hpp"
#include "../Event.h"
#include "../EventHandler.h"
#include "../ConvertS/Convert.h"
#include "../Node/NodeList.h"




extern Queue EventList;
extern std::vector<Convert> ConvertS;


#define TRUE   1


void ConnectionTcp::startServer(int interval_sec) {

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    while (true){
    if ((new_socket
                 = accept(server_fd, (struct sockaddr*)&address,
                          (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

        valread = read(new_socket, buffer, 1024);
        std::string ret(buffer, valread);


        nlohmann::json js = nlohmann::json::parse(ret);
        if (js.find("action") != js.end()) {
            nlohmann::json content = js.at("action");
            Event b;
            std::cout<<content.begin().key()<<std::endl;

            std::string *str = new std::string((char *) content.begin().value().dump().c_str());
            int data = atoi((char *) content.begin().value().dump().c_str());

           


            for (auto p: ConvertS) {

                // std::cout << "Convert Dest :" << p.distS()[0].c_str() << std::endl;
                if (std::strcmp(p.source().c_str(),content.begin().key().c_str()) == 0) {
                    std::cout << "Convert Source :" << p.source() << "  to  " << p.distS()[0]  <<  std::endl;
                    auto t = findTag(p.distS()[0]);
                    switch (t->conn->IProtocol) {
//                    case ProtocolIIOT::MQTT:
//                        b = Event(new ProtocolData{*str, &data, Name.Value}, TYPE::MQTT, t);
//                        EventList.push(std::move(b));
//                        break;
                        case ProtocolIIOT::S7:
                            b = Event(new ProtocolData{*str, &data, content.begin().key()}, TYPE::S7, t);
                            EventList.push(std::move(b));
                            break;
//                    case ProtocolIIOT::MODBUS:
//                        b = Event(new ProtocolData{*str, &data, Name.Value}, TYPE::MODBUS, t);
//                        EventList.push(std::move(b));
//                        break;
                        default:
                            break;
                    }
                }
            }
            send(new_socket, "ok", strlen("ok"), 0);
        }else{
            nlohmann::json content = js.at("read");
            std::string v;
            auto t = findTag(content.begin().key().c_str());
            if (strcmp(t->ValueType.Value.c_str(), "float")==0) {
                float  Res; memcpy (&Res, t->Value, 4);
                v = std::to_string(Res);
            }
            else if (strcmp(t->ValueType.Value.c_str(), "int")==0) {
                v = std::to_string(*((int32_t*)t->Value));
            }
            else if (strcmp(t->ValueType.Value.c_str(), "int16")==0) {
                v = std::to_string(*((int16_t*)t->Value));
            }
            else if (strcmp(t->ValueType.Value.c_str(), "bool")==0) {
                v = (*((bool*)t->Value))?"true":"false";
            }
            else if (strcmp(t->ValueType.Value.c_str(), "byte")==0) {
                v = std::to_string(*((int8_t*)t->Value));
            }

            std::cout<<"write "<< v << std::endl;
            send(new_socket, v.c_str(), strlen(v.c_str()), 0);
        }



        close(new_socket);
    }




//    send(new_socket, hello, strlen(hello), 0);
//    printf("Hello message sent\n");
//
//    // closing the connected socket
//    close(new_socket);
//    // closing the listening socket
//    shutdown(server_fd, SHUT_RDWR);



}

ConnectionTcp::~ConnectionTcp() {
  std::cout<< " STOP SERVER " <<std::endl;
}

ConnectionTcp::ConnectionTcp() {

}

void ConnectionTcp::async_run(int interval_sec) {

    thread = new std::thread(&ConnectionTcp::startServer, this, interval_sec);
    std::cout << " Server Started " << std::endl ;

}


