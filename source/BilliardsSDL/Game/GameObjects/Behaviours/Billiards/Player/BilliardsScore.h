#pragma once


class BilliardsScore
{
public:
	BilliardsScore(const int& addValue, const int& consecutiveAddValue, const int& addLastValue);
	~BilliardsScore();

	int GetCurrentValue() const;

	void Add();
	void AddConsecutive();
	void AddLast();


private:
	int m_currentValue;

	int m_addValue;
	int m_consecutiveAddValue;
	int m_addLastValue;
};