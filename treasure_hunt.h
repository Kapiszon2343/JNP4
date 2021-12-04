#ifndef UNTITLED67_TREASURE_HUNT_H
#define UNTITLED67_TREASURE_HUNT_H

#include "treasure.h"

//Koncept sporkania
template EncounterSide<Treasure>
concept T = std::is_base_of<Treasure>;

template EncounterSide<typename T>
//udostępnia typ o nazwie strenght_t
type_info<decltype(T)>::strenght_t;
//ma isArmed konwertowalny do bool??
is_bool_t<decltype(T)>::is_armed;
//Ma metodę o nazwie pay()
concept T = std::is_base_of<Adventurer, Veteran>::pay();
//Tutaj nie wiem jak zrobić więcej warunków
concept T = std::is_base_of<Adventurer, Veteran>::loot(Treasure);


//Zdarzenia
template Encounter<sideA, sideB>;
concept sideA = std::is_base_of<EncounterSide>;
concept sideB = std::is_base_of<EncounterSide>;

template <typename T>
concept T = std::is_base_of<Encounter<A,B>>;
void run(Encounter<A, B>) {
    //Będzie implementacja metody
}

template <typename T>
void expedition(Encounter<A, B> e, ...) {
    va_list arguments;
    va_start(arguments, e);
    //Implementacja wykonywania zdarzeń po kolei
    f
    va_end (arguments);

}
#endif //UNTITLED67_TREASURE_HUNT_H
