#include <include/EnigmaRepeater.h>

EnigmaRepeater::EnigmaRepeater(std::string ipAddr, int port)
	:m_ipAddr(ipAddr), m_port(port)
{
	ws.WSStart();
	// resolve QDN to IP addr
	std::string resolve_name = ResolveName(m_ipAddr);
	// set IP address
	SetIPAddr(resolve_name);
}

EnigmaRepeater::~EnigmaRepeater()
{
	ws.WSCleanup();
}

SOCKET EnigmaRepeater::CreateConnection()
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
		// TODO: log it
	}
	
	// timeout
	DWORD timeout = 1 * 1000;
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	return client;
}

void EnigmaRepeater::Receive(SOCKET client, HWND hwndRepeaterRes)
{
	char buf[MAX_RECV_SIZE];
	// bytes recv & total bytes recv
	int r_bytes = 0;
	int r_total = 0;
	// content len recv thus far & total content len recv
	int cl_current = 0;
	int cl_total = 0;

	// write to Edit Control
	SendMessage(hwndRepeaterRes, WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	int pos;
	std::string msg;
	do {
		ZeroMemory(buf, MAX_RECV_SIZE);
		r_bytes = recv(client, buf, 8192, 0);

		// first recv contains HTTP headers & get expected content length
		if (r_total < MAX_RECV_SIZE)
		{
			// msg string
			msg = std::string(buf, 0, r_bytes);

			/* Get Total Content Length */	
			int cl_sindex = msg.find(HTTP_CL_HEADER, 0);
			int cl_eindex = msg.find(HTTP_HEADER_SEP, cl_sindex);
			cl_sindex = cl_sindex + HTTP_CL_HEADER.size() + 1;
			int cl_len = cl_eindex - cl_sindex;
			std::string cl_str = msg.substr(cl_sindex, cl_len);

			// convert content len value to int
			std::stringstream cl_stream(cl_str);
			cl_stream >> cl_total;

			// get content recv thus far
			int current_total = msg.find(HTTP_HEADER_END, 0);
			cl_current = r_bytes - (current_total + HTTP_HEADER_END.size());

			// set text limit
			int hdr_size = current_total + HTTP_HEADER_END.size();
			int total = r_bytes + cl_total;
			SendMessage(hwndRepeaterRes, EM_SETLIMITTEXT, total, 0);

			// total byte count
			r_total += r_bytes;
		}
		else
		{
			// msg string
			msg = std::string(buf, 0, r_bytes);
			// content len count
			cl_current += r_bytes;
			// total byte recv count
			r_total += r_bytes;
		}
		// write response to file
		msg += "\r\n";
		pos = GetWindowTextLength(hwndRepeaterRes);
		SendMessage(hwndRepeaterRes, EM_SETSEL, pos, pos);
		SendMessage(hwndRepeaterRes, EM_REPLACESEL, false, (LPARAM)msg.c_str());
	} while (cl_current < cl_total);
	// TODO log recv bytes
}

void EnigmaRepeater::Send(SOCKET client, std::string msg)
{
	int c_send = send(client, msg.c_str(), msg.size(), 0);
	// TODO log it
}


std::string EnigmaRepeater::ResolveName(std::string name)
{
	struct addrinfo* name_ai;
	getaddrinfo(name.c_str(), NULL, NULL, &name_ai);

	struct sockaddr_in* name_sa = (struct sockaddr_in*)name_ai->ai_addr;
	char host[NI_MAXHOST];
	inet_ntop(AF_INET, &name_sa->sin_addr.S_un.S_addr, host, NI_MAXHOST);

	return host;
}

void EnigmaRepeater::SetIPAddr(std::string ipAddr)
{
	m_ipAddr = ipAddr;
}

std::string EnigmaRepeater::GetIPAddr()
{
	return m_ipAddr;
}