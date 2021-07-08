#include <cstdio>
#include "ttt.h"

constexpr Bitboard WIN_MASKS[8] = {
    0b001001001, 0b010010010, 0b100100100, 0b000000111, 
    0b000111000, 0b111000000, 0b100010001, 0b001010100
};

constexpr Bitboard bit(int i) { return 1ul << i; }

void TTT::print() const
{
    puts("\n");

    char p1 = (current & TURN) == X ? 'X' : 'O';
    char p2 = (current & TURN) == X ? 'O' : 'X';
    char c;

    for (int row = 0; row < 3; ++row) {

        puts("-------------");

        for (int col = 0; col < 3; ++col) {
            
            printf("| ");

            Bitboard mask = bit(col + row * 3);

            if (current & mask)
                c = p1;
            else if (all & mask)
                c = p2;
            else 
                c = '-';

            printf("%c ", c);
        }
        puts("|");
    }
    puts("-------------\n");
    printf("turn:   %c \n", p1);
    printf("result: ");
    
    switch (result()) {
        case EMPTY:	c = '?';    break;
        case X:		c = 'X';    break;
        case O:		c = 'O';    break;
        case DRAW:	c = '-';    break;
    }
    printf("%c \n\n", c);
}

void TTT::play() 
{
    print();

    while (result() == EMPTY) {
        Move move = ask_input();
        make_move(move);
        print();
    };
}

void TTT::reset() 
{
    all     = TURN;
    current = 0;
}

void TTT::make_move(Move move) 
{
    current ^= all;
    all     |= bit(move);
}

bool TTT::legal(Move move) const 
{
    if (move > 8)
        return false;

    return !(bit(move) & all);
}

int TTT::result() const
{
    auto player = all ^ current;

    for (auto mask : WIN_MASKS)
        if ((mask & player) == mask) 
            return player & TURN;

    if ((all & BOARD) == BOARD)
        return DRAW;

    return EMPTY;
}

Move TTT::ask_input() const
{
    long long move = -1;

    while (true) {

        printf("\nMake move: ");

        int result = scanf("%lld", &move);

        if (result == EOF || !result) {
            puts("\nIncorrect input");
        } else if (!legal(move)) {
            puts("\nIllegal move");
        } else {
            break;
        }
        while (fgetc(stdin) != '\n');
    };
    return move;
}

MoveList TTT::moves() const 
{
    MoveList moves;

    for (int i = 0; i < 9; ++i)
        if (!(bit(i) & all))
            moves.save(i);

    return moves;
}
