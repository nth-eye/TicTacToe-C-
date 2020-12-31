#include <string>
#include <vector>

#pragma once

namespace ttt {

using Action = int;
using ActionList = std::vector<int>;
using State = std::pair<unsigned, unsigned>;

inline constexpr unsigned BOARD = 0b111111111;
inline constexpr unsigned TURN = BOARD + 1;
inline constexpr unsigned WIN_MASKS[8] = {
    0b001001001, 0b010010010, 0b100100100,
    0b000000111, 0b000111000, 0b111000000,
    0b100010001, 0b001010100
};

enum  {	X, EMPTY, DRAW, O = TURN };

class Game {
    unsigned all = TURN;
    unsigned current = 0;
public:
    Game() = default;
    Game(State state) : all(state.first), current(state.second) {}

    void reset();
    void test();

    int result() const;
    int to_play() const     { return current & TURN; }
    bool terminal() const   { return result() != EMPTY; }
    bool legal(Action move) const;
    float reward() const;
    float act(Action move);

    State get_state() const { return { all, current }; }
    Action ask_input() const;
    ActionList legal_actions() const;

    std::string str() const;
};

}