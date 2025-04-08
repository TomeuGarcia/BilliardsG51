#pragma once


class BilliardsScore
{
public:
	struct Configuration
	{
	public:
		int p_addValue;
		int p_consecutiveAddValue;
		int p_addLastValue;
	};

public:
	BilliardsScore(const Configuration& configuration);
	~BilliardsScore();

	int GetCurrentValue() const;

	void Add();
	void AddConsecutive();
	void AddLast();


private:
	int m_currentValue;

	Configuration m_configuration;
};