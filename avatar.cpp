//Craig Bodo, CS 202, May 2018
//This file implements the class member functions of the hierarcy.
#include "avatar.h"

//Player class member function implementations

//Default constructor
player::player() {}

//Constructor with initialization list
player::player(char * name, char * email):
	name(NULL), email(NULL) {}

//Copy constructor
player::player(const player & to_copy):
	name(NULL), email(NULL)
{
	name = to_copy.name;
	email = to_copy.email;
}

//Destructor
player::~player()
{
	if(name)
	{
		delete [] name;
		name = NULL;
	}
	if(email)
	{
		delete [] email;
		email = NULL;
	}
}

//Adds new player
void player::new_player()
{
	char temp_name[100];
	char temp_email[200];

	cout << "Player Information" << endl;

	cout << "\nPlease enter your name: ";
	cin.get(temp_name, 100, '\n');
	cin.ignore(100, '\n');
	name = new char[strlen(temp_name) + 1];
	strcpy(name, temp_name);

	cout << "Please enter your email address: ";
	cin.get(temp_email, 200, '\n');
	cin.ignore(100, '\n');
	email = new char[strlen(temp_email) + 1];
	strcpy(email, temp_email);
}

//Functions for Operator Overloading
//Overloads the = operator
player & player::operator = (const player & to_assign)
{
	if(this == &to_assign)							
		return *this;								
	if(name)										
		delete [] name;								
	name = new char[strlen(to_assign.name) + 1];	
	strcpy(name, to_assign.name);					
	if(email)										
		delete [] email;							
	email = new char[strlen(to_assign.email) + 1];	
	strcpy(email, to_assign.email);					

	return *this;
}

//Overloads the << operator
ostream & operator << (ostream & out, const player & to_display)
{
	out << "\nPlayer"
		<< "\t\tPlayer: " << to_display.name << endl
		<< "\t\tEmail: " << to_display.email << endl;

	return out;
}

//Avatar class member function implementations

//Default constructor
avatar::avatar() {}

//Constructor with initialization list
avatar::avatar(char * handle, char * graphic):
	handle(NULL), graphic(NULL) {}

//Copy constructor
avatar::avatar(const avatar & to_copy):
	player(to_copy), handle(NULL), graphic(NULL)
{
	handle = to_copy.handle;
	graphic = to_copy.graphic;
}

//Destructor
avatar::~avatar()
{
	if(handle)
	{
		delete [] handle;
		handle = NULL;
	}
	if(graphic)
	{
		delete [] graphic;
		graphic = NULL;
	}
}

//Adds new avatar
void avatar::new_avatar()
{
	char temp_handle[100];
	char temp_graphic[100];

	new_player(); //create new base class object first

	cout << "\nAvatar Information" << endl;

	cout << "\nPlease enter your profile handle: ";
	cin.get(temp_handle, 100, '\n');
	cin.ignore(100, '\n');
	handle = new char[strlen(temp_handle) + 1];
	strcpy(handle, temp_handle);

	cout << "Please 'upload' your profile image: ";
	cin.get(temp_graphic, 100, '\n');
	cin.ignore(100, '\n');
	graphic = new char[strlen(temp_graphic) + 1];
	strcpy(graphic, temp_graphic);

}

//Functions for Operator Overloading
//Overloads the = operator
avatar & avatar::operator = (const avatar & to_assign)
{
	if(this == &to_assign) 								
		return *this;	   								
	player::operator=(to_assign); 						
	if(handle) 											
		delete [] handle; 								
	handle = new char[strlen(to_assign.handle) + 1];	
	strcpy(handle, to_assign.handle);					
	if(graphic)											
		delete [] graphic;								
	graphic = new char[strlen(to_assign.graphic) + 1];	
	strcpy(graphic, to_assign.graphic);					

	return *this;
}

//Overloads the << operator
ostream & operator << (ostream & out, const avatar & to_display)
{
	out << static_cast<const player&>(to_display)		
		<< endl
		<< "Avatar"
		<< "\t\tProfile Name: " << to_display.handle << endl
		<< "\t\tProfile Image: " << to_display.graphic << endl;

	return out;
}

//Character class member function implementations

//Default constructor
character::character() {}

//Constructor with initialization list
character::character(char * character_name, char * appearance):
	character_name(NULL), appearance(NULL) {}

//Copy constructor
character::character(const character & to_copy):
	avatar(to_copy), character_name(NULL), appearance(NULL)
{
	character_name = to_copy.character_name;
	appearance = to_copy.appearance;
}

//Destructor
character::~character()
{
	if(character_name)
	{
		delete [] character_name;
		character_name = NULL;
	}
	if(appearance)
	{
		delete [] appearance;
		appearance = NULL;
	}
}

//Adds a new character
void character::new_character()
{
	char temp_character_name[100];
	char temp_appearance[200];

	new_avatar(); //create new base class object first

	cout << "\nCharacter Information" << endl;

	cout << "\nPlease enter your character's name: ";
	cin.get(temp_character_name, 200, '\n');
	cin.ignore(100, '\n');
	character_name = new char[strlen(temp_character_name) + 1];
	strcpy(character_name, temp_character_name);

	cout << "Please enter your appearance (hat, sunglass, long hair, etc.): ";
	cin.get(temp_appearance, 200, '\n');
	cin.ignore(100, '\n');
	appearance = new char[strlen(temp_appearance) + 1];
	strcpy(appearance, temp_appearance);
}

//Functions for Operator Overloading
//Overloads the = operator
character & character::operator = (const character & to_add)
{
	if(this == &to_add)												
		return *this;												
	avatar::operator=(to_add);										
	if(character_name)												
		delete [] character_name;									
	character_name = new char[strlen(to_add.character_name) + 1];	
	strcpy(character_name, to_add.character_name);					
	if(appearance)													
		delete [] appearance;										
	appearance = new char[strlen(to_add.appearance) + 1];			
	strcpy(appearance, to_add.appearance);							

	return *this;													
}

//Overloads the << operator
ostream & operator << (ostream & out, const character & to_display)
{
	out << static_cast<const avatar&>(to_display)				
		<< endl
		<< "Character"
		<< "\tCharacter Name: " << to_display.character_name << endl
		<< "\t\tAppearance: " << to_display.appearance << endl << endl;

	return out;
}

//History class member function implementations

//Default constructor
history::history() {}

//Constructor with initialization list
history::history(int games_played, int games_won, int time, int points) {}

//Copy constructor
history::history(const history & to_copy): character(to_copy)
{
	games_played = to_copy.games_played;
	games_won = to_copy.games_won;
	time = to_copy.time;
	points = to_copy.points;
}

//Destructor
history::~history() {}

//Initializes data members to their random amounts
void history::new_history()
{
	new_character();

	games_played = random_played();
	games_won = random_won();
	time = random_time();
	points = random_points();
}

//Generates random numbers for games played
int history::random_played()
{
	games_played = rand() % 10000 + 1;
	return games_played;
}

//Generates random numbers for games played
int history::random_won()
{
	do
	{
		games_won = rand() % 10000 + 1;
	} while(games_won > games_played);

	return games_won;
}

//Generates random numbers for time played
int history::random_time()
{
	time = rand() % 1000000 + 1;
	return time;
}

//Generates random numbers for points
int history::random_points()
{
	int random_scale = rand() % 100 + 1;
	points = games_won * random_scale;
	return points;
}

//Function for operator overloading
//Overloads the << operator
ostream & operator << (ostream & out, const history & to_display)
{
	out << static_cast<const character&>(to_display)
		<< "\nYour History"
		<< "\tGames Played: " << to_display.games_played << endl
		<< "\t\tGames Won: " << to_display.games_won << endl
		<< "\t\tTotal time played: " << to_display.time / 60 << " hours" << endl
		<< "\t\tAverage Points/Game: " << to_display.points/to_display.games_won << endl
		<< "\t\tTotal points: " << to_display.points << endl;

	return out;
}

//Chest class member function implementations

//Default constructor
chest::chest() {}

//Constructor with initialization list
chest::chest(char * achievement):
	achievement(NULL) {}

//Copy constructor
chest::chest(const chest & to_copy):
	history(to_copy)
{
	achievement = to_copy.achievement;
}

//Destructor
chest::~chest()
{
	if(achievement)
	{
		delete [] achievement;
		achievement = NULL;
	}	
}

void chest::new_chest()
{
	char response;
	new_history();
	cout << "\nPlayer tool chest created.\n";
	cout << "\nWould you like to attempt an achievement? Y or N: ";
	cin >> response;
	cin.ignore(100, '\n');

	if(toupper(response)=='Y')
		new_achievement();
}

void chest::new_achievement()
{
	char temp[40];

	int random = rand() % 16;
	switch(random)
	{
		case 1:		strcpy(temp, "Beginner");
					break;
		case 2:		strcpy(temp, "Intermediate");
					break;
		case 3: 	strcpy(temp, "Experienced");
					break;
		case 4: 	strcpy(temp, "Professional");
					break;
		case 5:		strcpy(temp, "Beat the Boss");
					break;
		case 6:		strcpy(temp, "Undefeated");
					break;
		case 7:		strcpy(temp, "Top Ten");
					break;
		case 8:		strcpy(temp, "Top Five");
					break;
		case 9:		strcpy(temp, "Number One");
					break;
		case 10:	strcpy(temp, "Beat the Game");
					break;
		case 11:	strcpy(temp, "Level Up");
					break;
		case 12:	strcpy(temp, "Veteran (beat game on difficult)");
					break;
		case 13:	strcpy(temp, "Master (beat game on expert)");
					break;
		case 14:	strcpy(temp, "Winning Streak");
					break;
		case 15:	strcpy(temp, "Perfect Run");
					break;
		default:	cout << "Achievement not earned.";
					break;
	}
	achievement = new char[strlen(temp) + 1];
	strcpy(achievement, temp);
	cout << "*** Achievement Earned! ***\n"
		<< "    " << achievement << endl;
}

void chest::copy(const chest & to_copy)
{
	achievement = to_copy.achievement;
}

bool chest::exists()
{
	if(achievement)
		return true;
	return false;
}

//Functions for Operator Overloading
//
bool chest::operator < (const chest & to_compare)
{
	return (strcmp(this->achievement, to_compare.achievement) < 0);
}

//
bool chest::operator > (const chest & to_compare)
{
	return (to_compare.achievement < this->achievement);
}

//
bool chest::operator <= (const chest & to_compare)
{
	return (strcmp(this->achievement, to_compare.achievement)<=0);
}

//
bool chest::operator >= (const chest & to_compare)
{
	return (to_compare.achievement <= this->achievement);
}

//
bool chest::operator == (const chest & to_compare) const
{
	return (strcmp(this->achievement, to_compare.achievement)==0);
}

bool chest::operator != (const chest & to_compare)
{
	return !(this->achievement == to_compare.achievement);
}

//Overloads the = operator
chest & chest::operator = (const chest & to_add)
{
	if(this == &to_add)
		return *this;
	if(achievement)
		delete [] achievement;
	achievement = new char[strlen(to_add.achievement) + 1];
	strcpy(achievement, to_add.achievement);

	return *this;
}

ostream & operator << (ostream & out, const chest & to_display)
{
	out << static_cast<const history&>(to_display)
		<< endl
		<< "Your Achievements"
		<< '\t' << to_display.achievement << endl << endl; 
	
	return out;
}

