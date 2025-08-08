How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button
- add csv filenames on toolbar Project -> Properties -> Configuration Properties -> Debugging -> Command Arguments 

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task5.cpp -o task5
```
- to run, use the command:
```bash
./task5 <fileName.csv>
```

How it works?
- that's a classical NP-hard problem, which can be solved using dynamic programming in O(n * M), where n is #transactions and M is the max size of the backpack, the runtime is pseudo-polynomial, because it's actually exponential in log M
- my solution implements 2-approximation (meaning that implemented and optimal solution differ max. by factor 2) by sorting the transactions by descending fee/price
- given that the size of the input data is 10^5 items, implemented solution is actually very close to the optimal one (in practice << 2 times), so it's more effieceint in terms of computations and space utilized
- as mentioned before transactions are sorted in decsending order of ration fee/price and "packed" if there's left enough place in the backpack 
- the time complexity of the greedy approach is O(n), where n := #transactions

Note:
- example csv file is also provided



