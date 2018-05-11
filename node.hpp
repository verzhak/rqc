
#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>

using std::ostream;
using std::string;

class CNode
{
	const string _name;

	public:

		CNode(const string name);
		CNode(const CNode & node);

		bool operator!=(const CNode & node) const;
		friend ostream & operator<<(ostream & stream, const CNode & node);

		inline string name() const { return _name; };
};

#endif

