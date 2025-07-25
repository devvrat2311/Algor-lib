# Algorithms

*Implementation of various algorithms and data structures in C++, as given in the book Introduction to algorithms*

## Directory: 01-Foundations

*Various algortithms from the book are implemented in this folder with Make as the build tool*

Build Instructions: Ensure that C++ 14 or higher and GNU/Make is installed, and use command "Make" in the directory 01-Foundations after to build the program and run using ./bin/run command

## Directory: sfml-animations

*Using SFML(Simple and Fast Mutimedia Library), a C++ framework and library to make 2d animations of commonly seen sorting algorithms*

Build Instructions: Ensure that C++ 14 or higher and GNU/Make is installed, and use command "Make" in the directory sfml-animations. Then run ./sfml-game to launch the application just built.

    make
    ./sfml-game

### Using the Application

The application when run opens a window with an unsorted array of bars and is controlled via buttons:

    Esc: Escape the program
    S: Insertion sort the array
    B: Bubble sort the array
    E: Selection sort the array
    M: Merge sort the array

All these procedures will sort the array, to try another sorting algorithm the application has to be closed and opened again(for now).
