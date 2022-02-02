#pragma once

#include <iostream>
#include <string>

#include "node.hpp"
#include "pair.hpp"

namespace ft
{

	//
	// bool	_redBlackTree_violation_redRoot(node_type *node)
	// {
	// 	if
	// }

	bool _redBlackTree_violation_redParent_redChild(node_type *newNode)
	{

		if ((newNode->getColor() == RED) && newNode->parent)
		{
			if (newNode->parent->getColor() == RED)
				return (true);
		}
		return (false);
	}

	void _redBlackTree_fix(node_type *newNode)
	{
		// Check if violation
		node_type *node_check = newNode;
		node_type *former_parent = newNode->parent;
		while (node_check)
		{
			// _redBlackTree_debug_printDotTree();

			former_parent = node_check->parent;
			if (this->_redBlackTree_violation_redParent_redChild(node_check) == true)
				this->_redBlackTree_fix_rearrange(node_check);

			node_check = former_parent;
		}
	}

	void _redBlackTree_fix_rearrange(node_type *node)
	{

		node_type *grandParent = this->_redBlackTree_getGrandParent(node);
		node_type *uncle = this->_redBlackTree_getUncle(node, grandParent);

		if (uncle)
		{
			// Recolor parent, grandparent and uncle:
			if (uncle->getColor() == RED) // Scenario 2: uncle is RED
			{
				node->parent->setColor(BLACK);
				uncle->setColor(BLACK);
				grandParent->setColor(RED);

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

			node->parent->setColor(BLACK); // newNode->parent still points to the same since we rotate the grandParent
			grandParent->setColor(RED);	   // grandParent still points to former grand parent
		}
	}
};