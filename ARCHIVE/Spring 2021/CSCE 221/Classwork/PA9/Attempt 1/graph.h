#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cmath>
#include <list>
#include "hashtable_open_addressing.h"

class Graph {
 // TODO(student): implement Graph

    HashTable<size_t, std::hash<size_t>> body = {};
    HashTable<size_t, std::hash<size_t>> dijkstraPaths = {};
    std::list<std::pair<size_t,size_t>> mstD = {};

    bool dja = false;//lets distance function switch between dijkstra and prim

    size_t dSource = {};
    size_t aSource = {};
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
        if(body.findNode(src).addEdge(dest, weight) && body.findNode(dest).addEdge(src, weight)){
            ++numEdges;
            return true;
        }
        return false;
    }// - add a directed edge from src to dest with the specified weight if there is no edge from src to dest, return true on success, false otherwise.
    bool remove_vertex(size_t id){
        if(!contains_vertex(id)){ return false; } 

        for(size_t i = 0; i < body.findNode(id).getEdgeList().size(); i=i){
            remove_edge(body.findNode(id).getEdgeList().at(0).first,id);
        }

        body.findNode(id).clearEdges();
        body.remove(id);
        return true;
    }// - remove the specified vertex from the graph, including all edges of which it is a member, return true on success, false otherwise.
    bool remove_edge(size_t src, size_t dest) {
        if(!body.contains(src)){ return false; }

        
        if(body.findNode(src).removeEdge(dest) && body.findNode(dest).removeEdge(src)){
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
    std::list<std::pair<size_t,size_t>> prim(){
        dja = false;
        mstD = {};
        std::list<std::pair<size_t,size_t>> mst = {};
        if((edge_count() < vertex_count() - 1) || (edge_count() == 0)){
            return mst;
        }
        
        size_t k = 0;
        aSource = 0;
        while(!aSource){
            if( body.getNode(k).hasKey() &&  !body.getNode(k).isRemoved()){ aSource = body.position(body.getNode(k).getKey()); }
            ++k;
        }
        

        

        std::vector<size_t> visited = {};
        std::vector<size_t> unvisited = {};
        
        HashTable<size_t, std::hash<size_t>> temp = body;
        HashTable<size_t, std::hash<size_t>>::Node* cursor = &temp.findNode(temp.getNode(aSource).getKey());
        if(cursor->getEdgeList().size() == 0){
            return mst;
        }
        
        size_t minNode = {};
        size_t minWeight = {};
        

        int fb = 3;
        while(temp.size()) {
            if(!vectorContains(visited, cursor->getKey())){ visited.push_back(cursor->getKey())  ;}

            minNode = cursor->getEdgeList().at(0).first;
            minWeight = cursor->getEdgeList().at(0).second;
            //temp.print_table();
            for(size_t i = 0; i < cursor->getEdgeList().size(); ++i){
                if(!vectorContains(visited, cursor->getEdgeList().at(i).first)){
                    if(!vectorContains(unvisited, cursor->getEdgeList().at(i).first)){
                        unvisited.push_back(cursor->getEdgeList().at(i).first);
                    }
                }
            }
            cout << cursor->getKey() << " | " << cursor->getEdgeList().at(0).first << " | " << cursor->getEdgeList().at(0).second << " | "<< endl;
            for(size_t i = 0; i < visited.size(); ++i){//for every visited node, check all weights to unvisited nodes, only keeping the minimum weight
                cout << "visited node: " << visited.at(i) << endl;

                for(size_t j = 0; j < temp.findNode(visited.at(i)).getEdgeList().size(); ++j){
                    cout << " edge " << temp.findNode(visited.at(i)).getEdgeList().at(j).first << endl;

                    if(temp.findNode(visited.at(i)).getEdgeList().at(j).second < minWeight && !vectorContains(visited, temp.findNode(visited.at(i)).getEdgeList().at(j).first)){
                        cout << "sdfsdfasdfasdf" << endl;
                        minNode = temp.findNode(visited.at(i)).getEdgeList().at(j).first;
                        minWeight = temp.findNode(visited.at(i)).getEdgeList().at(j).second;
                        cursor = &temp.findNode(visited.at(i));
                    }
                    
                }
            }
            cout << cursor->getKey() << " | " << cursor->getEdgeList().at(0).first << " | " << cursor->getEdgeList().at(0).second << " | "<< endl;
            cout << minNode << "|||" << endl;
            //temp.print_table();
            if(!listContainsKey(mst, minNode)){
                mst.push_back(std::make_pair(cursor->getKey(), minNode));
                visited.push_back(minNode);
            }
            else{ 
                std::list<std::pair<size_t,size_t>>::iterator it = mst.begin();
                size_t dist = 0;
                for(size_t i = 0; i < mst.size(); ++i){
                    if((it->first == minNode) || (it->second == minNode)){
                        dist = cost(it->first, it->second);
                        break;
                    }
                    std::advance(it, 1);
                }

                if(dist > cost(minNode, cursor->getKey())){
                    it->first = minNode;
                    it->second = cursor->getKey();
                }
            }
            temp.findNode(cursor->getKey()).removeEdge(minNode);
            temp.findNode(minNode).removeEdge(cursor->getKey());
            //cout << "|||" << endl;
            //temp.print_table();
            printMST(mst);
            

            if(cursor->getEdgeList().size() == 0){
                temp.remove(cursor->getKey());
                cursor = nullptr;
                if(temp.findNode(minNode).getEdgeList().size() == 0){
                    temp.remove(temp.findNode(minNode).getKey());
                    visited.push_back(minNode);
                }
    
                for(size_t j = 0; j < unvisited.size(); j = j ){
                    if(vectorContains(visited, unvisited.at(0))){
                        unvisited.erase(unvisited.begin());
                    }
                    else{
                        cursor = &temp.findNode(unvisited.at(0));
                        break;
                    }
                }
                if(cursor == nullptr){
                    break;
                }
            }
            if(temp.findNode(minNode).getEdgeList().size() == 0){
                    temp.remove(temp.findNode(minNode).getKey());
                    if(!vectorContains(visited, minNode)){ visited.push_back(minNode); }
                }

            
            //temp.print_table();
            //cout << cursor->getKey() << " |  | "<< cursor->getEdgeList().size() << endl;;
           // cursor = nullptr;
           --fb;
        }
        //printMST(mst);
        //cout << visited.size();
        if(visited.size() < body.size()){mst = {};}
        mstD = mst;
        return mst;
    }// - compute a minimum spanning tree using Prim’s algorithm. Return a list of edges.  There may be more than one possible spanning tree depending on the starting vertex.  Any correct (minimum weight) tree will be recognized as such. You may assume that the graph is connected (if the MST does not exist, then the return value should be an empty list).
    bool listContainsKey(std::list<std::pair<size_t,size_t>> listComp, size_t key){
        std::list<std::pair<size_t,size_t>>::iterator it = listComp.begin();

        for(size_t i = 0; i < listComp.size(); ++i){
            if((it->first == key) || (it->second == key)){
                return true;
            }
            std::advance(it, 1);
        }
        return false;
    }
    bool vectorContains(std::vector<size_t> vec, size_t key){
        for(size_t i = 0; i < vec.size(); ++i){
            if(vec.at(i) == key){
                return true;
            }
        }
        return false;
    }
    void dijkstra(size_t source_id){
        dja = true;
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
        if(dja){
            if(!body.contains(dSource)){ return INFINITY; }
            if(dSource == id){
                return 0;
            }

            if((!dijkstraPaths.contains(id)) || (dijkstraPaths.findNode(id).getEdgeList().empty())){
                return INFINITY;
            }
            return dijkstraPaths.findNode(id).getEdgeList().at(0).second;
        }
        else{
            if(mstD.size() == 0 || !body.contains(id)){
                return INFINITY;
            }
            return 0;
        }
    }//  - assumes Dijkstra has been run, returns the cost of the shortest path from the Dijkstra-source vertex to the specified destination vertex, or INFINITY if the vertex or path does not exist.

    //Visualization
    void print_minimum_spanning_tree(std::ostream& os=std::cout) const {
        if(mstD.size() == 0){ os << "<no tree>" << endl;}
        std::list<std::pair<size_t,size_t>>::const_iterator it = mstD.begin();
        size_t dist = 0;
        for(size_t i = 0; i < mstD.size(); ++i){
            os << it->first << "--{" << cost(it->first, it->second) << "}" << it->second << endl;
            dist += cost(it->first, it->second);
            std::advance(it, 1);
        }
    }//- assumes Prim has been run, pretty prints the minimum spanning tree as a sequences of lines with the format <vertex> --{<edge weight>} <vertex>
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
    void printMST(std::list<std::pair<size_t,size_t>> mst) {
        if(mst.size() == 0){ cout << "<no tree>" << endl;}
        std::list<std::pair<size_t,size_t>>::iterator it = mst.begin();
        size_t dist = 0;
        for(size_t i = 0; i < mst.size(); ++i){
            cout << it->first << "->{" << cost(it->first, it->second) << "}" << it->second << endl;
            dist += cost(it->first, it->second);
            std::advance(it, 1);
        }
        cout << "tree cost: " << dist << endl;
        
    }
};

#endif  // GRAPH_H
