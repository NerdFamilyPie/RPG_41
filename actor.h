#include "/public/read.h"
#include <list>
#include <memory>
#include <algorithm>
#include <string>
using namespace std;


struct Actor{
	string name;
	int health = 100;
	int speed = 100;
	Actor(int new_health, int new_speed, string new_name){
		speed = new_speed;
		name = new_name;
		health = new_health;
	}
	friend ostream& operator<< (ostream &outs, const Actor &rhs){
		return outs << rhs.name;
	}
	void damage(Actor &actor, int damage){
		actor.set_hp(actor.get_hp() - damage);
		cout << name << " has damaged " << actor << " " << damage << " damage. " << actor.get_hp() << " remaining hp." << endl;
	}
	bool isAlive(){
		if(health <=0){
			return false;
		}
		return true;

	}
	void set_hp(int new_health){
		health = new_health;
	}
	int get_hp() {
		return health;
	}
	virtual string id() const {return "Actor"; }
};
	struct Hero : Actor {
		Hero(int new_health, int new_speed, string new_name) : Actor(new_health, new_speed, new_name) {}
		string id() const override {return "Hero";}
	};

	struct Monster : Actor{
		Monster(int new_health, int new_speed, string new_name) : Actor(new_health, new_speed, new_name) {}
		string id () const override {return "Monster";}
	};


	bool my_sort(const shared_ptr<Actor>&a, const shared_ptr<Actor>&b){
		return a->speed > b->speed;
	}

	


