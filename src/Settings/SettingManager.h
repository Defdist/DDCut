#pragma once

#include "Setting.h"
#include "WalkthroughType.h"

#include <list>
#include <string>
#include <map>

class SettingManager
{
public:
	static SettingManager& GetInstance();

    bool UpdateSettings(const std::list<Setting>& settings);

	bool GetEnableSlider() const;
	void SetEnableSlider(const bool enableSlider);

	bool GetPauseAfterGCode() const;
	void SetPauseAfterGCode(const bool pauseAfterGCode);

	int GetMinFeedRate() const;
	void SetMinFeedRate(const int minFeedRate);

	int GetMaxFeedRate() const;
	void SetMaxFeedRate(const int maxfeedRate);

	int GetTimeout() const;
	void SetTimeout(const int timeout);

	bool GetShowWalkthrough(const EWalkthroughType& type) const;
	void SetShowWalkthrough(const EWalkthroughType& type, const bool show);

private:
	SettingManager();
    std::string GetConfigFilePath() const;
	std::list<Setting> ReadSettingsFromFile() const;

	std::map<std::string, std::string> m_settingsByKey;
};