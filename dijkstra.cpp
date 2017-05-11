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

  void addVertex(string name)
  {
    
  }
  
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
    for(map<string, list< pair<string, int> > >::iterator it = adjList.begin(); it != adjList.end(); ++it)
    {
      cout << it->first;
      for(list< pair<string, int> >::iterator ti = adjList[it->first].begin(); ti != adjList[it->first].end(); ++ti)
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

map<string, int> distances;

class comparePair
{
  public:
    bool operator()(string lhs, string rhs)
    {
      return distances[lhs] > distances[rhs];
    }
};

bool comparer(string lhs, string rhs)
{
  return distances[lhs] > distances[rhs];
}

int shortestPath(graph ourGraph)
{
  _D_ "FINDING SHORTEST PATH\n";
  map<string, int> previous;

  vector<string> nodes;
  
  //auto comparer = [&](string lhs, string rhs){return distances[lhs] > distances[rhs];};

  for(map<string, list< pair<string, int> > >::iterator it = ourGraph.adjList.begin(); it != ourGraph.adjList.end(); ++it)
  {
    if(it->first == "airport")
    {
      _D_ "SOURCE IS ZERO\n";
      distances[it->first] = 0;
    }
    else
    {
      _D_ it->first << " IS INT MAX\n";
      distances[it->first] = INT_MAX;
    }
    //queue.push(make_pair(it->first, distances[it->first]));
    nodes.push_back(it->first);
    push_heap(nodes.begin(), nodes.end(), comparer);
  }
  
  while(!nodes.empty())
  {
    pop_heap(nodes.begin(), nodes.end(), comparer);
    string minimum = nodes.back();
    nodes.pop_back();
    //string minimum = queue.top().first;
    //queue.pop();
    _D_ "CHECKING MINIMUM; IT IS " << minimum << endl;

    if(minimum == "robotbar")
    {
      return distances["robotbar"];
    }
    if(distances[minimum] == INT_MAX)
    {
      break;
    }
    for(list< pair<string, int> >::iterator it = ourGraph.adjList[minimum].begin(); it != ourGraph.adjList[minimum].end(); ++it)
    {
      _D_ "CHECKING NEIGHBOR " << it->second << endl;
      int alt = distances[minimum] + it->second;
      _D_ "NEW DISTANCE IS " << alt << endl;
      if(alt < distances[it->first])
      {
        _D_ "NEW DISTANCE IS LESS THAN\n";
        distances[it->first] = alt;
        make_heap(nodes.begin(), nodes.end(), comparer);
      }
    }
  }
  return -1;
  /*map<string, int> distances;
  distances["airport"] = 0;
  
  priority_queue<pair<string, int>, vector<pair<string, int> >, comparePair> queue;
  
  for(map<string, list< pair<string, int> > >::iterator it = ourGraph.adjList.begin(); it != ourGraph.adjList.end(); ++it)
  {
    if(it->first != "airport")
    {
      distances[it->first] = INT_MAX;
    }
    queue.push(make_pair(it->first,distances[it->first]));
  }

  while(!queue.empty())
  {
    pair<string, int> current = queue.top();
    queue.pop();
    for(list< pair<string, int> >::iterator it = ourGraph.adjList[current.first].begin(); it != ourGraph.adjList[current.first].end(); ++it)
    {
      int alt;
      alt = distances[current.first] + it->second;
      if(alt < distances[it->first])
      {
        distances[it->first] = alt;
      }
    }
  }
  return distances["robotbar"];*/

  /*//int small = INT_MAX;
  map<string, bool> visited;
  map<string, int> distances;
  for(map<string, list< pair<string, int> > >::iterator it = ourGraph.adjList.begin(); it != ourGraph.adjList.end(); ++it)
  {
    distances[it->first] = INT_MAX;
  }
  distances["robotbar"] = INT_MAX;
  distances["airport"] = 0;
  priority_queue<pair<string, int>, vector<pair<string, int> >, comparePair> queue;
  queue.push(make_pair("airport",0));
  while(!queue.empty())
  {
    pair<string, int> temp = queue.top();
    queue.pop();
    string node = temp.first;
    for(list< pair<string, int> >::iterator it = ourGraph.adjList[node].begin(); it != ourGraph.adjList[node].end(); ++it)
    {
      if(distances[node] + it->second < distances[it->first])
      {
        distances[it->first] = distances[node] + it->second;
      }
      if(!visited[it->first])
      {
        pair<string, int> newPair;
	newPair.second=it->second;
	newPair.first=distances[it->first];
	queue.push(newPair);
	visited[it->first]=true;
      }
    }
  }
  return distances["robotbar"];*/

}

int main()
{
  int numCases;
  cin >> numCases;
  for(int i = 1; i <= numCases; i++)
  {
    graph current = getInput();
    if(DEBUG)current.print();
    cout << "#" << i << " : " << current.name << ", " << shortestPath(current) << " tokens.\n";
    _D_ endl;
  }
  return 0;
}
