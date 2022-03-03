#pragma once

#include <iostream>
#include <string>

#include "_redBlackTree.hpp"

#include "../commons/commons.hpp"
#include "../tools/tools.hpp"

namespace ft
{

	// template <class node_type, class value_compare>
	// bool	redBlackTree<node_type, value_compare>::_redBlackTree_violation_redRoot(node_type *node)
	// {
	// 	if
	// }

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_violation_redParent_redChild(node_type *newNode)
	{

		if ((newNode->_color == RED) && newNode->parent)
		{
			if (newNode->parent->_color == RED)
				return (true);
		}
		return (false);
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_fix(node_type *newNode)
	{
		// Check if violation
		bool previous_ok = false; // allows to skip scanning whole tree if 2 consecutive nodes are fine
		while (newNode)
		{
			if (this->_redBlackTree_violation_redParent_redChild(newNode) == true)
			{
				this->_redBlackTree_fix_rearrange(newNode);
				previous_ok = false;
			}
			else
			{
				if (previous_ok == true)
					return;
				previous_ok = true;
			}
			newNode = newNode->parent;
		}
	}
	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_fix_rearrange(node_type *node)
	{

		node_type *grandParent = this->_redBlackTree_getGrandParent(node);
		node_type *uncle = this->_redBlackTree_getUncle(node, grandParent);

		if (uncle)
		{
			// Recolor parent, grandparent and uncle:
			if (uncle->_color == RED) // Scenario 2: uncle is RED
			{
				node->parent->_color = BLACK;
				uncle->_color = BLACK;
				grandParent->_color = RED;

				return;
			}
		}
		// If Uncle is BLACK or NULL is the same
		if (this->_redBlackTree_triangleRelationship(node, grandParent)) // : rotation on parent
		{
			if (node->parent->left == node)
				this->_redBlackTree_rotate_right(node->parent); //
			else
				this->_redBlackTree_rotate_left(node->parent);
		}
		else
		{
			if (node->parent->left == node) // right direction
				this->_redBlackTree_rotate_right(grandParent);
			else // right direction
				this->_redBlackTree_rotate_left(grandParent);

			node->parent->_color = BLACK; // newNode->parent still points to the same since we rotate the grandParent
			grandParent->_color = RED;	  // grandParent still points to former grand parent
		}
	}
};