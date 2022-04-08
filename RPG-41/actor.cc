#include <string>

using namespace std;

class Actors {
	private:
		int health;
		int speed;
		int strength;
		string classs;
		string name;

	public:
		void attack(){

		}
		void talk(string text = "Line please!"){

		}
		Actors(){
			health = speed = strength = 0;
			classs = name = "";
		}
		Actors(int ahealth, int aspeed, int astrength, string aclasss, string aname){
			this->health = ahealth;
			this->speed = aspeed;
			this->strength = astrength;
			this->classs = aclasss;
			this->name = aname;
		}
		int GetHealth(){
			return health;
		}
		void SetHealth(int ahealth){
			this->health = ahealth;
		}
		int GetSpeed(){
			return speed;
		}
		void SetSpeed(int aspeed){
			this->speed = aspeed;
		}
		int GetStrength(){
			return strength;
		}
		void SetStrength(int astrength){
			this->strength = astrength;
		}
		string GetClasss(){
			return classs;
		}
		void SetClasss(string aclasss){
			this->classs = aclasss;
		}
		string GetName(){
			return name;
		}
		void SetName(string aname){
			this->name = aname;
		}
		
};

class Hero : public Actors {
	private:

	public:


};

class Monster : public Actors {
	private:

	public:

};
