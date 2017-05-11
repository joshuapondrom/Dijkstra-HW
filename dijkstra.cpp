//Joshua Pondrom

#include <iostream>
#include <utility>
#include <stdexcept>
#include <map>
#include <list>
#include <iomanip>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>

#define _D_ if(DEBUG) cout << 
const bool DEBUG = false;

using namespace std;

struct graph
{
  string name;
  int vertices;
  map<string, list< pair<string, int> > > adjList;
  
  void addEdge(string from, string to, int distance)
  {
    pair<string, int> newVertex (to, distance);
    try
    {
      adjList[from].push_back(newVertex);
    }
    catch(const std::out_of_range& err)
    {
      cerr << "Out of Range error: " << err.what() << endl;
    }
  }

  void print()
  {
    cout << "Town: " << name << endl;
    cout << "Vertices: " << vertices << endl;
    for(map<string, list< pair<string, int> > >::iterator it = adjList.begin();
        it != adjList.end(); ++it)
    {
      cout << it->first;
      for(list< pair<string, int> >::iterator ti = adjList[it->first].begin();
          ti != adjList[it->first].end(); ++ti)
      {
        cout << "->" << ti->first << " " << ti->second;
      }
      cout << endl;
    }
    cout << endl;
  }
};

graph getInput()
{
  graph current;
  cin >> current.name >> current.vertices;
  for(int i =0 ; i < current.vertices; i++)
  {
    string currentVertex;
    int numAdjacent;
    cin >> currentVertex;
    cin >> numAdjacent;
    while(numAdjacent --> 0)
    {
      string adjacentName;
      int distance;
      cin >> adjacentName;
      cin >> distance;
      current.addEdge(currentVertex, adjacentName, distance);
    }
  }
  current.addEdge("robotbar", "nowhere" ,0);
  return current;
}
namespace my_dist
{
  map<string, int> distances;
}

bool comparer(string lhs, string rhs)
{
  return my_dist::distances[lhs] > my_dist::distances[rhs];
}

int shortestPath(graph ourGraph)
{
  _D_ "FINDING SHORTEST PATH\n";
  map<string, int> previous;
  
  my_dist::distances.clear();
  vector<string> nodes;
  

  for(map<string,list<pair<string,int> > >::iterator 
      it = ourGraph.adjList.begin(); 
      it != ourGraph.adjList.end(); ++it)
  {
    if(it->first == "airport")
    {
      _D_ "SOURCE IS ZERO\n";
      my_dist::distances[it->first] = 0;
    }
    else
    {
      _D_ it->first << " IS INT MAX\n";
      my_dist::distances[it->first] = INT_MAX;
    }
    nodes.push_back(it->first);
    push_heap(nodes.begin(), nodes.end(), comparer);
  }
  
  while(!nodes.empty())
  {
    pop_heap(nodes.begin(), nodes.end(), comparer);
    string minimum = nodes.back();
    nodes.pop_back();
    _D_ "CHECKING MINIMUM; IT IS " << minimum << endl;

    if(minimum == "robotbar")
    {
      return my_dist::distances["robotbar"];
    }
    if(my_dist::distances[minimum] == INT_MAX)
    {
      break;
    }
    for(list<pair<string,int> >::iterator 
        it = ourGraph.adjList[minimum].begin(); 
	it != ourGraph.adjList[minimum].end(); ++it)
    {
      _D_ "CHECKING NEIGHBOR " << it->second << endl;
      int alt = my_dist::distances[minimum] + it->second;
      _D_ "NEW DISTANCE IS " << alt << endl;
      if(alt < my_dist::distances[it->first])
      {
        _D_ "NEW DISTANCE IS LESS THAN\n";
        my_dist::distances[it->first] = alt;
        make_heap(nodes.begin(), nodes.end(), comparer);
      }
    }
  }
  return -1;
}

int main()
{
  int numCases;
  cin >> numCases;
  for(int i = 1; i <= numCases; i++)
  {
    graph current = getInput();
    if(DEBUG)current.print();
    cout << "#" << i << " : " << current.name << ", " << shortestPath(current) 
         << " tokens.\n";
    _D_ endl;
  }
  return 0;
}
