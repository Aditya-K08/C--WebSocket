#include "WebSocketClient.h"
#include <websocketpp/common/thread.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <boost/asio.hpp>

WebSocketClient::WebSocketClient() {
    // Initialize WebSocket client
    ws_client.init_asio();
    ws_client.set_open_handler(websocketpp::lib::bind(&WebSocketClient::onOpen, this, websocketpp::lib::placeholders::_1));
    ws_client.set_message_handler(websocketpp::lib::bind(&WebSocketClient::onMessage, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
    ws_client.set_close_handler(websocketpp::lib::bind(&WebSocketClient::onClose, this, websocketpp::lib::placeholders::_1));
    ws_client.set_fail_handler(websocketpp::lib::bind(&WebSocketClient::onFail, this, websocketpp::lib::placeholders::_1));
}

WebSocketClient::~WebSocketClient() {}
void WebSocketClient::connectToServer(const std::string& uri) {
    try {
        // Create a WebSocket client instance
        websocketpp::client<websocketpp::config::asio_client> ws_client;

        // Create an error code object to capture any connection errors
        websocketpp::lib::error_code ec;

        // Create a connection_ptr using get_connection()
        auto con = ws_client.get_connection(uri, ec);

        // Check if there were any connection errors
        if (ec) {
            std::cerr << "Error connecting to server: " << ec.message() << std::endl;
            return;
        }

        // Now connect using the connection_ptr (shared pointer)
        ws_client.connect(con);

        // Run the WebSocket client to handle the connection
        ws_client.run();

    } catch (const std::exception& e) {
        // Handle any exceptions that occur during connection
        std::cerr << "Exception during connection: " << e.what() << std::endl;
    }
}


void WebSocketClient::sendMessage(const std::string& message) {
    try {
        ws_client.send(conn_hdl, message, websocketpp::frame::opcode::text);
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message: " << e.what() << std::endl;
    }
}

void WebSocketClient::startReceiving() {
    ws_client.run();
}

void WebSocketClient::closeConnection() {
    ws_client.close(conn_hdl, websocketpp::close::status::normal, "Normal Closure");
}

void WebSocketClient::onOpen(websocketpp::connection_hdl hdl) {
    std::cout << "Connection established" << std::endl;
}

void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::cout << "Received: " << msg->get_payload() << std::endl;
}

void WebSocketClient::onClose(websocketpp::connection_hdl hdl) {
    std::cout << "Connection closed" << std::endl;
}

void WebSocketClient::onFail(websocketpp::connection_hdl hdl) {
    std::cerr << "Connection failed" << std::endl;
}
