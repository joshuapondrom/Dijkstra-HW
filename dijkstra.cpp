//Joshua Pondrom
//1510 with Dr. Taylor
//Final Project

#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>

using namespace std;

struct graph
{
  string name;
  int vertices;
  vector< vector< pair<string, int> > > adjacencyList;
  
  void addEdge(string from, string to, int distance)
  {
    for(vector< pair<string, int> > i : adjacencyList)
    {
      if(i[0].first == from)
      {
        pair<string, int> newVertex (to, distance);
	cout << endl << endl;
	cout << i[0].first << " ";
	cout << i.size() << " ";
	i.push_back(newVertex);
	cout << i.size();
	cout << endl << endl;
        break;
      }
    }
  }

  void addVertex(string name)
  {
    pair<string, int> newVertex (name, 0);
    vector<pair<string, int> > newList;
    newList.push_back(newVertex);
    adjacencyList.push_back(newList);
  }
  
  void print()
  {
    cout << name << endl;
    cout << vertices << endl;
    for(vector< pair<string, int> > i : adjacencyList)
    {
      for(pair<string, int> j : i)
      {
        cout << setw(15) << j.first;
	cout << setw(15) << j.second;
	cout << endl;
      }
    }
  }
};


graph getInput()
{
  graph current;
  cin >> current.name >> current.vertices;
  for(int i = 0; i < current.vertices; i++)
  {
    string currentVertex;
    int numAdjacent;
    cin >> currentVertex;
    cin >> numAdjacent;
    current.addVertex(currentVertex);
    while(numAdjacent --> 0)
    {
      string adjacentName;
      int distance;
      cin >> adjacentName;
      cin >> distance;
      current.addEdge(currentVertex, adjacentName, distance);
    }
  }
  return current;
}


int main()
{
  int numCases;
  cin >> numCases;
  while(numCases --> 0)
  {
    graph current = getInput();
    current.print();
  }
  return 0;
}
