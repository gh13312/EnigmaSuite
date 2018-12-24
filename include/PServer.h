#pragma once
#include <include/WSInit.h>

class PServer
{
public:
	// Constructor
	PServer(int port);
	~PServer();
	// Receives request from browser
	std::string Receive(SOCKET client);
	// Sends response from website to browser
	void Send(SOCKET client, std::string msg);
	// Print message to log

	// Create the listener socket
	SOCKET CreateSocket();
	// Waits for a client to connect
	SOCKET WaitForConnection(SOCKET listener);

private:
	WSInit				ws;
	std::string			m_ipAddr = "0.0.0.0";
	int					m_port;
};