//Craig Bodo, CS 202, May 2018
//This file defines the class interfaces of the hierarcy.
//The hierarchy is as follows:
//Player is the most indirect base class. Avatar inherits from Player. 
//Character inherits from Avatar. History inherits from Character. 
//Chest inherits from History.
#include <iostream>
#include <cctype>
#include <cstring>
#include <stdlib.h>     // for srand and rand
#include <time.h>
using namespace std;

class player
{
  public:
    player();
    player(char * name, char * email);
    player(const player & to_copy);
    ~player();
	  //Functions for Operator Overloading
	  player & operator = (const player &);
    friend ostream & operator << (ostream &, const player &);
    void new_player();
    void remove_player();
    void display();
  protected:
    char * name;
    char * email;
};

class avatar: public player
{
  public:
    avatar();
    avatar(char * handle, char * graphic);
    avatar(const avatar & to_copy);
    ~avatar();
    void new_avatar();
    void remove_avatar();
    void display();
    //Functions for Operator Overloading
    avatar & operator = (const avatar &);
    friend ostream & operator << (ostream &, const avatar &);
  protected:
    char * handle;
    char * graphic;
};

class character: public avatar
{
  public:
    character();
    character(char * character_name, char * appearance);
    character(const character & to_copy);
    ~character();
    void new_character();
    void display();
    //Functions for Operator Overloading
    character & operator = (const character &);
    friend ostream & operator << (ostream &, const character &);
  protected:
    char * character_name;
    char * appearance;
};

class history: public character
{
  public:
    history();
    history(int games_played, int games_won, int time, int points);
    history(const history & to_copy);
    ~history();
    void new_history();
    int random_played();
    int random_won();
    int random_time();
    int random_points();
    void display_history();
    friend ostream & operator << (ostream &, const history &);
  protected:
    int games_played;
    int games_won;
    int time;
    int points;
};

class chest: public history
{
  public:
    chest();
    chest(char * achievement);
    chest(const chest & to_copy);
    ~chest();
    void new_chest();
    void new_achievement();
    void copy(const chest &);
    bool exists();
    //Functions for Operator Overloading
    bool operator < (const chest &);
    bool operator > (const chest &);
    bool operator <= (const chest &);
    bool operator >= (const chest &);
    bool operator == (const chest &) const;
    bool operator != (const chest &);
    chest & operator = (const chest &);
    friend ostream & operator << (ostream &, const chest &);
  protected:
    char * achievement;
};
