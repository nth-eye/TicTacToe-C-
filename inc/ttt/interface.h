#ifndef TTT_INTERFACE_H
#define TTT_INTERFACE_H

#include "ttt/engine.h"
#include <cstdio>

namespace ttt {

struct Interface : public Engine {

    void play()
    {
        print();
        while (result() == EMPTY) {
            act(input());
            print();
        };
    }

    void print() const
    {
        puts("\n");
        char p1 = turn() == X ? 'O' : 'X';
        char p2 = turn() == X ? 'X' : 'O';
        char c;
        for (int row = 0; row < 3; ++row) {
            puts("-------------");
            for (int col = 0; col < 3; ++col) {
                printf("| ");

                auto mask = bit(col + row * 3);

                if (opp & mask)
                    c = p1;
                else if (all & mask)
                    c = p2;
                else 
                    c = ' ';

                printf("%c ", c);
            }
            puts("|");
        }
        puts("-------------\n");
        printf("turn:   %c \n", p2);
        printf("result: ");
        
        switch (result()) {
            case EMPTY:	c = '?'; break;
            case X:		c = 'X'; break;
            case O:		c = 'O'; break;
            case DRAW:	c = '='; break;
        }
        printf("%c \n\n", c);
    }

    Move input() const
    {
        long long move = -1;

        while (true) {
            printf("\nMake move: ");
            int result = scanf("%lld", &move);
            if (result == EOF || !result)
                puts("\nIncorrect input");
            else if (!legal(move))
                puts("\nIllegal move");
            else
                break;
            while (fgetc(stdin) != '\n');
        };
        return move;
    }
};

}

#endif