#include "BilliardsScore.h"

BilliardsScore::BilliardsScore(const int& addValue, const int& consecutiveAddValue, const int& addLastValue)
	: m_currentValue(0), m_addValue(addValue), m_consecutiveAddValue(consecutiveAddValue), m_addLastValue(addLastValue)
{}

BilliardsScore::~BilliardsScore()
{}

int BilliardsScore::GetCurrentValue() const
{
	return m_currentValue;
}

void BilliardsScore::Add()
{
	m_currentValue += m_addValue;
}

void BilliardsScore::AddConsecutive()
{
	m_currentValue += m_consecutiveAddValue;
}

void BilliardsScore::AddLast()
{
	m_currentValue += m_addLastValue;
}
