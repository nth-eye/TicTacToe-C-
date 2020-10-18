#include "ttt.h"

namespace ttt {

void Game::reset() 
{
    turn = X;
    state.fill(0);
}

void Game::test() 
{
    std::cout << str() << std::endl;

    while (result() == EMPTY) {
        std::cout << "\nMake move: " << std::flush;
        auto move = ask_input();
        act(move);
        std::cout << str() << std::endl;
    };
}

int Game::result() const
{
    // Define player who just made move.
    int player = turn ^ BOTH;

    for (int cell = 0; cell < 9; cell += 3)
        if ((state[cell] & state[cell+1] & state[cell+2]) == player)
            return player;

    for (int cell = 0; cell < 3; ++cell)
        if ((state[cell] & state[cell+3] & state[cell+6]) == player)
            return player;

    if ((state[0] & state[4] & state[8]) == player)
        return player;

    if ((state[2] & state[4] & state[6]) == player)
        return player;

    for (auto cell : state)
        if (cell == EMPTY)
            return EMPTY;

    return BOTH;
}

bool Game::legal(Action move) const 
{
    if (move < 0 || move >= 9)
        return false;

    return state[move] == EMPTY;
}

float Game::reward() const
{
    switch (result()) {
        case X:
        case O: return 1.0f;
        default: return 0.0f;
    }
}

float Game::act(Action move) 
{
    state[move] = turn;
    turn ^= BOTH;

    return reward();
}

Action Game::ask_input() const
{
    Action move = -1;
    while (true) {
        std::cin >> move;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nIncorrect input\n" << std::endl;
        } else if (!legal(move)) {
            std::cout << "\nIllegal move\n" << std::endl;
        } else {
            break;
        }
    };
    return move;
}

ActionList Game::legal_actions() const 
{
    ActionList moves;

    for (int i = 0; i < 9; ++i)
        if (state[i] == EMPTY)
            moves.push_back(i);

    return moves;
}

std::string Game::str() const
{
    std::stringstream ss;
    ss << '\n';

    for (int row = 0; row < 3; ++row) {
        ss << "-------------\n";
        for (int col = 0; col < 3; ++col) {
            ss << '|';
            switch(state[row*3 + col]) {
                case X: ss << " X "; break;
                case O: ss << " O "; break;
                case EMPTY: ss << "   "; break;
                default: assert(false);
            }
        }
        ss << "|\n";
    }
    ss << "-------------\n";
    ss << "\nturn:\t" << (turn == X ? 'X' : 'O') << "\nwinner:\t";
    switch (result()) {
        case EMPTY:	ss << '-'; break;
        case X:		ss << 'X'; break;
        case O:		ss << 'O'; break;
        case BOTH:	ss << "draw"; break;
    }
    return ss.str();
}

}