//
// Created by aziz on 15.09.21.
//

#include "XmlReader.h"
#include "../ConvertS/OutputNode.h"
XmlReader::XmlReader() {}

bool XmlReader::setFile(std::string Name)
{

    pugi::xml_parse_result result = xmlDoc.load_file(Name.c_str());
    if (!result) {
        std::cout << "\nErr open xml file.\n";
        throw std::exception();
        return false;
    }
    return true;
}

void XmlReader::ExtraConnection(std::vector<Connection*> &conn)
{
    auto ConnectionS = xmlDoc.child("GateWay").child("ConnectionS");
    for (pugi::xml_node Connection: ConnectionS.children("Connection")) {

        if (  strcmp(Connection.attribute("Protocol").value(), "Mqtt") == 0) {

            ConnectionMqtt *mqtt = new ConnectionMqtt{};
            mqtt->SetData(Connection);
            conn.push_back(mqtt);
        }
        if (  strcmp(Connection.attribute("Protocol").value(), "S7") == 0) {
            ConnectionS7 *S7 = new ConnectionS7{};
            S7->SetData(Connection);
            conn.push_back(S7);
        }
        if (  !strcmp(Connection.attribute("Protocol").value(), "ModBus")) {
            ConnectionModbus *modbus = new ConnectionModbus{};
            modbus->SetData(Connection);
            conn.push_back(modbus);
        }
        if (  !strcmp(Connection.attribute("Protocol").value(), "Edge")) {
            ConnectionEdge *edge = new ConnectionEdge{};
            edge->SetData(Connection);
            conn.push_back(edge);
        }
        if (  !strcmp(Connection.attribute("Protocol").value(), "CAN")) {
            ConnectionCAN *can = new ConnectionCAN{};
            can->SetData(Connection);
            conn.push_back(can);
        }
        if (  !strcmp(Connection.attribute("Protocol").value(),"GPS")){
            ConnectionGPS *GPS = new ConnectionGPS{};
            GPS->SetData(Connection);
            conn.push_back(GPS);
        }
       /* if (  !strcmp(Connection.attribute("Protocol").value(),"SNMP")){
            ConnectionSnmp *Snmp = new ConnectionSnmp{};
            Snmp->SetData(Connection);
            conn.push_back(Snmp);
        }*/
        if (  !strcmp(Connection.attribute("Protocol").value(), "COAP")) {
            ConnectionCoap *Node = new ConnectionCoap{};
            Node->SetData(Connection);
            conn.push_back(Node);
        }

    }
}

void XmlReader::ExtraConvert(std::vector<Convert> &con, const std::vector<Connection*> &conn)
{
    auto convertS = xmlDoc.child("GateWay").child("ConvertS");
    for (pugi::xml_node convert: convertS.children("Convert")) {
        Convert c;
        c.setSource(convert.child("Source").child_value());
        for (auto dist:  convert.child("DistS").children("Dist")) {
            c.setDist(dist.child_value());
        }
        con.push_back(std::move(c));
    }

}

void XmlReader::ExtraOutputNode(std::vector<OutputNode*> &outnode)
{
    auto outputNodeS = xmlDoc.child("GateWay").child("OutputNodeS");
    for (pugi::xml_node outputNode: outputNodeS.children("OutputNode")) {
            OutputNode *out = new OutputNode();
            out->SetData(outputNode);
            outnode.push_back(std::move(out));
        }
        

}

void XmlReader::ExtraNetwork(Network &network)
{
    auto Network = xmlDoc.child("GateWay").child("Network");
    network.Name = Network.child("Name").child_value();
    network.NetMask = Network.child("NetMask").child_value();
    network.IP = Network.child("IP").child_value();
}
