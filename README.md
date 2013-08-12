Euler
=====

Program that uses a shunting-yard algorithm to parse a differential equation and subsequently solve using Euler's method.


TODO:
=====

- The parsing works fine (except for a few issues, like negative numbers needing to be called (0-n) instead of -n, and currently, floating points with empty tenths (or more) places (e.g. '1.01') are not properly processed.
- The actual Euler evaluation function works fine, but may not work with the parsed expression. This is because I had previously written the Euler program to work with a hardcoded-in mathematical function, and only later added in the parsing stuff.
- The parsed expression may not work with two variables. I don't fully remember however, it's been a few months since I've worked on this (sorry Aaron)
