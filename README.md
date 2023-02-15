# APT-A2-M3

## Implementing Qwirkle - Milestones 3: Individual Enhancements & Tests

**Prepared by Group 2**

- Carelle Mulawa-Richards (s3749114)
- Jacob Depares (s3851480)
- Alexander Barron (s3831619)
- Arian Najafi Yamchelo (s3910902)

RMIT University - Academic Integrity Warning:
> "For serious breaches of academic integrity, students can be charged with academic misconduct. Possible penalties include **cancellation of results** and **expulsion resulting in the cancellation of a student's program**."
For more information visit [Academic Integrity at RMIT](https://www.rmit.edu.au/students/my-course/assessment-results/academic-integrity)

## Enhancements

### Minor

1. **Help:** Use command "help" during a game to see a list of valid commands.
2. **Better invalid input:** Invalid inputs provide a more meaningful error message.
3. **Colour:** Tiles placed now have a corresponding background colour.
4. **Unicode/emoji tile symbols:** Tiles placed now have a corresponding emoji icon.

### Major

**1. Place multiple tiles (Not available in single player mode)**

to place multiple tile use the following command

```
> place multiple <colour><shape> at <row><col>
```

and to stop placing multiple tiles

```
> stop place multiple
```

**2. AI (Single player mode)**

to play against AI (single player mode) run the following command

```
./qwirkle --ai
```

## How to run

To run the app, change to the following directory

```
cd ../apt-a2-m3
```

and run the following command

```
make
```

and then

```
./qwirkle  
```

or to run the app with test mode enabled, run the following command

```
./qwirkle T
```

then you can play Qwirkle

```
Welcome to Qwirkle
------------------

Menu
----

1. New game
2. Load game
3. Help
4. Credits (show student information)
5. Quit
> 
```

## How to run tests

If you want to test the game, a set of predefined tests have been created and loaded. Run these with the following command from the games directory

```
./tests/run-tests.sh  
```

### References

Corob-msft (n.d.). How to: Define move constructors and move assignment operators (C++). [online] learn.microsoft.com. Available at: https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170 [Accessed 24 Jan. 2023].

DaniWeb. (n.d.). How to delete column in 2d vector, c++. [online] Available at: https://www.daniweb.com/programming/software-development/threads/488453/how-to-delete-column-in-2d-vector-c [Accessed 15 Feb. 2023].

Göhring, C. (2021). 3 Ways To Parse Command Line Arguments in C++: Quick, Do-It-Yourself, Or Comprehensive. [online] Medium. Available at: https://medium.com/@mostsignificant/3-ways-to-parse-command-line-arguments-in-c-quick-do-it-yourself-or-comprehensive-36913284460f [Accessed 15 Feb. 2023].

Not Defined Tech. (2022). How to add color to your Terminal output. [online] Available at: https://notdefined.tech/blog/how-to-add-color-to-your-terminal-output/ [Accessed 15 Feb. 2023].

Quora. (n.d.). How do you generate a random number between 1 and 6 in C++? [online] Available at: https://www.quora.com/How-do-you-generate-a-random-number-between-1-and-6-in-C?share=1 [Accessed 15 Feb. 2023].

Regexr.com. (n.d.). [online] Available at: https://regexr.com [Accessed 19 Jan. 2023].

Software Testing Help. (n.d.). C++ regex Tutorial: Regular Expressions In C++ With Examples. [online] Available at: https://www.softwaretestinghelp.com/regex-in-cpp/.

Stack Overflow. (n.d.). c - segmentation fault linked list. [online] Available at: https://stackoverflow.com/questions/21039913/segmentation-fault-linked-list [Accessed 13 Jan. 2023].

Stack Overflow. (n.d.). char - How do I increment letters in c++? [online] Available at: https://stackoverflow.com/questions/8487255/how-do-i-increment-letters-in-c [Accessed 13 Jan. 2023].

Stack Overflow. (n.d.). c++ - Checking whether a vector is empty. [online] Available at: https://stackoverflow.com/questions/3863282/checking-whether-a-vector-is-empty [Accessed 13 Jan. 2023].

Stack Overflow. (n.d.). c++ - how to do a vector deep copy. [online] Available at: https://stackoverflow.com/questions/45703227/how-to-do-a-vectorclass-objects-deep-copy [Accessed 15 Feb. 2023].

Stack Overflow. (n.d.). How can I diff 2 files while ignoring leading white space. [online] Available at: https://stackoverflow.com/questions/16423024/how-can-i-diff-2-files-while-ignoring-leading-white-space [Accessed 15 Feb. 2023].

Stack Overflow. (n.d.). Regex for numbers 1-25. [online] Available at: https://stackoverflow.com/questions/39138073/regex-for-numbers-1-25 [Accessed 19 Jan. 2023].

262588213843476 (n.d.). ANSI Escape Codes. [online] Gist. Available at: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797.

262588213843476 (n.d.). ANSI Escape Codes. [online] Gist. Available at: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797.

262588213843476 (n.d.). ANSI Escape Codes. [online] Gist. Available at: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797.

unicode-table.com. (n.d.). Geometric Shapes Extended. [online] Available at: https://unicode-table.com/en/blocks/geometric-shapes-extended/ [Accessed 15 Feb. 2023].

web, J.M.J. developer W.G.L.W.P. about the and WordPress, programming I. offer my services as a developer for your sites W. us page | S.W.G.L. (n.d.). ☺︎ Unicode symbols to copy/paste ✄✐. [online] wpRock. Available at: https://wprock.fr/en/t/unicode/ [Accessed 15 Feb. 2023].

www.programiz.com. (n.d.). C++ Ternary Operator (With Examples). [online] Available at: https://www.programiz.com/cpp-programming/ternary-operator.