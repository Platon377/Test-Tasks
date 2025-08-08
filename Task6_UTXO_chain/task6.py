import csv
from collections import defaultdict, deque

def read_csv(file):
    read = []
    f = open(file, newline = "")
    scanner = csv.DictReader(f, delimiter = ";")
    for row in scanner:
        input = [i for i in row["inputs"].split(";")]
        output = [i for i in row["outputs"].split(";")]
        read.append({"id" : row["id"], "inputs":input, "outputs" : output})
    f.close()
    return read

def filter(data):
    filtered = []
    for transaction in data:
        if len(transaction["inputs"]) == 1 and len(transaction["outputs"]) == 2:
            filtered.append(transaction)

    return filtered


def build_graph(transactions):
    gr = defaultdict(list)
    in_degree = defaultdict(int)
    nodes = set()

    for tx in transactions:
        parent = tx["inputs"][0]
        out1, out2 = tx["outputs"]
        gr[parent].append(out1)
        gr[parent].append(out2)

        nodes.add(parent)
        nodes.add(out1)
        nodes.add(out2)

        in_degree[out1]+=1
        in_degree[out2]+=1

        if parent not in in_degree:
            in_degree[parent] = 0

    return gr, in_degree, nodes

def find_roots(nodes, in_degree):
    return [node for node in nodes if in_degree[node] == 0]

def bfs(root, graph):
    visited = set()
    q = deque([(root, 0)])
    mx = 0

    while q:
        node, dist = q.popleft()
        visited.add(node)
        mx = max(mx, dist)
        for child in graph.get(node, []):
            if child not in visited:
                q.append((child, dist + 1))
                visited.add(child)

    return mx

def find_chain(graph, in_degree, nodes):
    mx_length = 0
    for root in find_roots(nodes, in_degree):
        length = bfs(root, graph)
        mx_length = max(mx_length, length)

    return mx_length

graph, in_degree, nodes = build_graph(filter(read_csv(input("Enter file name: "))))
longest_chain = find_chain(graph, in_degree, nodes)
print(longest_chain)
