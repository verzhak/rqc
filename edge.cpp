
#include "edge.hpp"

CEdge::CEdge(const CNode * node_1, const CNode * node_2, const unsigned length) :
	_node_1(node_1), _node_2(node_2), _length(length)
{
	;
}

CEdge::CEdge(const CEdge & edge) :
	_node_1(edge._node_1), _node_2(edge._node_2), _length(edge._length)
{
	;
}

ostream & operator<<(ostream & stream, const CEdge & edge)
{
	stream << "Edge: " << edge._node_1->name() << " -> " << edge._node_2->name() << " = " << edge._length;

	return stream;
}

