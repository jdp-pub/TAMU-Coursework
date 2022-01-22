#include "graph.h"
#include <iostream>
#include <cmath>
#include "hashtable_open_addressing.h"
#include <vector> 

int main() {
    // TODO(student): write many organized and effective tests
/*
    Constructors
    Graph() - makes an empty graph.
    Graph(const Graph&) - constructs a deep copy of a graph
    Graph& operator=(const Graph&) - assigns a deep copy of a graph
    ~Graph() - destructs a graph (frees all dynamically allocated memory)

    Capacity
    x size_t vertex_count() const - the number of vertices in the graph
    size_t edge_count() const - the number of edges in the graph

    Element Access
    x bool contains_vertex(size_t id) const - return true if the graph contains a vertex with the specified identifier, false otherwise.
    bool contains_edge(size_t src, size_t dest) const - return true if the graph contains an edge with the specified members (as identifiers), false otherwise.
    double cost(size_t src, size_t dest) const - returns the weight of the edge between src and dest, or INFINITY if none exists.

    Modifiers
    x bool add_vertex(size_t id) - add a vertex with the specified identifier if it does not already exist, return true on success or false otherwise.
    bool add_edge(size_t src, size_t dest, double weight=1) - add a directed edge from src to dest with the specified weight if there is no edge from src to dest, return true on success, false otherwise.
    bool remove_vertex(size_t id) - remove the specified vertex from the graph, including all edges of which it is a member, return true on success, false otherwise.
    bool remove_edge(size_t src, size_t dest) - remove the specified edge from the graph, but do not remove the vertices, return true on success, false otherwise.

    Optional
    Graph(Graph&&) - move constructs a deep copy of a graph
    Graph& operator=(Graph&&) - move assigns a deep copy of a graph
*/

    
    {//basic functionality
        Graph g = {};
        cout << "inserting 10...: " << std::boolalpha << g.add_vertex(10) << endl;
        cout << "inserting 10...: " << std::boolalpha << g.add_vertex(10) << endl;
        g.printGraph();
        cout << "contains 10?: " << std::boolalpha << g.contains_vertex(10) << endl;

        cout << "removing 10...: " << std::boolalpha << g.remove_vertex(10) << endl;
        cout << "removing 10...: " << std::boolalpha << g.remove_vertex(10) << endl;
        g.printGraph();

        cout << "inserting 10...: " << std::boolalpha << g.add_vertex(10) << endl;
        cout << "inserting 9...: " << std::boolalpha << g.add_vertex(9) << endl;
        test("graph_tests.cpp", "Insert edge, 9->{3}10", true, g.add_edge(9,10,3),__LINE__);
        test("graph_tests.cpp", "edge cost, 9->{3}10", 3.0, g.cost(9,10),__LINE__);
        g.printGraph();
    }
    
   
   {
        Graph g = {};
        // INSERT
        for(size_t i = 0; i < 10; ++i){
            test("graph_tests.cpp", "Graph::vertex_count()", i, g.vertex_count(), __LINE__);
            test("graph_tests.cpp", "Graph::add_vertex("+ std::to_string(i) + ")", true, g.add_vertex(i), __LINE__);
        }
        for(size_t i = 0; i < 10; ++i){
            test("graph_tests.cpp", "Graph::vertex_count()", 10, (int)(g.vertex_count()), __LINE__);
            test("graph_tests.cpp", "Graph::add_vertex(" + std::to_string(i) + ")", false, g.add_vertex(i), __LINE__);
        }
        g.printGraph();

        for(size_t i = 100; i < 110; ++i){
            test("graph_tests.cpp", "Graph::vertex_count()", i - 90, g.vertex_count(), __LINE__);
            test("graph_tests.cpp", "Graph::add_vertex("+ std::to_string(i) + ")", true, g.add_vertex(i), __LINE__);
        }
        for(size_t i = 100; i < 110; ++i){
            test("graph_tests.cpp", "Graph::vertex_count()", 20, (int)(g.vertex_count()), __LINE__);
            test("graph_tests.cpp", "Graph::add_vertex(" + std::to_string(i) + ")", false, g.add_vertex(i), __LINE__);
        }
        g.printGraph();

        for(size_t i = 0; i < 110; ++i){
            test("graph_tests.cpp", "Graph::contains_vertex(" + std::to_string(i) + ")", ((i < 10) || (i > 99)), g.contains_vertex(i), __LINE__);
        }
        for(size_t i = 0; i < 110; ++i){
            test("graph_tests.cpp", "Graph::remove_vertex(" + std::to_string(i) + ")", ((i < 10) || (i > 99)), g.remove_vertex(i), __LINE__);
        }

        g.printGraph();
        for(size_t i = 0; i < 10; ++i){
            test("graph_tests.cpp", "Graph::vertex_count()", i, g.vertex_count(), __LINE__);
            test("graph_tests.cpp", "Graph::add_vertex(" + std::to_string(i) + ")", true, g.add_vertex(i), __LINE__);
        }

        g.printGraph();
        test("graph_tests.cpp", "Graph::remove_vertex(" + std::to_string(5) + ")", true, g.remove_vertex(5), __LINE__);
        test("graph_tests.cpp", "Graph::remove_vertex(" + std::to_string(5) + ")", false, g.remove_vertex(5), __LINE__);
        g.printGraph();
        test("graph_tests.cpp", "Graph::remove_vertex(" + std::to_string(0) + ")", true, g.remove_vertex(0), __LINE__);
        g.printGraph();
        test("graph_tests.cpp", "Graph::remove_vertex(" + std::to_string(9) + ")", true, g.remove_vertex(9), __LINE__);
        g.printGraph();  
    }
    
    {// insert edge
        Graph g = {};

        for(size_t i = 0; i < 10; ++i){
            test("graph_tests.cpp", "Graph::vertex_count()", i, g.vertex_count(), __LINE__);
            test("graph_tests.cpp", "Graph::add_vertex("+ std::to_string(i) + ")", true, g.add_vertex(i), __LINE__);
        }
        g.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(0, 5, 10)", true, g.add_edge(0, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 4, 11)", true, g.add_edge(0, 4, 11), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 3)", true, g.add_edge(0, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 9, 100)", true, g.add_edge(5, 9, 100), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(111, 5555, 436534)", false, g.add_edge(111, 5555, 436534), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 5, 44)", false, g.add_edge(0, 5, 44), __LINE__);

        g.printGraph();

        g = g;
        g.printGraph();
        Graph k(g);
        k.printGraph();

        test("graph_tests.cpp", "g.Graph::add_vertex(555)", true, g.add_vertex(555), __LINE__);
        test("graph_tests.cpp", "g.Graph::add_edge(6, 8, 170)", true, g.add_edge(6, 8, 170), __LINE__);
        test("graph_tests.cpp", "g.Graph::add_edge(3, 4, 121)", true, g.add_edge(3, 4, 121), __LINE__);
        g.printGraph();
        k.printGraph();

        test("graph_tests.cpp", "k.Graph::add_vertex(755)", true, k.add_vertex(755), __LINE__);
        test("graph_tests.cpp", "k.Graph::add_edge(6, 4, 121)", true, k.add_edge(6, 4, 121), __LINE__);
        g.printGraph();
        k.printGraph();

        g = k;
        g.printGraph();
        test("graph_tests.cpp", "k.Graph::add_edge(9, 755, 123)", true, k.add_edge(9, 755, 123), __LINE__);
        g.printGraph();
        k.printGraph();

        test("graph_tests.cpp", "k.Graph::cost(9, 755)", 123.0, k.cost(9, 755), __LINE__);
        test("graph_tests.cpp", "k.Graph::cost(3, 755)", (double)(INFINITY), k.cost(3, 755), __LINE__);
        test("graph_tests.cpp", "k.Graph::cost(9, 75)", (double)(INFINITY), k.cost(9, 75), __LINE__);
        test("graph_tests.cpp", "k.Graph::cost(0, 4)", 11.0, k.cost(0, 4), __LINE__);

        test("graph_tests.cpp", "k.Graph::remove_edge(9, 755)", true, k.remove_edge(9, 755), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_edge(9, 755)", false, k.remove_edge(9, 755), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_edge(0, 755)", false, k.remove_edge(0, 755), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_edge(0, 4)", true, k.remove_edge(0,4), __LINE__);
        k.printGraph();

        test("graph_tests.cpp", "k.Graph::remove_vertex(0)", true, k.remove_vertex(0), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_vertex(0)", false, k.remove_vertex(0), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_vertex(1)", true, k.remove_vertex(1), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_vertex(6)",true, k.remove_vertex(6), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_vertex(110)", false, k.remove_vertex(110), __LINE__);
        k.printGraph();

        for(size_t i = 0; i < 10; ++i){
           k.add_vertex(i);
        }
        k.printGraph();
    }
    
    {//dijkstra
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_vertex(4);

        g.add_edge(1,2,3);
        g.add_edge(1,3,1);
        g.add_edge(2,3,1);
        g.add_edge(3,2,1);
        g.add_edge(3,4,10);

        g.printGraph();

        g.dijkstra(1);

        test("graph_tests.cpp", "Graph::distance(2)",2.0, g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(3)",1.0, g.distance(3), __LINE__);
        test("graph_tests.cpp", "Graph::distance(4)",11.0, g.distance(4), __LINE__);
        test("graph_tests.cpp", "Graph::distance(20)",(double)(INFINITY), g.distance(20), __LINE__);
        g.print_shortest_path(2);
        g.print_shortest_path(4);
        g.print_shortest_path(10);
        g.print_shortest_path(1);
    }

    {
        Graph g;
        g.add_vertex(1);
        g.add_vertex(2);
        g.add_vertex(3);
        g.add_vertex(4);


        test("graph_tests.cpp", "Graph::add_edge(1, 2)", true, g.add_edge(1, 2), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 3)", true, g.add_edge(1, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 3)", true, g.add_edge(2, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(3, 2)", true, g.add_edge(3, 2), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(4, 3)", true, g.add_edge(4, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 3)", false, g.add_edge(2, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(3, 2)", false, g.add_edge(3, 2), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(4, 3)", false, g.add_edge(4, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 1)", true, g.add_edge(2, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 4)", true, g.add_edge(2, 4), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 4)", true, g.add_edge(1, 4), __LINE__);

        g.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(0, 5, 10)", false, g.add_edge(0, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 4, 11)", false, g.add_edge(0, 4, 11), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 3)", false, g.add_edge(0, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 9, 100)", false, g.add_edge(5, 9, 100), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(111, 5555, 436534)", false, g.add_edge(111, 5555, 436534), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 5, 44)", false, g.add_edge(0, 5, 44), __LINE__);

        test("graph_tests.cpp", "Graph::add_edge(1, 5, 10)", false, g.add_edge(1, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 4, 11)", false, g.add_edge(5, 4, 11), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 30)", false, g.add_edge(1, 30), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(3, 9, 100)", false, g.add_edge(3, 9, 100), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(4, 5555, 436534)", false, g.add_edge(4, 5555, 436534), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 5, 44)", false, g.add_edge(2, 5, 44), __LINE__);

        g.printGraph();

        Graph t(g);
        t.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(3, 4)", true, g.add_edge(3, 4), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(3, 3)", true, g.add_edge(3, 3), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(4, 1)", true, g.add_edge(4, 1), __LINE__);

        t.printGraph();
        g.printGraph();

        test("graph_tests.cpp", "t.Graph::cost(1, 4)", 1.0, g.cost(1, 4), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(3, 755)", (double)(INFINITY), g.cost(3, 755), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(755, 3)", (double)(INFINITY), g.cost(3, 755), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(9, 75)", (double)(INFINITY), g.cost(9, 75), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(4, 2)", (double)(INFINITY), g.cost(4, 2), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(3, 1)", (double)(INFINITY), g.cost(3, 1), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(1, 3)", 1.0, g.cost(1, 3), __LINE__);
        test("graph_tests.cpp", "t.Graph::remove_edge(2, 4)", true, g.remove_edge(2,4), __LINE__);
        test("graph_tests.cpp", "t.Graph::cost(2, 4)", (double)(INFINITY), g.cost(2, 4), __LINE__);

        g.printGraph();

        Graph k;
        test("graph_tests.cpp", "k.Graph::cost(3, 755)", (double)(INFINITY), k.cost(3, 755), __LINE__);
        test("graph_tests.cpp", "k.Graph::remove_edge(2, 4)", false, k.remove_edge(2,4), __LINE__);
        test("graph_tests.cpp", "k.Graph::add_edge(4, 1)", false, k.add_edge(4, 1), __LINE__);

        
    }
    

    /*DIJKSTRA
        floating point weights, no path
        nonexistent vertex
        textbook example
    */
    
    {// floating point, disjoint paths
        Graph g;
        g.dijkstra(9);
        g.printGraph();
        test("graph_tests.cpp", "Graph::distance(1)", (double)(INFINITY) , g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(0)", true, g.add_vertex(0), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(10)", true, g.add_vertex(10), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(20)", true, g.add_vertex(20), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(110)", true, g.add_vertex(110), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(1230)", true, g.add_vertex(1230), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(13570)", true, g.add_vertex(13570), __LINE__);

        g.dijkstra(0);
        test("graph_tests.cpp", "Graph::distance(0)", 0.0 , g.distance(0), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", (double)(INFINITY) , g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(110)", (double)(INFINITY) , g.distance(110), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1230)", (double)(INFINITY) , g.distance(1230), __LINE__);
        test("graph_tests.cpp", "Graph::distance(13570)", (double)(INFINITY) , g.distance(13570), __LINE__);

        g.dijkstra(10);
        test("graph_tests.cpp", "Graph::distance(0)", (double)(INFINITY) , g.distance(0), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)",0.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(110)", (double)(INFINITY) , g.distance(110), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1230)", (double)(INFINITY) , g.distance(1230), __LINE__);
        test("graph_tests.cpp", "Graph::distance(13570)", (double)(INFINITY) , g.distance(13570), __LINE__);

        g.dijkstra(110);
        test("graph_tests.cpp", "Graph::distance(0)", (double)(INFINITY) , g.distance(0), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", (double)(INFINITY) , g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(110)", 0.0 , g.distance(110), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1230)", (double)(INFINITY) , g.distance(1230), __LINE__);
        test("graph_tests.cpp", "Graph::distance(13570)", (double)(INFINITY) , g.distance(13570), __LINE__);

        test("graph_tests.cpp", "Graph::add_edge(0, 10, 1.111)", true, g.add_edge(0, 10, 1.111), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 110, 110.0)", true, g.add_edge(0, 110, 110.0), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(0, 20, 1.0)", true, g.add_edge(0, 20, 1.0), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 110, 1.1711)", true, g.add_edge(10, 110, 1.1711), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1230, 10, 13.111)", true, g.add_edge(1230, 10, 13.111), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(110, 13570, 31.1511)", true, g.add_edge(110, 13570, 31.1511), __LINE__);
        g.printGraph();
        //////////////////////////////////////////////
        g.dijkstra(0);
        test("graph_tests.cpp", "Graph::distance(0)", 0.0 , g.distance(0), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", 1.111 , g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(20)", 1.0 , g.distance(20), __LINE__);
        test("graph_tests.cpp", "Graph::distance(110)", 2.2821 , g.distance(110), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1230)", (double)(INFINITY) , g.distance(1230), __LINE__);
        test("graph_tests.cpp", "Graph::distance(13570)", 33.4332 , g.distance(13570), __LINE__);

        g.dijkstra(10);
        test("graph_tests.cpp", "Graph::distance(0)", (double)(INFINITY) , g.distance(0), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)",0.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(110)", 1.1711 , g.distance(110), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1230)", (double)(INFINITY) , g.distance(1230), __LINE__);
        test("graph_tests.cpp", "Graph::distance(13570)", 32.3222 , g.distance(13570), __LINE__);

        g.dijkstra(110);
        test("graph_tests.cpp", "Graph::distance(0)", (double)(INFINITY) , g.distance(0), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", (double)(INFINITY) , g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(110)", 0.0 , g.distance(110), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1230)", (double)(INFINITY) , g.distance(1230), __LINE__);
        test("graph_tests.cpp", "Graph::distance(13570)", 31.1511 , g.distance(13570), __LINE__);

        g.printGraph();

    }

    {// dijkstra DAG spider shape
        Graph g;
        test("graph_tests.cpp", "Graph::add_vertex(5)", true, g.add_vertex(5), __LINE__);//body
        test("graph_tests.cpp", "Graph::add_vertex(9)", true, g.add_vertex(9), __LINE__);//head
        test("graph_tests.cpp", "Graph::add_vertex(90)", true, g.add_vertex(90), __LINE__);//fisrst joints
        test("graph_tests.cpp", "Graph::add_vertex(50)", true, g.add_vertex(50), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(59)", true, g.add_vertex(59), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(95)", true, g.add_vertex(95), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(1)", true, g.add_vertex(1), __LINE__);//second joints
        test("graph_tests.cpp", "Graph::add_vertex(10)", true, g.add_vertex(10), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(12)", true, g.add_vertex(12), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(2)", true, g.add_vertex(2), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(11)", true, g.add_vertex(11), __LINE__);//feet
        test("graph_tests.cpp", "Graph::add_vertex(101)", true, g.add_vertex(101), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(121)", true, g.add_vertex(121), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(21)", true, g.add_vertex(21), __LINE__);
        //g.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(5, 9, 10)", true, g.add_edge(5, 9, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 90, 10)", true, g.add_edge(5, 90, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 50, 10)", true, g.add_edge(5, 50, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 59, 10)", true, g.add_edge(5, 59, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 95, 10)", true, g.add_edge(5, 95, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(90, 1, 10)", true, g.add_edge(90, 1, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 10, 10)", true, g.add_edge(50, 10, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(59, 12, 10)", true, g.add_edge(59, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(95, 2, 10)", true, g.add_edge(95, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 11, 10)", true, g.add_edge(1, 11, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 101, 10)", true, g.add_edge(10, 101, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(12, 121, 10)", true, g.add_edge(12, 121, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 21, 10)", true, g.add_edge(2, 21, 10), __LINE__);
        //g.printGraph();

        g.dijkstra(5);
        test("graph_tests.cpp", "Graph::distance(5)", 0.0, g.distance(5), __LINE__);
        test("graph_tests.cpp", "Graph::distance(9)", 10.0, g.distance(9), __LINE__);
        test("graph_tests.cpp", "Graph::distance(90)", 10.0, g.distance(90), __LINE__);
        test("graph_tests.cpp", "Graph::distance(50)", 10.0, g.distance(50), __LINE__);
        test("graph_tests.cpp", "Graph::distance(59)", 10.0, g.distance(59), __LINE__);
        test("graph_tests.cpp", "Graph::distance(95)", 10.0, g.distance(95), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1)", 20.0, g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", 20.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(12)", 20.0, g.distance(12), __LINE__);
        test("graph_tests.cpp", "Graph::distance(2)", 20.0, g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(11)", 30.0, g.distance(11), __LINE__);
        test("graph_tests.cpp", "Graph::distance(101)", 30.0, g.distance(101), __LINE__);
        test("graph_tests.cpp", "Graph::distance(121)", 30.0, g.distance(121), __LINE__);
        test("graph_tests.cpp", "Graph::distance(21)", 30.0, g.distance(21), __LINE__);

        g.printGraph();
        g.dijkstra(90);
        test("graph_tests.cpp", "Graph::distance(5)", (double)(INFINITY), g.distance(5), __LINE__);
        test("graph_tests.cpp", "Graph::distance(9)", (double)(INFINITY), g.distance(9), __LINE__);
        test("graph_tests.cpp", "Graph::distance(90)",0.0, g.distance(90), __LINE__);
        test("graph_tests.cpp", "Graph::distance(50)", (double)(INFINITY), g.distance(50), __LINE__);
        test("graph_tests.cpp", "Graph::distance(59)",(double)(INFINITY), g.distance(59), __LINE__);
        test("graph_tests.cpp", "Graph::distance(95)", (double)(INFINITY), g.distance(95), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1)", 10.0, g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", (double)(INFINITY), g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(12)", (double)(INFINITY), g.distance(12), __LINE__);
        test("graph_tests.cpp", "Graph::distance(2)", (double)(INFINITY), g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(11)", 20.0, g.distance(11), __LINE__);
        test("graph_tests.cpp", "Graph::distance(101)", (double)(INFINITY), g.distance(101), __LINE__);
        test("graph_tests.cpp", "Graph::distance(121)",(double)(INFINITY), g.distance(121), __LINE__);
        test("graph_tests.cpp", "Graph::distance(21)", (double)(INFINITY), g.distance(21), __LINE__);
    }
    
    {// dijkstra spider shape
        Graph g;
        test("graph_tests.cpp", "Graph::add_vertex(5)", true, g.add_vertex(5), __LINE__);//body
        test("graph_tests.cpp", "Graph::add_vertex(9)", true, g.add_vertex(9), __LINE__);//head
        test("graph_tests.cpp", "Graph::add_vertex(90)", true, g.add_vertex(90), __LINE__);//fisrst joints
        test("graph_tests.cpp", "Graph::add_vertex(50)", true, g.add_vertex(50), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(59)", true, g.add_vertex(59), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(95)", true, g.add_vertex(95), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(1)", true, g.add_vertex(1), __LINE__);//second joints
        test("graph_tests.cpp", "Graph::add_vertex(10)", true, g.add_vertex(10), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(12)", true, g.add_vertex(12), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(2)", true, g.add_vertex(2), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(11)", true, g.add_vertex(11), __LINE__);//feet
        test("graph_tests.cpp", "Graph::add_vertex(101)", true, g.add_vertex(101), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(121)", true, g.add_vertex(121), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(21)", true, g.add_vertex(21), __LINE__);
        //g.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(5, 9, 10)", true, g.add_edge(5, 9, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 90, 10)", true, g.add_edge(5, 90, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 50, 10)", true, g.add_edge(5, 50, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 59, 10)", true, g.add_edge(5, 59, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 95, 10)", true, g.add_edge(5, 95, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(90, 1, 10)", true, g.add_edge(90, 1, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 10, 10)", true, g.add_edge(50, 10, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(59, 12, 10)", true, g.add_edge(59, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(95, 2, 10)", true, g.add_edge(95, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 11, 10)", true, g.add_edge(1, 11, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 101, 10)", true, g.add_edge(10, 101, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(12, 121, 10)", true, g.add_edge(12, 121, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 21, 10)", true, g.add_edge(2, 21, 10), __LINE__);

        test("graph_tests.cpp", "Graph::add_edge(9, 5, 10)", true, g.add_edge(9, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(90, 5, 10)", true, g.add_edge(90, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 5, 10)", true, g.add_edge(50, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(59, 5, 10)", true, g.add_edge(59, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(95, 5, 10)", true, g.add_edge(95, 5, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 90, 10)", true, g.add_edge(1, 90, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 50, 10)", true, g.add_edge(10, 50, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(12, 59, 10)", true, g.add_edge(12, 59, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 95, 10)", true, g.add_edge(2, 95, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 1, 10)", true, g.add_edge(11, 1, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(101, 10, 10)", true, g.add_edge(101, 10, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(121, 12, 10)", true, g.add_edge(121, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(21, 2, 10)", true, g.add_edge(21, 2, 10), __LINE__);
        //g.printGraph();

        g.dijkstra(5);
        test("graph_tests.cpp", "Graph::distance(5)", 0.0, g.distance(5), __LINE__);
        test("graph_tests.cpp", "Graph::distance(9)", 10.0, g.distance(9), __LINE__);
        test("graph_tests.cpp", "Graph::distance(90)", 10.0, g.distance(90), __LINE__);
        test("graph_tests.cpp", "Graph::distance(50)", 10.0, g.distance(50), __LINE__);
        test("graph_tests.cpp", "Graph::distance(59)", 10.0, g.distance(59), __LINE__);
        test("graph_tests.cpp", "Graph::distance(95)", 10.0, g.distance(95), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1)", 20.0, g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", 20.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(12)", 20.0, g.distance(12), __LINE__);
        test("graph_tests.cpp", "Graph::distance(2)", 20.0, g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(11)", 30.0, g.distance(11), __LINE__);
        test("graph_tests.cpp", "Graph::distance(101)", 30.0, g.distance(101), __LINE__);
        test("graph_tests.cpp", "Graph::distance(121)", 30.0, g.distance(121), __LINE__);
        test("graph_tests.cpp", "Graph::distance(21)", 30.0, g.distance(21), __LINE__);

        g.printGraph();
        g.dijkstra(90);
        test("graph_tests.cpp", "Graph::distance(5)", 10.0, g.distance(5), __LINE__);
        test("graph_tests.cpp", "Graph::distance(9)", 20.0, g.distance(9), __LINE__);
        test("graph_tests.cpp", "Graph::distance(90)",0.0, g.distance(90), __LINE__);
        test("graph_tests.cpp", "Graph::distance(50)", 20.0, g.distance(50), __LINE__);
        test("graph_tests.cpp", "Graph::distance(59)",20.0, g.distance(59), __LINE__);
        test("graph_tests.cpp", "Graph::distance(95)", 20.0, g.distance(95), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1)", 10.0, g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", 30.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(12)", 30.0, g.distance(12), __LINE__);
        test("graph_tests.cpp", "Graph::distance(2)", 30.0, g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(11)", 20.0, g.distance(11), __LINE__);
        test("graph_tests.cpp", "Graph::distance(101)",40.0, g.distance(101), __LINE__);
        test("graph_tests.cpp", "Graph::distance(121)",40.0, g.distance(121), __LINE__);
        test("graph_tests.cpp", "Graph::distance(21)", 40.0, g.distance(21), __LINE__);
    }
    

    {//dijkstra binary tree
        Graph g;
        test("graph_tests.cpp", "Graph::add_vertex(5)", true, g.add_vertex(5), __LINE__);//root
        test("graph_tests.cpp", "Graph::add_vertex(9)", true, g.add_vertex(9), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(90)", true, g.add_vertex(90), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(50)", true, g.add_vertex(50), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(59)", true, g.add_vertex(59), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(95)", true, g.add_vertex(95), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(1)", true, g.add_vertex(1), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(10)", true, g.add_vertex(10), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(12)", true, g.add_vertex(12), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(2)", true, g.add_vertex(2), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(11)", true, g.add_vertex(11), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(101)", true, g.add_vertex(101), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(121)", true, g.add_vertex(121), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(21)", true, g.add_vertex(21), __LINE__);
        //g.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(5, 9, 10)", true, g.add_edge(5, 9, 10), __LINE__);//depth 0
        test("graph_tests.cpp", "Graph::add_edge(5, 90, 10)", true, g.add_edge(5, 90, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(90, 50, 10)", true, g.add_edge(90, 50, 10), __LINE__);//depth 1
        test("graph_tests.cpp", "Graph::add_edge(90, 59, 10)", true, g.add_edge(90, 59, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(9, 10, 10)", true, g.add_edge(9, 10, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(9, 95, 10)", true, g.add_edge(9, 95, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(59, 12, 10)", true, g.add_edge(59, 12, 10), __LINE__);//depth 2
        test("graph_tests.cpp", "Graph::add_edge(59, 2, 10)", true, g.add_edge(59, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 11, 10)", true, g.add_edge(50, 11, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 101, 10)", true, g.add_edge(50, 101, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 121, 10)", true, g.add_edge(10, 121, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 21, 10)", true, g.add_edge(10, 21, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(95, 1, 10)", true, g.add_edge(95, 1, 10), __LINE__);
        g.printGraph();

        g.dijkstra(5);
        test("graph_tests.cpp", "Graph::distance(5)", 0.0, g.distance(5), __LINE__);
        test("graph_tests.cpp", "Graph::distance(9)", 10.0, g.distance(9), __LINE__);
        test("graph_tests.cpp", "Graph::distance(90)", 10.0, g.distance(90), __LINE__);
        test("graph_tests.cpp", "Graph::distance(50)", 20.0, g.distance(50), __LINE__);
        test("graph_tests.cpp", "Graph::distance(59)", 20.0, g.distance(59), __LINE__);
        test("graph_tests.cpp", "Graph::distance(95)", 20.0, g.distance(95), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1)", 30.0, g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", 20.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(12)", 30.0, g.distance(12), __LINE__);
        test("graph_tests.cpp", "Graph::distance(2)", 30.0, g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(11)", 30.0, g.distance(11), __LINE__);
        test("graph_tests.cpp", "Graph::distance(101)", 30.0, g.distance(101), __LINE__);
        test("graph_tests.cpp", "Graph::distance(121)", 30.0, g.distance(121), __LINE__);
        test("graph_tests.cpp", "Graph::distance(21)", 30.0, g.distance(21), __LINE__);


    }
    
    {//graph with cycles and branches, some two way paths, some disconnected branches
        Graph g;
        std::vector<size_t> nums = {5,9,90,50,59,95,1,10,12,2,11,101,121,21};
        test("graph_tests.cpp", "Graph::add_vertex(5)", true, g.add_vertex(5), __LINE__);//root
        test("graph_tests.cpp", "Graph::add_vertex(9)", true, g.add_vertex(9), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(90)", true, g.add_vertex(90), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(50)", true, g.add_vertex(50), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(59)", true, g.add_vertex(59), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(95)", true, g.add_vertex(95), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(1)", true, g.add_vertex(1), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(10)", true, g.add_vertex(10), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(12)", true, g.add_vertex(12), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(2)", true, g.add_vertex(2), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(11)", true, g.add_vertex(11), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(101)", true, g.add_vertex(101), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(121)", true, g.add_vertex(121), __LINE__);
        test("graph_tests.cpp", "Graph::add_vertex(21)", true, g.add_vertex(21), __LINE__);

        //square
        test("graph_tests.cpp", "Graph::add_edge(5, 9, 10)", true, g.add_edge(5, 9, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(5, 90, 10)", true, g.add_edge(5, 90, 5), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 90, 10)", true, g.add_edge(50, 90, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(9, 50, 10)", true, g.add_edge(9, 50, 40), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(90, 5, 10)", true, g.add_edge(90, 5, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(50, 9, 10)", true, g.add_edge(50, 9, 2), __LINE__);

        //square
        test("graph_tests.cpp", "Graph::add_edge(59, 95, 10)", true, g.add_edge(59, 95, 20), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(59, 1, 10)", true, g.add_edge(59, 1, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 10, 10)", true, g.add_edge(1, 10, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(95, 10, 10)", true, g.add_edge(95, 10, 2), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(1, 59, 10)", true, g.add_edge(1, 59, 5), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(10, 95, 10)", true, g.add_edge(10, 95, 1), __LINE__);

        //connect squares
        test("graph_tests.cpp", "Graph::add_edge(1, 50, 10)", true, g.add_edge(1, 50, 2), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(9, 59, 10)", true, g.add_edge(9, 59, 1), __LINE__);

        //triangle
        test("graph_tests.cpp", "Graph::add_edge(21, 101, 10)", true, g.add_edge(21, 101, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(101, 21, 10)", true, g.add_edge(101, 21, 1), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(101, 121, 10)", true, g.add_edge(101, 121, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(121, 21, 10)", true, g.add_edge(121, 21, 1), __LINE__);

        //connect trianlge
        test("graph_tests.cpp", "Graph::add_edge(10, 21, 10)", true, g.add_edge(10, 21, 10), __LINE__);

        //triangle (disconnected)
        test("graph_tests.cpp", "Graph::add_edge(12, 11, 10)", true, g.add_edge(12, 11, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(12, 2, 10)", true, g.add_edge(12, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 12, 10)", true, g.add_edge(11, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 2, 10)", true, g.add_edge(11, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 12, 10)", true, g.add_edge(2, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 11, 10)", true, g.add_edge(2, 11, 10), __LINE__);


        g.printGraph();

        g.dijkstra(5);

        test("graph_tests.cpp", "Graph::distance(5)", 0.0, g.distance(5), __LINE__);
        test("graph_tests.cpp", "Graph::distance(9)", 1.0, g.distance(9), __LINE__);
        test("graph_tests.cpp", "Graph::distance(90)",5.0, g.distance(90), __LINE__);
        test("graph_tests.cpp", "Graph::distance(50)", 5.0, g.distance(50), __LINE__);
        test("graph_tests.cpp", "Graph::distance(59)",2.0, g.distance(59), __LINE__);
        test("graph_tests.cpp", "Graph::distance(95)", 5.0, g.distance(95), __LINE__);
        test("graph_tests.cpp", "Graph::distance(1)", 3.0, g.distance(1), __LINE__);
        test("graph_tests.cpp", "Graph::distance(10)", 4.0, g.distance(10), __LINE__);
        test("graph_tests.cpp", "Graph::distance(12)", (double)(INFINITY), g.distance(12), __LINE__);
        test("graph_tests.cpp", "Graph::distance(2)", (double)(INFINITY), g.distance(2), __LINE__);
        test("graph_tests.cpp", "Graph::distance(11)", (double)(INFINITY), g.distance(11), __LINE__);
        test("graph_tests.cpp", "Graph::distance(101)", 15.0, g.distance(101), __LINE__);
        test("graph_tests.cpp", "Graph::distance(121)",25.0, g.distance(121), __LINE__);
        test("graph_tests.cpp", "Graph::distance(21)", 14.0, g.distance(21), __LINE__);

        
        for(size_t i = 0; i < nums.size(); ++i){//{5,9,90,50,59,95,1,10,12,2,11,101,121,21}
            g.dijkstra(nums.at(i));
            for(size_t j = 0; j < nums.size(); ++j){
                cout << "path for root:" << nums.at(i) << " to " << nums.at(j) << endl;
                g.print_shortest_path(nums.at(j));
                cout << "~~~~~~~~~~~~~" << endl;
            }
            cout << "|||||||||||" << endl;
        }

        g.dijkstra(10000);
            for(size_t j = 0; j < nums.size(); ++j){
                g.print_shortest_path(nums.at(j));
            }
            g.printGraph();
            for(size_t j = 0; j < nums.size(); ++j){//{5,9,90,50,59,95,1,10,12,2,11,101,121,21}
                g.remove_vertex(nums.at(j));
                g.printGraph();
            }
            for(size_t j = 0; j < nums.size(); ++j){//{5,9,90,50,59,95,1,10,12,2,11,101,121,21}
                g.add_vertex(nums.at(j));
                g.printGraph();
            }
        
            test("graph_tests.cpp", "Graph::add_edge(12, 11, 10)", true, g.add_edge(12, 11, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(12, 2, 10)", true, g.add_edge(12, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 12, 10)", true, g.add_edge(11, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 2, 10)", true, g.add_edge(11, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 12, 10)", true, g.add_edge(2, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 11, 10)", true, g.add_edge(2, 11, 10), __LINE__);
        g.printGraph();

        test("graph_tests.cpp", "Graph::remove_edge(12, 11, 10)", true, g.remove_edge(12, 11), __LINE__);
        test("graph_tests.cpp", "Graph::remove_edge(12, 2, 10)", true, g.remove_edge(12, 2), __LINE__);
        test("graph_tests.cpp", "Graph::remove_edge(11, 12, 10)", true, g.remove_edge(11, 12), __LINE__);
        test("graph_tests.cpp", "Graph::remove_edge(11, 2, 10)", true, g.remove_edge(11, 2), __LINE__);
        test("graph_tests.cpp", "Graph::remove_edge(2, 12, 10)", true, g.remove_edge(2, 12), __LINE__);
        test("graph_tests.cpp", "Graph::remove_edge(2, 11, 10)", true, g.remove_edge(2, 11), __LINE__);
        g.printGraph();

        test("graph_tests.cpp", "Graph::add_edge(12, 11, 10)", true, g.add_edge(12, 11, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(12, 2, 10)", true, g.add_edge(12, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 12, 10)", true, g.add_edge(11, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(11, 2, 10)", true, g.add_edge(11, 2, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 12, 10)", true, g.add_edge(2, 12, 10), __LINE__);
        test("graph_tests.cpp", "Graph::add_edge(2, 11, 10)", true, g.add_edge(2, 11, 10), __LINE__);
        g.printGraph();


    }
    return 0;
}
