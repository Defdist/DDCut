#include "FileDownloader.h"

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <fstream>
#include <string>

using namespace std;
using namespace asio;
using asio::ip::tcp;

bool FileDownloader::DownloadFile(const std::string& url, const std::string& outFilePath)
{
	const std::string serverName = "s3.amazonaws.com";
	const std::string getCommand = url.substr(24);

	// TODO: Create directories

	std::ofstream ofs(outFilePath, std::ofstream::out);
	GetFile(serverName, getCommand, ofs);
	ofs.close();

	return true;
}

void FileDownloader::GetFile(const std::string& serverName, const std::string& getCommand, std::ofstream& outFile)
{
	asio::error_code errorCode;
	asio::io_service ioService;
	asio::ssl::context ctx(asio::ssl::context::sslv23);
	ctx.set_default_verify_paths();
	asio::ssl::stream<asio::ip::tcp::socket> socket(ioService, ctx);

	// Get a list of endpoints corresponding to the server name.
	tcp::resolver resolver(ioService);
	tcp::resolver::query query(serverName, "https");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	socket.set_verify_mode(asio::ssl::verify_none);
	auto con = asio::connect(socket.lowest_layer(), endpoint_iterator, errorCode);

	socket.handshake(asio::ssl::stream_base::client, errorCode);

	asio::streambuf request;
	std::ostream request_stream(&request);

	request_stream << "GET " << getCommand << " HTTP/1.1\r\n";
	request_stream << "Host: " << serverName << "\r\n";
	request_stream << "Accept: */*\r\n";
	request_stream << "Connection: close\r\n\r\n\rn";

	// Send the request.
	asio::write(socket, request, errorCode);

	// Read the response status line.
	asio::streambuf response;
	asio::read_until(socket, response, "\r\n", errorCode);

	// Check that response is OK.
	std::istream response_stream(&response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;
	std::string status_message;
	std::getline(response_stream, status_message);

	// Read the response headers, which are terminated by a blank line.
	asio::read_until(socket, response, "\r\n\r\n");

	// Process the response headers.
	std::string header;
	while (std::getline(response_stream, header) && header != "\r")
	{
	}

	// Write whatever content we already have to output.
	if (response.size() > 0)
	{
		outFile << &response;
	}
	// Read until EOF, writing data to output as we go.
	while (asio::read(socket, response, asio::transfer_at_least(1), errorCode))
	{
		outFile << &response;
	}
}