#pragma once

#include <iostream>
#include <string>

#include "_redBlackTree.hpp"

#include "../commons/commons.hpp"
#include "../tools/tools.hpp"

namespace ft
{
	template <class node_type, class value_compare>
	redBlackTree<node_type, value_compare>::redBlackTree(void) : _comp()
	{
		;
	};
	template <class node_type, class value_compare>
	redBlackTree<node_type, value_compare>::~redBlackTree(void)
	{
		;
	};
}