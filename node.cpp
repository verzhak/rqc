
#include "node.hpp"

CNode::CNode(const string name) :
	_name(name)
{
	;
}

CNode::CNode(const CNode & node) :
	_name(node.name())
{
	;
}

bool CNode::operator!=(const CNode & node) const
{
	return name() != node.name();
}

ostream & operator<<(ostream & stream, const CNode & node)
{
	stream << "Node: " << node.name();

	return stream;
}

