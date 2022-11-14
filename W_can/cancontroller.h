#pragma once

#include <linux/can.h>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <thread>

using ReadCallback = std::function<void(canid_t can_id, const std::vector<unsigned char>&)>;

namespace CAN
{

class CanController
{
public:
    explicit CanController(const std::string& ifrname);
    ~CanController();
    static void setup(const std::string& ifrname, int bitrate);

    void start();
    void stop();

    void set_read_callback(ReadCallback readCallback);
    void send(canid_t can_id, const std::vector<unsigned char>& data);
private:
    bool run_flag;
    std::thread *receive_thread;
    void receive();
    ReadCallback _readCallback;
    int can_file;
};
}

