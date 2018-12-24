#pragma once
#include <include/WSInit.h>

class PClient
{
	public:
		PClient(std::string ipAddr, int port);
		~PClient();

		void Receive(SOCKET client, SOCKET b_client);
		void Send(SOCKET client, std::string msg);

		std::string GetIPAddr();
		void SetIPAddr(std::string ipAddr);

		SOCKET CreateConnection();
		std::string ResolveName(std::string name);


	private:
		WSInit						ws;
		std::string					m_ipAddr;
		int							m_port;
};