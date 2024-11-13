#include <iostream>
#include <string>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::client;
using websocketpp::connection_hdl;
using websocketpp::frame::opcode::text;

typedef client<websocketpp::config::asio_client> ws_client;
// g++ -std=c++11 -o websocket_client main.cpp -I"C:/Users/adity/webSoc/websocketpp" -I"C:/Users/adity/Downloads/boost_1_86_0/boost_1_86_0" -I"C:/Users/adity/Downloads/openssl-3.3.2/openssl-3.3.2/include" -I"C:/Program Files (x86)/OpenSSL-Win32/include" -L"C:/Program Files (x86)/OpenSSL-Win32/lib/MinGW/x86" -lssl -lcrypto -lboost_system -lpthread -lws2_32


const std::string URI = "ws://echo.websocket.events";


connection_hdl con_hdl;

void on_message(ws_client* c, connection_hdl hdl, ws_client::message_ptr msg) {
    std::cout << "Received: " << msg->get_payload() << std::endl;
}

void on_open(ws_client* c, connection_hdl hdl) {
    con_hdl = hdl;
    std::cout << "Connected to server!" << std::endl;
}

void on_fail(ws_client* c, connection_hdl hdl) {
    std::cout << "Connection failed!" << std::endl;
}

int main() {
    ws_client client;

    client.init_asio();

    client.set_open_handler(bind(&on_open, &client, std::placeholders::_1));
    client.set_fail_handler(bind(&on_fail, &client, std::placeholders::_1));
    client.set_message_handler(bind(&on_message, &client, std::placeholders::_1, std::placeholders::_2));

    try {

        websocketpp::lib::error_code ec;
        ws_client::connection_ptr con = client.get_connection(URI, ec);

        if (ec) {
            std::cout << "Error during connection: " << ec.message() << std::endl;
            return -1;
        }

        client.connect(con);

        std::thread t([&client]() {
            client.run();
        });

        std::string message;
        while (true) {
            std::cout << "Enter message to send to server (or type 'exit' to quit): ";
            std::getline(std::cin, message);

            if (message == "exit") {
                break;
            }

            client.send(con_hdl, message, text);
        }

        client.stop();
        t.join();

    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
