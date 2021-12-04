#ifndef __MEMBER_H__
#define __MEMBER_H__

#include "treasure.h"

using strength_t = int32_t;

template <size_t n>
concept small = n < 25;

namespace
{
	template <size_t N>
	constexpr static size_t fibonacci()
	{
		if constexpr (N > 1)
		{
			return fibonacci<N - 1>() + fibonacci<N - 2>();
		}
		else
		{
			return N;
		}
	}
}

template <integer ValueType, bool IsArmed>
// requires integer<ValueType>
class Adventurer
{
private:
	ValueType treasure;

public:
	constexpr Adventurer()
			: treasure(0) {}

	constexpr bool isArmed() const
	{
		return false;
	}

	constexpr void loot(ValueType &&lootingTreasure)
	{
		if constexpr (!lootingTreasure.IsTrapped)
		{
			treasure += lootingTreasure.loot();
		}
	}

	constexpr ValueType pay() const
	{
		ValueType tmp = treasure;
		treasure = 0;
		return tmp;
	}
};

template <integer ValueType>
class Adventurer<ValueType, true>
{
private:
	ValueType treasure;
	strength_t strength;

public:
	constexpr Adventurer() = delete;

	constexpr Adventurer(strength_t str)
			: treasure(0), strength(str) {}

	constexpr bool isArmed() const
	{
		return true;
	}

	constexpr strength_t getStrength() const
	{
		return strength;
	}

	constexpr void loot(ValueType &&lootingTreasure)
	{
		if constexpr (!lootingTreasure.IsTrapped)
		{
			treasure += lootingTreasure.loot();
		}
		else if constexpr (strength > 0)
		{
			treasure += lootingTreasure.loot();
			strength /= 2;
		}
	}

	constexpr ValueType pay() const
	{
		ValueType tmp = treasure;
		treasure = 0;
		return tmp;
	}
};

template <integer ValueType>
using Explorer = Adventurer<ValueType, false>;

template <integer ValueType, size_t completedExpeditions>
requires small<completedExpeditions>
class Veteran
{
private:
	ValueType treasure;
	strength_t strength;

public:
	constexpr Veteran()
			: treasure(0), strength(fibonacci<completedExpeditions>()) {}

	constexpr bool isArmed() const
	{
		return true;
	}

	constexpr strength_t getStrength() const
	{
		return strength;
	}

	constexpr void loot(ValueType &&lootingTreasure)
	{
		if constexpr (!lootingTreasure.IsTrapped)
		{
			treasure += lootingTreasure.loot();
		}
		else if constexpr (strength > 0)
		{
			treasure += lootingTreasure.loot();
			strength /= 2;
		}
	}

	constexpr ValueType pay() const
	{
		ValueType tmp = treasure;
		treasure = 0;
		return tmp;
	}
};

#endif // __MEMBER_H__
