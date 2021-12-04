#ifndef UNTITLED67_TREASURE_HUNT_H
#define UNTITLED67_TREASURE_HUNT_H

#include "treasure.h"
#include "member.h"

using std::same_as;


template <typename T>
concept EncounterSide = requires(T t)
                        {
                            same_as<T, Treasure<int, false> > ||
                                       same_as<T, Treasure<int, true> >;
                        }
                        ||
                        requires(T t)
                        {
                            typename T::strength_t;
                            same_as<bool, decltype(t.isArmed)>;
                            integer<decltype(t.pay())>;
                            t.loot((Treasure<decltype(t.evaluate), true>){t.pay(), true}) ||
                            t.loot((Treasure<decltype(t.evaluate), false>){t.pay(), false})   ;
                        };



/*template <typename A, typename B>
requires EncounterSide<A> || EncounterSide<B>
using Encounter = std::pair<A, B>;*/
//Zdarzenia
template <EncounterSide A, EncounterSide B>
using Encounter = std::pair<A, B>;

constexpr Treasure<int, false> t1(5);

//run()

template <EncounterSide A, EncounterSide B>
constexpr void run(Encounter<A, B> encounter)
{
    if(same_as<A,B> && (same_as<A, Treasure<int, false> >   ||  same_as<A, Treasure<int, true> >) &&
       (same_as<B, Treasure<int, false> >   ||  same_as<B, Treasure<int, true> >)) {
        //2 Treasurees
        std::cerr << "Can't realize" << std::endl;
        exit(-1);
    }
    else if(!same_as<A,B> && same_as<A, Treasure<int, false> >   ||  same_as<A, Treasure<int, true> >) {
        //loot B
        encounter.second.loot(encounter.first.evaluate());
    } else if(!same_as<A,B> && same_as<B, Treasure<int, false> >   ||  same_as<B, Treasure<int, true> >) {
        //loot A
        encounter.first.loot(encounter.second.evaluate());
    }

    else if(!encounter.first.isArmed() && !encounter.second.isArmed) {
    }
    else if(encounter.first.isArmed() && !encounter.second.isArmed()) {
        encounter.first.loot(encounter.second);
    }
    else if(!encounter.first.isArmed() && encounter.second.isArmed()) {
        encounter.second.loot(encounter.first);
    } else {
        if(encounter.first.getStrength() > encounter.second.getStrength()) {
            encounter.first.loot(encounter.second);
        } else if(encounter.first.getStrength() < encounter.second.getStrength()) {
            encounter.second.loot(encounter.first);
        }
    }


}

//expedition()

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
#endif //UNTITLED67_TREASURE_HUNT_H
