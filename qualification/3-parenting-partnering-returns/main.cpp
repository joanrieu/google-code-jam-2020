#include <iostream>
#include <set>

struct Task {
  unsigned index, start, end;
};

bool operator<(const Task &task1, const Task &task2) {
  int d1 = task1.start - task2.start;
  if (d1)
    return d1 < 0;
  int d2 = task2.end - task2.end;
  if (d2)
    return d2 < 0;
  return task1.index < task2.index;
}

int main() {
  unsigned cases;
  std::cin >> cases;

  for (unsigned i = 0; i < cases; ++i) {
    unsigned N;
    std::cin >> N;
    std::string schedule;
    schedule.resize(N, '?');
    std::set<Task> tasks;

    for (unsigned j = 0; j < N; ++j) {
      Task task;
      task.index = j;
      std::cin >> task.start >> task.end;
      tasks.insert(task);
    }

    unsigned busy_until[2] = {0, 0};

    for (const auto &task : tasks) {
      if (busy_until[0] <= task.start) {
        schedule[task.index] = 'C';
        busy_until[0] = task.end;
      } else if (busy_until[1] <= task.start) {
        schedule[task.index] = 'J';
        busy_until[1] = task.end;
      } else {
        schedule = "IMPOSSIBLE";
        break;
      }
      // std::cout << schedule << "\n";
    }

    std::cout << "Case #" << i + 1 << ": " << schedule << '\n';
  }
}
