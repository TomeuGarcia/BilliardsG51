#pragma once


enum class GameObjectTag
{
	None = 0,
	Ball = 1 << 0,
};

inline GameObjectTag operator&(const GameObjectTag& a, const GameObjectTag& b)
{
    return static_cast<GameObjectTag>(static_cast<int>(a) & static_cast<int>(b));
}

inline GameObjectTag operator|(const GameObjectTag& a, const GameObjectTag& b)
{
    return static_cast<GameObjectTag>(static_cast<int>(a) | static_cast<int>(b));
}

inline void operator|=(GameObjectTag& a, const GameObjectTag& b)
{
	a = a | b;
}