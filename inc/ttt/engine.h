#ifndef TTT_ENGINE_H
#define TTT_ENGINE_H

#include <cstdint>
#include <cstddef>
#include <bit>

namespace ttt {

inline constexpr int BOARD = 0b111111111;
inline constexpr int TURN  = BOARD + 1;

enum { X, EMPTY, DRAW, O = TURN };

using Bitboard  = uint_fast16_t;
using Move      = uint_fast8_t;

struct MoveList {
    constexpr MoveList(Bitboard bb) : bb{bb} {}
    constexpr MoveList begin()          { return bb; }
    constexpr MoveList end()            { return 0; }
    constexpr auto operator*() const    { return std::countr_zero(bb); }
    constexpr auto operator++()         { bb &= bb - 1; }
    constexpr bool operator!=(const MoveList&) const = default;
    constexpr bool operator==(const MoveList&) const = default;
private:
    Bitboard bb = 0;
};

constexpr auto bit(int i) { return 1ul << i; }

struct Engine {

    constexpr void reset()
    {
        all = TURN;
        opp = 0;
    }

    constexpr void act(Move move)
    {
        all |= bit(move);
        opp ^= all;
    }

    constexpr bool legal(Move move) const
    {
        return move < 9 && !(bit(move) & all);
    }

    constexpr auto moves() const
    {
        return ~all & BOARD;
    }

    constexpr int turn() const
    { 
        return opp & TURN; 
    }

    constexpr int result() const
    {
        constexpr int WIN_MASK[8] = {
            0b001001001, 0b010010010, 0b100100100, 0b000000111, 
            0b000111000, 0b111000000, 0b100010001, 0b001010100
        };
        for (int mask : WIN_MASK)
            if ((mask & opp) == mask) 
                return ~opp & TURN;
        return (all & BOARD) == BOARD ? DRAW : EMPTY;
    }
protected:
    Bitboard all = TURN;
    Bitboard opp = 0;
};

}

#endif
