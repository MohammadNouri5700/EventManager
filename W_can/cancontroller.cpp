#include "cancontroller.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <errno.h>
#include <sstream>

using namespace CAN;
using namespace std;

extern int errno;

CanController::CanController(const std::string &ifrname)
{
	if ((can_file = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		perror("Socket");
	}
	struct sockaddr_can addr;
	struct ifreq ifr;

	strcpy(ifr.ifr_name, ifrname.c_str());
	ioctl(can_file, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(can_file, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Bind");
	}
}

CanController::~CanController()
{
	stop();
	if (close(can_file) < 0)
	{
		perror("Close");
	}
}

void CanController::start()
{
	run_flag = true;
	receive_thread = new thread(&CanController::receive, this);
}

void CanController::stop()
{
	run_flag = false;
	if (receive_thread->joinable())
	{
		receive_thread->join();
	};
}

void CanController::set_read_callback(ReadCallback readCallback)
{
	_readCallback = readCallback;
}

void CanController::send(canid_t can_id, const std::vector<unsigned char> &data)
{
	struct can_frame frame;
	frame.can_id = can_id;
	frame.can_dlc = data.size();
	memcpy(frame.data, data.data(), data.size());

	
	//if (write(3, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
	if (write(can_file, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
	{
		perror("Write");
	}
}

void CanController::setup(const std::string &ifrname, int bitrate)
{
	std::ostringstream stringStream;
	stringStream << "ip link set down " << ifrname;
	system(stringStream.str().c_str());
	stringStream << "ip link set " << ifrname << " type can bitrate " << bitrate;
	system(stringStream.str().c_str());
	stringStream.clear();
	stringStream << "ip link set up " << ifrname;
	system(stringStream.str().c_str());
}

void CanController::receive()
{
	struct can_frame frame;
	std::vector<unsigned char> data;
	while (run_flag)
	{
		data.clear();
		int nbytes = read(can_file, &frame, sizeof(struct can_frame));

		if (nbytes < 0)
		{
			perror("Read");
		}

		printf("0x%03X [%d] ", frame.can_id, frame.can_dlc);

		for (int i = 0; i < frame.can_dlc; i++)
		{
			data.push_back(frame.data[i]);
			printf("%d ", frame.data[i]);
		}
		printf("\n");
		_readCallback(frame.can_id, data);
	}
}
