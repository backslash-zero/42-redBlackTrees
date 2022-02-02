#pragma once

#include <iostream>
#include <string>

#include "node.hpp"
#include "pair.hpp"

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

	void _redBlackTree_rootInsert(node_type *newNode)
	{
		this->_root = newNode;
		newNode->right = this->_ghost_node;
		_ghost_node->parent = newNode;
	}

	void _redBlackTree_simpleInsert(node_type *newNode)
	{
		if (this->_size == 0)
			_redBlackTree_rootInsert(newNode);
		else
		{
			iterator lowerBound = (this->lower_bound(newNode->data.first));
			node_type *lowerBoundNode = lowerBound.node_ptr();

			// case last element
			if (lowerBoundNode == this->_ghost_node)
			{
				lowerBoundNode->parent->right = newNode;
				newNode->parent = lowerBoundNode->parent;
				newNode->right = _ghost_node;
				_ghost_node->parent = newNode;
			}
			else // all other cases
			{
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

	void _redBlackTree_add(node_type *newNode)
	{
		// New Node already created when pointer passed.
		// 1. Insert node and color it RED

		_redBlackTree_simpleInsert(newNode);
		newNode->setColor(RED);

		// Scenario 1: node is root
		if (this->_root == newNode)
			newNode->setColor(BLACK);
		else
			_redBlackTree_fix(newNode);
		if (this->_root->getColor() == RED)
			this->_root->setColor(BLACK);
		this->_size++;
		// _redBlackTree_debug_printDotTree("end_add");
	}
};