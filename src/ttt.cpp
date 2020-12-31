#include <limits>
#include <sstream>
#include <iostream>

#include "ttt.h"

namespace ttt {

void Game::reset() 
{
    all = TURN;
    current = 0;
}

void Game::test() 
{
    std::cout << str() << std::endl;

    while (result() == EMPTY) {
        std::cout << "\nMake move: " << std::flush;
        auto move = ask_input();
        act(move);
        std::cout << str() << std::endl;
        for (const auto it : legal_actions())
            std::cout << int(it) << std::endl;
    };
}

int Game::result() const
{
    // Define player who just made move.
    auto player = all ^ current;

    for (const auto mask : WIN_MASKS) {
        if ((mask & player) == mask) 
            return player & TURN;
    }

    if ((all & BOARD) == BOARD)
        return DRAW;

    return EMPTY;
}

bool Game::legal(Action move) const 
{
    if (move < 0 || move >= 9)
        return false;

    return ((1 << move) & all) == 0;
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
    current ^= all;
    all |= (1 << move);

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
        if ((1 << i) & all == 0)
            moves.push_back(i);

    return moves;
}

std::string Game::str() const
{
    std::stringstream ss;
    ss << '\n';

    char p1 = (current & TURN) == X ? 'X' : 'O';
    char p2 = p1 == 'X' ? 'O' : 'X';

    for (int row = 0; row < 3; ++row) {
        ss << "-------------\n";
        for (int col = 0; col < 3; ++col) {
            ss << "| ";
            auto mask = (1ULL << (col + row*3));
            if (current & mask)
                ss << p1;
            else if (all & mask)
                ss << p2;
            else 
                ss << '-';
            ss << ' ';
        }
        ss << "|\n";
    }
    ss << "-------------\n";
    ss << "\nturn:\t" << p1 << "\nwinner:\t";
    switch (result()) {
        case EMPTY:	ss << '-';      break;
        case X:		ss << 'X';      break;
        case O:		ss << 'O';      break;
        case DRAW:	ss << "draw";   break;
    }
    return ss.str();
}

}