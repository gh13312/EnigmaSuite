#include <include/WSInit.h>

WSInit::WSInit()
{
	success = WSInit::WSStart();
}

/*
Starts up Winsock
returns true if successful
*/
bool WSInit::WSStart()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	bool s_bool = WSAStartup(ver, &data);
	return s_bool;
}

/*
Returns if winsock initialization is successful
*/

bool WSInit::IsSuccess() {
	return success;
}

/*
Cleans up Winsock resources
*/
void WSInit::WSCleanup() {
	WSACleanup();
}