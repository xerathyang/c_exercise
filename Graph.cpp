// Graph.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <limits>

using namespace std;

int minDist(int** narray, int start, int vertices, int dist[], bool sSet[]) {
	int minIndex = 0;
	//int Indexcomp = 999;
	//for (int i = 0; i < vertices; i++) {
	//	if (Indexcomp > narray[start-1][i] && sSet[i] != 1 && narray[start-1][i] != 0) {
	//		minIndex = i;
	//		Indexcomp = narray[start-1][i];
	//	}		
	//}
	int min = 999;
	//cout << "set ";
	//for (int i = 0; i < start; i++)
	//	cout << sSet[i] << " ";
	//cout << endl;
	//cout << "dist ";
	//for (int i = 0; i < start; i++)
	//	cout <<dist[i] << " ";
	//cout << endl;
	for (int i = 0; i < vertices; i++) {
		if (sSet[i] == false && dist[i] < min) {
			min = dist[i];
			minIndex = i;
		}
	}
	return minIndex;
}

void path(int parent[], int a) {
	if (parent[a] == -1)
		return;
	path(parent, parent[a]);
	cout << a+1 << " ";
}

class Graph {
public:
	Graph(int, int, int);
	void insert(int**,int, int, int);
	void ptr(int**);
private:
	int node,start;
};

Graph::Graph(int n, int e, int s) {
	node = n;
	start = s;
}

void Graph::insert(int** narray,int p, int q, int d) {
	
	narray[p - 1][q - 1] = d;
	narray[q - 1][p - 1] = d;
}



void Graph::ptr(int** narray) {
	int* dist = new int[node];
	bool* sSet = new bool[node];
	int* parent = new int[node];

	for (int i = 0; i < node; i++) {
		parent[i] = -1;
		dist[i] = 999;
		sSet[i] = false;
	}

	dist[start-1] = 0;

	for (int j = 0; j < node - 1; j++) {
		int count = minDist(narray, start, node, dist, sSet);
		sSet[count] = true;

		//cout << "set ";
		//for (int i = 0; i < start; i++)
		//	cout << sSet[i] << " ";
		//cout << endl;

		for (int t = 0; t < node; t++) {

			cout << narray[j][t] << endl;

			if (sSet[t] == false && narray[j][t] && dist[j] + narray[j][t] < dist[t]) {
				parent[t] = j;
				//for (int i = 0; i < start; i++)
				//	cout << parent[i] << " ";
				//cout << endl;
				dist[t] = dist[j] + narray[j][t];
				//for (int i = 0; i < start; i++)
				//	cout << dist[i] << " ";
				//cout << endl;
			}
		}
	}

	//cout << "	parent	dist			sSet" << endl;
	//for (int i = 0; i < node; i++) {
	//	cout << i << "\t" << parent[i] << "\t" << dist[i] << "\t\t\t" << sSet[i] << endl;
	//}

	for (int i = 0; i < node; i++) {
		if (i+1 == start) {
			continue;
		}
		cout << "Distance of " << start << " to " << i+1 << " : " << dist[i] << endl;
		cout << "Path: " << start << " ";
		path(parent, i);
		cout << endl;
	}
}

int main()
{
	int input,n,e,s,p,q,d;
	while (cin >> input) {
		n = input;
		int **narray = new int *[n];
		for (int i = 0; i < n; i++){
			narray[i] = new int[n];
		}
		for (int i = 0; i < n;i++){
			for (int j = 0; j < n;j++){
				narray[i][j] = 0;
			}
		}
		cin >> e >> s;
		Graph* shortetpath = new Graph(n, e, s);
		for (int i = 0; i < e; i++) {
			cin >> p >> q >> d;
			shortetpath->insert(narray,p, q, d);
		}
		shortetpath->ptr(narray);
	}
}