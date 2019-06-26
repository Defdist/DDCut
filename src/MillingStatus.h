#pragma once

enum EMillingStatus
{
	failed = -1,
	inProgress = 0,
	completed = 1
};

class MillingStatus
{
public:
	MillingStatus(const EMillingStatus status, const int percentage, const std::string& errorMessage)
		: m_status(status), m_percentage(percentage), m_errorMessage(errorMessage)
	{

	}

	inline EMillingStatus GetStatus() const { return m_status; }
	inline int GetPercentage() const { return m_percentage; }
	inline const std::string& GetErrorMessage() const { return m_errorMessage; }

private:
	const EMillingStatus m_status;
	const int m_percentage;
	const std::string m_errorMessage;
};