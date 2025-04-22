#include "BilliardsScore.h"

BilliardsScore::BilliardsScore(const Configuration& configuration)
	: m_currentValue(0), m_configuration(configuration)
{}

BilliardsScore::~BilliardsScore()
{}

int BilliardsScore::GetCurrentValue() const
{
	return m_currentValue;
}

void BilliardsScore::Add()
{
	IncrementScoreValue(m_configuration.addValue);
}

void BilliardsScore::AddConsecutive()
{
	IncrementScoreValue(m_configuration.consecutiveAddValue);
}

void BilliardsScore::AddLast()
{
	IncrementScoreValue(m_configuration.addLastValue);
}

void BilliardsScore::AddByOtherPlayer()
{
	IncrementScoreValue(m_configuration.addByOtherPlayerValue);
}

void BilliardsScore::SubtractWrong()
{
	IncrementScoreValue(m_configuration.subtractWrongValue);
}


void BilliardsScore::IncrementScoreValue(const int& valueIncrement)
{
	m_currentValue += valueIncrement;
}
