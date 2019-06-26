#include "RestClient.h"
#include "AuthKey.h"

static const std::string SERVER = "ddservices.deathathletic.com";

RestClient::RestClient(asio::ssl::stream<asio::ip::tcp::socket>& socket, asio::streambuf& request, asio::streambuf& response)
	: m_socket(socket), m_request(request), m_response(response)
{

}

RestResponse RestClient::Get(const std::string& path)
{
	asio::io_service ioService;
	asio::ssl::context ctx(asio::ssl::context::sslv23);
	ctx.set_default_verify_paths();
	asio::ssl::stream<asio::ip::tcp::socket> socket(ioService, ctx);

	asio::streambuf request;
	asio::streambuf response;

	// Form the request. We specify the "Connection: close" header so that the
	// server will close the socket after transmitting the response. This will
	// allow us to treat all data up until the EOF as the content.
	std::ostream requestStream(&request);
	requestStream << "GET " << path << " HTTP/1.1\r\n";
	requestStream << "Host: " << SERVER << "\r\n";
	requestStream << "Accept: application/json\r\n";
	requestStream << "Authorization:Basic " << AUTH_KEY << "\r\n";
	requestStream << "Content-Type: application/json\r\n";
	requestStream << "Content-Length: 0\r\n";
	requestStream << "Connection: close\r\n\r\n\r\n";

	// Start a synchronous resolve to translate the server and service names
	// into a list of endpoints.
	asio::ip::tcp::resolver::query query(SERVER, "https");

	RestClient client(socket, request, response);

	asio::ip::tcp::resolver resolver(ioService);
	auto res = resolver.resolve(query);

	return client.Resolve(res);
}

RestResponse RestClient::Post(const std::string& path, const std::string& jsonBody)
{
	asio::io_service ioService;
	asio::ssl::context ctx(asio::ssl::context::sslv23);
	ctx.set_default_verify_paths();
	asio::ssl::stream<asio::ip::tcp::socket> socket(ioService, ctx);

	asio::streambuf request;
	asio::streambuf response;

	// Form the request. We specify the "Connection: close" header so that the
	// server will close the socket after transmitting the response. This will
	// allow us to treat all data up until the EOF as the content.
	std::ostream requestStream(&request);
	requestStream << "POST " << path << " HTTP/1.1\r\n";
	requestStream << "Host: " << SERVER << "\r\n";
	requestStream << "Accept: application/json\r\n";
	requestStream << "Authorization:Basic " << AUTH_KEY << "\r\n";
	requestStream << "Content-Type: application/json\r\n";
	requestStream << "Content-Length: " << jsonBody.size() << "\r\n";
	requestStream << "Connection: close\r\n\r\n";
	requestStream << jsonBody << "\r\n";

	// Start a synchronous resolve to translate the server and service names
	// into a list of endpoints.
	asio::ip::tcp::resolver::query query(SERVER, "https");

	RestClient client(socket, request, response);

	asio::ip::tcp::resolver resolver(ioService);
	auto res = resolver.resolve(query);

	return client.Resolve(res);
}

RestResponse RestClient::Resolve(asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	std::cout << "Resolve OK" << "\n";
	m_socket.set_verify_mode(asio::ssl::verify_none);

	std::error_code err;
	auto con = asio::connect(m_socket.lowest_layer(), endpoint_iterator, err);

	if (err)
	{
		return RestResponse(0, err.message(), "");
	}

	return Connect();
}

RestResponse RestClient::Connect()
{
	std::cout << "Connect OK " << "\n";
	std::error_code err;
	m_socket.handshake(asio::ssl::stream_base::client, err);

	if (err)
	{
		return RestResponse(0, err.message(), "");
	}

	return Handshake();
}

RestResponse RestClient::Handshake()
{
	std::cout << "Handshake OK " << "\n";
	std::cout << "Request: " << "\n";
	const char* header = asio::buffer_cast<const char*>(m_request.data());
	std::cout << header << "\n";

	// The handshake was successful. Send the request.
	std::error_code err;
	auto req = asio::write(m_socket, m_request, err);

	if (err)
	{
		return RestResponse(0, err.message(), "");
	}

	return WriteRequest();
}

RestResponse RestClient::WriteRequest()
{
	// Read the response status line. The m_response streambuf will
	// automatically grow to accommodate the entire line. The growth may be
	// limited by passing a maximum size to the streambuf constructor.
	std::error_code err;
	auto read = asio::read(m_socket, m_response, err);
	//auto read = asio::read_until(m_socket, m_response, "\r\n", err);

	if (err && err.value() != 335544539 && err.value() != 1)
	{
		return RestResponse(0, err.message(), "");
	}

	return ReadStatusLine();
}

RestResponse RestClient::ReadStatusLine()
{
	std::cout << "Response: " << "\n";
	const char* resp = asio::buffer_cast<const char*>(m_response.data());
	std::cout << resp << "\n";

	// Check that response is OK.
	std::istream responseStream(&m_response);

	std::string httpVersion;
	responseStream >> httpVersion;

	unsigned int statusCode;
	responseStream >> statusCode;

	std::string statusMessage;
	std::getline(responseStream, statusMessage);

	if (!responseStream || httpVersion.substr(0, 5) != "HTTP/")
	{
		return RestResponse(0, "Invalid Response", "");
	}

	auto read = asio::read_until(m_socket, m_response, "\r\n\r\n");

	// Process the response headers.
	std::istream m_responsestream(&m_response);
	std::string header;
	while (std::getline(m_responsestream, header) && header != "\r")
	{
		std::cout << header << "\n";
	}
	std::cout << "\n";

	// Write whatever content we already have to output.
	std::stringstream body;
	body << &m_response;

	return RestResponse(statusCode, statusMessage, body.str());

	//if (statusCode != 200)
	//{
	//	std::cout << "Response returned with status code ";
	//	std::cout << statusCode << "\n";
	//	return RestResponse(statusCode, statusMessage, "");
	//}

	//std::cout << "Status code: " << statusCode << "\n";

	//// Read the response headers, which are terminated by a blank line.
	//auto read = asio::read_until(m_socket, m_response, "\r\n\r\n");

	//return ReadHeaders();
}

//RestResponse RestClient::ReadHeaders()
//{
//	// Process the response headers.
//	std::istream m_responsestream(&m_response);
//	std::string header;
//	while (std::getline(m_responsestream, header) && header != "\r")
//	{
//		std::cout << header << "\n";
//	}
//	std::cout << "\n";
//
//	// Write whatever content we already have to output.
//	std::stringstream body;
//	body << &m_response;
//
//	return RestResponse(200, "SUCCESS", body.str());
//}