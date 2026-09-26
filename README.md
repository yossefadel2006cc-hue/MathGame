# Math Quiz Game

A console-based Math Quiz game built with C++.

## Description

This project is a console-based math quiz where the player answers a series of randomly generated mathematical questions.

The player can choose the number of questions, difficulty level, and operation type. The program generates questions randomly, checks the player's answers, and displays the final quiz results.

## Features

* Choose the number of questions (1–20)
* Three difficulty levels:

  * Easy
  * Medium
  * Hard
  * Mixed
* Choose the operation type:

  * Addition
  * Subtraction
  * Multiplication
  * Division
  * Mixed
* Randomly generated questions
* Checks answers automatically
* Displays the correct answer when the player is wrong
* Tracks correct and incorrect answers
* Displays PASS or FAIL at the end
* Option to play again
* Console colors for correct and incorrect answers

## Technologies

* C++
* Enums
* Structs
* Functions
* Arrays
* Loops
* Conditional statements
* Random number generation
* Switch statements

## Difficulty Levels

| Level  | Number Range      |
| ------ | ----------------- |
| Easy   | 1–10              |
| Medium | 10–50             |
| Hard   | 50–100            |
| Mix    | Random difficulty |

## Project Structure

```text
Math-Game/
├── src/
│   └── MathGame.cpp
└── README.md
```

## How to Run

1. Clone the repository.
2. Open the project in a C++ development environment.
3. Compile the source file.
4. Run the generated executable.
5. Choose the quiz settings and start answering.

## Example

```text
How Many Questions Do You Want To Answer ? 5

Enter Questions Level : Easy [1], Med [2], Hard [3], Mix :[4]?
4

Enter Operation Type: Add [1], Sub [2], Mul [3], Div [4], MixOpType [5]?
5
```

After answering all questions, the game displays:

```text
Tha Final Result Of The Quiz : PASS

Number Of Questions     : 5
Questions Level         : Mix
Operation Type          : Mix
Number Of Right Answers : 4
Number Of Wrong Answers : 1
```

## Author

Youssef Adel
