#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <string>
#include <iostream>

class WebSocketClient {
public:
    WebSocketClient();
    ~WebSocketClient();

    void connectToServer(const std::string& uri);
    void sendMessage(const std::string& message);
    void startReceiving();
    void closeConnection();

private:
    typedef websocketpp::client<websocketpp::config::asio_client> client;
    client ws_client;
    websocketpp::connection_hdl conn_hdl;

    void onOpen(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg);
    void onClose(websocketpp::connection_hdl hdl);
    void onFail(websocketpp::connection_hdl hdl);
};

#endif
