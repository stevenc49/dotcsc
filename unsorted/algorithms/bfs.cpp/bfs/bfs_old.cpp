
#include <iostream>
#include <queue>
#include <list>
#include <map>

using namespace std;

const int NumberVertices = 8;

enum Color { WHITE, GRAY, BLACK };

struct vertex
{
    Color color;
    int distance;
    char parent;
};

int main()
{
    //create the vertices
    vertex r = {WHITE, 0, 0};
    vertex s = {WHITE, 0, 0};
    vertex t = {WHITE, 0, 0};
    vertex u = {WHITE, 0, 0};
    vertex v = {WHITE, 0, 0};
    vertex w = {WHITE, 0, 0};
    vertex x = {WHITE, 0, 0};
    vertex y = {WHITE, 0, 0};

    //create pointers to the vertex structures
    vertex *pr = &r;
    vertex *ps = &s;
    vertex *pt = &t;
    vertex *pu = &u;
    vertex *pv = &v;
    vertex *pw = &w;
    vertex *px = &x;
    vertex *py = &y;

    //create lists to hold the adjacent vertices for each corresponding vertex
    list<vertex*> r_list;
    list<vertex*> s_list;
    list<vertex*> t_list;
    list<vertex*> u_list;
    list<vertex*> v_list;
    list<vertex*> w_list;
    list<vertex*> x_list;
    list<vertex*> y_list;

    //add adjacent vertices to the lists
    r_list.push_back(ps);
    r_list.push_back(pv);

    s_list.push_back(pr);
    s_list.push_back(pw);

    t_list.push_back(pw);
    t_list.push_back(px);
    t_list.push_back(pu);

    u_list.push_back(pt);
    u_list.push_back(px);
    u_list.push_back(py);

    v_list.push_back(pr);

    w_list.push_back(ps);
    w_list.push_back(pt);
    w_list.push_back(px);

    x_list.push_back(pw);
    x_list.push_back(pt);
    x_list.push_back(pu);
    x_list.push_back(py);

    y_list.push_back(px);
    y_list.push_back(pu);

    //create the adjacency list
    list<vertex*> V[NumberVertices];    //the main array that stores the adjacency lists

    V[0] = r_list;
    V[1] = s_list;
    V[2] = t_list;
    V[3] = u_list;
    V[4] = v_list;
    V[5] = w_list;
    V[6] = x_list;
    V[7] = y_list;

    //BFS
    s.color = GRAY;
    s.distance = 0;
    s.parent = 0;

    queue<vertex*> q;
    q.push(ps);

    //map vertices to lists
    map<vertex*,list<vertex*>* > vertexToList;

    vertexToList[pr] = &r_list;
    vertexToList[ps] = &s_list;
    vertexToList[pt] = &t_list;
    vertexToList[pu] = &u_list;
    vertexToList[pv] = &v_list;
    vertexToList[pw] = &w_list;
    vertexToList[px] = &x_list;
    vertexToList[py] = &y_list;

    vertex* currentVertex;
    vertex* currentDescendant;

    //in while loop (add later)
    currentVertex = q.front();
    q.pop();

    //for each adj vertex in currentVertex
    list<vertex*> *currentAdjList = vertexToList[currentVertex];    //get corresponding adj list

    list<vertex*>::iterator it = (*currentAdjList).begin();

//    while(it != (*currentAdjList).end()) {
//        cout << *(*it).color << endl;
//    }

    cout << **currentAdjList.front()->color << endl;    //this is ridiculous, stop using pointers
    cout << &s_list;

//    cout << vertexToList[pr] << endl;
//    cout << &r_list << endl;

//    cout << currentParent << endl;

//    list<vertex*>::iterator p = r_list.begin();
//
//    while(p != r_list.end()) {
//        cout << *p << " ";
//        p++;
//    }
//
//    cout << endl;
//    cout << "front: " << r_list.front()->color << endl;


}


