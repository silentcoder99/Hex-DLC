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
	std::string payload = msg->get_payload();
	if (payload == "champ") {
		Member champion = mHexDLC.getChampion();
		std::string weights = FileIO::doubleArrayToString(champion.m_network.getWeights());

		mServer.send(hdl, weights, websocketpp::frame::opcode::text);
	}
	else if (payload == "stop") {
		mServer.send(hdl, "Exiting...", websocketpp::frame::opcode::text);
		mServer.close(hdl, websocketpp::close::status::going_away, "Server closing");
		mHexDLC.stop();
		mServer.stop();
	}
	else if (payload == "genCount") {
		long int generationCount = mHexDLC.getGenerationCount();
		mServer.send(hdl, std::to_string(generationCount), websocketpp::frame::opcode::text);
	}
	else if (payload == "layerSizes") {
		std::vector<int> layerSizes = mHexDLC.getLayerSizes();
		std::stringstream ss;
		for (auto layer : layerSizes) {
			ss << layer << ",";
		}
		mServer.send(hdl, ss.str(), websocketpp::frame::opcode::text);
	}
	else if (payload.find("setGenCount ") == 0) {
		std::string genCountString = payload.substr(12, payload.length() - 12);
		unsigned long int genCount = std::stoul(genCountString);
		mHexDLC.setGenerationCount(genCount);
		mServer.send(hdl, "Set Generation Count to " + std::to_string(genCount), websocketpp::frame::opcode::text);
	}
	else if (payload == "population") {
		Population pop = mHexDLC.getPopulation();
		std::string serializedPop = FileIO::populationToString(pop);
		mServer.send(hdl, serializedPop, websocketpp::frame::opcode::text);
	}
	else if (payload.find("setPopulation") == 0) {
		int firstLineBreak = payload.find_first_of('\n');
		std::string serializedPop = payload.substr(firstLineBreak + 1, payload.length() - firstLineBreak - 1);
		Population pop = FileIO::stringToPopulation(serializedPop);
		mHexDLC.setPopulation(pop);
		mServer.send(hdl, "Population set", websocketpp::frame::opcode::text);
	}
	else if (payload == "runTime") {
		double runTime = mHexDLC.getRunningTime();
		mServer.send(hdl, std::to_string(runTime), websocketpp::frame::opcode::text);
	}
	else if (payload == "getState") {
		std::string state = mHexDLC.getState();
		mServer.send(hdl, state, websocketpp::frame::opcode::text);
	}

	else {
		mServer.send(hdl, "Server does not understand the command " + msg->get_payload(), websocketpp::frame::opcode::text);
	}
}