#pragma once

#include <iostream>
#include <string>

#include "_redBlackTree.hpp"

#include "../commons/commons.hpp"
#include "../tools/tools.hpp"

/* 	Every node has a colour either red or black.
 *		- The root of the tree is always black.
 *		- There are no two adjacent red nodes (A red node cannot have a red parent or red child).
 *		- Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
 *		- All leaf nodes are black nodes.
 */

/****************************************************************
 *
 *	INSERTION STRATEGY:
 *
 *		1. Insert node and color it RED
 *		2. Recolor and rotate to fix violations of RBT rules
 *
 */

namespace ft
{
	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_rootInsert(node_type *newNode)
	{
		this->_root = newNode;
		newNode->right = this->_ghost_node;
		_ghost_node->parent = newNode;
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_LastElementInsert(node_type *newNode)
	{
		this->_ghost_node->parent->right = newNode;
		newNode->parent = this->_ghost_node->parent;
		newNode->right = _ghost_node;
		newNode->left = NULL;
		_ghost_node->parent = newNode;
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_simpleInsert(node_type *newNode)
	{
		if (this->_size == 0)
			_redBlackTree_rootInsert(newNode);
		else
		{

			// case last element
			if (this->_redBlackTree_checkLastNode(newNode))
				_redBlackTree_LastElementInsert(newNode);
			else // all other cases
			{
				node_type *lowerBoundNode = (this->lower_bound(newNode)).node_ptr();
				if (lowerBoundNode->left == NULL)
				{
					lowerBoundNode->left = newNode;
					newNode->parent = lowerBoundNode;
				}
				else
				{
					node_type *parent_node = max_node(lowerBoundNode->left);
					parent_node->right = newNode;
					newNode->parent = parent_node;
				}
			}
		}
	}

	template <class node_type, class value_compare>
	node_type *redBlackTree<node_type, value_compare>::redBlackTree_add(node_type *newNode)
	{
		// New Node already created when pointer passed.
		// 1. Insert node and color it RED
		_redBlackTree_simpleInsert(newNode);
		newNode->_color = RED;

		// Scenario 1: node is root
		if (this->_root == newNode)
			newNode->_color = BLACK;
		else if (this->_redBlackTree_violation_redParent_redChild(newNode)) // checking if theres a problem with inserted node.
			_redBlackTree_fix(newNode);
		if (this->_root->_color == RED)
			this->_root->_color = BLACK;
		this->_size++;
		return (newNode);
		//_redBlackTree_debug_printDotTree("add");
	}
};