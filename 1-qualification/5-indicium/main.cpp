#include <deque>
#include <iostream>
#include <map>

/**
 * THIS PROGRAM DOES NOT PRODUCE THE CORRECT OUTPUT.
 * THE SAMPLES ARE FINE BUT MORE COMPLEX EXAMPLES ARE NOT.
 */

int main() {
  unsigned cases;
  std::cin >> cases;

  for (unsigned i = 0; i < cases; ++i) {
    unsigned N, K;
    std::cin >> N >> K;
    std::cerr << "\ncase #" << i + 1 << ": with N = " << N << " and K = " << K
              << '\n';
    unsigned m[N * N] = {0};

    int delta;

    {
      // const unsigned offset = K / N - 1; // K >= N (no underflow)
      //  delta = K % N;

      unsigned offset = 0;
      delta = K - N;

      std::cerr << "iso diagonal leaves a delta = " << delta << '\n';

      for (unsigned y = 0; y < N; ++y) {
        for (unsigned x = 0; x < N; ++x) {
          m[y * N + x] = ((N + offset + y - x) % N) + 1;
        }
      }
    }

    for (unsigned trace_change_target = 0; trace_change_target < N;
         ++trace_change_target) {
      unsigned target_change_old_value =
          m[trace_change_target * N + trace_change_target];
      for (unsigned max_change =
               std::min(delta, int(N - target_change_old_value));
           max_change > 0; --max_change) {
        unsigned target_change_new_value = target_change_old_value + max_change;
        bool circular = false;
        std::deque<std::pair<std::pair<unsigned, unsigned>, unsigned>>
            change_list;
        std::map<std::pair<unsigned, unsigned>, unsigned> change_map;
        change_list.push_back({{trace_change_target, trace_change_target},
                               target_change_new_value});
        change_map.insert({{trace_change_target, trace_change_target},
                           target_change_new_value});
        std::cerr << "trying to replace " << target_change_old_value << " by "
                  << target_change_new_value << " at " << trace_change_target
                  << "x" << trace_change_target << '\n';

        for (auto it = change_list.begin();
             it != change_list.end() && !circular; ++it) {
          const auto change_x = it->first.first;
          const auto change_y = it->first.second;
          const auto change_old_value = m[change_y * N + change_x];
          const auto change_new_value = it->second;

          for (unsigned dup_x = 0; dup_x < N; ++dup_x) {
            if (m[change_y * N + dup_x] == change_new_value) {
              const auto insertion =
                  change_map.insert({{dup_x, change_y}, change_old_value});
              if (insertion.second ||
                  insertion.first->second == change_old_value) {
                change_list.push_back({{dup_x, change_y}, change_old_value});
              } else {
                circular = true;
              }
              break;
            }
          }

          for (unsigned dup_y = 0; dup_y < N; ++dup_y) {
            if (m[dup_y * N + change_x] == change_new_value) {
              const auto insertion =
                  change_map.insert({{change_x, dup_y}, change_old_value});
              if (insertion.second ||
                  insertion.first->second == change_old_value) {
                change_list.push_back({{change_x, dup_y}, change_old_value});
              } else {
                circular = true;
              }
              break;
            }
          }
        }

        int new_trace = 0;
        for (unsigned xy = 0; xy < N; ++xy) {
          auto it = change_map.find({xy, xy});
          if (it == change_map.end()) {
            new_trace += m[xy * N + xy];
          } else {
            new_trace += it->second;
          }
        }
        int new_delta = K - new_trace;

        if (!circular && new_delta > 0 && new_delta < delta) {
          for (auto it = change_list.begin();
               it != change_list.end() && !circular; ++it) {
            const auto change_x = it->first.first;
            const auto change_y = it->first.second;
            m[change_y * N + change_x] = it->second;
          }
          delta = new_delta;
          break;
        }
      }
    }

    if (!delta) {
      std::cout << "Case #" << i + 1 << ": POSSIBLE" << '\n';
      for (unsigned y = 0; y < N; ++y) {
        for (unsigned x = 0; x < N; ++x) {
          if (x > 0)
            std::cout << ' ';
          std::cout << m[y * N + x];
        }
        std::cout << '\n';
      }
    } else {
      std::cout << "Case #" << i + 1 << ": IMPOSSIBLE" << '\n';
    }
  }
}
