#include "engine.hh"
#include <string>
#include <vector>

extern std::vector<std::string> updated_word_list;
extern bool end_game;

void pattern_from_pattern_index(int (&pattern)[5], int pattern_index);

void update_word_list(int pattern_index, std::string &input_word);

void game_loop(const std::string &hidden_word);

void game_loop(const string &hidden_word, const string &current_guess);
