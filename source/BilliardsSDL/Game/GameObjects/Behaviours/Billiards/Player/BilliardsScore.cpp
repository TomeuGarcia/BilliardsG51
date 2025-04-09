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
	IncrementScoreValue(m_configuration.p_addValue);
}

void BilliardsScore::AddConsecutive()
{
	IncrementScoreValue(m_configuration.p_consecutiveAddValue);
}

void BilliardsScore::AddLast()
{
	IncrementScoreValue(m_configuration.p_addLastValue);
}

void BilliardsScore::AddByOtherPlayer()
{
	IncrementScoreValue(m_configuration.p_addByOtherPlayerValue);
}

void BilliardsScore::IncrementScoreValue(const int& valueIncrement)
{
	m_currentValue += valueIncrement;
}
