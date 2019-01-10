#include "SettingManager.h"

#include "Common/OSUtility.h"
#include "Logging/Logger.h"

#include <fstream>

SettingManager& SettingManager::GetInstance()
{
	static SettingManager instance;
	return instance;
}

SettingManager::SettingManager()
{
	std::list<Setting> settings = ReadSettingsFromFile();
	if (settings.empty())
	{
		Logger::GetInstance().Log("ReadSettings() - Config file path does not yet exist. Creating it now.");

		Setting ghostGunnerSetting("GhostGunner", "2.0");
		std::list<Setting> settings = { ghostGunnerSetting };

		UpdateSettings(settings);
	}
	else
	{
		for (auto settingIter = settings.cbegin(); settingIter != settings.cend(); settingIter++)
		{
			Setting setting = *settingIter;
			m_settingsByKey[setting.GetName()] = setting.GetValue();
		}
	}
}

std::list<Setting> SettingManager::ReadSettingsFromFile() const
{
    std::list<Setting> settings;

	const std::string configFilePath = GetConfigFilePath();
	if (!configFilePath.empty())
	{
		FILE* pFile = fopen(configFilePath.c_str(), "r");
		if (pFile != nullptr)
		{
			char cstr[100];
			while (fgets(cstr, 100, pFile) != NULL)
			{
				const std::string line(cstr);
				const int index = line.find("=");
				const std::string key = line.substr(0, index);
				const std::string value = line.substr(index + 1, line.size() - (index + 2));

				const Setting setting(key, value);
				settings.push_back(setting);
				Logger::GetInstance().Log("ReadSettings() - " + line);
			}

			fclose(pFile);
		}
	}
	else
	{
		Logger::GetInstance().Log("ReadSettings() - Config file path was not found.");
	}

    return settings;
}

bool SettingManager::GetEnableSlider() const
{
	if (m_settingsByKey.find("enable_slider") != m_settingsByKey.cend())
	{
		const std::string& value = m_settingsByKey.at("enable_slider");
		if (value == "true")
		{
			return true;
		}
	}

	return false;
}

void SettingManager::SetEnableSlider(const bool enableSlider)
{
	const std::list<Setting> settings = { {"enable_slider", enableSlider ? "true" : "false"} };
	UpdateSettings(settings);
}

bool SettingManager::GetPauseAfterGCode() const
{
	if (m_settingsByKey.find("pauseAfterGCode") != m_settingsByKey.cend())
	{
		const std::string& value = m_settingsByKey.at("pauseAfterGCode");
		if (value == "true")
		{
			return true;
		}
	}

	return false;
}

void SettingManager::SetPauseAfterGCode(const bool pauseAfterGCode)
{
	m_settingsByKey["pauseAfterGCode"] = pauseAfterGCode ? "true" : "false";
}

int SettingManager::GetMinFeedRate() const
{
	if (m_settingsByKey.find("minFeedRate") != m_settingsByKey.cend())
	{
		const std::string& value = m_settingsByKey.at("minFeedRate");
		return std::stoi(value);
	}

	return 30;
}

void SettingManager::SetMinFeedRate(const int minFeedRate)
{
	m_settingsByKey["minFeedRate"] = std::to_string(minFeedRate);
}

int SettingManager::GetMaxFeedRate() const
{
	if (m_settingsByKey.find("maxFeedRate") != m_settingsByKey.cend())
	{
		const std::string& value = m_settingsByKey.at("maxFeedRate");
		return std::stoi(value);
	}

	return 100;
}

void SettingManager::SetMaxFeedRate(const int maxFeedRate)
{
	m_settingsByKey["maxFeedRate"] = std::to_string(maxFeedRate);
}

int SettingManager::GetTimeout() const
{
	if (m_settingsByKey.find("timeout") != m_settingsByKey.cend())
	{
		const std::string& value = m_settingsByKey.at("timeout");
		return std::stoi(value);
	}

	return 580;
}

void SettingManager::SetTimeout(const int timeout)
{
	m_settingsByKey["timeout"] = std::to_string(timeout);
}

bool SettingManager::GetShowWalkthrough(const EWalkthroughType& type) const
{
	std::string settingName;
	if (type == EWalkthroughType::dashboard)
	{
		settingName = "show_dashboard_walkthrough";
	}
	else if (type == EWalkthroughType::milling)
	{
		settingName = "show_milling_walkthrough";
	}

	if (m_settingsByKey.find(settingName) != m_settingsByKey.cend())
	{
		const std::string& value = m_settingsByKey.at(settingName);
		if (value == "false")
		{
			return false;
		}
	}

	return true;
}

void SettingManager::SetShowWalkthrough(const EWalkthroughType& type, const bool show)
{
	if (type == EWalkthroughType::dashboard)
	{
		const std::list<Setting> settings = { {"show_dashboard_walkthrough", show ? "true" : "false"} };
		UpdateSettings(settings);
	}
	else if (type == EWalkthroughType::milling)
	{
		const std::list<Setting> settings = { {"show_milling_walkthrough", show ? "true" : "false"} };
		UpdateSettings(settings);
	}
}

bool SettingManager::UpdateSettings(const std::list<Setting>& settings)
{
	for (auto& setting : settings)
	{
		m_settingsByKey[setting.GetName()] = setting.GetValue();
	}

	const std::string configFilePath = GetConfigFilePath();
	if (configFilePath.empty())
	{
		Logger::GetInstance().Log("UpdateSettings() - Config file path was not found.");
		return false;
	}

	Logger::GetInstance().Log("UpdateSettings() - " + std::to_string(m_settingsByKey.size()));
	FILE* pFile = fopen(configFilePath.c_str(), "w");
	if (pFile != nullptr)
	{
		for (auto iter = m_settingsByKey.cbegin(); iter != m_settingsByKey.cend(); iter++)
		{
			fprintf(pFile, "%s=%s\n", iter->first.c_str(), iter->second.c_str());
		}

		fclose(pFile);
	}

	return true;
}

std::string SettingManager::GetConfigFilePath() const
{
	const std::string execPath = OSUtility::GetExecPath();
	if (execPath.empty())
	{
		Logger::GetInstance().Log("GetConfigFilePath() - Executable path was not found.");
		return "";
	}

#ifdef _WIN32
	return execPath + "\\ghost.conf";
#else
    return execPath + "/ghost.conf";
#endif
}
