#include "NapiUtil.h"

// Node.js headers
#include <node_api.h>

// DDCut Headers
#include "DDCutDaemon.h"
#include "DDLogger/DDLogger.h"

void Execute_InitializeDaemon(napi_env env, void* data)
{
	DDCutDaemon::GetInstance().Initialize();
}

void Complete_InitializeDaemon(napi_env env, napi_status status, void* data)
{
	NAPIContext* pContext = (NAPIContext*)data;

	napi_value callback;
	napi_get_reference_value(env, pContext->m_callback, &callback);

	napi_value global;
	napi_get_global(env, &global);

	napi_value result;
	napi_call_function(env, global, callback, 0, nullptr, &result);

	napi_delete_reference(env, pContext->m_callback);
	napi_delete_async_work(env, pContext->m_asyncWork);

	delete pContext;
}

napi_value InitializeDaemon(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status);

	napi_value resourceName;
	const std::string initializeStr = "INITIALIZE";
	status = napi_create_string_utf8(env, initializeStr.c_str(), initializeStr.size(), &resourceName);

	NAPIContext* pContext = new NAPIContext();

	status = napi_create_reference(env, args[0], 1, &pContext->m_callback);
	status = napi_create_async_work(env, NULL, resourceName, Execute_InitializeDaemon, Complete_InitializeDaemon, pContext, &pContext->m_asyncWork);
	status = napi_queue_async_work(env, pContext->m_asyncWork);

	return nullptr;
}

napi_value GetDDFile(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	DDFile* ddFile = daemon.GetDDFile();

	if (ddFile != nullptr)
	{
		status = napi_create_string_utf8(env, ddFile->GetPath().c_str(), ddFile->GetPath().size(), &result);
	}
	else
	{
		status = napi_create_string_utf8(env, "", 0, &result);
	}

	ASSERT_STATUS(status)
	return result;
}

napi_value SetDDFile(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	std::string ddFile;
	NAPI_GET_STRING(env, args[0], ddFile)

	const bool ddFileSet = DDCutDaemon::GetInstance().SetDDFile(ddFile);
	status = napi_get_boolean(env, ddFileSet, &result);
	ASSERT_STATUS(status)

	return result;
}

napi_value IsValidDDFile(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	std::string ddFile;
	NAPI_GET_STRING(env, args[0], ddFile)

	const bool valid = DDCutDaemon::GetInstance().IsValidDDFile(ddFile);

	status = napi_get_boolean(env, valid, &result);
	ASSERT_STATUS(status)

	return result;
}

napi_value GetGhostGunnerStatus(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	status = napi_create_int32(env, daemon.GetGhostGunnerStatus(), &result);

	return result;
}

napi_value GetAvailableGhostGunners(napi_env env, napi_callback_info info)
{
	napi_status status;

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const std::list<GhostGunner> availableGhostGunners = daemon.GetAvailableGhostGunners();

	napi_value ghostGunnersArray;
	status = napi_create_array_with_length(env, availableGhostGunners.size(), &ghostGunnersArray);
	ASSERT_STATUS(status)

	int i = 0;
	for (auto iter = availableGhostGunners.cbegin(); iter != availableGhostGunners.cend(); iter++)
	{
		const GhostGunner ghostGunner = *iter;

		napi_value ghostGunnerObj;
		status = napi_create_object(env, &ghostGunnerObj);
		ASSERT_STATUS(status)

		napi_value serialNumber;
		status = napi_create_string_utf8(env, ghostGunner.GetSerialNumber().c_str(), ghostGunner.GetSerialNumber().size(), &serialNumber);
		ASSERT_STATUS(status)
		status = napi_set_named_property(env, ghostGunnerObj, "serial_number", serialNumber);
		ASSERT_STATUS(status)

		napi_value path;
		status = napi_create_string_utf8(env, ghostGunner.GetPath().c_str(), ghostGunner.GetPath().size(), &path);
		ASSERT_STATUS(status)
		napi_set_named_property(env, ghostGunnerObj, "path", path);
		ASSERT_STATUS(status)

		status = napi_set_element(env, ghostGunnersArray, i++, ghostGunnerObj);
		ASSERT_STATUS(status)
	}

	return ghostGunnersArray;
}

napi_value GetJobs(napi_env env, napi_callback_info info)
{
	napi_status status;

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const std::vector<Job> jobs = daemon.GetJobs();

	napi_value jobsArray;
	status = napi_create_array_with_length(env, jobs.size(), &jobsArray);
	ASSERT_STATUS(status)

	int i = 0;
	for (auto iter = jobs.cbegin(); iter != jobs.cend(); iter++)
	{
		const Job job = *iter;

		napi_value jobObj;
		status = napi_create_object(env, &jobObj);
		ASSERT_STATUS(status)

		napi_value title;
		status = napi_create_string_utf8(env, job.GetTitle().c_str(), job.GetTitle().size(), &title);
		ASSERT_STATUS(status)
		status = napi_set_named_property(env, jobObj, "title", title);
		ASSERT_STATUS(status)

		napi_value prompt;
		status = napi_create_string_utf8(env, job.GetPrompt().c_str(), job.GetPrompt().size(), &prompt);
		ASSERT_STATUS(status)
		napi_set_named_property(env, jobObj, "prompt", prompt);
		ASSERT_STATUS(status)

		status = napi_set_element(env, jobsArray, i++, jobObj);
		ASSERT_STATUS(status)
	}


	return jobsArray;
}

napi_value SelectJob(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	int32_t jobIndex;
	status = napi_get_value_int32(env, args[0], &jobIndex);
	ASSERT_STATUS(status)

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const bool success = daemon.SelectJob(jobIndex);

	status = napi_get_boolean(env, success, &result);
	ASSERT_STATUS(status)

	return result;
}

napi_value GetAllSteps(napi_env env, napi_callback_info info)
{
	napi_status status;

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const std::vector<Operation> steps = daemon.GetAllSteps();

	napi_value stepsArray;
	status = napi_create_array_with_length(env, steps.size(), &stepsArray);
	ASSERT_STATUS(status)

	for (size_t i = 0; i < steps.size(); i++)
	{
		const Operation& step = steps[i];

		napi_value stepObj;
		status = napi_create_object(env, &stepObj);
		ASSERT_STATUS(status)

		napi_value title;
		status = napi_create_string_utf8(env, step.GetTitle().c_str(), step.GetTitle().size(), &title);
		ASSERT_STATUS(status)
		status = napi_set_named_property(env, stepObj, "Title", title);
		ASSERT_STATUS(status)

		status = napi_set_element(env, stepsArray, i, stepObj);
		ASSERT_STATUS(status)
	}

	return stepsArray;
}

napi_value GetStep(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value stepObj;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	int32_t stepIndex;
	status = napi_get_value_int32(env, args[0], &stepIndex);
	ASSERT_STATUS(status)

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	std::unique_ptr<Operation> pOperation = daemon.GetStep(stepIndex);
	if (pOperation != nullptr)
	{
		status = napi_create_object(env, &stepObj);
		ASSERT_STATUS(status)

		napi_value title;
		status = napi_create_string_utf8(env, pOperation->GetTitle().c_str(), pOperation->GetTitle().size(), &title);
		ASSERT_STATUS(status)
		status = napi_set_named_property(env, stepObj, "Title", title);
		ASSERT_STATUS(status)

		napi_value prompt;
		status = napi_create_string_utf8(env, pOperation->GetPrompt().c_str(), pOperation->GetPrompt().size(), &prompt);
		ASSERT_STATUS(status)
		status = napi_set_named_property(env, stepObj, "Prompt", prompt);
		ASSERT_STATUS(status)

		if (pOperation->Load())
		{
			if (pOperation->GetGCodeFile().getLines().size() > 0)
			{
				const GCodeFile& gcodeFile = pOperation->GetGCodeFile();

				std::string gcodeStr = "";
				for (auto iter = gcodeFile.getLines().cbegin(); iter != gcodeFile.getLines().cend(); iter++)
				{
					gcodeStr += iter->GetOriginal();
					gcodeStr += "<br/>"; // TODO: Return array instead, and have front-end add <br/> and step numbering.
				}

				napi_value gcode;
				status = napi_create_string_utf8(env, gcodeStr.c_str(), gcodeStr.size(), &gcode);
				ASSERT_STATUS(status)
				status = napi_set_named_property(env, stepObj, "GCode", gcode);
				ASSERT_STATUS(status)
			}

			if (pOperation->GetImage().size() > 0)
			{
				napi_value image;
				const std::string imageBase64 = pOperation->GetImageBase64();
				status = napi_create_string_utf8(env, imageBase64.c_str(), imageBase64.size(), &image);
				ASSERT_STATUS(status)
				status = napi_set_named_property(env, stepObj, "Image", image);
				ASSERT_STATUS(status)
			}
		}
	}

	return stepObj;
}

napi_value StartMilling(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	int32_t stepIndex;
	status = napi_get_value_int32(env, args[0], &stepIndex);
	ASSERT_STATUS(status)
		
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const bool millingStarted = daemon.StartMilling(stepIndex);

	status = napi_get_boolean(env, millingStarted, &result);
	ASSERT_STATUS(status)

	return result;
}

napi_value GetMillingStatus(napi_env env, napi_callback_info info)
{
	napi_status status;
	napi_value result;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	int32_t stepIndex;
	status = napi_get_value_int32(env, args[0], &stepIndex);
	ASSERT_STATUS(status)

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const MillingStatus millingStatus = daemon.GetMillingStatus(stepIndex);

	// TODO: Return status object, instead of just percentage.
	status = napi_create_uint32(env, millingStatus.GetPercentage(), &result);
	ASSERT_STATUS(status)

	return result;
}

napi_value EmergencyStop(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.EmergencyStop();

	return nullptr;
}

napi_value GetSettings(napi_env env, napi_callback_info info)
{
	napi_status status;

	napi_value settingsObj;
	status = napi_create_object(env, &settingsObj);
	ASSERT_STATUS(status)

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value pauseAfterGCode;
	status = napi_get_boolean(env, daemon.GetPauseAfterGCode(), &pauseAfterGCode);
	ASSERT_STATUS(status)
	status = napi_set_named_property(env, settingsObj, "pauseAfterGCode", pauseAfterGCode);
	ASSERT_STATUS(status)

	napi_value timeout;
	status = napi_create_uint32(env, daemon.GetTimeout(), &timeout);
	ASSERT_STATUS(status)
	status = napi_set_named_property(env, settingsObj, "timeout", timeout);
	ASSERT_STATUS(status)

	napi_value enableSlider;
	status = napi_get_boolean(env, daemon.GetEnableSlider(), &enableSlider);
	ASSERT_STATUS(status)
	status = napi_set_named_property(env, settingsObj, "enable_slider", enableSlider);
	ASSERT_STATUS(status)

	napi_value maxFeedRate;
	status = napi_create_uint32(env, daemon.GetMaxFeedRate(), &maxFeedRate);
	ASSERT_STATUS(status)
	status = napi_set_named_property(env, settingsObj, "maxFeedRate", maxFeedRate);
	ASSERT_STATUS(status)

	return settingsObj;
}

napi_value GetEnableSlider(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value enableSlider;
	napi_status status = napi_get_boolean(env, daemon.GetEnableSlider(), &enableSlider);
	ASSERT_STATUS(status)

	return enableSlider;
}

napi_value GetPauseAfterGCode(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value pauseAfterGCode;
	napi_status status = napi_get_boolean(env, daemon.GetPauseAfterGCode(), &pauseAfterGCode);
	ASSERT_STATUS(status)

	return pauseAfterGCode;
}

napi_value GetMinFeedRate(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value minFeedRate;
	napi_status status = napi_create_uint32(env, daemon.GetMinFeedRate(), &minFeedRate);
	ASSERT_STATUS(status)

	return minFeedRate;
}

napi_value GetMaxFeedRate(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value maxFeedRate;
	napi_status status = napi_create_uint32(env, daemon.GetMaxFeedRate(), &maxFeedRate);
	ASSERT_STATUS(status)

	return maxFeedRate;
}

napi_value GetTimeout(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value timeout;
	napi_status status = napi_get_boolean(env, daemon.GetTimeout(), &timeout);
	ASSERT_STATUS(status)

	return timeout;
}

napi_value GetFeedRate(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value feedRate;
	napi_status status = napi_get_boolean(env, daemon.GetFeedRate(), &feedRate);
	ASSERT_STATUS(status)

	return feedRate;
}

napi_value UpdateSettings(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	std::list<Setting> settings;

	// Pause After GCode
	napi_value pauseProp;
	status = napi_get_named_property(env, args[0], "pauseAfterGCode", &pauseProp);
	ASSERT_STATUS(status)

	napi_valuetype pauseValueType;
	status = napi_typeof(env, pauseProp, &pauseValueType);
	ASSERT_STATUS(status)

	if (pauseValueType == napi_boolean)
	{
		bool pause;
		status = napi_get_value_bool(env, pauseProp, &pause);
		ASSERT_STATUS(status)

		Setting pauseSetting = { "pauseAfterGCode", pause ? "true" : "false" };
		settings.push_back(pauseSetting);
	}

	// Timeout
	napi_value timeoutProp;
	status = napi_get_named_property(env, args[0], "timeout", &timeoutProp);
	ASSERT_STATUS(status)

	napi_valuetype timeoutValueType;
	status = napi_typeof(env, timeoutProp, &timeoutValueType);
	ASSERT_STATUS(status)

	if (timeoutValueType == napi_number)
	{
		uint32_t timeout;
		status = napi_get_value_uint32(env, timeoutProp, &timeout);
		ASSERT_STATUS(status)

		Setting timeoutSetting = { "timeout", std::to_string(timeout) };
		settings.push_back(timeoutSetting);
	}

	// Enable Slider
	napi_value enableSliderProp;
	status = napi_get_named_property(env, args[0], "enable_slider", &enableSliderProp);
	ASSERT_STATUS(status)

	napi_valuetype enableSliderValueType;
	status = napi_typeof(env, enableSliderProp, &enableSliderValueType);
	ASSERT_STATUS(status)

	if (enableSliderValueType == napi_boolean)
	{
		bool enableSlider;
		status = napi_get_value_bool(env, enableSliderProp, &enableSlider);
		ASSERT_STATUS(status)

		Setting enableSliderSetting = { "enable_slider", enableSlider ? "true" : "false" };
		settings.push_back(enableSliderSetting);
	}

	// Max FeedRate
	napi_value maxFeedRateProp;
	status = napi_get_named_property(env, args[0], "maxFeedRate", &maxFeedRateProp);
	ASSERT_STATUS(status)

	napi_valuetype maxFeedRateValueType;
	status = napi_typeof(env, maxFeedRateProp, &maxFeedRateValueType);
	ASSERT_STATUS(status)

	if (maxFeedRateValueType == napi_number)
	{
		uint32_t maxFeedRate;
		status = napi_get_value_uint32(env, maxFeedRateProp, &maxFeedRate);
		ASSERT_STATUS(status)

		Setting maxFeedRateSetting = { "maxFeedRate", std::to_string(maxFeedRate) };
		settings.push_back(maxFeedRateSetting);
	}

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	daemon.UpdateSettings(settings);

	return nullptr;
}

napi_value SetFeedRate(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	int32_t feedRate;
	status = napi_get_value_int32(env, args[0], &feedRate);
	ASSERT_STATUS(status)

	DDCutDaemon::GetInstance().SetFeedRate(feedRate);

	return nullptr;
}

napi_value UploadFirmware(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	AvailableFirmware firmware;

	napi_value versionProperty;
	napi_get_named_property(env, args[0], "Version", &versionProperty);
	NAPI_GET_STRING(env, versionProperty, firmware.VERSION);

	napi_value descriptionProperty;
	napi_get_named_property(env, args[0], "Description", &descriptionProperty);
	NAPI_GET_STRING(env, descriptionProperty, firmware.DESCRIPTION);

	napi_value filesArray;
	napi_get_named_property(env, args[0], "Files", &filesArray);
	uint32_t filesLength;
	napi_get_array_length(env, filesArray, &filesLength);

	for (size_t i = 0; i < filesLength; i++)
	{
		napi_value file;
		napi_get_element(env, filesArray, i, &file);

		std::string fileURL;
		NAPI_GET_STRING(env, file, fileURL)

		firmware.FILES.emplace_back(fileURL);
	}

	const bool uploaded = DDCutDaemon::GetInstance().UploadFirmware(firmware);

	napi_value result;
	napi_get_boolean(env, uploaded, &result);

	return result;
}

napi_value GetFirmwareUploadStatus(napi_env env, napi_callback_info info)
{
	DDCutDaemon& daemon = DDCutDaemon::GetInstance();

	napi_value firmwareUploadStatus;
	napi_status status = napi_create_uint32(env, daemon.GetFirmwareUploadStatus(), &firmwareUploadStatus);
	ASSERT_STATUS(status)

	return firmwareUploadStatus;
}

napi_value GetFirmwareVersion(napi_env env, napi_callback_info info)
{
	napi_status status;

	DDCutDaemon& daemon = DDCutDaemon::GetInstance();
	const FirmwareVersion version = daemon.GetFirmwareVersion();

	napi_value firmwareVersionObj;
	status = napi_create_object(env, &firmwareVersionObj);
	ASSERT_STATUS(status)

	napi_value grblVersion;
	status = napi_create_string_utf8(env, version.grblVersion.c_str(), version.grblVersion.size(), &grblVersion);
	ASSERT_STATUS(status)
	status = napi_set_named_property(env, firmwareVersionObj, "grblVersion", grblVersion);
	ASSERT_STATUS(status)

	napi_value ddVersion;
	status = napi_create_string_utf8(env, version.ddVersion.c_str(), version.ddVersion.size(), &ddVersion);
	ASSERT_STATUS(status)
	status = napi_set_named_property(env, firmwareVersionObj, "ddVersion", ddVersion);
	ASSERT_STATUS(status)

	return firmwareVersionObj;
}

struct GetFirmwareUpdatesContext
{
	NAPIContext m_napiContext;
	std::vector<AvailableFirmware> m_availableFirmware;
};

void Execute_GetAvailableFirmwareUpdates(napi_env env, void* data)
{
	GetFirmwareUpdatesContext* pContext = (GetFirmwareUpdatesContext*)data;
	pContext->m_availableFirmware = DDCutDaemon::GetInstance().GetAvailableFirmwareUpdates();
}

void Complete_GetAvailableFirmwareUpdates(napi_env env, napi_status status, void* data)
{
	GetFirmwareUpdatesContext* pContext = (GetFirmwareUpdatesContext*)data;

	napi_value callback;
	napi_get_reference_value(env, pContext->m_napiContext.m_callback, &callback);

	napi_value global;
	napi_get_global(env, &global);

	std::vector<AvailableFirmware> available = pContext->m_availableFirmware;

	napi_value availableArray;
	napi_create_array_with_length(env, available.size(), &availableArray);

	for (size_t i = 0; i < available.size(); i++)
	{
		const AvailableFirmware& availableFirmware = available[i];

		napi_value firmwareObj;
		napi_create_object(env, &firmwareObj);

		napi_value version;
		napi_create_string_utf8(env, availableFirmware.VERSION.c_str(), availableFirmware.VERSION.size(), &version);
		napi_set_named_property(env, firmwareObj, "Version", version);

		napi_value description;
		napi_create_string_utf8(env, availableFirmware.DESCRIPTION.c_str(), availableFirmware.DESCRIPTION.size(), &description);
		napi_set_named_property(env, firmwareObj, "Description", description);

		napi_value filesArray;
		napi_create_array_with_length(env, availableFirmware.FILES.size(), &filesArray);

		for (size_t j = 0; j < availableFirmware.FILES.size(); j++)
		{
			napi_value file;
			napi_create_string_utf8(env, availableFirmware.FILES[j].c_str(), availableFirmware.FILES[j].size(), &file);
			napi_set_element(env, filesArray, j, file);
		}

		napi_set_named_property(env, firmwareObj, "Files", filesArray);
		napi_set_element(env, availableArray, i, firmwareObj);
	}

	napi_value result;
	napi_value args[1] = { availableArray };
	napi_call_function(env, global, callback, 1, args, &result);

	napi_delete_reference(env, pContext->m_napiContext.m_callback);
	napi_delete_async_work(env, pContext->m_napiContext.m_asyncWork);

	delete pContext;
}

napi_value GetAvailableFirmwareUpdates(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status);

	GetFirmwareUpdatesContext* pContext = new GetFirmwareUpdatesContext();

	status = napi_create_reference(env, args[0], 1, &pContext->m_napiContext.m_callback);

	napi_value resourceName;
	const std::string resourceStr = "GET_AVAILABLE_FIRMWARE";
	status = napi_create_string_utf8(env, resourceStr.c_str(), resourceStr.size(), &resourceName);

	status = napi_create_async_work(env, NULL, resourceName, Execute_GetAvailableFirmwareUpdates, Complete_GetAvailableFirmwareUpdates, pContext, &pContext->m_napiContext.m_asyncWork);
	status = napi_queue_async_work(env, pContext->m_napiContext.m_asyncWork);

	return nullptr;
}

struct CustomerSupportContext
{
	NAPIContext m_napiContext;
	std::string m_email;
	std::string m_description;
	bool m_includeLogs;
	std::unique_ptr<CustServiceReqError> m_pError = std::unique_ptr<CustServiceReqError>(nullptr);
};

void Execute_SendCustomerSupportRequest(napi_env env, void* data)
{
	CustomerSupportContext* pContext = (CustomerSupportContext*)data;

	pContext->m_pError = DDCutDaemon::GetInstance().SendCustomerSupportRequest(pContext->m_email, pContext->m_description, pContext->m_includeLogs);
}

void Complete_SendCustomerSupportRequest(napi_env env, napi_status status, void* data)
{
	CustomerSupportContext* pContext = (CustomerSupportContext*)data;

	napi_value callback;
	napi_get_reference_value(env, pContext->m_napiContext.m_callback, &callback);

	napi_value global;
	napi_get_global(env, &global);

	napi_value errorObj;

	if (pContext->m_pError != nullptr)
	{
		napi_create_object(env, &errorObj);

		for (auto iter = pContext->m_pError->ERRORS.cbegin(); iter != pContext->m_pError->ERRORS.cend(); iter++)
		{
			napi_value errorStr;
			napi_create_string_utf8(env, iter->second.c_str(), iter->second.size(), &errorStr);
			napi_set_named_property(env, errorObj, iter->first.c_str(), errorStr);
		}
	}
	else
	{
		napi_get_null(env, &errorObj);
	}

	napi_value result;
	napi_value args[1] = { errorObj };
	napi_call_function(env, global, callback, 1, args, &result);

	napi_delete_reference(env, pContext->m_napiContext.m_callback);
	napi_delete_async_work(env, pContext->m_napiContext.m_asyncWork);

	delete pContext;
}

napi_value SendCustomerSupportRequest(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 4;
	napi_value args[4];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	CustomerSupportContext* pContext = new CustomerSupportContext();

	status = napi_create_reference(env, args[3], 1, &pContext->m_napiContext.m_callback);

	NAPI_GET_STRING(env, args[0], pContext->m_email)
	NAPI_GET_STRING(env, args[1], pContext->m_description)

	status = napi_get_value_bool(env, args[2], &pContext->m_includeLogs);
	ASSERT_STATUS(status)

	napi_value resourceName;
	const std::string resourceStr = "CUSTOMER_SUPPORT";
	status = napi_create_string_utf8(env, resourceStr.c_str(), resourceStr.size(), &resourceName);

	status = napi_create_async_work(env, NULL, resourceName, Execute_SendCustomerSupportRequest, Complete_SendCustomerSupportRequest, pContext, &pContext->m_napiContext.m_asyncWork);
	status = napi_queue_async_work(env, pContext->m_napiContext.m_asyncWork);

	return nullptr;
}

napi_value ShouldShowWalkthrough(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)
	
	std::string walkthrough;
	NAPI_GET_STRING(env, args[0], walkthrough)

	EWalkthroughType walkthroughType = EWalkthroughType::dashboard;
	if (walkthrough == "Dashboard")
	{
		walkthroughType = EWalkthroughType::dashboard;
	}
	else if (walkthrough == "Milling")
	{
		walkthroughType = EWalkthroughType::milling;
	}

	const bool show = DDCutDaemon::GetInstance().ShouldWalkthroughDisplay(walkthroughType);

	napi_value result;
	status = napi_get_boolean(env, show, &result);
	ASSERT_STATUS(status)

	return result;
}

napi_value SetShowWalkthrough(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 2;
	napi_value args[2];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status)

	std::string walkthrough;
	NAPI_GET_STRING(env, args[0], walkthrough)

	EWalkthroughType walkthroughType = EWalkthroughType::dashboard;
	if (walkthrough == "Dashboard")
	{
		walkthroughType = EWalkthroughType::dashboard;
	}
	else if (walkthrough == "Milling")
	{
		walkthroughType = EWalkthroughType::milling;
	}

	bool show;
	status = napi_get_value_bool(env, args[1], &show);
	ASSERT_STATUS(status)

	DDCutDaemon::GetInstance().SetShowWalkthrough(walkthroughType, show);

	return nullptr;
}

struct SoftwareUpdatesContext
{
	NAPIContext m_napiContext;
	std::unique_ptr<SoftwareUpdateStatus> m_pUpdate;
};

void Execute_CheckForUpdates(napi_env env, void* data)
{
	SoftwareUpdatesContext* pContext = (SoftwareUpdatesContext*)data;
	DDCutDaemon::GetInstance().CheckForUpdates().swap(pContext->m_pUpdate);
}

void Complete_CheckForUpdates(napi_env env, napi_status status, void* data)
{
	SoftwareUpdatesContext* pContext = (SoftwareUpdatesContext*)data;

	napi_value callback;
	napi_get_reference_value(env, pContext->m_napiContext.m_callback, &callback);

	napi_value global;
	napi_get_global(env, &global);

	napi_value availableUpdate = nullptr;
	if (pContext->m_pUpdate != nullptr)
	{
		napi_create_object(env, &availableUpdate);

		napi_value latestVersion;
		const std::string latestVersionStr = pContext->m_pUpdate->LATEST_VERSION;
		napi_create_string_utf8(env, latestVersionStr.c_str(), latestVersionStr.size(), &latestVersion);
		napi_set_named_property(env, availableUpdate, "LATEST_VERSION", latestVersion);

		napi_value releaseNotes;
		const std::string releaseNotesStr = pContext->m_pUpdate->RELEASE_NOTES;
		napi_create_string_utf8(env, releaseNotesStr.c_str(), releaseNotesStr.size(), &releaseNotes);
		napi_set_named_property(env, availableUpdate, "RELEASE_NOTES", releaseNotes);
	}

	napi_value result;
	napi_value args[1] = { availableUpdate };
	napi_call_function(env, global, callback, 1, args, &result);

	napi_delete_reference(env, pContext->m_napiContext.m_callback);
	napi_delete_async_work(env, pContext->m_napiContext.m_asyncWork);

	delete pContext;
}

napi_value CheckForUpdates(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status);

	SoftwareUpdatesContext* pContext = new SoftwareUpdatesContext();

	status = napi_create_reference(env, args[0], 1, &pContext->m_napiContext.m_callback);

	napi_value resourceName;
	const std::string resourceStr = "CHECK_FOR_UPDATES";
	status = napi_create_string_utf8(env, resourceStr.c_str(), resourceStr.size(), &resourceName);

	status = napi_create_async_work(env, NULL, resourceName, Execute_CheckForUpdates, Complete_CheckForUpdates, pContext, &pContext->m_napiContext.m_asyncWork);
	status = napi_queue_async_work(env, pContext->m_napiContext.m_asyncWork);

	return nullptr;
}

struct InstallUpdatesContext
{
	NAPIContext m_napiContext;
	bool m_downloaded;
};

void Execute_InstallUpdates(napi_env env, void* data)
{
	InstallUpdatesContext* pContext = (InstallUpdatesContext*)data;
	pContext->m_downloaded = DDCutDaemon::GetInstance().InstallUpdates();
}

void Complete_InstallUpdates(napi_env env, napi_status status, void* data)
{
	InstallUpdatesContext* pContext = (InstallUpdatesContext*)data;

	napi_value callback;
	napi_get_reference_value(env, pContext->m_napiContext.m_callback, &callback);

	napi_value global;
	napi_get_global(env, &global);

	napi_value downloaded = nullptr;
	napi_get_boolean(env, pContext->m_downloaded, &downloaded);

	napi_value result;
	napi_value args[1] = { downloaded };
	napi_call_function(env, global, callback, 1, args, &result);

	napi_delete_reference(env, pContext->m_napiContext.m_callback);
	napi_delete_async_work(env, pContext->m_napiContext.m_asyncWork);

	delete pContext;
}

napi_value InstallUpdates(napi_env env, napi_callback_info info)
{
	napi_status status;

	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	ASSERT_STATUS(status);

	InstallUpdatesContext* pContext = new InstallUpdatesContext();

	status = napi_create_reference(env, args[0], 1, &pContext->m_napiContext.m_callback);

	napi_value resourceName;
	const std::string resourceStr = "INSTALL_UPDATES";
	status = napi_create_string_utf8(env, resourceStr.c_str(), resourceStr.size(), &resourceName);

	status = napi_create_async_work(env, NULL, resourceName, Execute_InstallUpdates, Complete_InstallUpdates, pContext, &pContext->m_napiContext.m_asyncWork);
	status = napi_queue_async_work(env, pContext->m_napiContext.m_asyncWork);

	return nullptr;
}

napi_value Shutdown(napi_env env, napi_callback_info info)
{
	DDCutDaemon::GetInstance().Shutdown();

	return nullptr;
}

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports)
{
	DDCutDaemon::GetInstance();

	napi_status status;
	napi_property_descriptor descriptors[32] = {
		DECLARE_NAPI_METHOD("Initialize", InitializeDaemon),
		DECLARE_NAPI_METHOD("Shutdown", Shutdown),

		DECLARE_NAPI_METHOD("GetDDFile", GetDDFile),
		DECLARE_NAPI_METHOD("SetDDFile", SetDDFile),
		DECLARE_NAPI_METHOD("IsValidDDFile", IsValidDDFile),

		DECLARE_NAPI_METHOD("GetGhostGunnerStatus", GetGhostGunnerStatus),
		DECLARE_NAPI_METHOD("GetAvailableGhostGunners", GetAvailableGhostGunners),

		DECLARE_NAPI_METHOD("GetFeedRate", GetFeedRate),
		DECLARE_NAPI_METHOD("SetFeedRate", SetFeedRate),

		// Jobs & Operations
		DECLARE_NAPI_METHOD("GetJobs", GetJobs),
		DECLARE_NAPI_METHOD("SetSelectedJob", SelectJob),
		DECLARE_NAPI_METHOD("GetAllSteps", GetAllSteps),
		DECLARE_NAPI_METHOD("GetStep", GetStep),
		DECLARE_NAPI_METHOD("StartMilling", StartMilling),
		DECLARE_NAPI_METHOD("GetMillingStatus", GetMillingStatus),
		DECLARE_NAPI_METHOD("EmergencyStop", EmergencyStop),

		// Settings
		DECLARE_NAPI_METHOD("GetEnableSlider", GetEnableSlider),
		DECLARE_NAPI_METHOD("GetPauseAfterGCode", GetPauseAfterGCode),
		DECLARE_NAPI_METHOD("GetMinFeedRate", GetMinFeedRate),
		DECLARE_NAPI_METHOD("GetMaxFeedRate", GetMaxFeedRate),
		DECLARE_NAPI_METHOD("GetTimeout", GetTimeout),
		DECLARE_NAPI_METHOD("GetSettings", GetSettings),
		DECLARE_NAPI_METHOD("UpdateSettings", UpdateSettings),

		// Firmware
		DECLARE_NAPI_METHOD("UploadFirmware", UploadFirmware),
		DECLARE_NAPI_METHOD("GetFirmwareUploadStatus", GetFirmwareUploadStatus),
		DECLARE_NAPI_METHOD("GetFirmwareVersion", GetFirmwareVersion),
		DECLARE_NAPI_METHOD("GetAvailableFirmwareUpdates", GetAvailableFirmwareUpdates),

		// Support Center
		DECLARE_NAPI_METHOD("SendCustomerSupportRequest", SendCustomerSupportRequest),

		// Walkthroughs
		DECLARE_NAPI_METHOD("ShouldShowWalkthrough", ShouldShowWalkthrough),
		DECLARE_NAPI_METHOD("SetShowWalkthrough", SetShowWalkthrough),

		// Updates
		DECLARE_NAPI_METHOD("CheckForUpdates", CheckForUpdates),
		DECLARE_NAPI_METHOD("InstallUpdates", InstallUpdates)
	};

	status = napi_define_properties(env, exports, 32, descriptors);
	ASSERT_STATUS(status)
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)