#pragma once

#include <string>

class RestResponse
{
public:
	RestResponse(const unsigned int statusCode, const std::string& statusText, const std::string& responseBody)
		: m_statusCode(statusCode), m_statusText(statusText), m_responseBody(responseBody)
	{

	}

	inline unsigned int GetStatusCode() const { return m_statusCode; }
	inline const std::string& GetStatusText() const { return m_statusText; }
	inline const std::string& GetResponseBody() const { return m_responseBody; }

private:
	unsigned int m_statusCode;
	std::string m_statusText;
	std::string m_responseBody;
};