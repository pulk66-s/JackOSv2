import sys
import os
from env import find_all_dep_file
from graph import Graph, GraphParser
from display import display_graph

def check_arg():
    if len(sys.argv) != 2:
        print("Error: Invalid number of arguments")
        print("Usage: python3 main.py <dep_folder>")
        sys.exit(1)
    if not os.path.exists(sys.argv[1]):
        print("Error: Folder does not exist")
        sys.exit(1)

def main():
    check_arg()
    bin_path = sys.argv[1]
    all_dep_files = find_all_dep_file(bin_path)
    graph = Graph(all_dep_files)
    parser = GraphParser(graph)
    for file in all_dep_files:
        parser.parse_node(graph.deps[file])
    display_graph(graph)

if __name__ == "__main__":
    main()
