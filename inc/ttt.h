#ifndef TTT_H
#define TTT_H

#include <cstdint>
#include <cstddef>

using Bitboard  = uint_fast16_t;
using Move      = uint_fast8_t;

struct MoveList {
    const Move* begin() const { return &list[0]; }
    const Move* end() const   { return &list[len]; }
    size_t size() const       { return len; }
    void erase(size_t idx)    { list[idx] = list[--len]; }
    void save(Move m)         { list[len++] = m; }
private:
    Move list[9];
    size_t len = 0;
};

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