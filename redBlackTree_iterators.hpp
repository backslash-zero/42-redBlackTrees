#pragma once

#include <iostream>
#include <string>

#include "_redBlackTree.hpp"

#include "../commons/commons.hpp"
#include "../tools/tools.hpp"

namespace ft
{
	template <class node_type, class value_compare>
	typename redBlackTree<node_type, value_compare>::iterator redBlackTree<node_type, value_compare>::begin(void)
	{
		redBlackTree<node_type, value_compare>::iterator result(min_node(this->_root));
		return (result);
	}

	template <class node_type, class value_compare>
	typename redBlackTree<node_type, value_compare>::iterator redBlackTree<node_type, value_compare>::end(void)
	{
		redBlackTree<node_type, value_compare>::iterator result(this->_ghost_node);
		return (result);
	}
}