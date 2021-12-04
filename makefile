all: hunt_examples

#treasure.o: treasure.h
#	g++-11 -c -DEBUG -Wall -Wextra -O2 -std=c++20 treasure.h -o treasure.o
#member.o: member.h treasure.h
#	g++-11 -c -DEBUG -Wall -Wextra -O2 -std=c++20 member.h -o member.o
#treasure_hunt.o: member.h treasure.h treasure_hunt.h
#	g++-11 -c -DEBUG -Wall -Wextra -O2 -std=c++20 treasure_hunt.h -o treasure_hunt.o
hunt_examples.o: hunt_examples2.cc treasure_hunt.h treasure.h member.h
	g++-11 -c -DEBUG -Wall -Wextra -O2 -std=c++20 hunt_examples2.cc -o hunt_examples.o
hunt_examples: hunt_examples.o
	g++-11 hunt_examples.o -o hunt_examples




clean:
	rm -f *.o line
