#include <cstring>
#include <cassert>
#include <sstream>
#include <iostream>
#include <array>
#include <vector>
#include <limits>

#pragma once

namespace ttt {

using Action = int;
using ActionList = std::vector<int>;
using State = std::array<int, 9>;

enum : int { EMPTY, X, O, BOTH };

struct Game {

	static constexpr int NO_MOVE = -1;

	Game() { history.emplace_back(); };
	Game(State state_) : state(std::move(state_)) { history.push_back(state); }
	
	void reset();
	void test();

	int to_play() const { return turn; }
	int result() const;
	bool terminal() const { return result() != EMPTY; }
	bool legal(Action move) const;
	float reward() const;
	float act(Action move);

	Action ask_input() const;
	ActionList legal_actions() const;

	std::string str() const;

private:
	int turn = X;
	State state = {};
	std::vector<State> history;
};

}