#include <iostream> 
#include <string>
#include <fstream>
#include "game.h"
#include "mancala.h"

using namespace std;
using namespace main_savitch_14;

int main()
{
    string userInput = "Y";
    while (userInput != "n" && userInput != "N")
    {
        cout << '\n';
        cout << '\n';
        cout << '\n' << "//*************************************************//" << '\n';
        cout << "WELCOME TO DAN\'S MANCALA!!!!!" << '\n';
        cout << '\n' << "//*************************************************//" << '\n';
        cout << "Loading new game......" << '\n';
        game * newGame;
        game::who winner;
        newGame = new Mancala;
        cout << "Game Created, Starting Game....." << '\n';
        winner = newGame->play();
        if (winner == game::HUMAN)
            cout<<"GAME OVER, YOU WIN:)";
        else
            cout<<"GAME OVER, YOU LOSE:(";
        cout << '\n';
        cout << '\n';
        cout << "Would you like to play again? (Y/N)" << '\n';
        cin >> userInput;
    }
    
    cout << '\n' << '\n' << "The program has concluded" << '\n';
    cout << "Thanks for playing!" << '\n' << '\n' ;
	return 0;
}