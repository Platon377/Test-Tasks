<<<<<<< HEAD
How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task1.cpp -o task1
```
- to run, use the command:
```bash
./task1
```

How to terminate the execution?
- type the word "end" and press enter

How it works?
- all the data about orders is gathered into a class, providing getters for each field
- the trading process is implemented using multimaps, where the key is the price and the associate value is the Order object
- since trading is done between the order with the highest bid and lowest price, we need efficiently access and extract min and max, which in the multimap is done in O(1) and O(log n) respectively (since internally multimap is the balanced binary tree with elements as leafes)
- then prices of these orders are compared, leading to none or 1 (if it was only partially satisfied) order inserted back into the multimap - O(log n)
- so, the time complexity of 1 iteration of the while-loop is O(2*log n + log n + 1) = O(log n)
- the overall program runs indefinitely, accepting orders until the user inputs end
- so, the runtimes depends on the type of user interactions and number of intputs, so it's impossible to express the tiem complexity using O-notation


=======
# Test-Tasks
This repository contains the solutions to the problems
.
>>>>>>> cce319ff7b4713d081343a6bd90434c26c55beaf
