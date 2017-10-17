#include <fstream>
#include <sstream>

#include "student.h"

const int FIRST_STUDENT = 80000;

void testStudent() {
  Student s("Иван Иванов", 80000, 5.5);
  std::cout << s;
  std::ostringstream oss;
  oss << s;
  std::istringstream iss(oss.str());
  iss >> s;
  std::cout << s;
  std::cout << "->" << s.getName() << "<-\n";
}

Student* readStudents(int& n, std::istream& input = std::cin,
                      std::ostream& prompt = std::cout) {
  prompt << "Въведете брой студенти: ";
  input >> n;
  
  Student* sa = new Student[n];
  
  for(int i = 0; i < n; i++) {
    prompt << "Въведете студент №" << i + 1 << ": ";
    input >> sa[i];
  }
  return sa;
}

void printStudents(Student const* sa, int n,
                   std::ostream& output = std::cout) {
  output << n << std::endl;
  for(int i = 0; i < n; i++)
    output << sa[i];
}

void testReadPrintStudents() {
  int n;
  std::ostringstream empty;
  //  Student* sa = readStudents(n, std::cin);
  std::ifstream fi("students.txt");
  Student* sa = readStudents(n, fi, empty);
  std::ofstream fo("students_check.txt");
  printStudents(sa, n, fo);
}

void createMainBook(char const* mainBook, int capacity) {
  std::ofstream mb(mainBook, std::ios::out | std::ios::binary);
  Student empty;
  for(int i = 0; i < capacity; i++)
    mb.write((const char*)&empty, sizeof(Student));
}

void readStudent(std::istream& mb, int fn, Student& s) {
  int i = fn - FIRST_STUDENT;
  mb.seekg(i * sizeof(Student));
  mb.read((char*)&s, sizeof(Student));
}

void writeStudent(std::ostream& mb, Student const& s) {
  int i = s.getFN() - FIRST_STUDENT;
  mb.seekp(i * sizeof(Student));
  mb.write((const char*)&s, sizeof(Student));
}

 void writePassingGrades(char const* gradesFile,
                         char const* mainBook) {
  std::ifstream grades(gradesFile);
  std::ofstream mb(mainBook, std::ios::out | std::ios::binary);
  int n;
  grades >> n;
  for(int i = 0; i < n; i++) {
    Student s;
    grades >> s;
    if (s.getGrade() >= 3)
      writeStudent(mb, s);
  }
}

void increaseGrade(char const* mainBook, int fn) {
  std::fstream mb(mainBook, std::ios::in | std::ios::out | std::ios::binary);
  Student s;
  readStudent(mb, fn, s);
  s.setGrade(s.getGrade() + 1);
  writeStudent(mb, s);
}
  

int main() {
  //  testStudent();
  //  testReadPrintStudents();
  //  createMainBook("main.bk", 100);
  writePassingGrades("students.txt", "main.bk");
  increaseGrade("main.bk", 80005);
  return 0;
}
