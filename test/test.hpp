
#ifndef TEST_HPP
#define TEST_HPP

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mapper.hpp"

using namespace testing;

void mapper_init(CMapper & mapper)
{
	auto A = mapper.add_node("A");
	auto B = mapper.add_node("B");
	auto C = mapper.add_node("C");
	auto D = mapper.add_node("D");
	auto E = mapper.add_node("E");

	mapper.add_edge(A, B, 2);
	mapper.add_edge(A, C, 5);
	mapper.add_edge(A, E, 7);
	mapper.add_edge(B, C, 1);
	mapper.add_edge(C, D, 5);
	mapper.add_edge(C, E, 1);
	mapper.add_edge(D, E, 3);

	mapper.refresh_map();
}

TEST(CMapper, get_path)
{
	CMapper mapper;

	mapper_init(mapper);

	auto path = mapper.get_path(mapper.get_node("A"), mapper.get_node("D"));

	ASSERT_EQ(path.length(), 7);
	ASSERT_EQ(path.nodes_num(), 5);

	ASSERT_STREQ((* path.begin())->name().c_str(), "D");
	ASSERT_STREQ((* (path.begin() + 1))->name().c_str(), "E");
	ASSERT_STREQ((* (path.begin() + 2))->name().c_str(), "C");
	ASSERT_STREQ((* (path.begin() + 3))->name().c_str(), "B");
	ASSERT_STREQ((* (path.begin() + 4))->name().c_str(), "A");
}

TEST(CMapper, get_next_node_in_path)
{
	CMapper mapper;

	mapper_init(mapper);
	
	const CNode * next, * D = mapper.get_node("D");
	
	next = mapper.get_next_node_in_path(mapper.get_node("A"), D);
	ASSERT_STREQ(next->name().c_str(), "B");

	next = mapper.get_next_node_in_path(next, D);
	ASSERT_STREQ(next->name().c_str(), "C");

	next = mapper.get_next_node_in_path(next, D);
	ASSERT_STREQ(next->name().c_str(), "E");

	next = mapper.get_next_node_in_path(next, D);
	ASSERT_STREQ(next->name().c_str(), "D");
}

#endif

