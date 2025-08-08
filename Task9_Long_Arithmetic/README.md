How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task9.cpp -o task9
```
- to run, use the command:
```bash
./task9
```

How it works?
- the core idea is storing the big integers in a vector of digits
- vector is filled by converting the number from base 10 to another, large enough base, in this case base of 10^8
- all the arithmetical are implemented similarly to normal integer rules
- base 10^8 is chosen in order not to exit long long type while multiplying
- C++ language in this case is especially helpful, because it provides the opportunity to overload operators

Notes:
- in the main method unit tests are provided



