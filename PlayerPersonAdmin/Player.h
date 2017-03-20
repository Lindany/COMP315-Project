#ifndef Player_H
#define Player_H
#include "Person.h"
#include <string>
class Player : public Person
{
    public:
        Player();
        string name;
        int score;

        Player(string name);
        virtual int getScore()=0;//this shows that the method is pure virtual meaning it will be
        virtual int getLevel()=0;//implemented on another class that inherit the Player class
        virtual bool writeWord()=0;
        virtual void updateScore()=0;
        virtual ~Player();



    protected:

    private:
};

#endif // Player_H
