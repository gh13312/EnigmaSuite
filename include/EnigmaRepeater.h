#pragma once
#include <include/WSInit.h>

class EnigmaRepeater
{
public:
	EnigmaRepeater(std::string ipAddr, int port);
	~EnigmaRepeater();
	
	void Receive(SOCKET client, HWND hwndRepeaterRes);
	void Send(SOCKET client, std::string msg);

	SOCKET CreateConnection();
	std::string ResolveName(std::string name);

	std::string GetIPAddr();
	void SetIPAddr(std::string ipAddr);

private:
	WSInit							ws;
	std::string						m_ipAddr;
	int								m_port;
};