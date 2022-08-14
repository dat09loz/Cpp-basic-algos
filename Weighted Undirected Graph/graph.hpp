#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <map>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

	public:
        
        /* define your data structure to represent a weighted undirected graph */
        map<string, map<string, T>> adj_list; //store all vertices and edges (undirected) in the graph. This is a graph
        vector<pair<string, string>> edges;// a list of edges in the graph (non-duplicated)

        //this is the most effective approach to me because the complier won't freaks out this time
        //map of vertices with map of edges


        /* test1 */
		Graph(); // the contructor function.
		~Graph(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the graph.
		size_t num_edges(); // returns the total number of edges in the graph.

        /* test2 */
        void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.

        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the graph.

        /* test4 */
        void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.
        
        /* test8 */
        void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

        /* test9 */
		vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
		
        /* test10 */
        vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.
        
        /* test11 */
		bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
        
        /* test12 */
		Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.
		
        /* extra functions */
        // map<string, T> get_edges(const string&);// return all of the edges of a given vertex
        // void add_vertex_with_edges(const string&);
};

/* test1 */

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::~Graph() {}


template <typename T>
size_t Graph<T>::num_vertices() {// returns the total number of vertices in the graph.
    return adj_list.size();
}

template <typename T>
size_t Graph<T>::num_edges() {// returns the total number of edges in the graph.
    return edges.size();
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) { // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
    adj_list[u] = map<string, T>();     //add new map<string, T> as value of new key(vertex) u
}

template <typename T>
bool Graph<T>::contains(const string& u) {// checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
    if (adj_list.count(u) == 1) {  //if u is in the adj_list
        return true;
    }
    return false;
}

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {// returns a vector of all the vertices in the graph.
    vector<string> vertices;                    //initialise a vector contain all vertices in adj_list that will be returned in this function
    for (auto x : adj_list)                     //x is the object in adj_list, this will loop over all objects in adj_list
        vertices.push_back(x.first);            //add all the keys in adj_list inside the vertices vector;
    return vertices;                            
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {// adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
    if (contains(u) && contains(v)) { //check if the graph contain vertex u and v
        if (!adjacent(u, v) && !adjacent(v, u)) { //check if the edge between u and v is already existed
            adj_list[u].insert(make_pair(v, weight));   //add v as adjacent to u 
            adj_list[v].insert(make_pair(u, weight));   //add u as adjacent to v
            edges.push_back(make_pair(u, v));           //add new edge(u,v), ignore (v,u)
        }
    }
}

template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) {// check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
    vector<string> neighbours = get_neighbours(u); // get all neighbours belong to u
    if (neighbours.empty())     //check if the neighbour list of u is empty
        return false;           
    else {                      //loop over the neighbour list if the list is not empty
        int i = 0;
        while (i < neighbours.size()) {
            if (neighbours[i] == v)
                return true;    //return true if v is present in the neighbour list of u
            else
                i++;
        }
        return false; // if not then return false
    }
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {// returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
    return edges; //vector<pair<string, string>> edges;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {// returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
    vector<string> neighbours;
    for (auto x : adj_list[u]) //loop over adjacents and edges' weight of u
        neighbours.push_back(x.first);// add adjacent of u to list of its neighbours

    return neighbours;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {// returns the degree (all neighbours) of a vertex.
    vector<string> all_neighbours = get_neighbours(u);
    return all_neighbours.size();// number of neighbours of u
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) {// removes the edge between two vertices, if it exists.
    if (adjacent(u, v) && adjacent(v, u)) {  //check if the edge is exist
        for (auto x : adj_list[u]) {         //loop over all edges of u to find v
            if (x.first == v) {             
                adj_list[u].erase(x.first);  //erase v from edges list of u
                int i = 0;
                while (i < edges.size()){    //loop over edges vector to find the edge that we just deleted
                    if (edges[i].first == u && edges[i].second == v)
                        edges.erase(edges.begin() + i);     //delete that edge from the list
                    else
                        i++;
                }
                break;
            }
        }

        for (auto y : adj_list[v]) {        //loop over all edges of v to find u
            if (y.first == u) {             //same process as above
                adj_list[v].erase(y.first);
                int i = 0;
                while (i < edges.size()){
                    if (edges[i].first == v && edges[i].second == u)
                        edges.erase(edges.begin() + i);
                    else
                        i++;
                }
                break;
            }
        }
    }
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) {
    //loop over all edges of all vertices to find and delete edges that have u as their incidents
    for (auto x : adj_list) {       
        for (auto y : adj_list[x.first]) {  //
            if (y.first == u) {
                adj_list[x.first].erase(y.first);
                break;
            }
        }
    }

    for (int i=0; i < edges.size(); i++) {// loop over edges vector that contains all the edges in the graph to find and delete edges that have u
        if (edges[i].first == u || edges[i].second == u) {
            edges.erase(edges.begin() + i);
            i--;
        }
    }

    adj_list.erase(u); //finally, delete the vertex from the graph
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {// returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
    stack<string> s; //stack
    vector<string> visited; //visited history
    s.push(u); 
    while (!s.empty()) {
        auto visiting = s.top(); //save the string, and then pop
        s.pop();
        int i = 0;
        if (!(find(visited.begin(), visited.end(), visiting)!=visited.end())) {// check if the item is marked (exist in the visited vector) 
            visited.push_back(visiting);
            for (auto x : get_neighbours(visiting)) 
                s.push(x);
        }
    }
    return visited;
}

/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {// returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.
    queue<string> q; //queue
    vector<string> visited; //visited history
    q.push(u); 
    while (!q.empty()) {
        auto visiting = q.front(); //save the string, and then pop
        q.pop();
        int i = 0;
        if (!(find(visited.begin(), visited.end(), visiting)!=visited.end())) {// check if the item is marked (exist in the visited vector) 
            visited.push_back(visiting);// mark the unmarked vertex
            for (auto x : get_neighbours(visiting)) //add all neighbours of visiting vertex to the visiting list 
                q.push(x);
        }
    }
    return visited;
}

/* test11 */

template <typename T>
bool Graph<T>::contain_cycles() {
    if (num_edges() >= num_vertices()) //if the number of edges is equal or greater than the number of vertices, then it contains a cycle
        return true;

    return false;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {// returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.;
    Graph<T> mst;
    // add a starting point to build mst
    
    mst.add_vertex(adj_list.begin()->first);

    while (mst.num_vertices() < this->num_vertices()) {

        string smallest_vertex;// next vertex that have smallest weight
        string mst_vertex;// vertex that we are currently in to find their lowest weight edge
        T smallest_weight = 99999999;// the weight of the min weight edge

        //find the smallest edge of the current vertex
        for (string v : mst.get_vertices()){// loop over all vertices in the mst
            for (auto x : adj_list[v]) {   //loop over all edges of the selected vertex
                if(!mst.contains(x.first)) {//if x.first does not belong to mst
                    if(x.second < smallest_weight) {//compare x.second with smallest and update smallest vertex
                        mst_vertex = v;
                        smallest_weight = x.second;
                        smallest_vertex = x.first;
                    }
                }
            }
        }
        //add smallest vertex and edge to the mst
        mst.add_vertex(smallest_vertex);
        mst.add_edge(mst_vertex, smallest_vertex, smallest_weight);
    }

    return mst;
}