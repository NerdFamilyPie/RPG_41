#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ncurses.h>
#include <fstream>
using namespace std; //Boo hiss

class Map {
	vector<vector<char>> map;
	default_random_engine gen;
	public:
	//TODO: Write a getter and a setter to get/set the characters in the map


	//TODO: Write a function to save the map and reload the map
	static const char HERO     = 'H';
	static const char MONSTER  = 'M';
	static const char WALL     = '#';
	static const char WATER    = '~';
	static const char OPEN     = ' ';
	static const char TREASURE = '$';
	static const size_t SIZE = 50; //World is a 100x100 map
	static const size_t DISPLAY = 30; //Show a 20x20 area at a time
	//Randomly generate map
	void init_map() {
		uniform_int_distribution<int> d100(1,100);
		map.clear();
		map.resize(SIZE); //100 rows tall
		for (auto &v : map) v.resize(SIZE,' '); //100 columns wide
		for (size_t i = 0; i < SIZE; i++) {
			for (size_t j = 0; j < SIZE; j++) {
				//Line the map with walls
				if (i == 0 or j == 0 or i == SIZE-1 or j == SIZE-1) 
					map.at(i).at(j) = WALL;
				else if (i == SIZE/2 and j == SIZE/2) 
					map.at(i).at(j) = HERO;
				else {
					//5% chance of monster
					if (d100(gen) <= 5) {
						map.at(i).at(j) = MONSTER;
					}
					else if (d100(gen) <= 3) {
						map.at(i).at(j) = TREASURE;
					}
					else if (d100(gen) <= 10) { //10% each spot is wall
						map.at(i).at(j) = WALL;
					}
					else if (d100(gen) <= 3) { //3% each spot is water
						map.at(i).at(j) = WATER;
					}
					else if (d100(gen) <= 20) { //20% chance of water near other water
						if (map.at(i-1).at(j) == WATER or map.at(i+1).at(j) == WATER or map.at(i).at(j-1) == WATER or map.at(i).at(j+1) == WATER)
							map.at(i).at(j) = WATER;
					}
				}
			}
		}
			
	}

//oid saveMap(string filename){
//ofstream ins(filename);
//
//if(!ins){
///cout << "Bad file, cannot be opened." << endl;
//	return;
//}
//for(size_t i = 0; i < map.size(); i++){
//	for(size_t j = 0; j < map.size(); j++){
//		ins << map.at(i).at(j);
//	}
//	ins << endl;
//}
//
//

//oid loadmap(string filename){
//ifstream ins(filename);

//if(!lns){
//	cout << "Bad file" << endl;
//	return;
//}
//
//string line;
//while(getline(ins, line)){
//	map.push_back(line);
//}
//
//for(size_t i = 0; i < map.size(); i++){
//	for(size_t j = 0; j < map.at(0).size(); j++){
//		if(map.at(i).at(j) == "$"){
//			cout << "$ found" << endl;
//			break;
//		}
//	}
//}
//


	bool collision(int x, int y){
		if(map.at(y).at(x) == WALL){
			return true;
		}
		return false;
	}

	bool monsterContact(int x, int y){
		if(map.at(y).at(x) == MONSTER){
			return true;
		}
		return false;
	}

	bool onTreasure(int x, int y){
		if(map.at(y).at(x) == TREASURE){
			return true;
		}
		return false;
	}

	void pickUpTreasure(int x, int y){
		if(map.at(y).at(x) == TREASURE){
			map.at(y).at(x) = OPEN;
		}
	}



	void initialize_map() {

	ofstream ins("test.txt");
	
	map.clear();
	map.resize(SIZE);
	for(auto &v : map ) v.resize(SIZE, ' ');
	for(size_t i = 0; i < SIZE; i++){
	for(size_t j= 0;j < SIZE; j++){
		if(i == 0 or j == 0 or i == SIZE - 1 or j == SIZE - 1){
			map.at(i).at(j) = WALL;
		}
		else if (i == SIZE/2 and j == SIZE/2){
			map.at(i).at(j) = HERO;
		} else if (i == 5 && j%2!=0){
			map.at(i).at(j) = WALL;
		}
		else if(i%9==0 && j%12==1){
			map.at(i).at(j) = MONSTER;
		}
		map.at(10).at(36) = TREASURE;
		map.at(20).at(24) = TREASURE;
		
		ins << map.at(i).at(j);

	}
	ins << endl;

}

}

	//Draw the DISPLAY tiles around coordinate (x,y)
	void draw(int x, int y) {
		int start_x = x - DISPLAY/2;
		int end_x = x + DISPLAY/2;
		int start_y = y - DISPLAY/2;
		int end_y = y + DISPLAY/2;

		//Bounds check to handle the edges
		if (start_x < 0) {
			end_x = end_x - start_x;
			start_x = 0;
		}
		if (end_x > SIZE-1) {
			start_x = start_x - (end_x - (SIZE-1));
			end_x = SIZE-1;
		}
		if (start_y < 0) {
			end_y = end_y - start_y;
			start_y = 0;
		}
		if (end_y > SIZE-1) {
			start_y = start_y - (end_y - (SIZE-1));
			end_y = SIZE-1;
		}

		//Now draw the map using NCURSES
		for (size_t i = start_y; i <= end_y; i++) {
			for (size_t j = start_x; j <= end_x; j++) {
				if (i == y && j == x) {
					attron(A_UNDERLINE | A_BOLD);
					mvaddch(i-start_y,j-start_x,'H');
					attroff(A_UNDERLINE | A_BOLD);
				}
				else {
					int color = 1;
					if (map.at(i).at(j) == WALL)
						color = 1;
					else if (map.at(i).at(j) == WATER)
						color = 2;
					else if (map.at(i).at(j) == HERO)
						color = 3;
					else if (map.at(i).at(j) == TREASURE)
						color = 4;
					else if (map.at(i).at(j) == MONSTER)
						color = 6;

					attron(COLOR_PAIR(color));
					mvaddch(i-start_y,j-start_x,map.at(i).at(j));
					attroff(COLOR_PAIR(color));
				}
			}
		}
	}
	Map() {
	//	init_map();
		initialize_map();
	}
};
