#pragma once

// Node.js headers
#include <node_api.h>

#include <string>

struct NAPIContext
{
	napi_ref m_callback;
	napi_async_work m_asyncWork;
};

#define ASSERT_STATUS(status) \
	if (status != napi_ok) 	{ \
		napi_throw_error(env, "EINVAL", "Invalid Value"); \
		return nullptr; \
	}

class NapiUtil
{
public:
	static napi_status GetString(napi_env env, napi_value value, std::string& result)
	{
		char cstr[1024];
		size_t cstrLength;
		const napi_status status = napi_get_value_string_utf8(env, value, cstr, 1024, &cstrLength);
		if (status == napi_ok)
		{
			result = std::string(cstr, cstrLength);
		}

		return status;
	}
};

#define NAPI_GET_STRING(env, value, result) ASSERT_STATUS(NapiUtil::GetString(env, value, result))