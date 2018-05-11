
#include <iostream>

#include "mapper.hpp"

using std::cout;
using std::endl;

int main()
{
	CMapper mapper;

	auto n1 = mapper.add_node("n1");
	auto n2 = mapper.add_node("n2");
	auto n3 = mapper.add_node("n3");

	mapper.add_edge(n1, n2, 30);
	mapper.add_edge(n1, n3, 10);
	mapper.add_edge(n2, n3, 12);

	mapper.refresh_map();

	cout << mapper << endl;

	auto path = mapper.get_path(n1, n2);

	cout << path << endl;

	mapper.remove_node(n2);

	mapper.refresh_map();
	cout << mapper << endl;

	return 0;
}

