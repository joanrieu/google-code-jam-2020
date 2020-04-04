#include <iostream>
#include <sstream>

struct Result {
  unsigned index;
  std::string nested;
};

int main() {
  std::stringstream ss;
  unsigned cases;
  std::cin >> cases;
  Result results[cases];

  for (unsigned i = 0; i < cases; ++i) {
    std::string number;
    std::stringstream ss;
    std::cin >> number;
    unsigned depth = 0;
    for (const auto &c : number) {
      unsigned digit = c - '0';
      while (digit > depth) {
        ss << '(';
        ++depth;
      }
      while (digit < depth) {
        ss << ')';
        --depth;
      }
      ss << digit;
    }
    while (depth > 0) {
      ss << ')';
      --depth;
    }
    results[i] = {i + 1, ss.str()};
  }

  for (const auto &res : results)
    std::cout << "Case #" << res.index << ": " << res.nested << '\n';
}
