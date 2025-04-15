#pragma once
#include <memory>
#include <functional>
#include <forward_list>
#include <vector>



template <class T>
class SteppingBuffer
{
public:
	SteppingBuffer(const size_t& stepSize);
		
	void Clear();

	void TryExpand();
	std::vector<T>* GetCurrent();

	void IterateAll(const std::function<void(T&, const size_t& i)>& itCallback);


private:
	void GetTotalCounts(size_t& outCurrentCount, size_t& outCurrentMaxCount) const;

	void Expand();


private:
	size_t m_stepSize;

	std::forward_list<std::shared_ptr<std::vector<T>>> m_buffer;
};




template<class T>
inline SteppingBuffer<T>::SteppingBuffer(const size_t& stepSize)
	: m_stepSize(stepSize), m_buffer()
{
	Expand();
}

template<class T>
void SteppingBuffer<T>::Clear()
{
	for (auto l_it = m_buffer.begin(); l_it != m_buffer.end(); ++l_it)
	{
		l_it->get()->clear();
	}
	m_buffer.clear();
}

template<class T>
void SteppingBuffer<T>::TryExpand()
{
	size_t currentCount{ 0 };
	size_t currentMaxCount{ 0 };
	GetTotalCounts(currentCount, currentMaxCount);

	if (currentCount >= currentMaxCount)
	{
		Expand();
	}
}

template<class T>
std::vector<T>* SteppingBuffer<T>::GetCurrent()
{
	return &*m_buffer.front();
}



template<class T>
void SteppingBuffer<T>::IterateAll(const std::function<void(T&, const size_t& i)>& itCallback)
{
	size_t i{ 0 };

	for (auto l_it = m_buffer.begin(); l_it != m_buffer.end(); ++l_it)
	{
		std::vector<T>* v = l_it->get();
		for (auto v_it = v->begin(); v_it != v->end(); ++v_it)
		{
			itCallback(*v_it, i);
			++i;
		}
	}
}



template<class T>
void SteppingBuffer<T>::GetTotalCounts(size_t& outCurrentCount, size_t& outCurrentMaxCount) const
{
	outCurrentCount = 0;
	outCurrentMaxCount = 0;

	for (auto l_it = m_buffer.begin(); l_it != m_buffer.end(); ++l_it)
	{
		std::vector<T>* v = l_it->get();
		outCurrentCount += v->size();
		outCurrentMaxCount += m_stepSize;
	}
}

template<class T>
void SteppingBuffer<T>::Expand()
{
	auto v = m_buffer.emplace_front(std::make_shared<std::vector<T>>());
	v->reserve(m_stepSize);
}

