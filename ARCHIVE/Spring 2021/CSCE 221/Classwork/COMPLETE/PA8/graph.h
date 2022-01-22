#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cmath>
#include "hashtable_open_addressing.h"

class Graph {
 // TODO(student): implement Graph

    HashTable<size_t, std::hash<size_t>> body = {};
    HashTable<size_t, std::hash<size_t>> dijkstraPaths = {};

    size_t dSource = {};
    size_t numEdges = 0;

    public:
    //Constructors
    Graph(){}// - makes an empty graph.
    Graph(const Graph& other) : body(other.getBody()), numEdges(other.edge_count()) {}// - constructs a deep copy of a graph
    Graph& operator=(const Graph& other){ 
        if(&other == this) { return *this;}
        numEdges = other.edge_count(); 
        body = other.getBody(); 
        return *this;
    }// - assigns a deep copy of a graph
    ~Graph(){}// - destructs a graph (frees all dynamically allocated memory)

    //Capacity
    size_t vertex_count() const{ return body.size(); }// - the number of vertices in the graph
    size_t edge_count() const{ return numEdges; }// - the number of edges in the graph

    //Element Access
    bool contains_vertex(size_t id) const{ return body.contains(id); }// - return true if the graph contains a vertex with the specified identifier, false otherwise.
    bool contains_edge(size_t src, size_t dest) const{ 
        if(!body.contains(src) || !body.contains(dest)){return false;}
        return (body.findNode(src).getEdgeList().size() > body.findNode(src).findEdge(dest)); }// - return true if the graph contains an edge with the specified members (as identifiers), false otherwise.
    double cost(size_t src, size_t dest) const{ 
        if(!body.contains(src) || !contains_edge(src, dest)) {  return INFINITY; }

        double edgeCost = body.findNode(src).getEdgeList().at(body.findNode(src).findEdge(dest)).second;
        return edgeCost;
    }// - returns the weight of the edge between src and dest, or INFINITY if none exists.

    //Modifiers
    bool add_vertex(size_t id){ return body.insert(id); }// - add a vertex with the specified identifier if it does not already exist, return true on success or false otherwise.
    bool add_edge(size_t src, size_t dest, double weight=1){
        if(!body.contains(src) || !body.contains(dest)){ return false; }
        if(body.findNode(src).addEdge(dest, weight)){
            ++numEdges;
            return true;
        }
        return false;
    }// - add a directed edge from src to dest with the specified weight if there is no edge from src to dest, return true on success, false otherwise.
    bool remove_vertex(size_t id){
        if(!contains_vertex(id)){ return false; } 

        numEdges -= body.findNode(id).getEdgeList().size();
        body.findNode(id).clearEdges();
        body.remove(id);

        for(size_t i = 0; i < body.table_size(); ++i){
            if(body.getNode(i).hasKey()){
                if(body.getNode(i).removeEdge(id)){--numEdges;}
            }
        }
        return true;
    }// - remove the specified vertex from the graph, including all edges of which it is a member, return true on success, false otherwise.
    bool remove_edge(size_t src, size_t dest) {
        if(!body.contains(src)){ return false; }
        if(body.findNode(src).removeEdge(dest)){
            --numEdges;
            return true;
        }
        return false;
    }//- remove the specified edge from the graph, but do not remove the vertices, return true on success, false otherwise.

    //Optional
    //Graph(Graph&&){}// - move constructs a deep copy of a graph
    //Graph& operator=(Graph&&){}// - move assigns a deep copy of a graph
    HashTable<size_t, std::hash<size_t>> getBody() const {return body;}

    //~~~~~~~~~~~~~~~~~~~~~//
    //TASK 2
    void dijkstra(size_t source_id){
        if(!body.contains(source_id)){
            dSource = source_id;
            return;
        }

        HashTable<size_t, std::hash<size_t>> visited;
        std::vector<std::pair<size_t, double>> unvisited = {};

        dSource = source_id;
        double dist = 0;
        double distTemp = 0;

        dijkstraPaths.make_empty();
        
        

        HashTable<size_t, std::hash<size_t>>::Node* cursor = &body.findNode(source_id);
        if(!dijkstraPaths.contains(cursor->getKey())){dijkstraPaths.insert(cursor->getKey());}// if the node is not in the path table, add it to the table

        int fb = 10;
        while(cursor != nullptr) {
            visited.insert(cursor->getKey());
            
            
            for(size_t i = 0; i < cursor->getEdgeList().size(); ++i) {// compare all paths from current node
                //if the compared vertex doesnt exist in the path table, add it to the table
                //cout << cursor->getKey() << " | " << cursor->getEdgeList().at(i).first << " | " << cursor->getEdgeList().at(i).second << " | " << dist << endl;
                //dijkstraPaths.print_table();
                

                if(!dijkstraPaths.contains(cursor->getEdgeList().at(i).first)){
                    dijkstraPaths.insert(cursor->getEdgeList().at(i).first);
                    dijkstraPaths.findNode(cursor->getEdgeList().at(i).first).addEdge(cursor->getKey(), cursor->getEdgeList().at(i).second + dist);
                    unvisited.push_back(std::make_pair(cursor->getEdgeList().at(i).first, dist + cursor->getEdgeList().at(i).second));
                    continue;
                }
                
                //sets comparison distance
                distTemp = dist + cursor->getEdgeList().at(i).second;

                //replace compared edge with total distance from origin and last visited node
                
                if(dijkstraPaths.findNode(cursor->getEdgeList().at(i).first).getEdgeList().empty()) {
                    dijkstraPaths.findNode(cursor->getEdgeList().at(i).first).addEdge(cursor->getKey(), distTemp);
                }
                else if(dijkstraPaths.findNode(cursor->getEdgeList().at(i).first).getEdgeList().at(0).second >= distTemp) {
                    
                    dijkstraPaths.findNode(cursor->getEdgeList().at(i).first).addBegin(cursor->getKey(), distTemp);
                }
            }
            //advance cursor, update distance from origin
            HashTable<size_t, std::hash<size_t>>::Node* test = cursor;
            for(size_t j = 0; j < cursor->getEdgeList().size(); ++j ){
                if(!visited.contains(cursor->getEdgeList().at(j).first)){
                    
                    dist += cursor->getEdgeList().at(j).second;
                    if(dijkstraPaths.contains(cursor->getEdgeList().at(j).first)){
                        if(!dijkstraPaths.findNode(cursor->getEdgeList().at(j).first).getEdgeList().empty()){
                            if(dist > dijkstraPaths.findNode(cursor->getEdgeList().at(j).first).getEdgeList().at(0).second){
                                dist = dijkstraPaths.findNode(cursor->getEdgeList().at(j).first).getEdgeList().at(0).second;
                            }
                        }
                    }
                    cursor = &body.findNode(cursor->getEdgeList().at(j).first);
                    break;
                }
            }
            
            if(test == cursor){//once minimum wieght path is establied from source, visits unvisited nodes and finds minimum path in a sort of heirarchy of minimum paths
                for(size_t j = 0; j < unvisited.size(); j = j ){
                    if(visited.contains(unvisited.at(0).first)){
                        unvisited.erase(unvisited.begin());
                    }
                    else{
                        
                        dist = dijkstraPaths.findNode(unvisited.at(0).first).getEdgeList().at(0).second;
                        cursor = &body.findNode(unvisited.at(0).first);
                        break;
                    }
                }
                if(test == cursor){break;}
            }
            --fb;
        }

    }//  - compute the shortest path from the specified source vertex to all other vertices in the graph using Dijkstra’s algorithm.
    double distance(size_t id) const{
        if(!body.contains(dSource)){ return INFINITY; }
        if(dSource == id){
            return 0;
        }

        if((!dijkstraPaths.contains(id)) || (dijkstraPaths.findNode(id).getEdgeList().empty())){
            return INFINITY;
        }
        return dijkstraPaths.findNode(id).getEdgeList().at(0).second;
    }//  - assumes Dijkstra has been run, returns the cost of the shortest path from the Dijkstra-source vertex to the specified destination vertex, or INFINITY if the vertex or path does not exist.

    //Visualization
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const{
        if((!dijkstraPaths.contains(dest_id)) || (distance(dest_id) == INFINITY)){ os << "<no path>\n"; return;}

        HashTable<size_t, std::hash<size_t>>::Node* cursor = &dijkstraPaths.findNode(dest_id);
        std::vector<size_t> pathList = {};
        while(cursor->getKey() != dSource){
            pathList.push_back(cursor->getKey());
            cursor = &dijkstraPaths.findNode(cursor->getEdgeList().at(0).first);
        }
        pathList.push_back(dSource);

        for(size_t i = 0; i  < pathList.size(); ++i){
            os << pathList.at(pathList.size() - 1 - i);
            if(i != pathList.size() - 1) {
                os << " --> ";
            }
        }

        os << " distance: " << distance(dest_id) << endl;
    }//  - assumes Dijkstra has been run, pretty prints the shortest path from the Dijkstra source vertex to the specified destination vertex in a “ → “- separated list with “ distance: <distance>” at the end, where <distance> is the minimum cost of a path from source to destination, or prints “<no path>\n” if the vertex is unreachable.
    void printGraph() {
        cout << "Edges: " << edge_count() << endl;
        cout << "vertices: " << vertex_count() << endl;
        body.print_table(); 
        body.table_info();}
};

#endif  // GRAPH_H
