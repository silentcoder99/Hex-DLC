#pragma once

#include <server_http.hpp>

#include "HexDLC.h"

#define SERVER_PORT 20046

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

class DLCServer {
public:
	void start();

private:
	HexDLC mHexDLC;

    std::string makeResponse(std::string status, std::string content);

	bool mServerRunning;
	HttpServer mServer;

};
