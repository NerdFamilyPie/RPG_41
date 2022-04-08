//Put your name(s) here:
//What bullet points did you do:
//Delete this next line to let the code compile
#include "map.h"
#include "actor.h"
#include <unistd.h>

const int MAX_FPS = 90; //Cap frame rate 
const unsigned int TIMEOUT = 10; //Milliseconds to wait for a getch to finish
const int UP = 65; //Key code for up arrow
const int DOWN = 66;
const int LEFT = 68;
const int RIGHT = 67;

//Turns on full screen text mode
void turn_on_ncurses() {
	initscr();//Start curses mode
	start_color(); //Enable Colors if possible
	init_pair(1,COLOR_WHITE,COLOR_BLACK); //Set up some color pairs
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	timeout(TIMEOUT); //Set a max delay for key entry
}

//Exit full screen mode - also do this if you ever want to use cout or gtest or something
void turn_off_ncurses() {
	clear();
	endwin(); // End curses mode
	system("clear");
}


int main() {
	Hero Boji = {100, 150, "Boji"};
	Hero Skaarf = {100, 90, "Skaarf"};
	Hero Lance = {100, 50, "Lance"};

	vector<shared_ptr<Actor>> vec;
	vec.push_back(make_shared<Hero>(Boji));
	vec.push_back(make_shared<Hero>(Skaarf));
	vec.push_back(make_shared<Hero>(Lance));
	cout << "Press enter to continue dialogue: " << endl;
	cout << "You play as Boji, a young prince with almost zero physical strength. " << endl;
	cin.ignore();
	cout << "Alongside you are 2 companions, a baby dragon named Skaarf, and a loyal Knight named Lance." << endl;
	cin.ignore();
	cout << "Despite having no physical strength, Boji can incapacitate his enemies by taking advantage of their anataomy. Using a deliberate combination of speed and precision, his fighting style focuses on his oppponents pressure points. " << endl;
	cin.ignore();
		
	turn_on_ncurses();
	Map map;
	int x = Map::SIZE / 2, y = Map::SIZE / 2; //Start in middle of the world
	int old_x = -1, old_y = -1;
	while (true) {
		int ch = getch(); // Wait for user input, with TIMEOUT delay
		if (ch == 'q' || ch == 'Q') break;
		else if (ch == RIGHT) {
			x++;
			if (x >= Map::SIZE) x = Map::SIZE - 1; //Clamp value
		}
		else if (ch == LEFT) {
			x--;
			if (x < 0) x = 0;
		}
		else if (ch == UP) {
			y--;
			if (y < 0) y = 0;
		}
		else if (ch == DOWN) {
			y++;
			if (y >= Map::SIZE) y = Map::SIZE - 1; //Clamp value
		}
		else if (ch == ERR) { //No keystroke
			; //Do nothing
		}

		if(map.collision(x,y)){
			//add in protection against std::out of range
			y++;
			x--;
		}
		//Stop flickering by only redrawing on a change
		if (x != old_x or y != old_y) {
			if(map.monsterContact(x,y)){
				turn_off_ncurses();
				cout << "You've encountered monsters! " << endl;
				Monster m1 = {100, 70, "Goblin"}; 
				Monster m2 = {100, 50, "Zombie"};
				Monster m3 = {100, 1000, "Demon"};
				vec.push_back(make_shared<Monster>(m1));
			    vec.push_back(make_shared<Monster>(m2));
				vec.push_back(make_shared<Monster>(m3));
				sort(vec.begin(),vec.end(),my_sort);

				//keep fighting until either boji is dead or all the monsters are dead
				//all the monsters are dead if every monster is below 0hp
			
				while( m1.isAlive()  || m2.isAlive() || m3.isAlive()){
					for(const shared_ptr<Actor> a : vec){
						if(a->id() == "Monster"){
							cout << a << endl;
						}
					}


				}

				cout << "Wow, you killed all of them!" << endl;
				cin.ignore();

			
			}
			if(map.onTreasure(x,y)){
				map.pickUpTreasure(x,y);
				mvprintw(Map::DISPLAY+3,0,"You picked up treasure!");
			}
			//clear(); //Put this in if the screen is getting corrupted
			map.draw(x,y);
			mvprintw(Map::DISPLAY+1,0,"X: %i Y: %i\n",x,y);
			refresh();
		}
		old_x = x;
		old_y = y;
		usleep(1'000'000/MAX_FPS);
	}
	turn_off_ncurses();
}

