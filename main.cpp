#include <iostream>
#include "GateWay/Listener.h"
#include "GateWay/EventManager.h"
#include "GateWay/EventHandler.h"
#include "GateWay/Connection/XmlReader.h"
#include "GateWay/Connection/xmlnetwork.h"
#include "ErrorManager/ErrorManager.h"
#include "GateWay/Node/Tag.h"
#include "GateWay/Node/NodeList.h"
#include "ConnectionManager/ConnectionManager.h"
#include "grpcserver.h"
#include "mosquittopp.h"
#include "W_modbus/modbuspp/modbuspp.h"
//#include "W_modbus/modbuspp/master.h"

std::vector<Connection *> ConnectionS;
std::vector<ProtocolS::Protocol *> ListenerS;
std::vector<Convert> ConvertS;
std::vector<OutputNode *> OutnodeS;
ProtocolS::NodeList nodeList;
ERROR::ErrorManager errorManager;
GateWay::LISTENer::Listener ll{};
GateWay::EVENT::MANAGER::EventManager e_manager;
Network network;

std::thread e_m;
std::thread e_h;
bool connected;

using namespace GateWay::EVENT::MANAGER;
using namespace GateWay::EVENT::HANDLER;

////////////////////////////////////////////////////////////////////////////////////////////////
void sendRS485()
{
    struct termios tty;
    int hSerial = open("/dev/ttyO4", O_RDWR | O_NOCTTY | O_NDELAY);
    if (hSerial == -1)
        std::cout << "Opening of the port failed" << std::endl;
    fcntl(hSerial, F_SETFL, 0);
    if (tcgetattr(hSerial, &tty) != 0)
        std::cout << "Getting the parameters failed." << std::endl;
    if (cfsetispeed(&tty, B19200) != 0 || cfsetospeed(&tty, B19200) != 0)
        std::cout << "Setting the baud rate failed." << std::endl;

    // CFlags
    // Note: I am full aware, that there's an '=', and that it makes the '&=' obsolete, but they're in there for the sake of completeness.
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_cflag |= (CLOCAL | CREAD);            // und erlaubt 'Lesen'.
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    // Input Flags
    tty.c_iflag &= ~IGNBRK;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Local Flags
    tty.c_lflag = 0;

    // Output Flags
    tty.c_oflag = 0;

    // Control-Characters
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;
    if (tcsetattr(hSerial, TCSAFLUSH, &tty) != 0)
        std::cout << "Setting the new parameters failed" << std::endl;
    unsigned char C[] = {'H', 'A', 'M', 'I', 'D'};
    // while(1)
    for (auto c : C)
        write(hSerial, &c, 1);
    close(hSerial);
}

void ApplyIP()
{
    
    std::string cmd;
	//clean up all ip addresses
	cmd = "ip addr flush dev " + network.Name;
	
    system(cmd.c_str()); 

    cmd = "ip address add " + network.IP + "/24 dev " + network.Name;
    system(cmd.c_str()); 
    std::cout << "IP address added successfully " << network.IP << std::endl;
    
    
}

////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

int main()
{
    
    // std::string port ("/dev/ttyUSB1");
    // Modbus::Master mb (Modbus::Net::Rtu, port , "19200N1"); // new master on RTU
    // if you have to handle the DE signal of the line driver with RTS,
    // you should uncomment the lines below...
    // mb.rtu().setRts(RtsDown);
    // mb.rtu().setSerialMode(Rs485);
    // Modbus::Slave & slv = mb.addSlave (2); // SolarPi Pressure meter
    // std::cout << "Reads input registers of slave[" << slv.number() << "] on " <<
    //    mb.connection() << " (" << mb.settings() << ")" << std::endl;
    // if (mb.open ()) { // open a connection
    //     // success, do what you want here
    //     uint16_t values[2];
    //     //if (slv.readRegisters (1, values, 2) == 2) {
    //     if (slv.readInputRegisters (2, values, 2) == 2) {
    //     std::cout << "R0=" << values[0] << std::endl;
    //     std::cout << "R1=" << values[1] << std::endl;
    //     }
    //     else {
    //     std::cerr << "Unable to read input registers ! "  << mb.lastError() << std::endl;
    //     exit (EXIT_FAILURE);
    //     }
    //     mb.close();
    // }
    // else {
    //     std::cerr << "Unable to open MODBUS connection to " << port << " : " << mb.lastError() << std::endl;
    //     exit (EXIT_FAILURE);
    // }
    //    exit(0);
    ////////////////////////////////////////////////////////////////////////
    // sendRS485();

    //  try {

    //         SimpleSerial serial("/dev/ttyUSB0", 19200);

    //         serial.writeString("Hello world2\n");

    //         std::cout << serial.readLine() << std::endl;

    //     }
    //     catch (boost::system::system_error & e)
    //     {
    //         std::cout << "Error: " << e.what() << std::endl;
    //         return 1;
    //     }
    //      exit(0);
    /////////////////////
    mosqpp::lib_init();
    // system("sudo nmcli d wifi connect Inustry4");

    connected = false;

    XmlReader xml;
    std::string path{"/home/root/config.xml"};
    ////////////////////////////////////////////////////////////////////
    if (xml.setFile(path))
    {
        xml.
        (ConnectionS);
        xml.ExtraConvert(ConvertS, ConnectionS);
        xml.ExtraNetwork(network);
    }
    ApplyIP();
    for (auto i : ConnectionS)
    {
        std::cout << "\n****************************\n";
        i->print();
        std::cout << "\n****************************\n";
    }

    for (auto i : ConvertS)
    {
        std::cout << "\n****************************\n";
        i.Print();
        std::cout << "\n****************************\n";
    }

    CONNECTION::ConnectionManager ConnMan;
    std::cout << "config connection manager" << std::endl;
    ConnMan.Create();

    xml.ExtraOutputNode(OutnodeS);
    for (OutputNode *i : OutnodeS)
    {
        std::cout << "\n****************************\n";
        i->print();
        std::cout << "\n****************************\n";
    }

    std::cout << "start grpc" << std::endl;
    GrpcServer grpcserver("0.0.0.0:50051", &ConnMan);

    /// main//
    std::cout << "start event Manager" << std::endl;
    // EventManager e_manager{};
    std::cout << "start event handler" << std::endl;
    EventHandler e_handler{};

    std::cout << "bind event manager" << std::endl;
    e_m = std::thread(std::bind(&EventManager::Act, &e_manager));
    std::cout << "bind event handler" << std::endl;
    e_h = std::thread(std::bind(&EventHandler::Act, &e_handler));

    for (auto l : ListenerS)
    {
        ll.SetNodes(l);
    }
    std::cout << "Start out Node thread" << std::endl;
    for (auto n : OutnodeS)
    {
        n->async_run((int)(n->Timer.Value));
    }

    std::cout << "after starting, join able: " << e_m.joinable();
    e_m.join();
    e_h.join();

    std::cout << "\nHello, World!" << std::endl;
    while (true)
    {
        sleep(1);
    }
    
    mosqpp::lib_cleanup();
    return 0;
}
