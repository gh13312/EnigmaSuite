#include <include/EnigmaLogger.h>

EnigmaLogger::EnigmaLogger(HWND hwndEnigmaLogs) 
	:m_hwndEnigmaLogs(hwndEnigmaLogs)
{
	m_current_log = m_current_log + "Proxy is currently listening on localhost:8080";
}
void EnigmaLogger::appendToLog(std::string log_msg)
{
	m_current_log += log_msg;
}
std::string EnigmaLogger::getLog()
{
	return m_current_log;
}