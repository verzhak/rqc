
#include "mapper.hpp"

// #############################################################################
// Ноды

const CNode * CMapper::add_node(const string name)
{
	_nodes.insert(pair<string, CNode>(name, CNode(name)));

	return get_node(name);
}

const CNode * CMapper::get_node(const string name)
{
	auto it = _nodes.find(name);

	if(it == _nodes.end())
		throw invalid_argument("Node not exist");

	return & it->second;
}

void CMapper::remove_node(const CNode * node)
{
	_nodes.erase(_nodes.find(node->name()));

	auto del_edge = [&](const CNode * n1, const CNode * n2)
	{
		auto it = _edges.find(TEdgeKey(n1, n2));

		if(it != _edges.end())
			_edges.erase(it);
	};

	for(auto & n : _nodes)
	{
		del_edge(node, & n.second);
		del_edge(& n.second, node);
	}
}

// #############################################################################
// Ребра

const CEdge * CMapper::add_edge(const CNode * n1, const CNode * n2, const unsigned length)
{
	_edges.insert(pair<TEdgeKey, CEdge>(TEdgeKey(n1, n2), CEdge(n1, n2, length)));

	return get_edge(n1, n2);
}

const CEdge * CMapper::get_edge(const CNode * n1, const CNode * n2)
{
	auto it = _edges.find(TEdgeKey(n1, n2));

	if(it == _edges.end())
	{
		it = _edges.find(TEdgeKey(n2, n1));

		if(it == _edges.end())
			throw invalid_argument("Edge not exist");
	}

	return & it->second;
}

void CMapper::remove_edge(const CEdge * edge)
{
	_edges.erase(_edges.find(edge->nodes()));
}

// #############################################################################
// Mapper

CPath CMapper::get_path(const CNode * n1, const CNode * n2)
{
	CPath path;
	const CNode * next;

	path._length = _map[TEdgeKey(n1, n2)].length;

	for(
		next = n2;
		(* next) != (* n1);
		next = _map[TEdgeKey(n1, next)].next_node
	   )
		path._nodes.push_back(next);

	path._nodes.push_back(next);

	return path;
}

const CNode * CMapper::get_next_node_in_path(const CNode * n_from, const CNode * n_to)
{
	return _map[TEdgeKey(n_to, n_from)].next_node;
}

void CMapper::refresh_map()
{
	const unsigned num = _nodes.size();
	const unsigned num_2 = num * num;
	vector<unsigned> path_sizes(num_2, UINT_MAX);
	vector<int> prev_nodes(num_2, -1);
	vector<string> keys;
	unsigned v, u, k;

	for(auto & n : _nodes)
		keys.push_back(n.first);

	for(v = 0; v < num; v++)
		for(u = v; u < num; u++)
		{
			try
			{
				const unsigned ind = v * num + u, rev_ind = u * num + v;

				path_sizes[ind] = path_sizes[rev_ind] = get_edge(get_node(keys[v]), get_node(keys[u]))->length();

				prev_nodes[ind] = v;
				prev_nodes[rev_ind] = u;
			}				
			catch(const invalid_argument &)
			{
				;
			}
		}

	// #############################################################################
	// Алгоритм Дейкстры

	for(k = 0; k < num; k++)
	{
		const unsigned k_num = k * num;
		vector<unsigned> not_visited_nodes;

		// Хотя можно было бы использовать boost::conting_iterator
		for(v = 0; v < num; v++)
			not_visited_nodes.push_back(v);

		while(not_visited_nodes.size())
		{
			auto min_it = std::min_element(
					not_visited_nodes.begin(), not_visited_nodes.end(),
					[ & ](const unsigned & n1, const unsigned & n2)
					{
						return path_sizes[k_num + n1] < path_sizes[k_num + n2];
					});
			const unsigned v = * min_it;
			const unsigned k_num_v = k_num + v;

			if(path_sizes[k_num_v] != UINT_MAX)
			{
				for(u = 0; u < num; u++)
				{
					try
					{
						const unsigned edge = get_edge(get_node(keys[v]), get_node(keys[u]))->length();
						const unsigned new_cost = path_sizes[k_num_v] + edge;
						const unsigned k_num_u = k_num + u;

						if(path_sizes[k_num_u] > new_cost)
						{
							path_sizes[k_num_u] = new_cost;
							prev_nodes[k_num_u] = v;
						}
					}
					catch(const invalid_argument &)
					{
						;
					}
				}

				not_visited_nodes.erase(min_it);
			}
		}
	}

	// #############################################################################

	_map.clear();

	unsigned ind;

	for(v = 0, ind = 0; v < num; v++)
		for(u = 0; u < num; u++, ind++)
		{
			auto & it = _map[TEdgeKey(get_node(keys[v]), get_node(keys[u]))];

			if(v == u)
			{
				it.length = 0;
				it.next_node = get_node(keys[v]);
			}
			else
			{
				it.length = path_sizes[ind];
				it.next_node = get_node(keys[prev_nodes[ind]]);
			}
		}
}

// #############################################################################
// Служебные функции

ostream & operator<<(ostream & stream, const CMapper & mapper)
{
	for(auto & n : mapper._nodes)
		stream << n.second << '\n';

	for(auto & e : mapper._edges)
		stream << e.second << '\n';

	for(auto & p : mapper._map)
		stream << "Path: " << p.first.first->name() << " -> " << p.first.second->name() << " = " << p.second.length << ", " << p.second.next_node->name() << '\n';

	return stream;
}

