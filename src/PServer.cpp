#include<include/PServer.h>

/* Constructor */
PServer::PServer(int port)
	:m_port(port)
{
	ws.WSStart();
}

PServer::~PServer()
{
	ws.WSCleanup();
}

/*======================
PUBLIC F'n
========================*/

/* Sends msg received from PClient back to browser */
void PServer::Send(SOCKET client, std::string msg)
{
	send(client, msg.c_str(), msg.size(), 0);
}

/* Receives msg from browser
STRING: string received from browser */
std::string PServer::Receive(SOCKET client)
{
	std::string empty_str = "";
	char buf[MAX_RECV_SIZE];

	int r_bytes = 0;
	ZeroMemory(buf, MAX_RECV_SIZE);

	r_bytes = recv(client, buf, MAX_RECV_SIZE, 0);
	if (r_bytes > 0)
	{
		return std::string(buf, 0, r_bytes);
	}
	return empty_str;
}

/* Creates a proxy server
SOCKET: listener */
SOCKET PServer::CreateSocket()
{
	SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in l_addr;
	l_addr.sin_family = AF_INET;
	l_addr.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddr.c_str(), &l_addr.sin_addr.S_un.S_addr);

	//bind
	int l_bind = bind(listener, (sockaddr*)&l_addr, sizeof(l_addr));
	//listen
	int l_listen = listen(listener, SOMAXCONN);
	return listener;
}

/* Accepts client connection
SOCKET: connection from the browser */
SOCKET PServer::WaitForConnection(SOCKET listener)
{
	sockaddr_in c_addr;
	int c_addr_size = sizeof(c_addr);
	SOCKET client = accept(listener, (sockaddr*)&c_addr, &c_addr_size);

	CHAR host[NI_MAXHOST];
	inet_ntop(AF_INET, &c_addr.sin_addr, host, NI_MAXHOST);

//	std::cout << host << " connected on " << ntohs(c_addr.sin_port) << std::endl;
	return client;
}