cmake_minimum_required(VERSION 3.16.5)
project(Event_manager)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Wconversion -Weffc++" )


include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)

include_directories(W_modbus/modbuspp)
include_directories(wireless)
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_package(pugixml REQUIRED)
find_package(libcoap REQUIRED)
find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(modbuspp REQUIRED libmodbuspp)
pkg_check_modules(modbus REQUIRED libmodbus)
find_package(PahoMqttCpp REQUIRED)

add_subdirectory(W_coap)
add_subdirectory(W_mqtt)
add_subdirectory(W_S7)
add_subdirectory(ErrorManager)
add_subdirectory(lib/mqttclient)
add_subdirectory(lib/protos)
add_subdirectory(GrpcServer)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(PKG  PahoMqttCpp::paho-mqttpp3
        modbuspp
        modbus
        snap7
        coap-3
        pthread
        boost_system boost_thread boost_timer boost_chrono boost_regex rt
        pugixml
        iw
        )

set(MODBUS W_modbus/ModBus.cpp  W_modbus/Server.cpp  W_modbus/Master.cpp )

set( LIB
        W_can/cancontroller.cpp   
        
        MouseKey/key.cpp
        MouseKey/mouse.cpp

        GateWay/Listener.cpp 
        GateWay/EventManager.cpp 

        Protocols/Protocol.cpp 
        Protocols/SubscriberProtocol.cpp 
        Protocols/CanProtocol.cpp 
        Protocols/PublisherProtocol.cpp
        Protocols/ServerProtocol.cpp 
        Protocols/MasterProtocol.cpp 
        Protocols/ServerProtocol.cpp 
        Protocols/S7Protocol.cpp 


        GateWay/SignalS.cpp
        GateWay/ThreadPool.cpp 
        GateWay/Thread_Call.cpp  
        W_gps/GpsMessagesParser.cpp 
        Protocols/GpsProtocol.cpp 

        GateWay/Connection/Connection.cpp
        GateWay/Connection/ConnectionModbus.cpp GateWay/Connection/ConnectionModbus.cpp
        GateWay/Connection/ConnectionMqtt.cpp 
        GateWay/Connection/ConnectionCan.cpp 
        GateWay/Connection/ConnectionS7.cpp 
        GateWay/Connection/XmlReader.cpp 
        GateWay/Connection/ConnectionGPS.cpp 
        ErrorManager/ErrorManager.cpp   ErrorManager/Error.cpp
        GateWay/Event.cpp  GateWay/Data.cpp 
        GateWay/Node/Tag.cpp 
        GateWay/Node/NodeList.cpp 
        GateWay/Node/MqttTag.cpp 
        GateWay/Node/CanTag.cpp 
        ConnectionManager/ConnectionManager.cpp
        GateWay/Node/S7Tag.cpp GateWay/Node/ModBusTag.cpp
        GateWay/Connection/ConnectionCoap.cpp GateWay/Node/CoapTag.cpp
        GateWay/ConvertS/Convert.cpp Protocols/CoapProtocol.cpp
        GateWay/ConvertS/OutputNode.cpp

        GateWay/EventHandler.cpp Protocols/KeyProtocol.cpp
        Protocols/MouseProtocol.cpp

        
        Entity/GateSetting/setting.cpp Entity/EdgeProcess/edges.cpp
        Entity/EdgeProcess/edgeprocess.cpp Entity/Tag/tags.cpp
        Entity/Panel/panel.cpp Protocols/CentralProtocol.cpp
        GateWay/Node/EdgeTag.cpp GateWay/Connection/ConnectionEdge.cpp
        Entity/command/command.cpp
        Entity/TagValue/tagValue.cpp
        Entity/TagValue/getTagValue.cpp
        wireless/wifi.cpp
        MouseKey/eventfinder.cpp
        )

add_executable(Event_manager main.cpp ${LIB} ${MODBUS})
link_libraries(Event_manager GrpcServer W_coap W_mqtt W_S7 ${PKG} ${MODBUSPP_LIBRARIES}
gRPC::grpc++
protobuf::libprotobuf)
target_link_libraries(Event_manager GrpcServer W_coap W_mqtt W_S7 ${PKG} ${MODBUSPP_LIBRARIES}
        gRPC::grpc++ 
        protobuf::libprotobuf)
add_definitions(${MODBUSPP_CFLAGS} ${MODBUSPP_CFLAGS_OTHER})
include_directories(
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/W_gps"
        "${PROJECT_SOURCE_DIR}/W_coap"
        "${PROJECT_SOURCE_DIR}/W_mqtt"
        "${PROJECT_SOURCE_DIR}/W_S7"
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/atomic_queue/include")
target_include_directories(Event_manager  PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/W_coap"
        "${PROJECT_SOURCE_DIR}/W_mqtt"
        "${PROJECT_SOURCE_DIR}/W_S7"
        "${PROJECT_SOURCE_DIR}/include"
        #"${PROJECT_SOURCE_DIR}/ErrorManager"

        )
include(CPack)

set(HOME $ENV{HOME})
configure_file(${PROJECT_SOURCE_DIR}/include/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config/config.h)
