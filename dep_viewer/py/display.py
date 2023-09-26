from pyvis.network import Network
import networkx as nx

def display_graph(graph):
    net = Network(notebook=True)
    for name, node in graph.nodes.items():
        net.add_node(name, label=name)
    net.toggle_physics(True)
    for name, node in graph.nodes.items():
        for dep in node.children:
            net.add_edge(name, dep.name)
    net.show("graph.html")
