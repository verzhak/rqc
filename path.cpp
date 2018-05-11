
#include "path.hpp"

CPath::CPath()
{
	_length = 0;
}

ostream & operator<<(ostream & stream, const CPath & path)
{
	stream << "Path = " << path._length << ": BEGIN -> ";

	for(auto & n : path._nodes)
		stream << n->name() << " -> ";

	stream << "END";

	return stream;
}

