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
	Edge(int either_,int other_, int cost_,Edge * link_) :either(either_),other(other_), cost(cost_), link(link_) {}


};

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
	// 顶点表
	Vertex * NodeTable;
public:
	//顶点的数据和索引的对应 
	map<string, int> findVertex;
	Graph() : v(0), e(0), NodeTable(NULL) {}
	Graph(int sz) {
		v = sz;
		NodeTable = new Vertex[v];
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
	}
	//创建顶点
	void createVertex() {
		cout << "请依次输入各顶点的名称：" << endl;
		for (int i = 0; i < v; i++) {
			cin >> NodeTable[i].data;
			findVertex[NodeTable[i].data] = i;
		}
	}
	//创建边
	void createEdge() {	
		string v1data, v2data;
		int weight;
		cout << "请输入两个顶点及边: ";
		cin >> v1data >> v2data >> weight;
		while (v1data != "?") {
			int v1 = findVertex[v1data];
			int v2 = findVertex[v2data];
			insertEdge(v1, v2, weight);
			cout << "请输入两个顶点及边: ";
			cin >> v1data >> v2data >> weight;
		}
	}
	//指定两个顶点之间插入边
	void insertEdge(int v1, int v2, int weight) {
		Edge * e_v1 = new Edge(v1,v2, weight, NodeTable[v1].adj);
		Edge * e_v2 = new Edge(v2,v1, weight, NodeTable[v2].adj);
		NodeTable[v1].adj = e_v1;
		NodeTable[v2].adj = e_v2;
		e++;
	}
	//输出
	void output() {
		for (int i = 0; i < v; i++) {
			cout << NodeTable[i].data;
			Edge * p = NodeTable[i].adj;
			while (p != NULL) {
				cout << p->cost << NodeTable[p->other].data << ' ';
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
	string nodeData(int v) {
		return NodeTable[v].data;
	}
};
struct cmp {
	bool operator()(Edge & e1, Edge & e2) {
		return e1.cost > e2.cost;
	}
};
class Prime {
private:
	////标志顶点是否被访问过的数组
	bool * marked;
	////按照边的权重存边的优先队列
	priority_queue<Edge,vector<Edge>,cmp> pq;
	// 最小生成树的边集合
	vector<Edge> mst;
	//访问指定顶点
	void visit(Graph & G, int v) {
		marked[v] = true;
		Edge * p = G.adj(v);
		while (p != NULL) {
			if (!marked[p->other]) {
				pq.push(*p);
			}
			p = p->link;
		}
	}
public:
	Prime(Graph & G,string begin) {
		marked = new bool[G.getV()];
		for (int i = 0; i < G.getV(); i++) {
			marked[i] = false;
		}
		visit(G, G.findVertex[begin]);
		while (!pq.empty()) {
			Edge e = pq.top();
			pq.pop();
			int v = e.either, w = e.other;
			if (marked[v] && marked[w]) continue;
			mst.push_back(e);
			if (!marked[v]) visit(G, v);
			if (!marked[w]) visit(G, w);
		}
		cout << "生成Prim最小生成树！" << endl;
	}
	~Prime() {
		delete[] marked;
	}
	//输出最小生成树
	void output(Graph &G) {
		cout << "最小生成树的的顶点及边为：" << endl;
		cout << endl;
		for (int i = 0; i < mst.size(); i++) {
			cout << G.nodeData(mst[i].either) << "<-("<<mst[i].cost <<")->"<< G.nodeData(mst[i].other) << '\t';
		}
		cout << endl;
	}

};


int main() {
	//freopen("Text8.txt", "r", stdin);
	priority_queue<Edge> pq;
	
	Graph * graph = NULL;
	int v;
	Prime * prime = NULL;
	char order;
	cout << "**                     电网造价模拟系统                     **" << endl;
	cout << "==============================================================" << endl;
	cout << "**                     A---创建电网顶点                     **" << endl;
	cout << "**                     B---添加电网的边                     **" << endl;
	cout << "**                     C---构造最小生成树                   **" << endl;
	cout << "**                     D---显示最小生成树                   **" << endl;
	cout << "**                     E---退出   程序                      **" << endl;
	cout << "==============================================================" << endl << endl;
	cout << "请选择操作：";
	cin >> order;
	string begin;
	while (order != 'E') {
		switch (order)
		{
		case 'A':
			cout << "请输入顶点的个数：";
			cin >> v;
			graph = new Graph(v);
			graph->createVertex();			
			break;
		case 'B':	
			if (graph) graph->createEdge();
			//graph->output();
			break;
		case 'C':
			
			cout << "请输入起始顶点：";
			cin >> begin;
			prime = new Prime(*graph,begin);
			break;
		case 'D':
			if(prime) prime->output(*graph);
		default:
			break;
		}
		cout << endl;
		cout << "请选择操作：";
		cin >> order;
	}
	return 0;
}

		



			


