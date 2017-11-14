#ifndef _HORSE_H
#define _HORSE_H

#include <iostream>
#include <vector>
#include <utility>
#include "lstack.cpp"

using Position = std::pair<int, int>;
using Path     = LinkedStack<Position>;
using StackFrame = LinkedStack<Position>;
using Stack    = LinkedStack<StackFrame>;
using Step     = std::pair<Position, Position>;

class HorseWalker {
private:

  using ChessBoardRow = std::vector<bool>;
  using ChessBoard    = std::vector<ChessBoardRow>;
  
  ChessBoard chessBoard;
  Path path;

  bool insideBoard(int x) { return 0 <= x && x < chessBoard.size(); }
  
public:
  HorseWalker(int _boardSize = 8);

  bool findPathRec(Position start, Position end);

  bool findPathStack(Position start, Position end);

  bool findPathQueue(Position start, Position end);

  void printBoard() const;

  void printPath() const;
};

std::ostream& operator<<(std::ostream& os, Position const& pos) {
  return os << '(' << pos.first << ',' << pos.second << ')';
}

std::ostream& operator<<(std::ostream& os, Step const& step) {
  return os << '[' << step.first << "->" << step.second << ']';
}



#endif
