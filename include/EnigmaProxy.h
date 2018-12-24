#pragma once
#include <include/WSInit.h>
#include <include/PServer.h>
#include <include/PClient.h>
#include <thread>

class EnigmaProxy
{
	public:
		EnigmaProxy(HWND hwndProxyRequest, HWND hwndButtonSend);
		void StartProxyService();
		void ForwardReceive();
		std::string GetHostname(std::string msg);

		std::string gethostname() { return m_hostname; }
		std::string getrequest() { return m_request; }

	private:
		HWND								m_hwndProxyRequest = 0;
		HWND								m_hwndButtonSend = 0;
		PServer								m_server = 0;
		SOCKET								m_listener = 0;
		SOCKET								m_browser = 0;
		std::string							m_hostname = "127.0.0.1";
		std::string							m_request = "Get / HTTP/1.1\r\nHost: 127.0.0.1\r\n";
}; 