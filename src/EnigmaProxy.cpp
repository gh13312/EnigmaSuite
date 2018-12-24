#include <include/EnigmaProxy.h>

EnigmaProxy::EnigmaProxy(HWND hwndProxyRequest, HWND hwndButtonSend)
	:m_hwndProxyRequest(hwndProxyRequest), m_hwndButtonSend(hwndButtonSend)
{
}

void EnigmaProxy::StartProxyService()
{
	m_server = PServer(8080);
	
	while (true)
	{
		m_listener = m_server.CreateSocket();
		m_browser = m_server.WaitForConnection(m_listener);
		closesocket(m_listener);

		int r_browser_len = 0;

		do
		{

			//recv string browser
			m_request = m_server.Receive(m_browser);
			r_browser_len = m_request.size();

			// update proxy edited control
			SetWindowText(m_hwndProxyRequest, m_request.c_str());

			// enable forward button
			EnableWindow(m_hwndButtonSend, true);

			// Get the hostname from request
			if (strlen(m_request.c_str()) > 10) {
				m_hostname = GetHostname(m_request);
			}

		} while (r_browser_len > 0);
	}
}

void EnigmaProxy::ForwardReceive()
{
	// Connection to the remote web server
	PClient p_client(m_hostname, 80);
	SOCKET client = p_client.CreateConnection();
	
	// Forward request to the remote webserver
	p_client.Send(client, m_request);
	p_client.Receive(client, m_browser);
	closesocket(client);

	// disable forward button
	EnableWindow(m_hwndButtonSend, false);
}

std::string EnigmaProxy::GetHostname(std::string msg)
{
	// starting index of "Host:"
	int host_sindex = msg.find(HTTP_HOST_HEADER, 0);

	// ending index of "\r\n"
	int host_eindex = msg.find(HTTP_HEADER_SEP, host_sindex);

	// +1 accounts for the space after Host :
	host_sindex = host_sindex + HTTP_HOST_HEADER.size() + 1;

	int host_len = host_eindex - host_sindex;
	std::string hostname = msg.substr(host_sindex, host_len);

	return hostname;
}