#include <iostream>
#include "cricker_scorecard.h"
using namespace std;

//function to add batting order 
void Team ::addBattingName(string inputName)
{
    name = inputName;
}

//function to calculate score and check different condition
int Player::calculateScore(string inputScore)  //inheriting from base class
{

    if ((inputScore == "Wd") || (inputScore == "Nb"))
    {
        return 10;
    }
    else if (inputScore == "W")
    {
        balls++;
        return 11;
    }
    else
    {
        int runs = stoi(inputScore);
        if (runs >= 0 && runs <= 6 && runs != 5)
        {
            if (runs == 4)
            {
                fours++;
            }
            if (runs == 6)
            {
                sixs++;
            }
            score += runs;
            balls++;
            return runs;
        }
        else
        {
            return 12;
        }
    }
}

//function to views scorecard
void Scorecard::viewScoreCard()   //inheriting from derived class
{
    cout << name << "\t\t" << score << "\t" << fours << "\t" << sixs << "\t" << balls << endl;
}

int main()
{
    int numberOfPlayers, numberOfOvers, teamScore[2] = {0, 0}, teamWickets[2] = {0, 0};
    cout << "No. of players for each team:";
    cin >> numberOfPlayers;
    cout << "No. of overs:";
    cin >> numberOfOvers;
    for (int team = 1; team <= 2; team++)
    {
        // declared array type object for storing players
        Scorecard battingOrder[numberOfPlayers];
        cout << "Batting Order for team" << team << ":" << endl;
        for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++)
        {
            string inputName;
            cin >> inputName;
            battingOrder[playerNumber].addBattingName(inputName);
        }
        // declared pointer type object for class to store current players
        Scorecard *onstrike, *offstrike;
        onstrike = &battingOrder[0];
        offstrike = &battingOrder[1];
        
        int nextPlayerIndex = 2;
        float over = 0;
        while (over < numberOfOvers)
        {
            cout << "Over" << over + 1 << endl;
            int currentBall = 0;
            while (currentBall < 6)
            {
                if (teamWickets[team - 1] >= numberOfPlayers - 1)//condition for all out
                {
                    break;
                }
                if (teamScore[1] > teamScore[0])//checks team2 score is greater than team 1 or not
                {
                    break;
                }
                string inputScore;
                cin >> inputScore;
                int runs = onstrike->calculateScore(inputScore);
                if (runs == 10)
                {
                    teamScore[team - 1]++;
                }
                else if (runs == 11)
                {
                    teamWickets[team - 1]++;
                    onstrike = &battingOrder[nextPlayerIndex++]; //if onstrike batsman gets out new batsman come on strike
                    currentBall++;
                }
                else if (runs == 12)
                {
                    cout << "Invalid Score" << endl;
                }
                else
                {
                    teamScore[team - 1] += runs;
                    currentBall++;
                    if (runs == 1 || runs == 3)
                    {
                        //if scored run 1 or 3 there is change in strike
                        Scorecard *temp;
                        temp = onstrike;
                        onstrike = offstrike;
                        offstrike = temp;
                    }
                }
            }
            //printing scorecard after each over
            cout << "Scorecard for Team " << team << endl;
            cout << "Player Name\tScore\t4s\t6s\tBalls" << endl;
            for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++)
            {
                battingOrder[playerNumber].viewScoreCard();
            }
            cout << "Total:" << teamScore[team - 1] << "/" << teamWickets[team - 1] << endl;
            //after completion of over changing strike
            if (currentBall == 6)
            {
                Scorecard *temp;
                temp = onstrike;
                offstrike = offstrike;
                offstrike = temp;
                over++;
                cout << "Overs: " << over << endl;
            }
            //if team gets all out calculating overs 
            else
            {
                over += currentBall / 10.0;
                cout << "Overs: " << over << endl;
                break;
            }
        }
    }

    //printing match result
    if (teamScore[0] > teamScore[1])
    {
        cout << "Team 1 won the match by " << teamScore[0] - teamScore[1] << " runs";
    }
    else
    {
        cout << "Team 2 won the match by " << numberOfPlayers - teamWickets[1] << " wickets";
    }
}