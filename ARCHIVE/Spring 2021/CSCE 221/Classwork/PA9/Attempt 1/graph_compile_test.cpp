#include <iostream>
#include "graph.h"

int main() {
    Graph G;
    G.add_vertex(1);
    G.add_vertex(2);
    G.add_vertex(3);
    std::cout << G.vertex_count() << std::endl;
    std::cout << G.contains_vertex(1) << std::endl;
    std::cout << G.distance(1) << std::endl;
    G.add_edge(1,2,3);
    G.add_edge(2,3,4);
    std::cout << G.edge_count() << std::endl;
    std::cout << G.contains_edge(1,2) << std::endl;
    std::cout << G.cost(1,2) << std::endl;
    Graph copy = G;
    G = copy;
    G.remove_vertex(1);    
    G.remove_edge(1,2);
    std::list<std::pair<size_t,size_t>> mst = G.prim();
    double tree_cost = 0;
    for (const auto& edge : mst) {
        tree_cost += G.cost(edge.first,edge.second);
    }
    std::cout << tree_cost <<std::endl;
}
