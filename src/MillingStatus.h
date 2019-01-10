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
	MillingStatus(const EMillingStatus status, const int percentage)
		: m_status(status), m_percentage(percentage)
	{

	}

	inline EMillingStatus GetStatus() const { return m_status; }
	inline int GetPercentage() const { return m_percentage; }

private:
	const EMillingStatus m_status;
	const int m_percentage;
};