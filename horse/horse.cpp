#include "lstack.cpp"
#include "horse.h"
#include <cmath>

HorseWalker::HorseWalker(int boardSize) {
  for(int i = 0; i < boardSize; i++)
    chessBoard.push_back(ChessBoardRow(boardSize));
}

void HorseWalker::printBoard() const {
  /*
  for(int i = 0; i < chessBoard.size(); i++) {
    for(int j = 0; j < chessBoard.size(); j++)
      std::cout << (chessBoard[i][j] ? 'X' : '_');
    std::cout << std::endl;
  }
  */
  for(auto row : chessBoard) { // row <-> chessBoard[i]
    for(auto pos : row) // pos <-> row[j] <-> chessBoard[i][j]
      std::clog << (pos ? 'X' : '_');
    std::clog << std::endl;
  }

  std::clog << std::endl;
}

void HorseWalker::printPath() const {
  Path copy = path;
  while (!copy.empty())
    std::clog << copy.pop() << ' ';
  std::clog << std::endl;
}

bool HorseWalker::findPathRec(Position start, Position end) {
  // "лошо" дъно: несупех
  if (!insideBoard(start.first) ||
      !insideBoard(start.second) ||
      chessBoard[start.first][start.second])
    return false;

  // стъпка напред
  std::clog << "Стъпваме на " << start << std::endl;
  chessBoard[start.first][start.second] = true;
  printBoard();
  path.push(start);

  // "добро" дъно: успех
  if (start == end) {
    printPath();
    return true;
  }

  for(int dx = -2; dx <= 2; dx++)
    if (dx != 0)
      //      for(int sign = -1; sign <= 1; sign += 2)
      for(int sign : {-1, 1}) {
        int dy = sign * (3 - abs(dx));
        Position newstart(start.first + dx, start.second + dy);
        if (findPathRec(newstart, end))
          return true;
      }
  // нито една от възможностите не е била успешна
  // стъпка назад
  std::clog << "Стъпка назад от " << start << std::endl;
  path.pop();
  return false;
}

bool HorseWalker::findPathStack(Position start, Position end) {
  Stack stack;
  StackFrame stackFrame;
  stackFrame.push(start);
  stack.push(stackFrame);

  while (!stack.empty()) {
    // Поглеждаме текущата рамка
    StackFrame& currentFrame = stack.peek();
    // Поглеждаме текущия кандидат
    Position current = currentFrame.peek();
  
    // "лошо" дъно: несупех
    if (!insideBoard(current.first) ||
        !insideBoard(current.second) ||
        chessBoard[current.first][current.second]) {;
      // махаме кандидата от стековата рамка
      currentFrame.pop();
      // Дали това беше последният кандидат в стековата рамка?
      if (currentFrame.empty()) {
        // махаме празната стекова рамка от стека
        stack.pop();
        // Обявяваме стъпка назад (използваме предишната стекова рамка
        // за да видим кой е бил неуспешния кандидат)
        StackFrame& oldFrame = stack.peek();
        std::clog << "Стъпка назад от " << oldFrame.peek() << std::endl;
        // И го махаме
        oldFrame.pop();

        // Понеже това е стъпка назад, махаме неуспешния кандидат от пътя
        path.pop();
      }
    }
    else {

      // стъпка напред
      std::clog << "Стъпваме на " << current << std::endl;
      chessBoard[current.first][current.second] = true;
      printBoard();
      path.push(current);

      // "добро" дъно: успех
      if (current == end) {
        printPath();
        return true;
      }

      // стъпка напред, създаваме нова стекова рамка с кандидати
      StackFrame newFrame;
      for(int dx = 2; dx >= -2; dx--)
        if (dx != 0)
          //      for(int sign = -1; sign <= 1; sign += 2)
          for(int sign : {1, -1}) {
            int dy = sign * (3 - abs(dx));
            Position newcurrent(current.first + dx, current.second + dy);
            // Добавяме поредния какндидат
            newFrame.push(newcurrent);
          }
      // добавяме новата стекова рамка на стека, "симулираме" рекусивно
      // извикване
      stack.push(newFrame);
    }
  }

  // "рекурсията" е приключила без да намери път, значи неуспех
  return false;
}


int main() {
  HorseWalker hw(4);
  //  hw.findPathRec({0, 0}, {3, 2});
  //  hw.findPathStack({0, 0}, {0, 0});
  // hw.findPathStack({0, 0}, {1, 2});
  hw.findPathStack({0, 0}, {3, 2});
  return 0;
}
