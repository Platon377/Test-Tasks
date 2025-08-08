How to run? (in PyCharm)
- open the source file in PyCharm
- run, using appropriate button

How to run? (in terminal)
- install the requests and beautifulsoup4
```bash 
pip install requests
pip install beautifulsoup4
```
- to run, use the command:
```bash
python3 task4.py
```

How it works?
- the search is based on the BFS, starting from the page, passed by user
- to optimize the search, we store already visited links
- to improve the speed of search, the parallelizaton with threads is used