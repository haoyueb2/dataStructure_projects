#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#pragma warning(disable:4996)
using namespace std;
struct Edge {
	int either;
	int other;
	int cost;
	Edge * link;
	Edge(int either_, int other_, int cost_, Edge * link_) :either(either_), other(other_), cost(cost_), link(link_) {}
};
//data存拓扑排序的顺序
struct Vertex {
	string data;
	Edge * adj;
	Vertex() :data(""), adj(NULL) {}
};
class Graph {
private:
	//节点个数 
	int v;
	//边的个数   
	int e;
	//顶点表
	Vertex * NodeTable;
public:
	//顶点的拓扑顺序和索引的对应 
	map<string, int> findVertex;
	//入度数组兼入度为零顶点栈
	int *count;
	Graph() : v(0), e(0), NodeTable(NULL) {}
	Graph(int sz) {
		v = sz;
		NodeTable = new Vertex[v];
		count = new int[v];
		for (int i = 0; i < v; i++) {
			count[i] = 0;
		}
	}
	~Graph() {
		for (int i = 0; i < v; i++) {
			Edge * p = NodeTable[i].adj;
			while (p != NULL) {
				Edge * tmp = p;
				p = p->link;
				delete tmp;
			}
		}
		delete[] NodeTable;
	}
	//创建边
	void createEdge(int m) {
		int v1, v2;
		int weight;

		for(int i = 0; i < m; i++) {
			cin >> v1 >> v2 >> weight;
			//索引即顶点，减一存入，输出加一就好
			insertEdge(v1-1, v2-1, weight);

		}
	}
	// 指定两个顶点之间插入边 
	void insertEdge(int v1, int v2, int weight) {
		count[v2]++;
		Edge * e_v1 = new Edge(v1, v2, weight, NodeTable[v1].adj);
		NodeTable[v1].adj = e_v1;
		e++;
	}
	//输出
	void output() {
		for (int i = 0; i < v; i++) {
			cout << i+1;
			Edge * p = NodeTable[i].adj;
			while (p != NULL) {
				cout << p->cost << p->other+1 << ' ';
				p = p->link;
			}
			cout << endl;
		}
	}
	//获取顶点个数
	int getV() {
		return v;
	}
	//获取边的个数
	int getE() {
		return e;
	}
	//获取指定顶点的边链表
	Edge * adj(int v) {
		return NodeTable[v].adj;
	}
	//获取指定顶点的数据
	string & nodeData(int v) {
		return NodeTable[v].data;
	}
};
bool topologicalSort(Graph &G) {
	int n = G.getV();
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (G.count[i] == 0) {
			G.count[i] = top;
			top = i;
		}
	}
	int v;
	for (int i = 0; i < n; i++) {
		if (top == -1) {
			//cout << "有回路" << endl;
			return false;
		}
		else {
			v = top;
			top = G.count[top];
			G.nodeData(v) = to_string(i);
			G.findVertex[to_string(i)] = v;
			//cout << G.nodeData(v);
			//cout << v+1;
			Edge * p = G.adj(v);
			while (p != NULL) {
				if (--G.count[p->other] == 0) {
					G.count[p->other] = top;
					top = p->other;
				}
				p = p->link;
			}
		}
	}
	return true;
}
void criticalPath(Graph &G) {
	int n = G.getV();
	vector<int > Ve(n);
	vector<int > Vl(n);
	int w;
	for (int i = 0; i < n; i++) {
		Ve[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int v = G.findVertex[to_string(i)];//找到拓扑顺序对应顶点
		Edge * p = G.adj(v);
		while (p != NULL) {
			w = p->cost;
			if (Ve[v] + w > Ve[p->other]) {
				Ve[p->other] = Ve[v] + w;//核心语句
			}
			p = p->link;
		}
	}
	
	cout << Ve[G.findVertex[to_string(n - 1)]] << endl;
	for (int i = 0; i < n; i++) {
		Vl[i] = Ve[G.findVertex[to_string(n-1)]];
	}
	for (int i = n - 2; i >= 0; i--) {
		int v = G.findVertex[to_string(i)];//找到拓扑逆序对应顶点
		Edge * p = G.adj(v);
		while (p != NULL) {
			w = p->cost;
			if (Vl[p->other] - w < Vl[v]) {
				Vl[v] = Vl[p->other] - w;//核心语句
			}
			//cout << "debug:" << p->either + 1 << "->" << p->other + 1 << endl;
			p = p->link;
		}
		
	}
	for (int i = 0; i < n; i++) {
		Edge * p = G.adj(i);
		while (p != NULL) {
			w = p->cost;
			int Ae = Ve[i];
			int Al = Vl[p->other] - w;
			if (Ae == Al) {
				cout << i+1 << "->" << p->other+1 << endl; //核心语句
			}
			p = p->link;
		}
		
	}
}



int main() {
	//freopen("Text9.txt", "r", stdin);
	int n, m;
	cin >> n;
	cin >> m;
	Graph * graph = new Graph(n);
	graph->createEdge(m);
	//graph->output();
	cout << "结果为:" << endl;
	if (topologicalSort(*graph)) {
		criticalPath(*graph);
	}
	else {
		cout << 0;
	}
	return 0;
}