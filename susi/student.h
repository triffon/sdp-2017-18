#ifndef _STUDENT_H
#define _STUDENT_H

#include <iostream>

const int MAX = 100;

class Student {
 private:

  char name[MAX];
  int fn;
  double grade;
  
 public:
  
  Student(char const* _name = "", int _fn = 0, double _grade = 0);

  char const* getName() const { return name; }

  int getFN() const { return fn; }

  double getGrade() const { return grade; }

  void setGrade(int _grade) { grade = _grade; } // Домашно: проверка за коректност

  friend std::istream& operator>>(std::istream&, Student&);
};

std::ostream& operator<<(std::ostream&, Student const&);

#endif
