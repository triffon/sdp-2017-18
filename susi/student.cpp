#include "student.h"

#include <cstring>

Student::Student(char const* _name, int _fn, double _grade) :
  fn(_fn), grade(_grade) {
  if (_name == nullptr)
    name[0] = '\0';
  strncpy(name, _name, MAX);
  name[MAX-1] = '\0';
}

std::ostream& operator<<(std::ostream& os, Student const& s) {
  return os << s.getFN() << ' ' <<
    s.getGrade() << ' ' <<
    s.getName() << std::endl;
  // Домашно: направете формата да е Ф№, име, оценка
}

std::istream& operator>>(std::istream& is, Student& s) {
  char space;
  return (is >> s.fn >> s.grade).get(space).getline(s.name, MAX);
}
