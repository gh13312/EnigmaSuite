#pragma once
#include <string>

#define MAX_RECV_SIZE							8192

// HTTP STRING

const std::string HTTP_HEADER_SEP = "\r\n";
const std::string HTTP_HEADER_END = "\r\n\r\n";
const std::string HTTP_HOST_HEADER = "Host:";
const std::string HTTP_CL_HEADER = "Content-Length:";

// GUI strings
const TCHAR* const FILE_MENU = "File";
const TCHAR* const FILE_EXIT = "Exit";

// GUI Controls

#define GUI_DEFAULT_WIDTH						1024
#define GUI_DEFAULT_HEIGHT						760

#define FILE_MENU_EXIT							901

#define TAB_MAIN								1000
#define TAB_PROXY								0
#define TAB_SPIDER								1
#define TAB_REPEATER							2
#define TAB_LOG									3

// PROXY controls, max: 002
#define PROXY_BUTTON_HTTP_REQUEST				001
#define PROXY_EDIT_HTTP_REQUEST					002


#define SPIDER_HTTP_FOUND						101

// REPEATER controls, max: 207
const std::string TMP_FILE_REPEATER				= "~EnigmaRepeater";
const std::string REPEATER_HOST_DEFAULT			= "www.bbc.com";
const std::string REPEATER_PORT_DEFAULT			= "80";
const std::string REPEATER_REQ_DEFAULT			= "GET / HTTP/1.1\r\nHost: www.bbc.com\r\n\r\n";
const std::string REPEATER_RES_DEFAULT			= "";

#define REPEATER_HTTP_REQUEST					201
#define REPEATER_HTTP_RESPONSE					202
#define REPEATER_EDIT_HOST						204
#define REPEATER_EDIT_PORT						205
#define REPEATER_STATIC_HOST					206
#define REPEATER_STATIC_PORT					207
#define REPEATER_BUTTON_HTTP_REQUEST			203

#define LOG_INFO_FIELD							301