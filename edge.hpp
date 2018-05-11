
#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <utility>

#include "node.hpp"

using std::ostream;
using std::pair;

typedef pair<const CNode *, const CNode *> TEdgeKey;

class CEdgeKeyCompare
{
	public:

		inline bool operator()(const TEdgeKey & key_1, const TEdgeKey & key_2)
		{
			return 
				(key_1.first->name() < key_2.first->name())
				||
				(
				 key_1.first->name() == key_2.first->name()
				 &&
				 key_1.second->name() < key_2.second->name()
				);
		};
};

class CEdge
{
	const CNode * _node_1;
	const CNode * _node_2;
	const unsigned _length;

	public:

		CEdge(const CNode * node_1, const CNode * node_2, const unsigned length);
		CEdge(const CEdge & edge);

		friend ostream & operator<<(ostream & stream, const CEdge & edge);

		inline unsigned length() const { return _length; };
		inline TEdgeKey nodes() const { return TEdgeKey(_node_1, _node_2); };
};

#endif

