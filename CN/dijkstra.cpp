#include <stdio.h>
#include <conio.h>
#include <limits.h>

#define INF INT_MAX
#define MAX 100
#define NIL 0

struct Graph {
private:
	int vertices;
	int edges;
	int pLength[MAX];
	int pred[MAX];
	bool state[MAX];
	int weight[MAX][MAX];
	bool** adjMatrix;
public:
	Graph(int v, int e) : vertices(v), edges(e) {
		adjMatrix = new bool*[vertices];
		for (int i = 0; i < vertices; ++i) {
			adjMatrix[i] = new bool[vertices];
			for (int j = 0; j < vertices; ++j)
				adjMatrix[i][j] = false;
		}
	}
	
	void init();
	int minLength();
	void connectVertices(int, int, int);
	void showGraph();
  bool findState();
	void dijkstra(int);
  void showSPath(int);
  void pathPrinter(int, int);
};

void Graph :: init() {
	for (int i = 0; i < vertices; i++) {
		pLength[i] = INF;
  	pred[i] = NIL;
		state[i] = true;
	}
}

int Graph :: minLength() {
	int min = INF;
	int pos; 
	for (int i = 0; i < vertices; i++) {
		if (pLength[i] <= min && state[i] == true) {
			min = pLength[i];
			pos = i;
		}
	}
	return pos;
}

bool Graph :: findState() {
  int flag = 0;
  for(int i = 0; i < vertices; ++i) {
    if(state[i] == true || pLength[i] == INF) {
      flag = 1;
      break;
    }
  }
  return (flag == 1)? true : false;
}

void Graph :: dijkstra(int src) {
	int curr, minVer;
	init();
	pLength[src] = 0;
  while (findState() != false) {
    minVer = minLength();
    state[minVer] = false;
    curr = minVer;
    for (int i = 0; i < vertices; i++) {
      if (adjMatrix[curr][i] == true && state[i] == true) {
        if (pLength[curr] + weight[curr][i] < pLength[i]) {
            pLength[i] = pLength[curr] + weight[curr][i];
            pred[i] = curr;
        }
      }
    }
  }
  for(int i = 0; i < vertices; i++) 
    printf("\n%d -> %d : %d ", src, i, pLength[i]);
 
  printf("\n\n");
  showSPath(src);
}

void Graph :: connectVertices(int i, int j, int w) {
	adjMatrix[i][j] = true;
  weight[i][j]    = w;
}

void Graph :: showGraph() {
	for (int i = 0; i < vertices; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < vertices; ++j)
			printf("%d ", adjMatrix[i][j]);
		printf("\n");
	}
}

void Graph :: pathPrinter(int src, int i) {
  if(pred[i] == src) 
    printf("%d--", pred[i]);
  else {
    pathPrinter(src, pred[i]);
    printf("%d--",pred[i]);
  }
}

void Graph :: showSPath(int src) {
   for(int i = 0; i < vertices; ++i) {
     printf("%d -> %d : ", src, i);
     pathPrinter(src, i);
     printf("%d",i);
     printf("\n");
   }
}

int main() {

	unsigned int v = 0, sv = 0, e = 0, w = 0, srcVertex = 0, desVertex = 0;
//	printf("\n Enter the number of vertices and edges of the graph:");
//	scanf("%d%d", &v, &e);
	Graph g(8, 16);	
/*	for (int counter = 0; counter < e; counter++) {
		printf("\n Enter source and destination: ");
		scanf("%d%d", &srcVertex, &desVertex);
		printf("\n Enter the weight on that edge: ");
		scanf("%d", &w);
		printf("\n");
		g.connectVertices(srcVertex, desVertex, w);
	}
*/
   
    g.connectVertices(0,1,8);
    g.connectVertices(0,2,2);
    g.connectVertices(0,3,7);
    g.connectVertices(1,5,16);
    g.connectVertices(2,0,5);
    g.connectVertices(2,3,4);
    g.connectVertices(2,6,3);
    g.connectVertices(3,4,9);
    g.connectVertices(4,5,5);
    g.connectVertices(4,0,4);
    g.connectVertices(4,7,8);
    g.connectVertices(6,2,6);
    g.connectVertices(6,3,3);
    g.connectVertices(6,4,4);
    g.connectVertices(7,5,2);
    g.connectVertices(7,6,5);
  
	  g.showGraph();
	  printf("\nEnter Start Vertex : ");
	  scanf("%d", &sv);
	  g.dijkstra(sv);

	  return 0;

}


