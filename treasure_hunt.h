#ifndef UNTITLED67_TREASURE_HUNT_H
#define UNTITLED67_TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"

using std::same_as;

template <typename T>
concept isTreasure = (requires {
                       same_as<T, Treasure<int, false>>;
                     }) ||
                     (requires {
                       same_as<T, Treasure<int, true>>;
                     });

template <typename T>
concept isAdventurer = requires(T t)
{
  typename T::strength_t;
  same_as<bool, decltype(t.isArmed)>;
  integer<decltype(t.pay())>;
  t.loot((Treasure<int, true>){t.pay(), true}) ||
      t.loot((Treasure<int, false>){t.pay(), false});
};

template <typename T>
concept EncounterSide = requires
{
  isTreasure<T>;
}
|| requires
{
  isAdventurer<T>;
};

/*template <typename A, typename B>
requires EncounterSide<A> || EncounterSide<B>

using Encounter = std::pair<A, B>;*/
// Zdarzenia
template <EncounterSide A, EncounterSide B>
using Encounter = std::pair<A, B>;

constexpr Treasure<int, false> t1(5);

// run()
template <EncounterSide A, EncounterSide B>
requires requires
{
  isAdventurer<A>;
  isAdventurer<B>;
}
constexpr void run(Encounter<A, B> encounter)
{
  if (encounter.first.isArmed && !encounter.second.isArmed)
  {
    encounter.first.loot(Treasure<decltype(encounter.second.pay()), false>(encounter.second.pay()));
  }
  else if (!encounter.first.isArmed && encounter.second.isArmed)
  {
    encounter.second.loot(Treasure<decltype(encounter.first.pay()), false>(encounter.first.pay()));
  }
  else
  {
    if (encounter.first.getStrength() > encounter.second.getStrength())
    {
      encounter.first.loot(Treasure<decltype(encounter.second.pay()), false>(encounter.second.pay()));
    }
    else if (encounter.first.getStrength() < encounter.second.getStrength())
    {
      encounter.second.loot(Treasure<decltype(encounter.first.pay()), false>(encounter.first.pay()));
    }
  }
}

template <EncounterSide A, EncounterSide B>
requires requires
{
  isAdventurer<A>;
  isTreasure<B>;
}
constexpr void run(Encounter<A, B> encounter)
{
  encounter.first.loot(encounter.second.getLoot());
}

template <EncounterSide A, EncounterSide B>
requires requires
{
  isTreasure<A>;
  isAdventurer<B>;
}
constexpr void run(Encounter<A, B> encounter)
{
  encounter.second.loot(encounter.first.getLoot());
}

template <isTreasure A, isTreasure B>
constexpr void run(Encounter<A, B> encounter)
{
  std::cout << same_as<A, Treasure<int, false>> << " " << same_as<B, Treasure<int, true>> << std::endl;
  std::cout << isTreasure<A> << " " << isTreasure<B> << std::endl;
  // 2 Treasurees
  (void)encounter;
  std::cerr << "Can't realize" << std::endl;
  exit(-1);
}

// expedition()

template <typename Encounter>
constexpr void expedition(Encounter t)
{
  run(t);
}

template <typename Encounter, typename... Args>
constexpr void expedition(Encounter t, Args... args)
{
  run(t);
  expedition(args...);
}

#endif // UNTITLED67_TREASURE_HUNT_H
