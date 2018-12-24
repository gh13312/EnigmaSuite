#pragma once
#include <include/WSInit.h>

class EnigmaLogger
{
	public:
		EnigmaLogger(HWND hwndEnigmaLogs);
		void appendToLog(std::string log_msg);
		std::string getLog();

	private:
		HWND							m_hwndEnigmaLogs = 0;
		std::string						m_current_log = "";
};