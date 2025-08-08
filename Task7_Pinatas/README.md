How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task7.cpp -o task7
```
- to run, use the command:
```bash
./task7
```

How it works?
- the solution uses the dynamic programming paradigma by dividing the initial problem to the problems, already solved
- to store the already computed results, the matrix is used, so the space complexity is O(n^2)
- the time complexity is O(n^3)



