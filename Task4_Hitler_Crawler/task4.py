import requests
from bs4 import BeautifulSoup
from collections import deque
from concurrent.futures import ThreadPoolExecutor

start = input('Enter the starting link: ')
ziel = "/wiki/Adolf_Hitler"
base_url = start.split("/wiki")[0]

def getLinks(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.text, "html.parser")

    found = set()
    for link in soup.find(id = "bodyContent").find_all("a"):
        if "href" not in link.attrs:
            continue
        if link["href"].startswith("/wiki/") and ":" not in link["href"]:
            found.add(base_url + link["href"])

    return found

def BFSlike(start, target, depth):
    visited = set([start])
    cur_level = [(start, [start])]

    for i in range(depth + 1):
        next_level = []
        with ThreadPoolExecutor(5) as pool:
            res = []
            for url, path in cur_level:
                res.append((pool.submit(getLinks, url), path))

            for future, path in res:
                try:
                    links = future.result()
                except:
                    continue

                for link in links:
                    if link.endswith(target):
                        return path + [link]
                    if link not in visited:
                        visited.add(link)
                        next_level.append((link, path + [link]))

        cur_level = next_level


res = BFSlike(start, ziel, 6)
if res:
    print("Path:")
    for step in res:
        print(step)

else:
    print("Hitler not found")
