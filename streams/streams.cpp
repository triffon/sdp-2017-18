#include <iostream>
#include <iomanip>

std::ostream& pretty_hex(std::ostream& os) {
  return os << std::hex << std::setw(20) << std::left <<
    std::setfill('_') << std::showbase;
}

int main() {
  std::cout << std::showbase << std::hex << 42 << std::endl;
  int n;
  std::cin >> std::hex >> n;
  std::cout << pretty_hex << n << std::endl;
  return 0;
}
