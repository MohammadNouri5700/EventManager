//
// Created by aziz on 07.09.21.
//

#include "GpsMessagesParser.h"

enumGGAProtocolHeaders headersResolver(string messageID)
{
    if (messageID == "$GPRMC" ) return $GPRMC; // comment
    if (messageID == "$GPVTG" ) return $GPVTG;
    if (messageID == "$GPGGA" ) return $GPGGA;
    if (messageID == "$GPGSA" ) return $GPGSA;
    if (messageID == "$GPGSV" ) return $GPGSV;
    if (messageID == "$GPGLL" ) return $GPGLL;
    return $ERR;
}

std::string structNMEAFieldsGPRMC::json()
{
    std::string json{};
    std::stringstream ss;
    ss << "\nGPRMC{" <<
       "\nMessageID : " << strMessageID <<
       "\nUTCTime : " << strUTCTime <<
       "\nStatus : "  << strStatus <<
       "\nLatitude : " << strLatitude <<
       "\nNSIndicator : " << strNSIndicator <<
       "\nLongitude : " << strLongitude <<
       "\nEWindicator : " << strEWindicator <<
       "\nSpeedOverGround : " << strSpeedOverGround <<
       "\nCourseOverGround : " << strCourseOverGround <<
       "\nDate : " << strDate <<
       "\nMagneticVariation : " << strMagneticVariation <<
       "\nMode : " << strMode <<
       "\nChecksum : " << strChecksum << "\n}\n";
    return ss.str();
}

std::string structNMEAFieldsGPVTG::json()
{
    std::string json{};
    json = std::string("\nGPVTG{")+
           "\nMessageID : " + strMessageID +
           "\nCourseOverGround : " +strCourseOverGround +
           "\nFixedField : " + strFixedField +
           "\nCourseOverGroundMagnetic : " + strCourseOverGroundMagnetic +
           "\nFixedFieldMagnetic : " + strFixedFieldMagnetic +
           "\nSpeedOverGround : " + strSpeedOverGround +
           "\nFixedFieldKnots : "+ strFixedFieldKnots +
           "\nSpeedOverGroundKm_h : " + strSpeedOverGroundKm_h +
           "\nFixedFieldKm : "  + strFixedFieldKm +
           "\nMode : " + strMode +
           "\nChecksum : " + strChecksum + "\n}\n";

    return json;
}

std::string structNMEAFieldsGPGGA::json()
{
    std::string json{};
    json = std::string("\nGPGGA{")+
           "\nMessageID : " + strMessageID +
           "\nUTCTime : " + strUTCTime +
           "\nLatitude : " + strLatitude +
           "\nNSIndicator : " + strNSIndicator +
           "\nLongitude : " + strLongitude +
           "\nEWIndicator : " + strEWIndicator +
           "\nPositionFixStatus : " + strPositionFixStatus +
           "\nPositionFixFlags : " + strPositionFixFlags +
           "\nSatellitesUsed : " + strSatellitesUsed +
           "\nHDOP : " + strHDOP +
           "\nAltitude : " + strAltitude +
           "\nUnitsM : " + strUnitsM +
           "\nGeoidSeparation : " + strGeoidSeparation +
           "\nUnitsMeters : " + strUnitsMeters+
           "\nAgeofDifferentialCorrections : " + strAgeofDifferentialCorrections +
           "\nDiffReferenceStationID : " + strDiffReferenceStationID +
           "\nChecksum : " + strChecksum + "\n}\n";
    return json;
}

std::string structNMEAFieldsGPGLL::json()
{
    std::string json{};
    json = std::string("\nGPGLL") +
           "\nMessageID : " + strMessageID +
           "\nLatitude : " + strLatitude +
           "\nNSIndicator : " + strNSIndicator +
           "\nLongitude : " + strLongitude +
           "\nEWindicator : " + strEWindicator +
           "\nUTCTime : " + strUTCTime +
           "\nValid : " + strValid +
           "\nMode : " + strMode +
           "\nChecksum : " + strChecksum + "\n}\n";
    return json;
}

vector<string> GpsMessagesParser::strSpliterUtility(std::string strStrm, char c)
{
    {
        vector<string> result;
        stringstream gpsFields(strStrm);
        while (gpsFields.good()) {
            std::string substr;
            getline(gpsFields, substr, c);
            result.push_back(substr);
        }
        return result;
    }
}

void GpsMessagesParser::fetchNMEA()
{
    if (start) {
        std::thread thrdFetchNMEA(&GpsMessagesParser::thrdFetchNMEAHandler, this);
        thrdFetchNMEA.join();
    }
}

void GpsMessagesParser::thrdFetchNMEAHandler()
{
    try {
        string NMEA;
        while (start) {
            NMEA = readNMEASentence();
            vector<string> splitedGPSData;
            splitedGPSData = strSpliterUtility(NMEA, ',');
            NEMAFieldsSpliter(splitedGPSData);
            GpsCb((bGPRMC?jasonGPRMC():""), (bGPVTG?jasonGPVTG():""), (bGPGGA?jasonGPGGA():""), (bGPGLL?jasonGPGLL():""), coord.first, coord.second, Time);
            bGPRMC = bGPVTG = bGPGGA = bGPGLL = false;
        }
    } catch (system::system_error &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void GpsMessagesParser::fillGPRMCFields(const vector<string> &vectSplitedGPSData)
{

    vector<string> modeChecksumFields;
    NMEAFieldsGPRMCTmp.strMessageID = vectSplitedGPSData[0];
    NMEAFieldsGPRMCTmp.strUTCTime = vectSplitedGPSData[1];
    NMEAFieldsGPRMCTmp.strStatus = vectSplitedGPSData[2];
    NMEAFieldsGPRMCTmp.strLatitude = vectSplitedGPSData[3];
    NMEAFieldsGPRMCTmp.strNSIndicator = vectSplitedGPSData[4];
    NMEAFieldsGPRMCTmp.strLongitude = vectSplitedGPSData[5];
    NMEAFieldsGPRMCTmp.strEWindicator = vectSplitedGPSData[6];
    NMEAFieldsGPRMCTmp.strSpeedOverGround = vectSplitedGPSData[7];
    NMEAFieldsGPRMCTmp.strCourseOverGround = vectSplitedGPSData[8];
    NMEAFieldsGPRMCTmp.strDate = vectSplitedGPSData[9];
    NMEAFieldsGPRMCTmp.strMagneticVariation = vectSplitedGPSData[10];
    //NMEAFieldsGPRMCTmp. = vectSplitedGPSData[11];
    modeChecksumFields = strSpliterUtility(vectSplitedGPSData[12], '*');
    NMEAFieldsGPRMCTmp.strMode = modeChecksumFields[0] ;
    NMEAFieldsGPRMCTmp.strChecksum = modeChecksumFields[1];

    Time =  NMEAFieldsGPRMCTmp.strUTCTime.empty() ? 0 : std::stod(NMEAFieldsGPRMCTmp.strUTCTime);
    coord.first =  NMEAFieldsGPRMCTmp.strLongitude.empty() ? 0 : std::stod(NMEAFieldsGPRMCTmp.strLongitude);
    coord.second =  NMEAFieldsGPRMCTmp.strLatitude.empty() ? 0 : std::stod(NMEAFieldsGPRMCTmp.strLatitude);
}

void GpsMessagesParser::fillGPGGAFields(const vector<string> &vectSplitedGPSData)
{

    NMEAFieldsGPGGATmp.strMessageID = vectSplitedGPSData[0];
    NMEAFieldsGPGGATmp.strUTCTime  = vectSplitedGPSData[1];
    NMEAFieldsGPGGATmp.strLatitude   =  vectSplitedGPSData[2];
    NMEAFieldsGPGGATmp.strNSIndicator = vectSplitedGPSData[3];
    NMEAFieldsGPGGATmp.strLongitude = vectSplitedGPSData[4];
    NMEAFieldsGPGGATmp.strEWIndicator  = vectSplitedGPSData[5];
    NMEAFieldsGPGGATmp.strPositionFixStatus = vectSplitedGPSData[6];
    NMEAFieldsGPGGATmp.strPositionFixFlags = vectSplitedGPSData[7];
    NMEAFieldsGPGGATmp.strSatellitesUsed = vectSplitedGPSData[8];
    NMEAFieldsGPGGATmp.strHDOP = vectSplitedGPSData[9];
    NMEAFieldsGPGGATmp.strAltitude = vectSplitedGPSData[10];
    NMEAFieldsGPGGATmp.strUnitsM = vectSplitedGPSData[11];
    NMEAFieldsGPGGATmp.strGeoidSeparation = vectSplitedGPSData[12]; //todo
    /*NMEAFieldsGPGGATmp.strUnitsMeters = vectSplitedGPSData[13];
    NMEAFieldsGPGGATmp.strAgeofDifferentialCorrections = vectSplitedGPSData[14];
    NMEAFieldsGPGGATmp.strDiffReferenceStationID = vectSplitedGPSData[15] ; //todo
    NMEAFieldsGPGGATmp.strChecksum= vectSplitedGPSData[14];*/


    Time =  NMEAFieldsGPGGATmp.strUTCTime.empty() ? 0 : std::stod(NMEAFieldsGPGGATmp.strUTCTime);
    coord.first =  NMEAFieldsGPGGATmp.strLongitude.empty() ? 0 : std::stod(NMEAFieldsGPGGATmp.strLongitude);
    coord.second =  NMEAFieldsGPGGATmp.strLatitude.empty() ? 0 : std::stod(NMEAFieldsGPGGATmp.strLatitude);

}

void GpsMessagesParser::fillGPVTGFields(const vector<string> &vectSplitedGPSData)
{
    //cout << "filling GPVTG Fields" << endl;
    vector<string> modeChecksumFields;
    NMEAFieldsGPVTGTmp.strMessageID = vectSplitedGPSData[0];
    NMEAFieldsGPVTGTmp.strCourseOverGround  = vectSplitedGPSData[1];
    NMEAFieldsGPVTGTmp.strFixedField   =  vectSplitedGPSData[2];
    NMEAFieldsGPVTGTmp.strCourseOverGroundMagnetic = vectSplitedGPSData[3];
    NMEAFieldsGPVTGTmp.strFixedFieldMagnetic = vectSplitedGPSData[4];
    NMEAFieldsGPVTGTmp.strSpeedOverGround  = vectSplitedGPSData[5];
    NMEAFieldsGPVTGTmp.strFixedFieldKnots = vectSplitedGPSData[6];
    NMEAFieldsGPVTGTmp.strSpeedOverGroundKm_h = vectSplitedGPSData[7];
    NMEAFieldsGPVTGTmp.strFixedFieldKm = vectSplitedGPSData[8];
    modeChecksumFields = strSpliterUtility(vectSplitedGPSData[9], '*');
    NMEAFieldsGPVTGTmp.strMode = modeChecksumFields[0] ;
    NMEAFieldsGPVTGTmp.strChecksum= modeChecksumFields[1];
}

void GpsMessagesParser::fillGPGLLFields(const vector<string> &vectSplitedGPSData)
{
    //cout << "filling GPGLL Fields " << endl;
    vector<string> modeChecksumFields;
    NMEAFieldsGPGLLTmp.strMessageID = vectSplitedGPSData[0];
    NMEAFieldsGPGLLTmp.strLatitude = vectSplitedGPSData[1];
    NMEAFieldsGPGLLTmp.strNSIndicator = vectSplitedGPSData[2];
    NMEAFieldsGPGLLTmp.strLongitude = vectSplitedGPSData[3];
    NMEAFieldsGPGLLTmp.strEWindicator = vectSplitedGPSData[4];
    NMEAFieldsGPGLLTmp.strUTCTime = vectSplitedGPSData[5];
    NMEAFieldsGPGLLTmp.strValid = vectSplitedGPSData[6];
    modeChecksumFields = strSpliterUtility(vectSplitedGPSData[7], '*');
    NMEAFieldsGPGLLTmp.strMode = modeChecksumFields[0];
    NMEAFieldsGPGLLTmp.strChecksum= modeChecksumFields[1];

    Time =  NMEAFieldsGPGLLTmp.strUTCTime.empty() ? 0 : std::stod(NMEAFieldsGPGLLTmp.strUTCTime);
    coord.first =  NMEAFieldsGPGLLTmp.strLongitude.empty() ? 0 : std::stod(NMEAFieldsGPGLLTmp.strLongitude);
    coord.second =  NMEAFieldsGPGLLTmp.strLatitude.empty() ? 0 : std::stod(NMEAFieldsGPGLLTmp.strLatitude);
}

void GpsMessagesParser::NEMAFieldsSpliter(vector<std::string> vectSplitedGPSData)
{
    //  vector<string> modeChecksumFields;
    switch (headersResolver(vectSplitedGPSData[0]) ) {
    case $GPRMC :
        fillGPRMCFields(vectSplitedGPSData);
        bGPRMC = true;
        break;
    case $GPVTG :
        fillGPVTGFields(vectSplitedGPSData);
        bGPVTG = true;
        break;
    case $GPGGA :
        fillGPGGAFields(vectSplitedGPSData);
        bGPGGA = true;
        break;
    case $GPGSA :
        //cout << "$GPGSA" << endl;
        break;
    case $GPGSV :
        //cout << "$GPGSV" << endl;
        break;
    case $GPGLL :
        fillGPGLLFields(vectSplitedGPSData);
        bGPGLL = true;
        break;
    default :
        //cout << "nothing has splited"<< endl;
        break;
    }
}

std::string GpsMessagesParser::readNMEASentence()
{
    string result;
    char c;
    do {
        asio::read(*gpsSerialPortInterface, asio::buffer(&c, 1));

        switch (c) {
        case '\r':
            break;
        case '\n':
            return result;
        default:
            result+=c;
        }
    } while ( c != '\n' );
    return "";
}

json_t GpsMessagesParser::jasonGPRMC()
{
    return NMEAFieldsGPRMCTmp.json();
}

json_t GpsMessagesParser::jasonGPVTG()
{
    return NMEAFieldsGPVTGTmp.json();
}

json_t GpsMessagesParser::jasonGPGGA()
{
    return NMEAFieldsGPGGATmp.json();
}

json_t GpsMessagesParser::jasonGPGLL()
{
    return NMEAFieldsGPGLLTmp.json();
}

void GpsMessagesParser::setGpsCb(const gpsCallback &gpsCb)
{
    GpsCb = gpsCb;
}

GpsMessagesParser::GpsMessagesParser(string port, unsigned int baud_rate)
{
    try {
        gpsPort = port;
        gpsSerialPortInterface.reset(new boost::asio::serial_port(io, port));
        gpsSerialPortInterface->set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
        start =true;
    } catch (boost::system::system_error& e) {
        cerr<<"Error: " << e.what()
            <<"\nInfo: "  << boost::diagnostic_information(e) <<endl;
        start = false;
        ERROR::Error err{ERR_GPS, "GPS can not connected", "how to debug GPS", ERROR::ErrorType::RUN_TIME, 7};
        errorManager.AddError(err);
    }
}

double GpsMessagesParser::getTime() const
{
    return Time;
}

const pair<double, double> &GpsMessagesParser::getCoord() const
{
    return coord;
}

