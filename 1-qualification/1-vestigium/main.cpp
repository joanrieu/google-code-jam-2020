#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

struct Result {
  unsigned index, trace, dup_rows, dup_columns;
};

int main() {
  std::stringstream ss;
  unsigned cases;
  std::cin >> cases;
  std::vector<Result> results(cases);

  for (unsigned i = 0; i < cases; ++i) {
    unsigned N;
    std::cin >> N;
    unsigned m[N * N];
    const std::bitset<100> N_bits((__uint128_t(1) << N) - 1);
    unsigned trace = 0, dup_rows = 0, dup_columns = 0;

    for (unsigned y = 0; y < N; ++y) {
      auto dups = N_bits;
      for (unsigned x = 0; x < N; ++x) {
        unsigned c;
        std::cin >> c;
        if (x == y)
          trace += c;
        m[y * N + x] = c;
        dups.set(c - 1, false);
      }
      if (dups.any())
        ++dup_rows;
    }

    for (unsigned x = 0; x < N; ++x) {
      auto dups = N_bits;
      for (unsigned y = 0; y < N; ++y) {
        dups.set(m[y * N + x] - 1, false);
      }
      if (dups.any())
        ++dup_columns;
    }

    results[i] = {i + 1, trace, dup_rows, dup_columns};
  }

  for (const auto &res : results)
    std::cout << "Case #" << res.index << ": " << res.trace << ' '
              << res.dup_rows << ' ' << res.dup_columns << '\n';
}
