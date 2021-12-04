#ifndef __TREASURE_H__
#define __TREASURE_H__

#include <iostream>

using std::is_integral;

template <typename T>
concept integer = is_integral<T>::value;

template <typename ValueType, bool IsTrapped>
class Treasure
{
private:
  ValueType value;

public:
  constexpr Treasure(ValueType val)
      : value(val) {}

  constexpr ValueType evaluate() const
  {
    return value;
  }

  constexpr ValueType getLoot()
  {
    ValueType tmp = value;
    value = 0;
    return tmp;
  }
};

template <typename ValueType>
using SafeTreasure = Treasure<ValueType, false>;

template <typename ValueType>
using TrappedTreasure = Treasure<ValueType, true>;

#endif // __TREASURE_H__
