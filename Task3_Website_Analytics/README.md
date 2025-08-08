How to run? (in VS)
- open the source file in Visual Studio
- run, using appropriate button
- add csv filenames on toolbar Project -> Properties -> Configuration Properties -> Debugging -> Command Arguments 

How to run? (in terminal)
- to compile, use the command 
```bash 
g++ -Wall -std=c++17 task3.cpp -o task3
```
- to run, use the command:
```bash
./task3 <fileName1.csv> <fileName2.csv>
```

How it works?
- the data is read from 2 csv file with ";" as a delimeter; the columns should be arranged in form user_id,  product_id, timestamp
- the unordered map is used to store the data, where ther user_id is the key and its associated value is a set of the visited pages
- firstly we iterate through the users of the second day (O(n)) and check whether they're present among the users of the first day (since unsorted_map is a hashtable internally, this check is done in expected O(1))
- then we check whether the set difference of the pages visted on both days is empty set, if not, then on the second day user visited the page that hadn’t been visited by this user on the first day
- this check was impemented as the seperate function and benefits heavily from the fact that unordered_set inside is also a hash table, providing .find() method with expected O(1) time
- reading data from the file in this case is dominatin in O, so the general time complexity is O(m + n), where m and n is the #users on first and second days respectively (more detailed in code in form of comments)

Note:
- example csv files are also provided



