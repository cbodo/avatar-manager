//This program allows a client application to track a player's
//gaming statistics via a character avatar. This program is
//designed to demonstrate the use of operator overloading
//and the use of a 2-3 tree abstract data type.
#include "tree.h"

int main()
{
	chest player_one;

	//Initialier for random number generator
	srand (time(NULL));

	//Adds whitespace
	for(int i = 0; i < 100; ++i)
		cout << '\n';

	player_one.new_chest();
	cout << player_one;

	return 0;
}
