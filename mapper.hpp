
#ifndef MAPPER_HPP
#define MAPPER_HPP

#include <iostream>
#include <string>
#include <map>
#include <climits>
#include <stdexcept>
#include <algorithm>
#include <memory>

#include "node.hpp"
#include "edge.hpp"
#include "path.hpp"

using std::ostream;
using std::string;
using std::map;
using std::min;
using std::invalid_argument;
using std::unique_ptr;
using std::make_unique;

struct SMapElement
{
	unsigned length;
	const CNode * next_node;
};

/*!

  \brief Класс, описывающий граф сети

*/
class CMapper
{
	map<string, CNode> _nodes;
	map<TEdgeKey, CEdge, CEdgeKeyCompare> _edges;
	map<TEdgeKey, SMapElement, CEdgeKeyCompare> _map;

	public:

		/*!

		  \brief Добавление ноды

		  \param name - строка, содержащая имя новой ноды

		  \return Указатель на созданную ноду

		*/
		const CNode * add_node(const string name);
		
		/*!

		  \brief Получение указателя на ноду

		  \param name - строка, содержащая имя ноды

		  \return Указатель на ноду

		*/
		const CNode * get_node(const string name);

		/*!

		  \brief Удаление ноды

		  \param name - строка, содержащая имя удаляемой ноды

		  Будут удалены также все ребра графа, содержащие данную ноду

		*/
		void remove_node(const CNode * node);

		/*!

		  \brief Добавление ребра

		  \param n1, n2 - указатели на описатели оконечных нод
		  \param length - целое, беззнаковое, вес ребра

		  \return Указатель на созданное ребро

		*/
		const CEdge * add_edge(const CNode * n1, const CNode * n2, const unsigned length);

		/*!

		  \brief Получение указателя на ребро

		  \param n1, n2 - указатели на описатели оконечных нод

		  \return Указатель на ребро

		*/
		const CEdge * get_edge(const CNode * n1, const CNode * n2);

		/*!

		  \brief Удаление ребра

		  \param edge - указатель на удаляемое ребро

		*/
		void remove_edge(const CEdge * edge);

		/*!

		  \brief Обновление таблицы маршрутизации по алгоритму Дейкстры

		*/
		void refresh_map();

		/*!

		  \brief Получение кратчайшего маршрута между ребрами в текущей таблице маршрутизации

		  \param n1, n2 - указатели на описатели оконечных нод

		*/
		CPath get_path(const CNode * n1, const CNode * n2);

		friend ostream & operator<<(ostream & stream, const CMapper & mapper);
};

#endif

