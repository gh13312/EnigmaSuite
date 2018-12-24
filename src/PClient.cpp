#include <include/PClient.h>

PClient::PClient(std::string ipAddr, int port)
	:m_ipAddr(ipAddr), m_port(port)
{
	ws.WSStart();
	std::string resolve_name = ResolveName(m_ipAddr);
	SetIPAddr(resolve_name);
	// Log resolved name
}

PClient::~PClient()
{
	ws.WSCleanup();
}

// Add second argument for brower
void PClient::Receive(SOCKET client, SOCKET b_client)
{
	char buf[MAX_RECV_SIZE];
	
	// bytes recv & total bytes recv
	int r_bytes = 0;
	int r_total = 0;

	// bytes sent & total bytes sent
	int s_bytes = 0;
	int s_total = 0;

	// content len recv thus far & total content len recv
	int cl_current = 0;
	int cl_total = 0;

	int current_total = 0;
	std::string msg;

	// keep receiving HTTP until done
	// reimplement this
	do {
		ZeroMemory(buf, MAX_RECV_SIZE);
		// Get message from remote web server
		r_bytes = recv(client, buf, MAX_RECV_SIZE, 0);

		if (r_total < MAX_RECV_SIZE & r_bytes > 0)
		{
			// msg string
			msg = std::string(buf, 0, r_bytes);

			
			/* Get Total Content Length */
			int cl_sindex = msg.find(HTTP_CL_HEADER, 0);
			if (cl_sindex > 0)
			{
				int cl_eindex = msg.find(HTTP_HEADER_SEP, cl_sindex);
				cl_sindex = cl_sindex + HTTP_CL_HEADER.size() + 1;
				int cl_len = cl_eindex - cl_sindex;
				std::string cl_str = msg.substr(cl_sindex, cl_len);

				// convert content len value to int
				std::stringstream cl_stream(cl_str);
				cl_stream >> cl_total;
				current_total = msg.find(HTTP_HEADER_END, 0);
			}
			// get content recv thus far
			cl_current = r_bytes - (current_total + HTTP_HEADER_END.size());		
		}
		else
		{
			// content len count
			cl_current += r_bytes;
			// total byte recv count
			r_total += r_bytes;
		}
		r_total += r_bytes;
		// Forward response to browser client
		s_bytes = send(b_client, buf, r_bytes, 0);
		s_total += s_bytes;

	} while ((cl_current < (cl_total)) && (r_bytes > 0));
	ZeroMemory(buf, MAX_RECV_SIZE);
	// Log total sent to browser
	// Log total recv
	// std::cout << "Total Received from HTTP: " << r_total << std::endl;
	// std::cout << "Total Sent to Browser: " << s_total << std::endl;
}

void PClient::Send(SOCKET client, std::string msg)
{
	// Send request to remote server
	int c_send = send(client, msg.c_str(), msg.size(), 0);
}

std::string PClient::GetIPAddr()
{
	return m_ipAddr;
}
void PClient::SetIPAddr(std::string ipAddr)
{
	m_ipAddr = ipAddr;
}

SOCKET PClient::CreateConnection()
{
	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in c_addr;
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddr.c_str(), &c_addr.sin_addr.S_un.S_addr);

	int c_addr_size = sizeof(c_addr);
	int c_connect = connect(client, (sockaddr*)&c_addr, c_addr_size);
	if (c_connect == SOCKET_ERROR)
	{
		// LOG cannot connect
	}
	return client;
}

/* Resolve domain name to IP address
STRING: IP Address string */
std::string PClient::ResolveName(std::string name)
{
	struct addrinfo* name_ai;
	getaddrinfo(name.c_str(), NULL, NULL, &name_ai);
	struct sockaddr_in * name_sa = (struct sockaddr_in *)name_ai->ai_addr;

	char host[NI_MAXHOST];
	inet_ntop(AF_INET, &name_sa->sin_addr.S_un.S_addr, host, NI_MAXHOST);

	return host;
}