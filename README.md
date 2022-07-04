# ttt

Simple TicTacToe game environment in C++20 (only for `std::countr_zero`, otherwise C++11 possible) which uses as little resources as possible with the help of bitboards. By rewriting `input()` and `print()` functions in `Interface`, the engine can be integrated in any specific environment and device.

## How to use

```cpp
#include "ttt/interface.h"
...
ttt::Interface{}.play();
```
