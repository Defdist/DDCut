#pragma once

#include "RestResponse.h"

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <asio.hpp>
#include <asio/ssl.hpp>

class RestClient
{
public:
	static RestResponse Post(const std::string& path, const std::string& jsonBody);
	static RestResponse Get(const std::string& path);
private:
	RestClient(asio::ssl::stream<asio::ip::tcp::socket>& socket, asio::streambuf& request, asio::streambuf& response);

	RestResponse Resolve(asio::ip::tcp::resolver::iterator endpoint_iterator);
	RestResponse Connect();
	RestResponse Handshake();
	RestResponse WriteRequest();
	RestResponse ReadStatusLine();
	RestResponse ReadHeaders();
	RestResponse ReadContent();

	asio::ssl::stream<asio::ip::tcp::socket>& m_socket;
	asio::streambuf& m_request;
	asio::streambuf& m_response;
};