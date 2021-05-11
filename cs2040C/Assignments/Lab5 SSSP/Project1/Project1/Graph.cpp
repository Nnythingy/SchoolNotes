#include "Graph.h"
//uncomment this to include your own "heap.h"
//we will assume that you use the same code in your previous assignment
#include "heap.h"

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}


Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}

int Graph::shortestDistance(int s, int d)
{
	// implement your code here
	_al[s].start();
	Heap<nodeWeightPair> pq;
	List<int> travelPath;
	int* visted = new int[_nv]{ 0 };
	int* parent = new int[_nv]{ 0 };

	parent[s] = -1;
	while (!_al[s].end())
	{
		int negweg = _al[s].current().weight() * -1;
		nodeWeightPair newnode = nodeWeightPair(_al[s].current().nodeIndex(), negweg);
		visted[_al[s].current().nodeIndex()] = negweg;
		parent[_al[s].current().nodeIndex()] = s;
		pq.insert(newnode);
		_al[s].next();
	}
	
	while (!pq.empty())
	{
		nodeWeightPair relaxed = pq.extractMax();
		visted[relaxed.nodeIndex()] = relaxed.weight();
		_al[relaxed.nodeIndex()].start();
		while (!_al[relaxed.nodeIndex()].end())
		{
			int currnod = _al[relaxed.nodeIndex()].current().nodeIndex();
			int currweg = _al[relaxed.nodeIndex()].current().weight() * -1;
			if (visted[currnod] < 0)
			{
				if ((visted[relaxed.nodeIndex()] + currweg) > visted[currnod])
				{
					nodeWeightPair torep = nodeWeightPair(currnod, visted[currnod]);
					nodeWeightPair tonew = nodeWeightPair(currnod, visted[relaxed.nodeIndex()] + currweg);
					pq.increaseKey(torep, tonew);
					visted[currnod] = visted[relaxed.nodeIndex()] + currweg;
					parent[currnod] = relaxed.nodeIndex();
				}
			}
			else
			{
				nodeWeightPair tmp = nodeWeightPair(currnod, visted[relaxed.nodeIndex()] + currweg);
				pq.insert(tmp);
				visted[currnod] = visted[relaxed.nodeIndex()] + currweg;
				parent[currnod] = relaxed.nodeIndex();
			}
			_al[relaxed.nodeIndex()].next();
		}
	}
	
	if (visted[d]) {
		int exit = d;
		while (exit != s)
		{
			travelPath.insertHead(exit);
			exit = parent[exit];
		}
		cout << "Path: " << s;
		travelPath.start();
		while (!travelPath.end())
		{
			cout << " " << travelPath.current(); travelPath.next();
		}
		cout << endl;
		return visted[d]*-1;
	}
	else { return -1; }
}

void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}
Graph::~Graph()
{

	delete[] _al;

}