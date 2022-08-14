#include "tree.hpp"

int main(){

	BST<int> t;
	
	t.add_vertex("A", 1);
	t.add_vertex("B", 3);
	t.add_vertex("C", 5);
	t.add_vertex("D", 10);
	t.add_vertex("G", 20);
	t.add_vertex("E", 15);
	t.add_vertex("H", 30);
	t.add_vertex("F", 17);
	
	cout << boolalpha;
	cout << "Number of vertices in the bst: " << t.num_vertices() << endl;
	cout << "Number of edges in the bst: " << t.num_edges() << endl;
	cout << "Total weight: " << t.sum_weight() << endl << endl;
	
	cout << "Vertices in the bst: ";
	for (string x : t.get_vertices()) {
		cout << x << " ";
	}
	cout << endl;

	cout << "Leaves in the bst: ";
	for (string x : t.get_leaves()) {
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "G adjacent B: " << t.adjacent("G", "B") << endl;
	cout << "B adjacent C: " << t.adjacent("B", "C") << endl;
	cout << "C adjacent B: " << t.adjacent("C", "B") << endl << endl;

	cout << "Edges in the bst: ";
	for (auto x : t.get_edges()) {
		cout << "(" << x.first << " " << x.second << ") ";
	}
	cout << endl << endl;

	cout << "Neighbour of C: ";
	for (auto x : t.get_neighbours("C")) {
		cout << x << " ";
	}
	cout << endl;
	cout << "Degree: " << t.degree("C") << endl << endl;

	cout << "Preorder Traversal: ";
	for (auto x : t.preorder_traversal()) {
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "Inorder Traversal: ";
	for (auto x : t.inorder_traversal()) {
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "Postorder Traversal: ";
	for (auto x : t.postorder_traversal()) {
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "Breadth First Traversal: ";
	for (auto x : t.breadth_first_traversal()) {
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "Path from F to B: ";
	for (auto x : t.path("F", "B")) {
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "Path with largest weight: ";
	for(auto x : t.path_with_largest_weight()){
		cout << x << " ";
	}
	cout << endl << endl;

	cout << "Height: " << t.height() << endl << endl ;

	t.remove_vertex("G");

	cout << "Remove vertex/vertices." << endl;

	cout << "Edges in the bst: ";
	for (auto x : t.get_edges()) {
		cout << "(" << x.first << " " << x.second << ") ";
	}
	cout << endl << endl;

	cout << "Vertices in the bst: ";
	for (string x : t.get_vertices()) {
		cout << x << " ";
	}
	cout << endl;
// REFERENCE

// num_vertices() == 8

// num_edges() == 7

// get_vertices == {"A", "B", "C", "D", "E", "F", "G", "H"}

// get_leaves== {"B", "D", "E"}

// adjacent("G", "B") == true        adjacent("F", "B") == false

// get_edges() == {("C", "A"), ("C", "H"), ("A", "D"), ("H", "G"), ("G", "F"), ("G", "B"), ("F", "E")}

// get_neighbours("G") == {"H", "F", "B"}

// degree("F") == 2

// path("D", "F") == {"D", "A", "C", "H", "G", "F"}

// path_with_largest_weight() == {"E", "F", "G", "B"} or {"B", "G", "F", "E"}

// height() == 4
}