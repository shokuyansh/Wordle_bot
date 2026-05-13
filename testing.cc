#include "answer_list.hh"
#include "engine.hh"
#include "game_loop.hh"
#include "ranking.hh"
#include <iostream>
#include <string>
using std::priority_queue;
using std::string;
using std::vector;

string hidden_word;
int turns;
int limit = 0;
int freq_of_turns_taken_to_solve[6] = {0};

void testing_performance() {
  for (auto aw : answer_list) {
    updated_word_list = word_list;
    string current_guess = ranking_list[0].word;
    turns = 0;
    hidden_word = aw;
    for (int i = 0; i < 6; i++) {
      turns++;
      game_loop(hidden_word, current_guess);
      if (end_game) {
        end_game = false;
        break;
      }
      float max_entropy = -1.0f;
      string max_entropy_word = "";
      float entropy = 0.0f;
      priority_queue<Word, vector<Word>, CompareEntropy> rank_list;
      int index = 1;
      for (auto guess_word : updated_word_list) {
        Word gw;
        gw.word = guess_word;
        entropy = entropy_for_word(gw, updated_word_list);
        rank_list.push({guess_word, entropy});
      }
      limit = 0;

      current_guess = rank_list.top().word;
    }
    freq_of_turns_taken_to_solve[turns - 1]++;
  }
}
void performance_result() {
  float avg_score = 0;
  for (int s = 0; s < 6; s++) {
    printf("\n %d : %d\n", s + 1, freq_of_turns_taken_to_solve[s]);
    avg_score += (s + 1) * freq_of_turns_taken_to_solve[s];
  }
  avg_score /= answer_list.size();
  printf("AVERAGE SCORE : %f", avg_score);
}
int main() {
  testing_performance();
  performance_result();
}
