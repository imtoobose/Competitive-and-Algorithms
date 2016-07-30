#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <utility>
 
using namespace std;
#define pb push_back
#define mp make_pair
#define loop(a,b,c) for(int a=b; a<c; a++)
typedef long long ll;
typedef unsigned long ul;
typedef unsigned long long ull;
static const long long MAX= 1000000000;
    
class Vertex{
    public:
    Vertex(long);
    long name;
    vector<pair<Vertex*, ll>> neighbors;
    void addneigh(Vertex*, ll);
    vector<pair<Vertex*, ll>> getneigh(void);
};
typedef vector<pair<Vertex*, ll>> vertvec;
 
class Graph{
    public:
    Graph(long);
    vector<Vertex*> verts;
    void addedge(long, long, ll);
};
 
Vertex:: Vertex(long n){
    this->name=n;
}
 
void Vertex:: addneigh(Vertex* v, ll cost){
    (this->neighbors).pb(mp(v, cost));
}
 
vertvec Vertex:: getneigh(void){
    return this->neighbors;
}
 
Graph:: Graph(long n){
    loop(i, 0, n){
        Vertex* v = new Vertex(i);
        (this->verts).pb(v);
    }
}
 
void Graph:: addedge(long x, long y, ll cost){
    ((this->verts).at(x-1))->addneigh((this->verts).at(y-1), cost);
       
}
  
  
int main(){
  long c, f, x, y;
  ll z;
  cin>>c>>f;
  Graph g(c);
  loop(i, 0, f){
    cin>>x>>y>>z;
    g.addedge(x,y,z);
    }
    
  //floyd warshall algorithm 
  vector <vector<ll>> distance(c, vector<ll> (c, MAX));
  loop(i, 0, c){
    vertvec temp= g.verts.at(i)->neighbors;
    distance[i][i]=0;
    for(auto it= temp.begin(); it!=temp.end(); it++)
      {
      distance[g.verts.at(i)->name][it->first->name]=it->second;
    }
  }
  
  loop(k, 0, c){
    loop(i, 0, c){
      loop(j, 0, c){
        if(distance[i][j]> distance[i][k]+ distance[k][j])
        {
          distance[i][j]=distance[i][k]+distance[k][j];
        }
      }
    }
  }
  
  int q;
  cin>>q;
  loop(i, 0, q){
      cin>>x>>y;
      if(distance[x-1][y-1]!=MAX)
        cout<<distance[x-1][y-1]<<"\n";
      else
        cout<<-1<<"\n";
  }
    
  return 0;
} 
