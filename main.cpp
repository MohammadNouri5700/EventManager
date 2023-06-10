#include <iostream>
#include "GateWay/Listener.h"
#include "GateWay/EventManager.h"
#include "GateWay/EventHandler.h"
#include "GateWay/Connection/XmlReader.h"
#include "ErrorManager/ErrorManager.h"
#include "GateWay/Node/Tag.h"
#include "GateWay/Node/NodeList.h"
#include "ConnectionManager/ConnectionManager.h"
#include "grpcserver.h"
#include "mosquittopp.h"
#include "W_modbus/modbuspp/modbuspp.h"
//#include "W_modbus/modbuspp/master.h"
#include "W_gps/GpsMessagesParser.h"



#include <mqtt/client.h>  // Mosquitto client.

std::vector<Connection *> ConnectionS;
std::vector<ProtocolS::Protocol *> ListenerS;
std::vector<Convert> ConvertS;
std::vector<OutputNode *> OutnodeS;
ProtocolS::NodeList nodeList;
ERROR::ErrorManager errorManager;
GateWay::LISTENer::Listener ll{};
GateWay::EVENT::MANAGER::EventManager e_manager;
#include<unistd.h>

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
////////////////////////////////////////////////////////////////////////////////////////////////
class SimpleSerial
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
    SimpleSerial(std::string port, unsigned int baud_rate)
        : io(), serial(io, port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
        serial.set_option(boost::asio::serial_port_base::character_size(8));
        serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    }

    /**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void writeString(std::string s)
    {
        boost::asio::write(serial, boost::asio::buffer(s.c_str(), s.size()));
    }

    /**
     * Blocks until a line is received from the serial device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
    std::string readLine()
    {
        // Reading data char by char, code is optimized for simplicity, not speed
        using namespace boost;
        char c;
        std::string result;
        for (;;)
        {
            asio::read(serial, asio::buffer(&c, 1));
            switch (c)
            {
            case '\r':
                break;
            case '\n':
                return result;
            default:
                result += c;
            }
        }
    }

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};
/////////////////////////////////////////////////////////////////////////


/**
 * @brief Prints the Gps Data
 * 
 *  
 * We consider NEO6 is connected to laptop by USB
 * 
 * @author MohammadNouri
 */
void  readGps(){
    SimpleSerial serial("/dev/tty05",  9600);

    int i= 0;
 while(true){
        try
        {
            // We consider NEO6 is connected to laptop by USB
            serial.writeString("RXM");
            std::cout <<  serial.readLine() << std::endl;

            // if(rs232Config.enabled == true)
            // serial.writeString("Hello world2\n");

        }
        catch (boost::system::system_error &e)
        {
            i++;
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    std::cout << "You have got more than 50 error: " << std::endl;
}


int start_sub(){
    // In order to connect the mqtt client to a broker,
    // Define an Ip address pointing to a broker. In this case, the localhost on port 1883.
    std::string ip = "iot-mqtt.pod.ir:1883";
    // Then, define an ID to be used by the client when communicating with the broker.
    std::string id = "NG340F190E3YA3C02ESCIEI";

    // Construct a client using the Ip and Id, specifying usage of MQTT V5.
    mqtt::client client(ip, id, mqtt::create_options(MQTTVERSION_5));
    // Use the connect method of the client to establish a connection to the broker.
    client.connect();
    // In order to receive messages from the broker, specify a topic to subscribe to.
    client.subscribe("dvcout/75r8nn7z3rg/NG340F190E3YA3C02ESCIEI/twin/#");
    // Begin the client's message processing loop, filling a queue with messages.
    client.start_consuming();

    bool running = true;
    while (running)
    {
        // Construct a message pointer to hold an incoming message.
        mqtt::const_message_ptr messagePointer;

        // Try to consume a message, passing messagePointer by reference.
        // If a message is consumed, the function will return `true`,
        // allowing control to enter the if-statement body.
        if (client.try_consume_message(&messagePointer))
        {
            // Construct a string from the message payload.
            std::string messageString = messagePointer -> get_payload_str();
            // Print payload string to console (debugging).
            std::cout << messageString << std::endl;

            // Perform processing on the string.
            // This is where message processing can be passed onto different
            // functions for parsing.
            // Here, we break the loop and exit the program if a `quit` is received.
            if (messageString == "quit")
            {
                running = false;
            }
        }
    }

    return 0;
}



int main()
{
//    start_sub();


//    tag_->outputTime = boost::posix_time::microsec_clock::local_time();
//    td = tag_->outputTime - tag_->inputTime;
//    std::cout << "time : " << td.total_milliseconds() << std::endl
//              << std::endl;


    //  GpsMessagesParser ff =  GpsMessagesParser("/dev/ttyUSB0",9600);
    // ff.fetchNMEA();
    // readGps();
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
//    sleep(5);
    connected = false;

    XmlReader xml;
//    std::string path{"/home/root/config.xml"};
    std::string path{"./config.xml"};
    ////////////////////////////////////////////////////////////////////
    if (xml.setFile(path))
    {
        xml.ExtraConnection(ConnectionS);
//        sleep(5);
        xml.ExtraConvert(ConvertS, ConnectionS);
//        sleep(5);
    }

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
//    sleep(5);
    CONNECTION::ConnectionManager ConnMan;
    std::cout << "config connection manager" << std::endl;
    ConnMan.Create();
//    sleep(5);
    xml.ExtraOutputNode(OutnodeS);
    for (OutputNode *i : OutnodeS)
    {
        std::cout << "\n****************************\n";
        i->print();
        std::cout << "\n****************************\n";
    }
//    sleep(5);
    std::cout << "start grpc" << std::endl;
    GrpcServer grpcserver("0.0.0.0:50051", &ConnMan);

    /// main//
    std::cout << "start event Manager" << std::endl;
    // EventManager e_manager{};
    std::cout << "start event handler" << std::endl;
    EventHandler e_handler{};
//    sleep(5);
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
//    sleep(5);
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
