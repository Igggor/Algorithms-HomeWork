#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using Vertex = size_t;

class Graph {
public:
    Graph();
    Graph(size_t n);
    bool empty() const;
    size_t size() const;
    Graph(size_t vertex_count);
    const std::vector<Vertex>& GetAdjucents(Vertex v) const;
    std::vector<Vertex>& GetAdjucents(Vertex v);
    Graph(const Graph& rhs);
    Graph(Graph&& rhs);
    
    Graph getTranspose() const;
    std::vector<std::vector<Vertex>> kosarajuSCC() const;
    
private:
    std::vector<std::vector<Vertex>> graph_;
};

size_t Graph::size() const {
    return graph_.size();
}

bool Graph::empty() const {
    return !size();
}

Graph::Graph(size_t vertex_count) : graph_(vertex_count) {}

Graph::Graph(const Graph& rhs) {
    graph_ = rhs.graph_;
}

Graph::Graph(Graph&& rhs) {
    graph_ = std::move(rhs.graph_);
}

const std::vector<Vertex>& Graph::GetAdjucents(Vertex v) const {
    return graph_[v];
}

std::vector<Vertex>& Graph::GetAdjucents(Vertex v) {
    return graph_[v];
}

Graph Graph::getTranspose() const {
    Graph transpose(size());
    
    for (Vertex u = 0; u < size(); ++u) {
        for (Vertex v : GetAdjucents(u)) {
            transpose.GetAdjucents(v).push_back(u);
        }
    }
    
    return transpose;
}

void fillOrderDFS(Vertex u, const Graph& graph, 
                 std::vector<bool>& visited, std::stack<Vertex>& stack) {
    visited[u] = true;
    
    for (Vertex v : graph.GetAdjucents(u)) {
        if (!visited[v])
            fillOrderDFS(v, graph, visited, stack);

    }    
    stack.push(u);
}

void dfsSCC(Vertex u, const Graph& graph, 
            std::vector<bool>& visited, std::vector<Vertex>& component) {
    visited[u] = true;
    component.push_back(u);
    
    for (Vertex v : graph.GetAdjucents(u)) {
        if (!visited[v])
            dfsSCC(v, graph, visited, component);
    }
}

std::vector<std::vector<Vertex>> Graph::kosarajuSCC() const {
    std::stack<Vertex> stack;
    std::vector<bool> visited(size(), false);
    std::vector<std::vector<Vertex>> sccList;
    
    for (Vertex u = 0; u < size(); ++u) {
        if (!visited[u])
            fillOrderDFS(u, *this, visited, stack);
    }
    
    Graph transpose = getTranspose();
    
    std::fill(visited.begin(), visited.end(), false);
    
    while (!stack.empty()) {
        Vertex u = stack.top();
        stack.pop();
        
        if (!visited[u]) {
            std::vector<Vertex> component;
            dfsSCC(u, transpose, visited, component);
            sccList.push_back(component);
        }
    }
    
    return sccList;
}
