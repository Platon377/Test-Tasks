How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task8.cpp -o task8
```
- to run, use the command:
```bash
./task8
```

How it works?
- the optimal strategy is to buy and fix affordable laptops with the highst gain first
- for that puprose we use min and max heap
- in the min heap we store pairs (price, gain), if the price is less than current capital, then we can afford this laptop and it's added into the max heap
- from the max heap we take the elemnt with the highest gain, meaning that we process this laptop and change the capital c accordingly
- the heap is appropriate data structure, because we only insert elements and delete the min/max, which heap accomplishes in O(log n) time
- the process continues until there are enough laptops or N is not exceeded



