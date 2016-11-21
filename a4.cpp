/*
I came up with the algorithm after analyzing tree diameter, thanks to posts from Geekstogeeks.
The algorithm works as follows:
First, randomly choose a node and do BFS. Store distance from this node to other node in array A.
Second, choose the node with largest distance in A, if there are multiple nodes with the same largest distance,
randomly choose one(This does not change the result), marke the node as S.
Third, do a BFS from S and store distance from A to any other nodes in array B.
Then, the longest distance for node i is max(A[i],B[i]).
*/
#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<limits>


using namespace std;
list<int> * tree;
int infinity = numeric_limits<int>::min();

int BFS(int* array, int size, int source) {
	int maxDistIndex;
    //create a queue and add source to it
	queue<int> Q;
	Q.push(source);
	array[source] = 0;
	//while Q is not empty, pop front node and push all of its unvisited neighbours onto Q and update their distances

	while(!Q.empty()) {
        int prev = Q.front();
		Q.pop();
		list<int>::iterator it = tree[prev].begin();
		while(it != tree[prev].end()) {
            if(array[(*it)] == infinity) {
                Q.push((*it));
                array[(*it)] = array[prev] + 1;
            }
			++it;
		}
	}

	//find the first node with max distance and return its index
	int maxDist = 0;
	for(int i  = 0; i < size; i ++) {
		if(array[i] > maxDist){
			maxDist = array[i];
			maxDistIndex = i;
		}
	}
	return maxDistIndex;
}

void printMaxDis(int* A, int* B, int size) {
	for(int i = 0; i < size; i++) {
		if(A[i] >= B[i]) {
			cout << A[i];
		}
		else {
			cout << B[i];
		}
		cout << "\n";
	}
}

int main() {
	int N;
	cin >> N;

	//implement the special graph(tree) with adjacency list
	tree = new list<int> [N];

	//store each node and its adjacent nodes in a list, there are N such lists
	int u, v;
	for(int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	//randomly chose a node, for simplicity choose the first node as source1 node and do BFS to find distance from source node to other nodes
	int arrayA[N], arrayB[N], arrayC[N];

	//initialize distance with infinity
	for (int i = 0; i < N; i++) {
		arrayA[i] = infinity;
	}

	for (int i = 0; i < N; i++) {
		arrayB[i] = infinity;
	}
    for (int i = 0; i < N; i++) {
		arrayC[i] = infinity;
	}
	//store distances into arrayA while doing BFS, and return index with max distance(if there are multiple indexes, return the first one)
	int source2 = BFS(arrayA, N, 0);
	int source3 = BFS(arrayB, N, source2);
    BFS(arrayC, N, source3);

	//max distance of node i is max(arrarB[i], arrayC[i]), print out the max distance
	printMaxDis(arrayB, arrayC, N);
	return 0;
}
