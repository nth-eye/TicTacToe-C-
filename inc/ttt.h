#ifndef TTT_H
#define TTT_H

#include <cstdint>
#include <array>

using Bitboard  = uint_fast16_t;
using Move      = uint_fast8_t;
using MoveList  = std::array<Move, 9>;

constexpr Bitboard BOARD    = 0b111111111;
constexpr Bitboard TURN     = BOARD + 1;

enum { X, EMPTY, DRAW, O = TURN };

struct TTT {

    void print() const;
    void play();
    void reset();
    void make_move(Move move);
    bool legal(Move move) const;

    int turn() const    { return current & TURN; }
    int result() const;

    Move ask_input() const;
    MoveList moves() const;
private:
    Bitboard all        = TURN;
    Bitboard current    = 0;
};

#endif // TTT_H