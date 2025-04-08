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
	m_currentValue += m_configuration.p_addValue;
}

void BilliardsScore::AddConsecutive()
{
	m_currentValue += m_configuration.p_consecutiveAddValue;
}

void BilliardsScore::AddLast()
{
	m_currentValue += m_configuration.p_addLastValue;
}
