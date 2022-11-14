//
// Created by aziz on 02.01.22.
//
#include <iostream>
#include "wifi.h"
 #include <algorithm>
#include <regex>
#include <fstream>
#include<boost/algorithm/string.hpp>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <resolv.h>
#include <arpa/inet.h>

using namespace std;
#define BUFSIZE 8192
char gateway[255];

struct route_info {
    struct in_addr dstAddr;
    struct in_addr srcAddr;
    struct in_addr gateWay;
    char ifName[IF_NAMESIZE];
};

std::string GetLevel(std::string s)
{


    std::regex r("(level=)([-]*\\d*)");
    std::smatch match;
    std::string ss{"null"};
    if (std::regex_search(s, match, r) == true) {
        ss = match.str(2);
        //std::cout << "signal level " << ss<< std::endl;
    }
    return ss;
}

std::string GetBitrate(std::string s)
{


    std::regex r("(\\d*)");
    std::smatch match;
    std::string ss{"null"};
    if (std::regex_search(s, match, r) == true) {
        ss = match.str();
        //std::cout << "Bitrate " << ss<< std::endl;
    }
    return ss;
}


std::map<std::string,networks> wifi::SystemScan(void)
{
    system("iwlist  wlx7cc2c62577c4 scan | egrep 'ESSID|Quality' > wifiessid.tmp") ;
    std::string Essid;
    std::string line;
    ifstream myfile;
    myfile.open("wifiessid.tmp");
    while (getline(myfile, Essid))
    {
        boost::trim(Essid);
        std:cout << Essid<<std::endl;
        int locEssid = Essid.find("\"")+1;
        std::string tokenEssid = Essid.substr(locEssid, Essid.length()-locEssid-1); 
        getline(myfile, Essid);
        networks tempNetwork;
        tempNetwork.Essid = tokenEssid;
        int locQuality = Essid.find("level=")+1;
        if (locQuality > 0)
         {
             std::string tokenQuality = Essid.substr(locQuality+5,   4 ); 
             tempNetwork.Quality = tokenQuality;
             networkList[tokenEssid].Essid = tokenEssid;
             char tempstring[10];
             char tempstringnew[10];
             strncpy(tempstring,networkList[tokenEssid].Quality.c_str(),2);
             
             strcpy(tempstringnew , tokenQuality.c_str());
             tempstringnew[2] = tempstring[2] = '\0';
             if(atoi(tempstring)<atoi(tempstringnew))
             networkList[tokenEssid].Quality = tempNetwork.Quality;
         }
    }
    return networkList;
}

std::string wifi::findEssidName()
{
 int           fd;
   struct iwreq  w;
   char          essid[IW_ESSID_MAX_SIZE];
    char iface[50] = "wlx7cc2c62577c4";

   if (!iface) return NULL;

   fd = socket(AF_INET, SOCK_DGRAM, 0);
   printf("Socket desc is: %d\n", fd);

   if(fd <0)
   {
    printf("Socket failed: %d", fd);
   }

   strncpy (w.ifr_ifrn.ifrn_name, iface, IFNAMSIZ);
   memset (essid, 0, IW_ESSID_MAX_SIZE);
   w.u.essid.pointer = (caddr_t *) essid;
   w.u.data.length = IW_ESSID_MAX_SIZE;
   w.u.data.flags = 0;

   int ret = ioctl (fd, SIOCGIWESSID, &w);
   printf("ioctl ret is : %d\n", ret);

   ret = ioctl (fd, SIOCGIFHWADDR, &w);
   printf("ioctl ap details ret is : %d\n", ret);
   //get HWaddr
   u_int8_t hd[6];

    memcpy(hd,w.u.ap_addr.sa_data,sizeof(hd));
    int i=0;
    printf("HWaddr:");
    for(i;i<6;i++)
    {
        printf("%02X:",hd[i]);
    }
   
   
   std::cout<< std::endl<< essid << std::endl;
   close (fd);

   return strdup (essid);

}

std::vector<std::string> wifi::getifconfig(void)
{
    struct ifaddrs *ifaddr;
    int family, s ,s2;
    char host[NI_MAXHOST];
    char subnet[NI_MAXHOST];
    char str[INET_ADDRSTRLEN];
    socklen_t addrlen;         /* input */
    struct sockaddr *addr;     /* input */
    std::vector<std::string> netinfo ;
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

 if (getifaddrs(&ifaddr) == -1) {
               perror("getifaddrs");
               exit(EXIT_FAILURE);
           }

           for (struct ifaddrs *ifa = ifaddr; ifa != NULL;
                    ifa = ifa->ifa_next) {
               if (ifa->ifa_addr == NULL)
                   continue;

               family = ifa->ifa_addr->sa_family;

                   s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),
                           host, NI_MAXHOST,
                           NULL, 0, NI_NUMERICHOST);
                   s2 = getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in), subnet, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                   if(!strcmp(ifa->ifa_name , "wlx7cc2c62577c4") && s==0){
                       std::cout<<"ip ="<<host<<std::endl;
                        std::cout<<"mask ="<<subnet<<std::endl;
                        netinfo.push_back(host);
                        netinfo.push_back(subnet);
                        netinfo.push_back("192.168.0.1");
                        netinfo.push_back("4.2.2.4");
                   }
                       
           }

          freeifaddrs(ifaddr);
    return netinfo;       
 }

bool wifi::Scan(void)
{

    accessPoints_.clear();
    essID_.clear();
    wireless_scan_head head;
    wireless_scan *result;
    char buffer[128];
    int state = 0;
    int counter =0;
    /* Perform the scan */
    do{
        state = iw_scan(sock_, (char*)(ifName_.data()), range_.we_version_compiled, &head);
        std::cout << " SCAN ======= " << counter << state << head.result << std::endl;
    } while((state !=0 || head.result ==NULL) && counter++ < 5);

    if ( state < 0) {
        std::cout << "Error during iw_scan. Aborting. Error = " << state << std::endl ;
        return false;
    }
        std::cout << "wifi scan compeleted ... " << state << std::endl ;
    // /* Traverse the results */
     result = head.result;
     std::cout << result << std::endl;

    auto find_essid = [&result](std::string s)->bool{ return (std::string(result->b.essid).compare(s)==0); };
    std::cout << "test 1" << std::endl;
     while (NULL != result) {
         access_point accP;

         auto it = std::find_if(essID_.begin(), essID_.end(), find_essid);


        std::cout << "test 2" << std::endl;


         if (it == essID_.end()) {


             essID_.push_back(std::string(result->b.essid));

             accP.essId_ = std::string(result->b.essid);


             if (result->has_maxbitrate) {
                 iw_print_bitrate(buffer, sizeof(buffer), result->maxbitrate.value);
                 accP.bitrate_ = GetBitrate(std::string{buffer});


             }
//-----------------------------------------------
            std::cout << "test 3  -----" << essID_.size()  << std::endl;
            // for (decltype(essID_.size()) i = 0; i < essID_.size(); ++i)
            // {
            //     std::cout << essID_[i] << std::endl;
            // }
//-----------------------------------------------
             if (result->has_stats) {
                 iw_print_stats(buffer, sizeof(buffer), &result->stats.qual, &range_, 1);

                 accP.State_ = GetLevel(std::string{buffer});
             }

            std::cout << "test 4" << std::endl;


             accessPoints_.push_back(accP);
         }
         result = result->next;
     }
    std::cout << "test 5" << std::endl;

     result = head.result;
     /* free results */
     while (result && result->next) {
         wireless_scan *tmp;
         tmp = result->next;
         free (result);
         result = tmp;
     }

     std::cout << "test 6" << std::endl;
     if (result) {
         free(result);
     }
     std::cout << "test 7" << std::endl;
    return true; //TODO
}

wifi::wifi()
{

     sock_ = iw_sockets_open();

    /* Get some metadata to use for scanning */
     if (iw_get_range_info(sock_, ifName_.data(), &range_) < 0) {
         std::cout << "Error during iw_get_range_info. Aborting.\n";
     }


}

void wifi::print(void)
{

    for (auto a: accessPoints_) {
        std::cout << a.toJson() << "\n";
    }

}

wifi::~wifi()
{
     iw_sockets_close(sock_);
}

int wifi::Turn(std::string data)
{
    std::string Command = "nmcli radio wifi "+ data;
    system(Command.c_str()) ;
    return 0;
}


std::string wifi::Connect(std::string data)
{
    std::string line;
    ifstream myfile;
    nlohmann::json j = nlohmann::json::parse(data);
    std::string Essid = j.at("networkName").get<std::string>();
    std::string Pass = j.at("networkPassword").get<std::string>();
    std::string Command;
    std:string ReturnValue = "";
    if(Pass.length() > 0){
        std::cout << "Essid = " << Essid << " " << "Pass = " << Pass << std::endl;
        Command= "nmcli d wifi connect "+Essid+" password "+Pass+" &> tempcommand.txt";
        std::cout << Command << std::endl;
    }else{
         std::cout << "Essid = " << Essid << " " << "Pass = " << Pass << std::endl;
        Command= "nmcli d wifi connect "+Essid +" &> tempcommand.txt";
        std::cout << Command << std::endl;
    }
    system(Command.c_str()) ;
    myfile.open("tempcommand.txt");
    getline(myfile, ReturnValue);
    
    return ReturnValue;
}

json wifi::toJson()
{

    json access, j, m, acc;

    for (auto a : accessPoints_) {
        access.push_back(a.toJson());
    }
    acc["messageAccessPoints"]= access;
    j= {{"messageId", "wifi"}, {"message", acc}};
    return j;
}

json access_point::toJson()
{

    json j;

    j= {{"essId", essId_}, {"bitrate", "55"/*bitrate_*/}, {"State", "11"/*State_*/}};

    return j;
}

bool Connect(std::string essID, std::string password, std::string ifName)
{

    std::string  command{ "wpa_passphrase " + essID + " " + password + " | tee /etc/wpa_supplicant.conf" };
    system(command.c_str());


    command = {"wpa_supplicant -i" + ifName + "-c /etc/wpa_supplicant.conf -B"};
    system(command.c_str());

    command = {"udhcpc -b -i" + ifName};
    system(command.c_str());

    return false;
}
