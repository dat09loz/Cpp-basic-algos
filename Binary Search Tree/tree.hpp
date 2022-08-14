#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

template <typename T> // the template allows the weight of vertex to take any numeric data type (denoted by T).
class BST {

	public:
        /* define your data structure to represent a binary search tree (bst) */


        vector<string> vertices;// represent the bst
        map<string, T> weights; //represent the  weight of each vertex


        /* test1 */
		BST(); // the contructor function.
		~BST(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the bst.
		size_t num_edges(); // returns the total number of edges in the bst.
        T sum_weight(); // return the total weight of all the vertices in the bst.

        /* test2 */
        void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
        vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
                                     //     Leaves are the vertices that do not have any children in the bst.

        /* test4 */
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
		
        /* test8 */
        vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
        
        /* test9 */
        vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
        
        /* test10 */
        vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
		
        /* test11 */
        vector<string> path(const string&, const string&); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
                                                            //     A path should include the source and destination vertices at the begining and the end, respectively.

        /* test12 */
        vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
                                       //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.

        /* test13 */
        size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

        /* test14 */
        void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.

        /* extra functions*/
        T get_weight(const string&); //return the weight of the given vertex
        int index_of(const string&); //return the index of the given vertex
        bool path_from(string&, vector<string>&, string&); //contruct a path between root to given vertex
        bool has_left_child(int);// check if the vertex have left child
        bool has_right_child(int);//check if the vertex have right child
        void move_tree_up(int, int);
        int left_most_child(int); //return left most child of a vertex
};

/* test1 */

template <typename T>
BST<T>::BST() {
    vertices.resize(100);// initialise the size of the bst.
}

template <typename T>
BST<T>::~BST() {}


template <typename T>
size_t BST<T>::num_vertices() {// returns the total number of vertices in the bst.
    return weights.size();
}

template <typename T>
size_t BST<T>::num_edges() {// returns the total number of edges in the bst.
    if (num_vertices() >= 2) //if there are more 2 vertices in the bst
        return num_vertices() - 1;

    return 0;//none or only one vertex
}

template <typename T>
T BST<T>::sum_weight() {// return the total weight of all the vertices in the bst.
    auto sum = 0;
    for (auto x : weights) {//sum of all the weight in the weights vector
        sum = sum + x.second;
    }
    return sum;
}

/* test2 */

template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {// adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
    if (!contains(u)) {// check if u exist in the bst
        int pos = 0; //the position that u will be inserted
        while (pos < vertices.size() && contains(vertices[pos])) {// if the position is not empty, go down
            if (w < get_weight(vertices[pos]))
                pos = 2 * pos + 1; //go to the left if i the weight is smaller
            else
                pos = 2 * pos + 2; //otherwise, go to the right
        }
        if (pos >= vertices.size()) {// if vertices running out of space, double the size
            vertices.resize(2*vertices.size());
        }
        vertices[pos] = u;//insert new vertex into the position
        weights.insert(make_pair(u, w));
    }
}

template <typename T>
bool BST<T>::contains(const string& u) {// checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
    for (auto x : weights) {// search the vertices inside weights map
        if (x.first == u)
            return true;
    }
    return false;
}

/* test3 */

template <typename T>
vector<string> BST<T>::get_vertices() {// returns a vector of all the vertices in the bst.
    vector<string> all_vertices;// vector that contain vertices in the bst (without empty string in between)
    for (auto x : weights) {
        all_vertices.push_back(x.first);
    }
    return all_vertices;
}

template <typename T>
vector<string> BST<T>::get_leaves() {// returns a vector of all the leaves in the bst.
    vector<string> leaves;// vector that contains leaves in the bst
    for (auto x : weights) {
        int i = index_of(x.first);// check every vertex in the bst
        if (!contains(vertices[2*i+1]) && !contains(vertices[2*i+2]))// if the vertex does not have any left/right child
            leaves.push_back(x.first);      
    }
    return leaves;
}

/* test4 */

template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) { // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
    if (u != v) {// prevent adding identical pairs
        if (2*index_of(u)+1 == index_of(v) || 2*index_of(u)+2 == index_of(v)) {//if v is the child of u
            return true;
        } if (2*index_of(v)+1 == index_of(u) || 2*index_of(v)+2 == index_of(u)) {//if u is the child of v
            return true;
        }
    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> BST<T>::get_edges() { // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
    vector<pair<string, string>> edges;
    for (auto x : weights) { //insert edges in the edges vector
        for (auto y : weights) {// checking every possible pairs
            if (find(edges.begin(), edges.end(), make_pair(y.first, x.first)) != edges.end())// if the pairs already existed, jump to next step
                continue;
            if (adjacent(x.first, y.first))
                edges.push_back(make_pair(x.first, y.first));
        }
    }
    return edges;
}

/* test6 */

template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {// returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
    vector<string> neighbours;
    for (auto x : weights) {//check all of the vertices in the bst that is adjacent to u
        if (adjacent(u, x.first))
            neighbours.push_back(x.first);
    }
    return neighbours;
}

template <typename T>
size_t BST<T>::degree(const string& u) {// returns the degree of a vertex.
    return get_neighbours(u).size();
}

/* test7 */

template <typename T>
vector<string> BST<T>::preorder_traversal() {// returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
    vector<string> preorder;
    stack<string> s;
    string current = vertices.front();
    s.push(current);//current node
    while (preorder.size() < weights.size()) {// loop until every vertices in the bst is captured
        if (!(find(preorder.begin(), preorder.end(), current)!=preorder.end()))// if vertex not in the traversal list
            preorder.push_back(current);
        if (contains(vertices[2*index_of(current)+2]))
            s.push(vertices[2*index_of(current)+2]);
        if (contains(vertices[2*index_of(current)+1]))//left child will be visited first
            s.push(vertices[2*index_of(current)+1]);
        current = s.top();// move to the next vertex in the stack
        s.pop();
    }
    return preorder;
}

/* test8 */

template <typename T>
vector<string> BST<T>::inorder_traversal() {// returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
    vector<string> inorder;
    stack<string> s;
    string current = vertices.front();// iterate from the root
    while (contains(current) || !s.empty()) {//loop until the stack is empty || current vertex is already visited
        if (contains(current)) {
            s.push(current);
            current = vertices[2*index_of(current)+1];
        } else {
            current = s.top();
            s.pop();
            if (!(find(inorder.begin(), inorder.end(), current)!=inorder.end())) 
                inorder.push_back(current);
            current = vertices[2*index_of(current)+2];
        }
    }
    return inorder;
}

/* test9 */

template <typename T>
vector<string> BST<T>::postorder_traversal() {// returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
    vector<string> postorder;
    stack<string> s;
    string current = vertices.front();
    string last = "";
    while (postorder.size() < weights.size()) {
        if (contains(current) && !(find(postorder.begin(), postorder.end(), current)!=postorder.end())) {
            s.push(current);
            current = vertices[2*index_of(current)+1];// visit the left child
        } else {
            if (contains(vertices[2*index_of(s.top())+2]) && vertices[2*index_of(s.top())+2] != last)
                current = vertices[2*index_of(s.top())+2];
            else {
                current = s.top();
                s.pop();
                if (!(find(postorder.begin(), postorder.end(), current)!=postorder.end()))
                    postorder.push_back(current);
                last = current;
            }
        }
    }
    return postorder;
}

/* test10 */

template <typename T>
vector<string> BST<T>::breadth_first_traversal() {// returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
    vector<string> bst;
    queue<string> q;
    q.push(vertices.front());
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        bst.push_back(current);
        if (contains(vertices[2*index_of(current)+1]))
            q.push(vertices[2*index_of(current)+1]);
        if (contains(vertices[2*index_of(current)+2]))
            q.push(vertices[2*index_of(current)+2]);
    }
    return bst;
}

/* test11 */

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v){
    vector<string> path, path1, path2;
    string v1 = u;
    string v2 = v;
    int intersec = -1;
    if (contains(u) && contains(v)) {//find path1 from root to u and from root to v (path2)
        path_from(vertices.front(), path1, v1);
        path_from(vertices.front(), path2, v2);
    }
    int p1 = 0, p2 = 0;
    while (p1 < path1.size() || p2 < path2.size()) {//else, find intersection point
        if (p1 == p2 && path1[p1] == path2[p2]) {
            p1++;
            p2++;
        } else {
            intersec = p2 - 1;
            break;
        }
    }
    for (int i = path1.size() - 1; i > intersec; i--)//push (path1 -> intersect - 1 + intersect -> path 2) to path from u to v 
        path.push_back(path1[i]);    
    for (int i = intersec; i < path2.size(); i++)
        path.push_back(path2[i]);

    return path;
}

/* test12 */

template <typename T>
vector<string> BST<T>::path_with_largest_weight() {// returns a path that has the largest weight in the bst.
    T max = -1;
    vector<string> max_path;
    for (auto x : weights) {
        for (auto y : weights) {
            T sum = 0;
            for (auto z : path(x.first, y.first))// calculate the sum weight of the current path
                sum += get_weight(z); 
            if (sum > max) {// if the current weight is bigger than the max, replace max with current
                max = sum;
                max_path.clear();//clear the current max path record, then replace it with the current path as max path
                for (auto t : path(x.first, y.first)) 
                    max_path.push_back(t);
            }
        }
    }
    return max_path;
}

/* test13 */

template <typename T>
size_t BST<T>::height() {// returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.
    int max = 0;
    for (auto x : get_leaves()) {//find the longest path from root to leaves
        vector<string> path;
        path_from(vertices.front(), path, x);
        if (max < path.size() - 1)
            max = path.size() - 1;
    }
    return max;
}

/* test14 */

template <typename T>
void BST<T>::remove_vertex(const string& u) {
    if (contains(u)) {
        int index_u = index_of(u);
        if(!has_left_child(index_of(u)) && !has_right_child(index_of(u))){// case 1: remove a leaf
            vertices[index_u] = "";
            weights.erase(u);
            return;
        }
        else if(has_left_child(index_u) && has_right_child(index_u)){//case 3: remove vertex which have 2 children
            int new_index = left_most_child(2*index_u+2);
            vertices[index_u] = vertices[new_index];
            vertices[new_index] = "";
            weights.erase(u);
        } else { // case 2: remove vertex that have 1 child
            int index_child;
            if(has_left_child(index_u)){// we only have left child
                index_child = 2*index_u+1;
            } 
            if(has_right_child(index_u)){ // we have only right child
                index_child = 2*index_u+2;
            }
            move_tree_up(index_child, index_u); // move child to the position of u, so the new index of child is index_u  
            weights.erase(u);
        }
    }
}

/*extra function*/
template <typename T>
int BST<T>::left_most_child (int u) {// find the left most child's index of u
    int target = u;
    while (has_left_child(target))
        target = 2*u+1;
    return target;
}

template <typename T>
T BST<T>::get_weight(const string& u) {//use when iterating through vertices, not weights or when we cannot use weights[u] 
    for (auto x : weights){    //loop over weights vector to find the weight of u
        if (x.first == u)
            return x.second;     //delete that edge from the list
    }
    return 0;
}

template <typename T>
int BST<T>::index_of(const string& u) {//find the index of a vertex	
	int pos = 0; // search from the root
	while (pos < vertices.size() && contains(vertices[pos]) && vertices[pos] != u){
		if(get_weight(u) < get_weight(vertices[pos])){
			pos = 2 * pos + 1;
		} else {
			pos = 2 * pos + 2;
		}
	}
	if (pos < vertices.size() && contains(vertices[pos])){
		return pos;
	} else {
		return -1;
	}
}

template <typename T>
bool BST<T>::path_from(string& root, vector<string>& path, string& u) {//find a path from root to the given vertex
    //idea from https://www.geeksforgeeks.org/print-path-between-any-two-nodes-in-a-binary-tree/
    if (!contains(root))
        return false;
    path.push_back(root);
    if (root == u)
        return true;
    if (path_from(vertices[2*index_of(root)+1], path, u) || path_from(vertices[2*index_of(root)+2], path, u))
        return true;
    path.pop_back();
    return false;
}

template <typename T>
bool BST<T>::has_left_child(int u) {// if u have left child, return true
    if (2*u+1 < vertices.size() && contains(vertices[2*u+1])) {
        return true;
    }
    return false;
} 

template <typename T>
bool BST<T>::has_right_child(int u) {// if u have right child, return true
    if (2*u+2 < vertices.size() && contains(vertices[2*u+2])) {
        return true;
    }
    return false;
}

template <typename T>
void BST<T>::move_tree_up (int original_index, int new_index){// recursively move the children up after deleting removing parent vertex
    vertices[new_index] = vertices[original_index];
    vertices[original_index] = "";
    if(has_left_child(original_index)){
        move_tree_up(2*original_index+1, 2*new_index+1);
    }
    if(has_right_child(original_index)){
        move_tree_up(2*original_index+2, 2*new_index+2);
    }
}