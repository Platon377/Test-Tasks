How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task2.cpp -o task2
```
- to run, use the command:
```bash
./task2
```

How it works?
- the road is internally marked as 0 in the matrix, the wall is 1
- the algorithm is using the backtracking strategy and recursion
- the vector for deciding the next step is constantly shuffled, what creates more interesting patters and doesn't allow universal strategies(i.e. there's no bias in direction)
- since each cell is visted once, the time complexity of the algorithm is O(Height * Width)
- for odd dimensions there is always a path from the entrance to the exit


