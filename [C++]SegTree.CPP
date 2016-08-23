#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
#define loop(a,b,c) for(ll a=b; a<c; a++)
#define pb push_back

typedef vector<ll> vecl;

ll max(ll a, ll b){
  return a>b? a: b;
}

class Node{
  public:
  Node(ll);
  ll _value;
  Node* _left;
  Node* _right;
};

class SegTree{
public:
  SegTree(vecl);
  Node* _tree_source;
  ll _count;
  ll queryRange(ll, ll);
  
private:
  vector <Node*> _values;
  Node* buildtree(ll, ll);
  ll _queryRange(Node*, ll, ll, ll, ll);
};

Node:: Node (ll value){
  this->_value= value;
  this->_left  = NULL;
  this->_right = NULL;
}

Node* SegTree:: buildtree(ll start, ll end){
  if(start==end){
    return (this->_values).at(start);
    //Node* n= new Node(0);
    //return n;
  }
  else{
    ll mid = (start+end)/2;
    Node* leftchild  = this->buildtree(start, mid);
    Node* rightchild = this->buildtree(mid+1, end);
    Node* n = new Node(max(leftchild->_value, rightchild->_value));
    n->_left= leftchild;
    n->_right= rightchild;
    return n;
  }
}


SegTree:: SegTree(vecl buildfrom){
  vector <Node*> values;
  ll count =0;
  for(auto it= buildfrom.begin(); it!=buildfrom.end(); it++){
    values.pb(new Node(*it));
    count+=1;
  }
  this->_values = values;
  this->_count  = count;
  this->_tree_source= this->buildtree(0, count-1);
}

ll SegTree:: _queryRange(Node* n, ll start, ll end, ll left , ll right){
  if ((right<start)||(left>end))
    return 0;
  else if(left<=start && right>=end)
    return n->_value;
  else{
    ll mid = (start+end)/2;
    return this->_queryRange(n->_left, start, mid, left, right)+ this->_queryRange(n->_right, mid+1, end, left, right);
  }
}

ll SegTree:: queryRange(ll left, ll right){
  return _queryRange(this->_tree_source, 0, this->_count-1, left, right);
}

int main(){
  ll n, x, sum=0, andprod;
  vecl vals;
  cin>>n;
  loop(i, 0, n){
    cin>>x;
    vals.pb(x);
  }
  SegTree s(vals);

  loop(i, 0, n-1){
    loop(j, i+1; n){
      andprod= i&j;
      if(andprod==i|| andprod==j){
        sum+= s.queryRange(i, j);
      }
    }
  }
  return 0;
}
