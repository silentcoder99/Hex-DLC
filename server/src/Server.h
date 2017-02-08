#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "HexDLC.h"

#define SERVER_PORT 20046

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;

class DLCServer {
public:
	void start();

private:
	void onMessage(websocketpp::connection_hdl hdl, WebsocketServer::message_ptr msg);
	HexDLC mHexDLC;

	bool mServerRunning;
	WebsocketServer mServer;

};