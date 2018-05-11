
#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <vector>

#include "node.hpp"

using std::ostream;
using std::vector;

class CPath
{
	unsigned _length;
	vector<const CNode *> _nodes;

	friend class CMapper;

	public:

		CPath();

		friend ostream & operator<<(ostream & stream, const CPath & path);

		inline unsigned length() { return _length; };
		inline unsigned nodes_num() { return _nodes.size(); };
		inline vector<const CNode *>::iterator begin() { return _nodes.begin(); };
		inline vector<const CNode *>::iterator end() { return _nodes.end(); };
};

#endif

