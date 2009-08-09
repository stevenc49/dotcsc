
#include <iostream>
#include <limits>
#include <map>
#include <list>
#include <queue>

using namespace std;

const int INFINITY = INT_MAX;

enum Color { WHITE, GRAY, BLACK };

class Vertex
{
public:
    Vertex();
    Vertex(char id);
    ~Vertex();
    char Vertex::getId() const;
    void Vertex::setId(char arg);

    bool operator <(const Vertex& rhs) const
    {
        return id < rhs.id;
    }

private:
    char id;
};

Vertex::Vertex(): id('0')
{}

Vertex::Vertex(char id): id(id)
{}

Vertex::~Vertex()
{
}

char Vertex::getId() const
{
    return id;
}

void Vertex::setId(char arg)
{
    id = arg;
}

int main()
{
    //created the vertices
    Vertex r('r');
    Vertex s('s');
    Vertex t('t');
    Vertex u('u');
    Vertex v('v');
    Vertex w('w');
    Vertex x('x');
    Vertex y('y');

    //use maps for keeping track of color, distance and parents
    map< Vertex , Color> color;
    color[r] = WHITE;
    color[s] = WHITE;
    color[t] = WHITE;
    color[u] = WHITE;
    color[v] = WHITE;
    color[w] = WHITE;
    color[x] = WHITE;
    color[y] = WHITE;

    map< Vertex , int> distance;
    distance[r] = INFINITY;
    distance[s] = INFINITY;
    distance[t] = INFINITY;
    distance[u] = INFINITY;
    distance[v] = INFINITY;
    distance[w] = INFINITY;
    distance[x] = INFINITY;
    distance[y] = INFINITY;

    map< Vertex , char> parent;
    parent[r] = '0';
    parent[s] = '0';
    parent[t] = '0';
    parent[u] = '0';
    parent[v] = '0';
    parent[w] = '0';
    parent[x] = '0';
    parent[y] = '0';

    //create the adj lists
    list<Vertex> adj_r;
    list<Vertex> adj_s;
    list<Vertex> adj_t;
    list<Vertex> adj_u;
    list<Vertex> adj_v;
    list<Vertex> adj_w;
    list<Vertex> adj_x;
    list<Vertex> adj_y;

    adj_r.push_back(s);
    adj_r.push_back(v);

    adj_s.push_back(r);
    adj_s.push_back(w);

    adj_t.push_back(w);
    adj_t.push_back(x);
    adj_t.push_back(u);

    adj_u.push_back(t);
    adj_u.push_back(x);
    adj_u.push_back(y);

    adj_v.push_back(r);

    adj_w.push_back(s);
    adj_w.push_back(t);
    adj_w.push_back(x);

    adj_x.push_back(w);
    adj_x.push_back(t);
    adj_x.push_back(y);
    adj_x.push_back(u);

    adj_y.push_back(x);
    adj_y.push_back(u);

    //map vertices to corresponding lists
    map< Vertex , list<Vertex> > adj;
    adj[r] = adj_r;
    adj[s] = adj_s;
    adj[t] = adj_t;
    adj[u] = adj_u;
    adj[v] = adj_v;
    adj[w] = adj_w;
    adj[x] = adj_x;
    adj[y] = adj_y;

    //other objects
    queue<Vertex> q;
    Vertex currentVertex;
    Vertex currentDecescendant;

    //start algorithm
    color[s] = GRAY;
    distance[s] = 0;
    parent[s] = NULL;

    q.push(s);

    //in while loop
    while( !q.empty() )
    {
        //dequeue
        currentVertex = q.front();
        q.pop();

        //for each currentDecescendant in adj[currentVertex]
        list<Vertex>::iterator it;
        for(it = adj[currentVertex].begin(); it != adj[currentVertex].end(); it++)
        {
            currentDecescendant.setId( it->getId() );

            if( color[currentDecescendant]==WHITE )
            {
                color[currentDecescendant] = GRAY;
                distance[currentDecescendant] = distance[currentVertex] + 1;
                parent[currentDecescendant] = currentVertex.getId();

                q.push(currentDecescendant);
            }
        }

        color[currentVertex] = BLACK;
    }

    cout << "distance[r]: " << distance[r] <<endl;
    cout << "distance[s]: " << distance[s] <<endl;
    cout << "distance[t]: " << distance[t] <<endl;
    cout << "distance[u]: " << distance[u] <<endl;
    cout << "distance[v]: " << distance[v] <<endl;
    cout << "distance[w]: " << distance[w] <<endl;
    cout << "distance[x]: " << distance[x] <<endl;
    cout << "distance[y]: " << distance[y] <<endl;

    cout << endl;

    cout << "parent[r]: " << parent[r] <<endl;
    cout << "parent[s]: " << parent[s] <<endl;
    cout << "parent[t]: " << parent[t] <<endl;
    cout << "parent[u]: " << parent[u] <<endl;
    cout << "parent[v]: " << parent[v] <<endl;
    cout << "parent[w]: " << parent[w] <<endl;
    cout << "parent[x]: " << parent[x] <<endl;
    cout << "parent[y]: " << parent[y] <<endl;

    cout << endl;

    char travaller = 'u';
    char source = 's';

    while(travaller!=source)
    {
        cout << parent[travaller];
        travaller = parent[travaller];
    }

    return 0;
}
