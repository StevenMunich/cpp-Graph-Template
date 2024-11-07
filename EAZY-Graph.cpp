#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>

using namespace std;

// Circle Object
class Circle {
public:
    Circle(double r) : radius(r) {}
    Circle() : radius(0) {}

    double getRadius() const { return radius; }
    void setRadius(double r) { radius = r; }
    double getArea() const { return radius * radius * 3.14; }
    string toString() const { return "Circle with radius: " + to_string(radius); }

private:
    double radius;
};

// Binary Search Node template class
template<class T>
class Gnode {	
public:
    T el; // Main object
    T *reference = &el;
    vector<Gnode<T>> connectedNodes; // Connections / Edges
    int objectNumber = 0; //Object number re-assigned in .addToGraph
    
    Gnode() { // If T is a pointer type, initialize el to nullptr instead of 0    
    //cout << "blank constructor used" << endl;
    }
    Gnode(T t) : el(t) 
	{
    cout << "Object constructor used" << endl;
	}

    // Display connections
    void displayConnections() const {
        for (const Gnode<T>& G : connectedNodes) {
        	cout << "Node Address " << &G << "element address: " << &G.el << endl;
        	cout << "Hello from: " << objectNumber << " is connected to ";
            cout << G.el.toString() << endl; //ALWAYS USE ToSTRING WITH TEMPLATES. Squares do not have a radius. Squirrels do not have a shell. ToSTRING IS MOST COMMON
            
        }
    }//end void
	    
    void addEdge(Gnode<T>& p){
    	connectedNodes.push_back(p);
	}
    
};

template<class T>
class Graph {
public:
    Gnode<T>* root;
    vector<Gnode<T>> allNodes;
    int ItemsInGraph = 0;

    // Constructor
    Graph() : root(nullptr) {}

    // Add to graph
    void addToGraph(T object) {
        if (root == nullptr) {
            root = new Gnode<T>(object);
            allNodes.push_back(*root);
            allNodes[ItemsInGraph].objectNumber = ItemsInGraph;
            ItemsInGraph++;
        }
        else{
        	allNodes.push_back(Gnode<T>(object)); //Gnode is NEW, the constructor will get called.
        	allNodes[ItemsInGraph].objectNumber = ItemsInGraph;
        	ItemsInGraph++;
		}//end if      
    }//end addToGraph()
    
    //Add Edges
    void addEdge(int src, int dst){
    	allNodes[src].addEdge(allNodes[dst]);
	}

    // Visit node
    void visit(const Gnode<T>* p) const {
        cout << p->el.toString() << endl;
    }

    // Check if graph is empty
    bool isEmpty() const {
        return root == nullptr;
    }

    // Destructor
    ~Graph() {
        clear();
    }

    // Clear graph
    void clear() {
    	Gnode<T>* p;
    	for(Gnode<Circle>& node : allNodes){
    		p = &node;
    		delete p;
		}
        root = nullptr;
        cout << "graph deleted all elements succesfully" << endl;
    }
};

// Main function
int main() {
    // Create a graph of circles
    cout << "How many items would you like in the graph?" << endl;
    int n;
    cin >> n;

    Graph<Circle> myGraph;

    for (int i = 0; i < n; i++) {
        double radius;
        cout << "Enter the radius of circle " << (i) << ": ";
        cin >> radius;
        Circle c(radius);
        myGraph.addToGraph(c);
    }

//Main Loop
	int i = 0;
	
	while (i != 999){
		cout << "1. Add Edge. \t 2. Display edges \t 3. Display vertices \t 4. Display graph size \5. View memory map ";
		cin >> i;
		
	if(i==1){
		int dst, src;
		
		cout << "enter first node:";
		cin >> src;
		cout << "enter destination node:";
		cin >> dst;
		myGraph.addEdge(src, dst);
		
	}//end if
	
	if(i==2)
		for (const Gnode<Circle>& node : myGraph.allNodes) 
	       	node.displayConnections();
	//end if	
	if(i == 3){
	 	cout << "Graph contents:" << endl;
    	for (const Gnode<Circle>& node : myGraph.allNodes)
       		 cout << node.el.toString() << endl;
	}//end if	
	
	if(i==4) cout << "Item Count in graph: " << myGraph.ItemsInGraph << endl; //end if
	
	if(i==5) {
		for(const Gnode<Circle>& node : myGraph.allNodes)
			cout << "Memory address: " << &node << " Contains Object at -> " << node.reference << endl;
	}
	
		
	} //end while(!=999)
   
   
    return 0;
} //end main()

