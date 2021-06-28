#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

map<int, vector<int>> g1;

void addEdge(int v1, int v2) {
  g1[v1].push_back(v2);
  g1[v2].push_back(v1);
}

int main() {
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  addEdge(1, 2);
  addEdge(2, 4);
  addEdge(2, 5);
  addEdge(4, 8);
  addEdge(4, 9);
  addEdge(5, 10);
  addEdge(5, 11);
  addEdge(1, 3);
  addEdge(3, 6);
  addEdge(3, 7);
  addEdge(6, 12);
  addEdge(6, 13);

  // DFS
  stack<int> q;
  map<int, int> mt;
  for (int i = 0; i < v.size(); i++) {
    mt[i] = 0;
  }

  int current = 1;
  bool flag = true;

  while (flag) {
    // Output current node
    if (mt[current] == 0) {
      cout << current << " ";
      // Loop
      // Set node as visited
      mt[current] = 1;
      // Push all elements in queue
      vector<int> temp = g1[current];
      for (int i = 0; i < temp.size(); i++) {
        if (mt[temp[i]] == 0)
          q.push(temp[i]);
      }
    }
    if (q.empty()) {
      flag = false;
    } else {
      current = q.top();
      q.pop();
    }
  }
  return 0;
}