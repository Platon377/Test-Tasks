How to run? (in PyCharm)
- open the source file in PyCharm
- run, using appropriate button

How to run? (in terminal)
- to run, use the command:
```bash
python3 task6.py
```

How it works?
- the problem is actually a graph problem, where we need to firstly filter transaction, based on the given criteria and then find the longest path
- firstly we read the data from the csv file, the columns should be named id, inputs, outputs
- then the data is being filtered, for the internal representation of the graph the adjacency list is used
- since there should be 1 input and 2 outputs, the graph after filtering is the forest of the binary trees
- then it's enough to find the roots and start from them the bfs to find the longest path in each tree
- the maximal length of the all the pathes in each tree is the solution to the problem

Note:
- example csv file is also provided