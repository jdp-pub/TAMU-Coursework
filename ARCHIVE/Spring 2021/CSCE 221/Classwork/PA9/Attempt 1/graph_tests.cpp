#include "graph.h"
#include <iostream>
#include <cmath>
#include "hashtable_open_addressing.h"
#include <vector> 

int main() {
    // TODO(student): write many organized and effective tests
    /*
    {
        Graph g;

        g.add_vertex(1);
        g.add_vertex(2);
        g.add_edge(1,2, 3);
        g.add_vertex(3);
        g.add_vertex(4);
        g.add_edge(1,4, 5);
        
        g.printGraph();
        g.remove_vertex(1);

        g.printGraph();

        g.add_edge(2,4, 5);
        g.add_edge(3,4, 5);
        g.add_edge(2,3, 5);

        g.printGraph();

        g.remove_edge(2,4);
        g.printGraph();

        g.remove_edge(2,3);
        g.printGraph();

        g.remove_edge(3,4);
        g.printGraph();

        g.prim();
    }

    {
        Graph g;

        g.add_vertex(1);
        g.add_vertex(2);
        
        g.add_vertex(3);
        g.add_vertex(4);
        g.add_edge(1,2, 3);
        g.add_edge(1,4, 5);
        g.add_edge(4,3, 3);
        g.add_edge(2,3, 2);
        g.add_edge(1,3, 1);
        g.add_edge(4,2, 1);

        g.printGraph();
        std::list<std::pair<size_t,size_t>> mst = g.prim();
        std::list<std::pair<size_t,size_t>>::iterator it = mst.begin();
        for(size_t i = 0; i < mst.size(); ++i){
            cout << it->first << "->{" << g.cost(it->first, it->second) << "}" << it->second << endl;
            std::advance(it, 1);
        }
        
    }
    */
    {
        Graph g;

        g.printGraph();
        g.printMST(g.prim());

        for(size_t i = 0; i < 10; ++i){
            g.add_vertex(i);
        }

        g.add_edge(0,1, 10);
        g.add_edge(1,2, 10);
        g.add_edge(0,3,30);
        g.add_edge(0,4,30);
        g.add_edge(1,4, 10);
        g.add_edge(3,4, 10);
        g.add_edge(3,2, 5);
        g.add_edge(5,0, 20);
        g.add_edge(5,4, 20);
        g.add_edge(6,2, 5);
        g.add_edge(6,1, 5);
        g.add_edge(7,5, 5);
        g.add_edge(7,1, 5);
        g.add_edge(8,5, 10);
        g.add_edge(8,0, 10);
        g.add_edge(9,2, 100);

        g.printGraph();


        
        g.printMST(g.prim());

        
    }

    {
        std::cout << "make an empty graph" << std::endl;
Graph G;

std::cout << "add vertices" << std::endl;
for (size_t n = 1; n <= 7; n++) {
	G.add_vertex(n);
}

std::cout << "add undirected edges" << std::endl;
G.add_edge(1,2,5);  // 1 --{5} 2; (edge between 1 and 2 with weight 5)
G.add_edge(1,3,3);
G.add_edge(2,3,2);
G.add_edge(2,5,3);
G.add_edge(2,7,1);
G.add_edge(3,4,7);
G.add_edge(3,5,7);
G.add_edge(4,1,2);
G.add_edge(4,6,6);
G.add_edge(5,4,2);
G.add_edge(5,6,1);
G.add_edge(7,5,1);

std::cout << "G has " << G.vertex_count() << " vertices" << std::endl;
std::cout << "G has " << G.edge_count() << " edges" << std::endl;

std::cout << "compute a minimum spanning tree" <<std::endl;
std::list<std::pair<size_t,size_t>> mst = G.prim();

std::cout << "print minimum spanning tree" <<std::endl;
double tree_cost = 0;
for (const std::pair<size_t,size_t>& edge : mst) {
    std::cout << edge.first << " --{"<<G.cost(edge.first,edge.second)<<"} " << edge.second << ";" << std::endl;
    tree_cost += G.cost(edge.first,edge.second);
}
std::cout << "tree cost = " << tree_cost <<std::endl;

    }
    return 0;
}
