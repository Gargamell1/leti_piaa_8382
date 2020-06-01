

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include <map>
#include <set>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::map;
using std::set;

struct A {
    char one;
    char two;
    double three;
    A(char a, char b, double c) {
        one = a;
        two = b;
        three = c;
    }
};

struct Node {//vertex
    static Node* beg;
    static Node* end;
    char name;
    double g;
    double h;
    Node* prev;
    vector<std::pair<Node*, double> > neig;//edges
    
    Node(char c) { // Point initialization
        name = c;
        g = 999999;
        prev = 0;
    }
    
    double f() {//heuristic function

        return g+h;
    }
};

Node* Node::beg;
Node* Node::end;

void foo() {
    vector<Node*> q;//Vector open peaks

    vector<Node*> u;//Closed Peaks Vector

    q.push_back(Node::beg);
    Node::beg->g = 0;
    while (q.size() != 0) 
	{
        int ind = 0;
        for (int i = 1; i < q.size(); i++)//Finding the vertex with the smallest f ()

            if (q[i]->f() < q[ind]->f())
                ind = i;
        Node* curr = q[ind];
        if (curr == Node::end)
            return;
        
        q.erase(q.begin() + ind);
        u.push_back(curr);//Adding to the vector of closed vertices the selected vertex with the smallest value f ()

        for (int i = 0; i < curr->neig.size(); i++) {//Updating weights for vertices

            double score = curr->g + curr->neig[i].second;
            Node* v = curr->neig[i].first;
            int j = 0;
            for (;j < u.size(); j++)//Check Transition Conditions
                if (u[j] == v)
                    break;
            if (j < u.size() && score >= v->g)
                continue;
            
            v->prev = curr;//Making way
            v->g = score;
            j = 0;
            for (; j < q.size(); j++)
                if (q[j] == v)
                    break;
            if (j >= q.size())
                q.push_back(v);
        }
            vector<Node*> vec;
    Node* node = curr;
//Output intermediate result	    
    cout<<curr->f()<<" = f() of ";//Output heuristic function for the current vertex
           while(node != 0) {
        vec.push_back(node);
        node = node->prev;
    }
    for (int i = vec.size() - 1; i >= 0; i--)//Output current way

        cout << vec[i]->name;
	    cout<<endl;	   
    }
 
}

int main() {
    int n;
    char a, b;
    double c;
    map<char, Node*> nodes;//An analogue of the dictionary where the name of the vertex corresponds to the vertex

    Node* beg;
    Node* end;
    
    cin >> n;
    cin >> a >> b;
    if (a == b) {
        cout << a;
        return 0;
    }
    beg = new Node(a);//starting point

    end = new Node(b);//End point

    nodes[a] = beg;
    nodes[b] = end;
    Node::beg = beg; 
    Node::end = end; 
//Enter
    for (int i = 0; i < n; i++) {
        cin >> a >> c;
        if (nodes.find(a) == nodes.end()) {//if there is no such peak yet

            nodes[a] = new Node(a);
        }   
        nodes[a]->h = c;
    } 

    while(cin >> a >> b >> c) {
        if (nodes.find(a) == nodes.end()) {//if there is no such peak yet

            nodes[a] = new Node(a);
        }
        if (nodes.find(b) == nodes.end()) {//if there is no such peak yet

            nodes[b] = new Node(b);
        }
        nodes[a]->neig.push_back(std::pair<Node*, double>(nodes[b], c));
    }

    
    foo();
    vector<Node*> vec;
    Node* node = Node::end;
    while(node != 0) {//Building the final path

        vec.push_back(node);
        node = node->prev;
    }
    for (int i = vec.size() - 1; i >= 0; i--)//Response output

        cout << vec[i]->name;
}
