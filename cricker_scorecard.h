#pragma once
#include<iostream>
using namespace std;

class Team
{
    public:
    string name;
    public:

    Team(){
        name="";
   }

    void addBattingName(string inputName);
    
};

class Player:public Team{
    public:
    int score,fours,sixs,balls;

    public:

    Player(){
        score=0;
        fours=0;
        sixs=0;
        balls=0;
    }
    int calculateScore(string inputScore);

};


class Scorecard:public Player{
    public:

    void viewScoreCard();

};

