#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <exception>
#include <sstream>
#include "mancala.h"

using namespace std;
using namespace main_savitch_14;

void Mancala::make_move(const string& move)
{
  int numericMove = atoi(move.c_str());//converts move to int
  int selection = numericMove;
  int currentHole;//finds start of next hole

  if(last_mover() == COMPUTER)//Offsets for bottom row
  {
    selection = selection + 7;
    currentHole = selection + 1;//If its human selection, starts moving counter clockwise to the right
  }
  else
  {
    currentHole = selection - 1;//If its computer selection, starts moving counter clockwise to the left
  }
  int piecesInMove = currentBoard[selection];//Picks up pieces in hole
  currentBoard[selection] = 0;//Emptys out selected hole
  while (piecesInMove != 0)//Iterates through until hand is empty counter clockwise
  {
    if (currentHole <= 7 && currentHole > 0)
    {
      currentBoard[currentHole]++;//Adds a piece to new hole
      piecesInMove--;//Deduces piece from hand
      currentHole--;
    }
    else if (currentHole == 0)
    {
      currentBoard[currentHole]++;//Adds a piece to new hole
      piecesInMove--;//Deduces piece from hand
      currentHole = 8;
    }
    else if (currentHole >= 8 && currentHole <= 13)
    {
      currentBoard[currentHole]++;//Adds a piece to new hole
      piecesInMove--;//Deduces piece from hand
      currentHole++;
    }
    else if (currentHole > 13)
    {
      currentHole = 7;
      currentBoard[currentHole]++;//Adds a piece to new hole
      piecesInMove--;//Deduces piece from hand
      currentHole--;
    }
    else if (currentHole == 13)
    {
      currentBoard[currentHole]++;//Adds a piece to new hole
      piecesInMove--;//Deduces piece from hand
      currentHole = 7;
    }
    else
    {
      cout<<"ERROR ERROR UNKNOWN EXCEPTION";
    }
  }
  if (currentHole == 6 && last_mover() == COMPUTER)
  {
    game::make_move(move);
  }
  if (currentHole == 8 && last_mover() == HUMAN)
  {
    game::make_move(move);
  }
  game::make_move(move);
}
// Restart the game from the beginning:
void Mancala::restart()
{
  resetPieces();
  game::restart();
}

game* Mancala::clone( )const
{
  Mancala *toReturn = new Mancala(*this);
  return toReturn;
}

// Compute all the moves that the next player can make:
void Mancala::compute_moves(queue<string>& moves)const
{
  string move;
  for(int x=0; x<7; x++)
  {
    stringstream ss;//create a stringstream
    ss << x;//add number to the stream
    move = ss.str();
    if (is_legal(move))
    {
      moves.push(move);
    }
  }
}

// Display the status of the current game:
void Mancala::display_status()const
{
  displayCurrentBoard(cout);
}

// Evaluate a board position:
// NOTE: positive values are good for the computer.
int Mancala::evaluate( )const
{
  return getComputerScore() - getHumanScore();
}

// Return true if the current game is finished:
bool Mancala::is_game_over( )const
{
  //If someone has over half
  if (getHumanScore() > 24)
  {
    cout << "GAME OVER, YOU WIN:)" <<  '\n';
    return true;
  }

  if(getComputerScore() > 24)
  {
    cout << "GAME OVER, YOU LOSE:(" <<  '\n';
    return true;
  }
  if ((currentBoard[1] == 0 && currentBoard[2] == 0 && currentBoard[3] == 0 && currentBoard[4] == 0 && currentBoard[5] == 0 && currentBoard[6] == 0) || (currentBoard[8] == 0 && currentBoard[9] == 0 && currentBoard[10] == 0 && currentBoard[11] == 0 && currentBoard[12] == 0 && currentBoard[13] == 0))
  {
    if (getHumanScore() > getComputerScore())
    {
      cout << "GAME OVER, YOU WIN:)" <<  '\n';
    }
    else
    {
      cout << "GAME OVER, YOU LOSE:(" <<  '\n';
    }
    return true;
  }
  else
  {
    return false;
  }
}

// Return true if the given move is legal for the next player:
bool Mancala::is_legal(const string& move)const
{
  try
  {
    // checking valid integer
    int numericMove = atoi(move.c_str());
    if (next_mover() == HUMAN)
    {
      numericMove = numericMove + 7;
      if (numericMove > 7 && numericMove < 14 && currentBoard[numericMove] != 0)
        {return true;}
      else
        {return false;}
    }
    else{
      if (numericMove > 0 && numericMove < 7 && currentBoard[numericMove] != 0)
        {return true;}
      else
        {return false;}
    }
  }
  catch (invalid_argument e)
  {
    return false;
  }

}

void Mancala::displayCurrentBoard(ostream& outs) const
{
  outs << '\n' << '\n' << '\n';
  outputCurrentGameInfo(outs);
  outs << "1-6 (Left To Right)                <---Opponets Goal || Your Goal--->" << '\n';
  generateDividerLine(false, outs);
  string currentLine = "";

  int totalRowHeight = goalHeight / 2;
  for(int y=0; y <= totalRowHeight; y++)//Top Row
  {
    outs << "||";
    for (int x=0; x <= totalBoardWidthInCells - 1; x++)
    {
      if (x > 0 && x < 7)
      {
        currentLine = "|" + fillHoleProperly(currentBoard[x], y, false) + "|";
        outs << setw(cellWidth) << currentLine;
      }
      else
      {
        currentLine = "|" + fillHoleProperly(currentBoard[x], y, true) + "|";
        outs << setw(goalWidth) << currentLine;
      }
    }
    outs << "||" << '\n';
  }
  generateDividerLine(true, outs);
  for(int y=0; y <= totalRowHeight; y++)//Bottom Row
  {
    outs << "||";
    for (int x=0; x <= totalBoardWidthInCells - 1; x++)
    {
      if (x > 0 && x < 7)
      {
        currentLine = "|" + fillHoleProperly(currentBoard[x + 7], y, false) + "|";
        outs << setw(cellWidth) << currentLine;
      }
      else
      {
        currentLine = "|" + fillHoleProperly(currentBoard[x], y+6, true) + "|";
        outs << setw(goalWidth) << currentLine;
      }
    }
    outs << "||" << '\n';
  }
  generateDividerLine(false, outs);
}

string Mancala::fillHoleProperly(int holeAmount, int holeRow, bool isGoal)const
{
  string toReturn = "";
  int rowPieceCapacity = 3;
  if (isGoal)
  {
    rowPieceCapacity = rowPieceCapacity + 3;
  }
  int shouldBePlaced = holeRow * rowPieceCapacity;
  int toBePlaced = 0;
  int placed = 0;
  toBePlaced = holeAmount - shouldBePlaced;
  while (placed < rowPieceCapacity)
  {
    if (toBePlaced > 0)//PlacesPieceOnString
    {
      toReturn = toReturn + "(X)";
      toBePlaced--;
    }
    else //Else its an empty space
    {
      toReturn = toReturn + "   ";
    }
    placed++;
  }
  return toReturn;
}

void Mancala::generateDividerLine(bool isCenterDivider, ostream& outs)const
{
  outs << "||";
  if (!isCenterDivider)
  {
    for (int x=1; x <= totalBoardWidthInCells; x++)
    {
      if (x == 1 || x == 8)
      {
        outs << setw(goalWidth) << "++++++++++++++++++++";
      }
      else
      {
        outs << setw(cellWidth) << "+++++++++++";
      }
    }
  }
  else
  {
    for (int x=1; x <= totalBoardWidthInCells; x++)
    {
      if (x == 1 || x == 8)
      {
        outs << setw(goalWidth) << "|                  |";
      }
      else
      {
        outs << setw(cellWidth) << "+++++++++++";
      }
    }
  }
  outs << "||" << '\n';
}

//Resets pieces to original position
void Mancala::resetPieces()
{
  for (int x=0; x<13; x++)
  {
    currentBoard[x] = 0;
  }
  int pieces = 48;
  for (int x=0; pieces>0; x++)
  {
    if (x != 0 && x != 7)
    {
      currentBoard[x]++;
      //Testing Purposes
      //currentBoard[0]++;
      //currentBoard[7]++;
      pieces--;
    }
    if (x==13)
    {
      x=0;
    }
  }
}
int Mancala::getHumanScore()const
{
  return currentBoard[7];
}
int Mancala::getComputerScore()const
{
  return currentBoard[0];
}
void Mancala::outputCurrentGameInfo(ostream& outs)const
{
  outs << '\n' << "//*************************************************//" << '\n';
  outs << "Current Move Number: " << moves_completed() << '\n';
  if (last_mover() == COMPUTER)
  {
    outs << "It is your Turn" << '\n';
  }
  else
  {
    outs << "Computer\'s Turn....." << '\n';
  }
  outs << setw(15) << "  HUMAN SCORE:";
  outs << setw(4) << getHumanScore();
  outs << setw(15) << "  COMPUTER SCORE:" ;
  outs << setw(4) << getComputerScore() << '\n' ;
  outs << "//*************************************************//" << '\n' << '\n';
}
