#include <queue>
#include <string>
#include <vector>

using std::priority_queue;
using std::string;
using std::vector;
// Forming struct for priority queue
struct Word {
  string word;
  float entropy;
  int prob_distribution[243] = {0};
  vector<int> current_pattern = {0, 0, 0, 0, 0};
};
struct CompareEntropy {
  bool operator()(Word w1, Word w2) { return w1.entropy < w2.entropy; }
};
enum COLOR_SET { GREY = 0, YELLOW = 1, GREEN = 2 };

void prob_of_all_patterns_of_a_word(Word &guess_word);

float entropy_for_word(Word &guess_word);

int pattern_matcher(const Word &guess_word, const string &word);
