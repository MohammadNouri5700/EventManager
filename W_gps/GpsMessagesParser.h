//
// Created by aziz on 07.09.21.
//
/*
 * File:   GpsMessagesParser.h
 * Author: Terraneo Federico
 * Distributed under the Boost Software License, Version 1.0.
 *
 * Created on September 10, 2009, 12:12 PM
 */
#ifndef EVENT_MANAGER_GPSMESSAGESPARSER_H
#define EVENT_MANAGER_GPSMESSAGESPARSER_H

#include <boost/asio.hpp>
#include <iostream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <string.h>
#include <boost/thread.hpp>
#include <thread>
#include <functional>
#include <boost/date_time.hpp>
#include "../ErrorManager/ErrorManager.h"
#include <utility>
extern ERROR::ErrorManager errorManager;

using json_t = std::string;

using namespace boost;
using namespace std;

struct structNMEAFieldsGPRMC {
    string strMessageID{};
    string strUTCTime{};
    string strStatus{};
    string strLatitude{};
    string strNSIndicator{};
    string strLongitude{};
    string strEWindicator{};
    string strSpeedOverGround{};
    string strCourseOverGround{};
    string strDate{};
    string strMagneticVariation{};
    string strMode{};
    string strChecksum{};
    std::string json();
};

struct structNMEAFieldsGPVTG {
    string strMessageID{};
    string strCourseOverGround{};
    string strFixedField{};
    string strCourseOverGroundMagnetic{};
    string strFixedFieldMagnetic{};
    string strSpeedOverGround{};
    string strFixedFieldKnots{};
    string strSpeedOverGroundKm_h{};
    string strFixedFieldKm{};
    string strMode{};
    string strChecksum{};
    std::string json();
};

struct structNMEAFieldsGPGGA {
    string strMessageID{};
    string strUTCTime{};
    string strLatitude{};
    string strNSIndicator{};
    string strLongitude{};
    string strEWIndicator{};
    string strPositionFixStatus{};
    string strPositionFixFlags{};
    string strSatellitesUsed{};
    string strHDOP{};
    string strAltitude{};
    string strUnitsM{};
    string strGeoidSeparation{};
    string strUnitsMeters{};
    string strAgeofDifferentialCorrections{};
    string strDiffReferenceStationID{};
    string strChecksum{};
    std::string json();

};

struct structNMEAFieldsGPGLL {
    string strMessageID{};
    string strLatitude{};
    string strNSIndicator{};
    string strLongitude{};
    string strEWindicator{};
    string strUTCTime{};
    string strValid{};
    string strMode{};
    string strChecksum{};
    std::string json();
};

using GPRMC_t = structNMEAFieldsGPRMC;
using GPVTG_t = structNMEAFieldsGPVTG;
using GPGGA_t = structNMEAFieldsGPGGA;
using GPGLL_t = structNMEAFieldsGPGLL;

enum  enumGGAProtocolHeaders {
    $GPRMC,
    $GPVTG,
    $GPGGA,
    $GPGSA,
    $GPGSV,
    $GPGLL,
    $ERR
} ;

enumGGAProtocolHeaders headersResolver(string messageID);

using gpsCallback = std::function< void(json_t, json_t, json_t, json_t, double, double, double) >;

class GpsMessagesParser
{
public:
    virtual ~GpsMessagesParser(){ /*TODO*/ }
    /**
    * Constructor.
    * \param port device name, example "/dev/ttyUSB0" or "COM4"
    * \param baud_rate communication speed, example 9600 or 115200
    * \throws boost::system::system_error if cannot open the
    * gpsSerialPortInterface device
    */

    /// @brief <SPAN dir="rtl"> تابع سازنده با ورودی stClient</SPAN>
    ///
    /// @pre  <SPAN dir="rtl"> از مقدار دهی با Null  یا تهی پرهیز شود</SPAN>
    ///
    /// @param c  مسیری که کلاینت به از ان پیام دریافت می‌کند یا ارسال می‌نماید

    /*GpsMessagesParser(string port, unsigned int baud_rate): io(), gpsSerialPortInterface(io, port)
    {
        gpsSerialPortInterface.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }*/

    GpsMessagesParser(string port, unsigned int baud_rate);


    /**
     * Write a string to the gpsSerialPortInterface device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void writeString(std::string s)
    {
        boost::asio::write(*gpsSerialPortInterface, boost::asio::buffer(s.c_str(), s.size()));
    }

    /**
     * Blocks until a line is received from the gpsSerialPortInterface device.
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */

    std::string readNMEASentence();

    void NEMAFieldsSpliter(vector<std::string> vectSplitedGPSData) ;

    void fillGPGLLFields(const vector<string> &vectSplitedGPSData) ;

    void fillGPVTGFields(const vector<string> &vectSplitedGPSData);

    void fillGPGGAFields(const vector<string> &vectSplitedGPSData);

    void fillGPRMCFields(const vector<string> &vectSplitedGPSData);

    void thrdFetchNMEAHandler();

    /// @brief <SPAN dir="rtl"> تابع سازنده با ورودی stClient</SPAN>
    ///
    /// @pre  <SPAN dir="rtl"> از مقدار دهی با Null  یا تهی پرهیز شود</SPAN>
    ///
    /// @param c  مسیری که کلاینت به از ان پیام دریافت می‌کند یا ارسال می‌نماید

    ///

    void fetchNMEA();

    double getTime() const;

    const pair<double, double> &getCoord() const;

    vector<string> strSpliterUtility(std::string strStrm, char c);

    json_t jasonGPRMC();
    json_t jasonGPVTG();
    json_t jasonGPGGA();
    json_t jasonGPGLL();

private:
    boost::asio::io_service io{};
    boost::shared_ptr<boost::asio::serial_port> gpsSerialPortInterface{};
    structNMEAFieldsGPRMC NMEAFieldsGPRMCTmp{};
    bool bGPRMC{false};
    structNMEAFieldsGPVTG NMEAFieldsGPVTGTmp{};
    bool bGPVTG{false};
    structNMEAFieldsGPGGA NMEAFieldsGPGGATmp{};
    bool bGPGGA{false};
    structNMEAFieldsGPGLL NMEAFieldsGPGLLTmp{};
    bool bGPGLL{false};

    double Time{};
    std::pair<double, double> coord{};

    std::string gpsPort{"/dev/ttyUSB0"} ;
    unsigned int gpsBaudRate {9600} ;
    gpsCallback GpsCb{};
public:
    void setGpsCb(const gpsCallback &gpsCb);
    bool start =  true;
};

#endif //EVENT_MANAGER_GPSMESSAGESPARSER_H
