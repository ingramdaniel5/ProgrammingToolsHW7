#include <string>
#include <iostream>
#include "game.h"

namespace main_savitch_14
{
    class Mancala: public game
    {
    // *******************************************************************
    // VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEND:
    // The overriding function should call the original when it finishes.
    // *******************************************************************
    // Have the next player make a specified move:
    public:
      void make_move(const std::string& move);
        // Restart the game from the beginning:
      void restart();
      game* clone() const;
        // Compute all the moves that the next player can make:
      void compute_moves(std::queue<std::string>& moves)const;
      // Display the status of the current game:
      void display_status()const;
      // Evaluate a board position:
      // NOTE: positive values are good for the computer.
      int evaluate()const;
      // Return true if the current game is finished:
      bool is_game_over()const;
      // Return true if the given move is legal for the next player:
      bool is_legal(const std::string& move)const;

    private:
      /*
      0 = left goal
      1-6 = top row
      7 = right goal
      8-13 = bottom row
      */
      int currentBoard[13];
      const static int cellWidth = 11;
      const static int goalWidth = 20;
      const static int goalHeight = 10;
      const static int totalBoardWidthInCells = 8;
      const static int totalBoardHeightInCells = 2;
      void resetPieces();
      void displayCurrentBoard(std::ostream& outs) const;
      void generateDividerLine(bool isCenterDivider, std::ostream& outs)const;
      std::string fillHoleProperly(int holeAmount, int holeRow, bool isGoal)const;
      int getHumanScore()const;
      int getComputerScore()const;
      void outputCurrentGameInfo(std::ostream& outs)const;
  };
}