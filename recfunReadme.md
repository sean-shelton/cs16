#recfun

This project was used in order to help us learn recursive functions.

The function "stars" uses recursion in order to print a line of stars

"triangle" uses stars in order to create recursively designed right triangles. 
The smallest width of the triangle is denoted with m, and the largest width is denoted by n.

"numbers" takes a string, and based on the number of levels, utilizes recursion within a for loop
in order to print out the given string, appended with levels at the end.

"bears" plays a game called bears through recursion, and returns true if it is possible to win with the given number n,
false if it is not possible. If the number is ever equal to 42, then the game is won and it returns true.
Otherwise, if the number is divisible by 5, it subtracts 42 if that would lead to winning the game.
If the number is divisible by 3 or 4, it will multiply the last two digits of your number and subtract that
many bears from the number if that would lead to winning the game, and if the product of those two digits is not equal to 0.
If the number is divisible by two, then it will divide the number by two and continue the game if possible.

"pattern" draws a pattern that is created through recursion based upon the values of n and i.
