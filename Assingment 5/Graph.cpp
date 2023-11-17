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

void printPath(int* node, int index) {
    if (node[index] != -1) {
        printPath(node, node[index]);
    }
    cout << " ";
    cout << index;
}

int Graph::shortestDistance(int s, int d) {
    int infinity = (int) - 1e9;
    int* distance = (int*) calloc(_nv, sizeof(int));
    int* node = (int*) calloc(_nv, sizeof(int));
    Heap<nodeWeightPair> pq;

    pq.insert(nodeWeightPair(s, 0));

    node[s] = -1;
    for (int i = 0; i < _nv; i++) {
        if (i != s) {
            distance[i] = infinity;
        }
    }

    while (!pq.empty()) {
        nodeWeightPair v = pq.extractMax();
        _al[v.nodeIndex()].start();

        while (!_al[v.nodeIndex()].end() && v.nodeIndex() != d) {
            nodeWeightPair neighbour = _al[v.nodeIndex()].current();
            int newDistance = distance[v.nodeIndex()] - neighbour.weight();

            if (neighbour.nodeIndex() != v.nodeIndex() && distance[neighbour.nodeIndex()] < newDistance) {
                if (distance[neighbour.nodeIndex()] != infinity) {
                    pq.increaseKey(neighbour, nodeWeightPair(neighbour.nodeIndex(), newDistance));
                }
                else {
                    pq.insert(nodeWeightPair(neighbour.nodeIndex(), newDistance));
                }
                node[neighbour.nodeIndex()] = v.nodeIndex();
                distance[neighbour.nodeIndex()] = newDistance;
            }
            _al[v.nodeIndex()].next();
        }
    }

    // Task 2 printing the path
    int shortestDist = -distance[d];
    if (distance[d] != infinity) {
        cout << "Path:";
        printPath(node, d);
        cout << endl;
    }
    else {
        shortestDist = -1;
    }

    free(distance);
    return shortestDist;
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
