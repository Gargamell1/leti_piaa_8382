// эвристическая функция - близость символов в ASCII

/*
a e
a b 3.0
b c 1.0
c d 1.0
a d 5.0
d e 1.0

ade
*/

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

struct Node {
    static Node* beg;
    static Node* end;
    char name;
    double g;
    double h;
    Node* prev;
    vector<std::pair<Node*, double> > neig;
    
    Node(char c) {
        name = c;
        g = 999999; // 
        prev = nullptr;
    }
    
    double f() {
        return g+h;
    }
};

Node* Node::beg;
Node* Node::end;

void foo() {
    vector<Node*> q;
    vector<Node*> u;
    q.push_back(Node::beg);
    Node::beg->g = 0;
    while (q.size() != 0) {
        int ind = 0;
        for (int i = 1; i < q.size(); i++)
            if (q[i]->f() < q[ind]->f())
                ind = i;
        Node* curr = q[ind];
        if (curr == Node::end)
            return;
        
        q.erase(q.begin() + ind);
        u.push_back(curr);
        for (int i = 0; i < curr->neig.size(); i++) {
            double score = curr->g + curr->neig[i].second;
            Node* v = curr->neig[i].first;
            int j = 0;
            for (;j < u.size(); j++)
                if (u[j] == v)
                    break;
            if (j < u.size() && score >= v->g)
                continue;
            
            v->prev = curr;
            v->g = score;
            j = 0;
            for (; j < q.size(); j++)
                if (q[j] == v)
                    break;
            if (j >= q.size())
                q.push_back(v);
        }
            
    }
}

int main() {
    int n;
    char a, b;
    double c;
    map<char, Node*> nodes;
    Node* beg;
    Node* end;
    
    cin >> n;
    cin >> a >> b;
    if (a == b) {
        cout << a;
        return 0;
    }
    beg = new Node(a);
    end = new Node(b);
    nodes[a] = beg;
    nodes[b] = end;
    Node::beg = beg; 
    Node::end = end; 

    for (int i = 0; i < n; i++) {
        cin >> a >> c;
        if (nodes.find(a) == nodes.end()) {
            nodes[a] = new Node(a);
        }   
        nodes[a]->h = c;
    } 

    while(cin >> a >> b >> c) {
        if (nodes.find(a) == nodes.end()) {
            nodes[a] = new Node(a);
        }
        if (nodes.find(b) == nodes.end()) {
            nodes[b] = new Node(b);
        }
        nodes[a]->neig.push_back(std::pair<Node*, double>(nodes[b], c));
    }

    
    foo();
    vector<Node*> vec;
    Node* node = Node::end;
    while(node != nullptr) {
        vec.push_back(node);
        node = node->prev;
    }
    for (int i = vec.size() - 1; i >= 0; i--)
        cout << vec[i]->name;
}
