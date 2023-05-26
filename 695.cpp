#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cassert>
using namespace std;
#define all(x) (x).begin(), (x).end()
const int MAXN = 1e7 + 20;

struct Lift {
  int lift_capacity;
  enum { EMPTY, USED } state; // mutable
  std::vector<int>::iterator quicksum_begin; // ต้องมีตัวก่อนหน้าเสมอ
  std::vector<int>::iterator quicksum_end;

  bool can_simulate_by(int time, int mentor_weight) const {
    auto it = quicksum_begin;
    for (; time >= 1 && it != quicksum_end; --time) {
      int quicksum_base = *prev(it);
      int lift_available_space = lift_capacity - mentor_weight;
      it = std::upper_bound(it, quicksum_end, quicksum_base + lift_available_space);
    }
    return it == quicksum_end && time >= 0;
  }
};

int main(){
  std::cin.sync_with_stdio(false);

  int count_lift, count_student, count_question;
  std::cin >> count_lift >> count_student >> count_question;
  assert(count_lift <= 10);
  assert(count_question <= 10);

  std::vector<int> lifts_capacity(count_lift);
  std::vector<int> mentors_weight(count_lift);
  std::vector<int> quicksum_student(count_student + 1, 0); // quick sumc to
  std::vector<int> question(count_question); // quick sumc to

  for (auto& i : lifts_capacity) std::cin >> i;
  for (auto& i : mentors_weight) std::cin >> i;
  for (int i = 1; i <= count_student; ++i) { // input quicksum
    int student_weight;
    std::cin >> student_weight;
    quicksum_student[i] = quicksum_student[i-1] + student_weight;
  }
  for (auto& i : question) std::cin >> i;

  assert(quicksum_student[0] == 0);
  assert(quicksum_student.size() == count_student + 1);
  // quicksum_student = [0, a, a + b, a + b + c, a + b + c + d, ...]


  for (const int max_time : question) { // start questions

    std::sort(all(lifts_capacity)); // optimize check for little capacity to larger
    std::vector<Lift> lift_dp;
    for (int i = 0; i != count_lift; ++i) {
      int split_at;
      std::cin >> split_at;
      lift_dp.push_back({
        lifts_capacity[i],
        Lift::EMPTY, // mutable
        quicksum_student.begin() + split_at,
        quicksum_student.end(), // will change
      });
      if (i > 0) {
        lift_dp[i - 1].quicksum_end = lift_dp[i].quicksum_begin;
      }
    }

    bool is_solve = false;
    std::sort(all(mentors_weight)); // prepare for permutation

    do { // start permutation mentor
      for (Lift& ll : lift_dp) ll.state = Lift::EMPTY; // reset state
      is_solve |= std::all_of(all(mentors_weight), [&](int curr_mentor_weight) { // all mentor must match some lift
        return std::any_of(all(lift_dp), [&](Lift& ll) {
          if (ll.state == Lift::EMPTY && ll.can_simulate_by(max_time, curr_mentor_weight)) {
            ll.state = Lift::USED;
            return true;
          } else {
            return false;
          }
        });
      });
    } while (!is_solve && std::next_permutation(all(mentors_weight))); // end permutation mentor

    std::cout << (is_solve ? "P": "F") << "\n";

  } // end questions
  return 0;
}
