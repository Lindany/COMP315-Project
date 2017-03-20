#include <iostream>
using namespace std;
#include <string>

class Player{

private:

	string name;
	int *score, *level, *correctWords, *incorrectWords,*timeTook;

public:

	Player(string n);

	string getName(){ return name;}

	int getScore(){ return *score; }

	int getLevel(){ return *level; }

	void updateLevel(){ *level++; }

	int getCorrectWords(){ return *correctWords; }

	int getIncorrectWords(){ return *incorrectWords; }

	int getTimeTook(){ return *timeTook; }

	~Player();
};

Player::Player(string n){

	name = n;
	*score = 0;
	*level = 1;
	*correctWords = 0;
	*incorrectWords = 0;
	*timeTook = 0;
}

Player::~Player(){

	delete score;
	delete correctWords;
	delete incorrectWords;
	delete timeTook;
}