class Graph:
    def __init__(self, files):
        self.deps = { k: GraphNode(k) for k in files }
        self.nodes = {}

    def __str__(self):
        return str({ k: str(v) for k, v in self.deps.items() })

    def contains(self, name):
        return name in map(lambda x: x.name, self.nodes.values())

class GraphNode:
    def __init__(self, path = None):
        self.path = path if path is not None else ""
        self.name = ""
        if path is None:
            self.content = ""
        else:
            with open(path, "r") as f:
                self.content = f.read()
        self.children = []

    def __str__(self):
        return str({
            "path": self.path,
            "content": self.content,
        })

class GraphParser:
    def __init__(self, graph):
        self.graph = graph

    def parse_node(self, node):
        words = node.content.split()
        words = [ w for w in words if w != "\\" and not w.endswith(".o:") ]
        name, deps = words[0], words[1:]
        if not self.graph.contains(name):
            node.name = name
            self.graph.nodes[name] = node
        for dep in deps:
            if dep not in self.graph.nodes:
                new_node = GraphNode()
                new_node.name = dep
                self.graph.nodes[dep] = new_node
            if self.graph.nodes[dep] not in self.graph.nodes[name].children:
                self.graph.nodes[name].children.append(self.graph.nodes[dep])
