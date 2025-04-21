#pragma once


class BilliardsScore
{
public:
	struct Configuration
	{
	public:
		int addValue;
		int consecutiveAddValue;
		int addLastValue;
		int addByOtherPlayerValue;
		int subtractWrongValue;
	};

public:
	BilliardsScore(const Configuration& configuration);
	~BilliardsScore();

	int GetCurrentValue() const;

	void Add();
	void AddConsecutive();
	void AddLast();
	void AddByOtherPlayer();
	void SubtractWrong();

private:
	void IncrementScoreValue(const int& valueIncrement);


private:
	int m_currentValue;

	Configuration m_configuration;
};