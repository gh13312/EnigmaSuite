#pragma once
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <include/CONSTANTS.h>
#include <sstream>

#pragma once
#pragma comment(lib, "Ws2_32.lib")

class WSInit
{
public:
	WSInit();
	bool WSStart();
	void WSCleanup();
	bool IsSuccess();

private:
	bool		success = false;
};