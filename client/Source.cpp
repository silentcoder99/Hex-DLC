#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <sstream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

std::string command;

std::string getPopulationInput() {
	std::stringstream ss;
	std::string line;
	while (std::getline(std::cin, line)) {
		ss << line << std::endl;
	}
	return ss.str();
}

void on_open(client* c, websocketpp::connection_hdl h) {
	if (command == "setPopulation") {
		std::string population = getPopulationInput();
		c->send(h, command + "\n" + population, websocketpp::frame::opcode::text);
	}
	else {
		c->send(h, command, websocketpp::frame::opcode::text);
	}
}

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
	
	std::cout << msg->get_payload();
	c->close(hdl, websocketpp::close::status::normal, "got what I need");
	c->stop();
}

int main(int argc, char* argv[]) {
	// Create a client endpoint
	client c;

	std::string uri = "ws://localhost:20046";

	if (argc >= 3) {
		uri = argv[1];

		for (int argIndex = 2; argIndex < argc; argIndex++) {
			command += argv[argIndex];
			if (argIndex != argc - 1) {
				command += " ";
			}
		}

		try {

			c.set_access_channels(websocketpp::log::alevel::none);
			c.clear_access_channels(websocketpp::log::alevel::none);

			// Initialize ASIO
			c.init_asio();

			// Register our message handler
			c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));

			c.set_open_handler(bind(&on_open, &c, ::_1));

			websocketpp::lib::error_code ec;
			client::connection_ptr con = c.get_connection(uri, ec);
			if (ec) {
				std::cout << "could not create connection because: " << ec.message() << std::endl;
				return 0;
			}

			// Note that connect here only requests a connection. No network messages are
			// exchanged until the event loop starts running in the next line.
			c.connect(con);

			// Start the ASIO io_service run loop
			// this will cause a single connection to be made to the server. c.run()
			// will exit when this connection is closed.
			c.run();
		}
		catch (websocketpp::exception const & e) {
			std::cout << e.what() << std::endl;
		}
	}
}
