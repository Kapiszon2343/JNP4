#include "treasure_hunt.h"
#include <cstdint>

constexpr int soloHunt()
{
  Explorer<int> a;
  // Adventurer<int, true> a2 = {1};
  Treasure<int, false> t1(5);
  Treasure<int, false> t2(6);
  SafeTreasure<int> t3(7);
  TrappedTreasure<int> t4(10);

  // Encounter<decltype(a), decltype(a2)> e = {a, a2};

  Encounter<decltype(a), decltype(t1)> e1 = {a, t1};
  Encounter<decltype(t2), decltype(a)> e2 = {t2, a};
  Encounter<decltype(t3), decltype(a)> e3 = {t3, a};
  Encounter<decltype(a), decltype(t4)> e4 = {a, t4};

  // run(e);
  expedition(e1);
  // expedition(e1, e2, e3, e4);

  return a.pay(); // 18
}

int main()
{
  std::cout << soloHunt();
  return 0;
}