#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "eventfinder.h"

using namespace std;
using namespace boost;

std::string exec(const std::string &cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string find_event(std::string name)
{
    auto text = exec("cat /proc/bus/input/devices");
    std::vector<std::string> tokens;

    auto re = boost::regex("\n\n");
    auto re_event = boost::regex("event\\d");
    boost::split_regex(tokens, text, re);
    for (const auto& t : tokens) {
        if (t.find(name) != std::string::npos) {
            boost::smatch what;
            if (boost::regex_search(t, what, re_event)) {
                cout << std::string(what[0].first, what[0].second) << std::endl;
                return "/dev/input/"+ std::string(what[0].first, what[0].second);
            }
        }
    }
    throw std::runtime_error("cannot find event");
}