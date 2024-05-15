# Arithmetic Expression Evaluator

This C++ repository provides a solution for validating, converting, and evaluating arithmetic expressions. The program allows users to input numerical or abstract equations and performs various operations on them, including checking validity, converting to postfix and prefix notations, and evaluating the expressions to produce results. 

## Data Structures Used

The project utilizes the following data structures:

- **Stack**: Implemented to handle operations such as push, pop, and peek for managing operators during expression conversion.
- **Queue**: Utilized for storing operands and operators during postfix notation conversion.
- **Structs**: Defines a node structure used for implementing stack and queue functionalities.

## Features

- **Input Validation**: Checks the validity of the input expression, ensuring correct usage of brackets and operators.
- **Conversion to Postfix and Prefix Notations**: Converts the input expression into postfix and prefix notations using stack and queue data structures.
- **Expression Evaluation**: Evaluates the expression to produce the result, supporting standard arithmetic operations (+, -, *, /) and additional operators (^ for exponentiation and % for remainder).
- **User Interaction**: Allows users to input numerical or abstract equations, providing flexibility in expression types.
- **Error Handling**: Prompts users to re-enter expressions if they are invalid, ensuring accurate processing of valid expressions.

## Usage

1. Run the program and choose the type of equation input (numerical or abstract).
2. Enter the equation as prompted.
3. The program will validate the expression, convert it to postfix and prefix notations, and display the results.
4. If desired, the program can also evaluate the expression and display the result.

## Implementation Details

The project is implemented using object-oriented programming principles, with classes for Stack, Queue, and Equation. It employs dynamic memory allocation for storing and manipulating expression data, ensuring efficient memory usage.
