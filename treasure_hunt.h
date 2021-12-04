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
                            t.loot((Treasure<int, true>){t.pay(), true}) ||
                            t.loot((Treasure<int, false>){t.pay(), false})   ;
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
    if((same_as<A, Treasure<int, false> >   ||  same_as<A, Treasure<int, true> >) &&
            (same_as<B, Treasure<int, false> >   ||  same_as<B, Treasure<int, true> >)) {
        //2 Treasurees
        std::cerr << "Can't realize" << std::endl;
        exit(-1);
    }
    else if(same_as<A, Treasure<int, false> >   ||  same_as<A, Treasure<int, true> >) {
            //loot B
            encounter.second.loot(encounter.first.evaluate());
        return;
    } else if(same_as<B, Treasure<int, false> >   ||  same_as<B, Treasure<int, true> >) {
            //loot A
        encounter.first.loot(encounter.second.evaluate());
        return;
    }

    else if(!encounter.first.isArmed() && !encounter.second.isArmed) {
    }
    else if(encounter.first.isArmed() && !encounter.second.isArmed()) {
        encounter.first.loot(encounter.second.pay());
    }
    else if(!encounter.first.isArmed() && encounter.second.isArmed()) {
        encounter.second.loot(encounter.first.pay());
    } else {
        if(encounter.first.getStrength() > encounter.second.getStrength()) {
            encounter.first.loot(encounter.second.pay());
        } else if(encounter.first.getStrength() < encounter.second.getStrength()) {
            encounter.second.loot(encounter.first.pay());
        }
    }


}

//expedition()

template <typename Encounter, typename... Args>
constexpr void expedition(Encounter t, Args ... args) {
    run(t);
    expedition(args...);
}

#endif //UNTITLED67_TREASURE_HUNT_H
