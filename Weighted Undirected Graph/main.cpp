        #include "graph.hpp"

int main() {
	
    Graph<int> g;

    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");
    g.add_vertex("D");
    g.add_vertex("E");
    g.add_vertex("F");

    g.add_edge("A", "B", 7);
    g.add_edge("A", "C", 2);
    g.add_edge("C", "D", 4);
    g.add_edge("C", "D", 4);
    g.add_edge("C", "E", 8);
    g.add_edge("B", "E", 10);
    g.add_edge("A", "E", 6);
    g.add_edge("B", "C", 3);
    g.add_edge("B", "F", 5);
    g.add_edge("E", "F", 10);

    cout << "The visiting order of DFS (starting from B):";
    for (string x : g.depth_first_traversal("B")){
        cout << " " << x;
    }
    cout << "\n" << endl;

    //g.remove_edge("B", "C");
    //g.remove_vertex("F");

    cout << "Number of vertices: " << g.num_vertices() << endl; // should be 5
    cout << "Number of edges: " << g.num_edges() << "\n" << endl; // should be 6
    vector<pair<string, string>> mst = g.get_edges();
    for (int i = 0; i < mst.size(); ++i) {
        cout << mst[i].first << ' ' << mst[i].second << "\n";
    }

    cout << "Is vertex A in the graph? " << g.contains("A") << endl; // should be 1 or true
    cout << "Is vertex F in the graph? " << g.contains("F") << "\n" << endl; // should be 0 or false

    cout << "Is there an edge between A and B? " << g.adjacent("A", "B") << endl; // should be 1 or true
    cout << "Is there an edge between B and C? " << g.adjacent("B", "C") << endl; // should be 0 or false

    cout << "Degree of D: " << g.degree("D") << endl; // should be 1
    cout << "Degree of B: " << g.degree("B") << endl; // should be 2
    cout << "Degree of E: " << g.degree("E") << "\n" <<endl; // should be 3

    //g.remove_vertex("A");

    cout << "Degree of D: " << g.degree("D") << endl; // should be 1
    cout << "Degree of B: " << g.degree("B") << endl; // should be 1
    cout << "Degree of E: " << g.degree("E") << "\n" <<endl; // should be 2

    cout << "Number of edges: " << g.num_edges() << "\n" << endl;
    mst = g.get_edges();
    for (int i = 0; i < mst.size(); ++i) {
        cout << mst[i].first << ' ' << mst[i].second << "\n";
    }

    cout << "The visiting order of DFS (starting from B):";
    for (string x : g.depth_first_traversal("B")){
        cout << " " << x;
    }
    cout << endl;

    cout << "The visiting order of BFS (starting from B):";
    for (string x : g.breadth_first_traversal("B")){
        cout << " " << x;
    }
    cout << endl;


    cout << "Cycle? " << g.contain_cycles() << "\n" << endl;

    Graph<int> m = g.minimum_spanning_tree();
    cout << "Number of vertices in minimum spanning tree: " << m.num_vertices() << "\n";
    cout << "Number of edges in minimum spanning tree: " << m.num_edges() << "\n";

    mst = m.get_edges();
    for (int i = 0; i < mst.size(); ++i) {
        cout << mst[i].first << ' ' << mst[i].second << "\n";
    }
}