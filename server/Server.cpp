#include "Server.h"
#include <iostream>

#include <boost/thread.hpp>

#include "FileIO.h"

using namespace websocketpp;

void DLCServer::start() {
	boost::thread([this]() {

		try {
			// Logging settings
			mServer.set_access_channels(websocketpp::log::alevel::all);
			mServer.clear_access_channels(websocketpp::log::alevel::frame_payload);

			// Init 
			mServer.init_asio();

			mServer.set_message_handler(std::bind(&DLCServer::onMessage, this, lib::placeholders::_1, lib::placeholders::_2));

			mServer.listen(SERVER_PORT);
			mServer.start_accept();
		
			mServer.run();

		}
		catch (const websocketpp::exception& e) {
			std::cerr << e.what() << std::endl;
		}

	});

	mHexDLC.run();
}

void DLCServer::onMessage(websocketpp::connection_hdl hdl, WebsocketServer::message_ptr msg)
{
	if (msg->get_payload() == "champ") {
		Member champion = mHexDLC.getChampion();
		std::string weights = FileIO::doubleArrayToString(champion.m_network.getWeights());

		mServer.send(hdl, weights, websocketpp::frame::opcode::text);
	}
	else if (msg->get_payload() == "stop") {
		mServer.send(hdl, "Exiting...", websocketpp::frame::opcode::text);
		mHexDLC.stop();
		mServer.stop();
	}
	else if (msg->get_payload() == "gencount") {
		long int generationCount = mHexDLC.getGenerationCount();
		mServer.send(hdl, std::to_string(generationCount), websocketpp::frame::opcode::text);
	}
	else {
		mServer.send(hdl, "Server does not understand the command " + msg->get_payload(), websocketpp::frame::opcode::text);
	}
}