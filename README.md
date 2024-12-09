# EECS 348 Term Project Calculator
Authors: EECS Group 12

## Purpose 
The overall purpose of this project was to create a basic calculator that followed PEMDAS (see glossary for definition). taking in there equations with the basic operations (+,-,/,*,**,%,()) with more details in Getting Started. The program lets the user input in their equation and gets the solution but it also tells them when they do something wrong i.e. if they divide by zero it tells them they can not divide by zero. This all can be accessed on our GetHub to  run on cycle servers run "make cycle_run". 

## Introduction
The Calculator software takes in an equation and returns a solution following PEMDAS. The purpose is to complete a given equation promptly. The calculator's features include checking that the equation is valid. Dividing by zero will raise an error. It also allows the user to get their solution with decimals included. 

## Installation
To install the calculator, clone the repo and run the make file from source using ``make %filepath%``. Once the program is running just enter in your equation when prompted and hit enter and it will give you the solution. make defaults to using clang. To run on cycle servers run ``make cycle_run``. This builds and runs the calculator. ``cd src; make cycle_run`` 

## Getting started
After running the program from the make file from the source the user is asked to enter an equation. The user needs to follow some basic rules when entering their problem. If the user is using addition they will press “+”, subtraction is “-”, multiplication “*”, division is “/”, exponents are “**” or "^", the remainder is “%” and if they want to include parentheses they will use “(“ and “)”. See example #4. 

## Advanced features
Although this is a simple program we made sure to make it clear what the user is doing wrong for example errors tell the user what they are doing wrong in their error code instead of just saying an invalid equation. as well as it allows the user to put in a + before their number to indicate that it is a positive number i.e. ```+8 - 2 = 10.```

## Troubleshooting 
Some common problems are if the user divides by zero or if they enter an invaded character i.e. “A”. If the user divides by zero they will be told that they have entered an invalid integer letting them know that their equation needs to be changed for the equation to be completed. If they enter in a character then they will receive a prompt that tells them that they entered an invalid syntax which lets them know that they need to fix that mistake.

## Examples 
Some examples for each operation would be addition is ``1 + 1 = 2`` then subtraction ``1 - 1 = 0`` for multiplication ``2 * 2 = 4``, division ``2 / 2 = 1``, modular ``2 % 1 = 1``, exponent ``4 * 2 = 16`` and finally parentheses ``2 * (1 + 2) = 2 * (3) = 6`` for a more complex problem ``4/2+(3*4**2)%2-2``. the program will follow PEMDAS so looking at the parentheses first the program will see ``3*4**2`` it will do the exponent first to get 4 to the power of 2 which is 16 then it will do 4 * 16 = 64 the program then looks at the new equation ``4/2+(64)%2-2`` the next step in PEMDAS is a division of ``4 / 2 = 2`` then modular of ``64 % 2 = 0``  now the looking back at the main equation ``2+0-2`` and following the last 2 steps of PEMDAS the software will do ``2 + 0 = 2`` and then ``2 - 2 = 0``.
Glossary of terms


The glossary is documented on our github.

## FAQ 
Q1: Does this program work on a Mac?

A1: Yes, compile with G++ or Clang with C++ version 17. 

Q2: Who can I contact for support?

A2: This program comes as is. If you discover an issue, please create an issue on the repo. 

Q3: Why does it start with parenthesis?

A3: The calculator follows the laws of PEMDAS where Parenthesis is the highest priority of operations

