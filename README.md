# String Expression Calculator
This is a micro project made by Aaditya Thakkar.

## tokenize() function -> int
The algorithm used in the `tokenize` function is a simple tokenizing algorithm that separates the input string into an array of tokens, where each token is either an operator or an operand.

The algorithm works as follows:
1. Initialize two variables, `i` and `numBracks`, to 0. `i` is used as an index for the tokens array, and `numBracks` is used to keep track of the number of brackets in the input string.
2. Use a `while` loop to iterate through the input string character by character.
3. Within the `while` loop, use the `isdigit` function to check if the current character is a digit. If it is, use the `strtol` function to convert the string of digits to a long integer and store the result in the `tokens` array.
4. If the current character is an operator (`+`, `-`, `*`, `/`, `^`, `!`, `%`, `(`, or `)`), store the operator in the `tokens` array. Also, increment the `numBracks` variable if the operator is `(`.
5. If the current character is a space, ignore it and continue to the next character.
6. If the current character is any other type of character, print an error message and exit the program.
7. Continue the `while` loop until the end of the input string is reached.
8. After the `while` loop, check if the `numBracks` variable is greater than 1. If it is, print an error message and exit the program.
9. Finally, return the number of tokens in the `tokens` array.
