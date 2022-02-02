
#pragma once

#include <iostream>
#include <string>

#include "node.hpp"
#include "pair.hpp"

/*	RED BLACK TREE RULES
 * 	Every node has a colour either red or black.
 *
 *		- The root of the tree is always black.
 *		- There are no two adjacent red nodes (A red node cannot have a red parent or red child).
 *		- Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
 *		- All leaf nodes are black nodes.
 *
 */

namespace ft
{

	bool _redBlackTree_markDoubleBlack(node_type *v_deleted, node_type *u_replacer)
	{
		// Case 1: either V or U is red
		if (_redBlackTree_oneRed(v_deleted, u_replacer))
		{
			// mark childen as black
			if (u_replacer)
				u_replacer->setColor(BLACK);
			return (false);
		}
		else
		{
			// mark u as double black
			if (u_replacer == this->_root) // no problem in this case
			{
				return (false);
			}
			else
			{
				return (true);
			}
		}
	}

	void _redBlackTree_simpleRemove_bothParent(node_type *node)
	{
		// We can either use predecessor or [successor]
		node_type *tmp(_redBlackTree_inOrderSuccessor(node));
		node->data = tmp->data;
		// ??? Do we need to also assign color: node->setColor(tmp->getColor());
		_redBlackTree_simpleRemove(tmp);
		return;
	}

	void _redBlackTree_simpleRemove_singleParent(node_type *node)
	{
		bool doubleBlack;
		bool parentRelationship = RIGHT;
		node_type *tmp;

		// Checkign which side has a child
		if (node->left)
			tmp = node->left;
		else
			tmp = node->right;
		doubleBlack = _redBlackTree_markDoubleBlack(node, tmp);
		node->data = tmp->data;
		this->_redBlackTree_copyNode(node, tmp, false); // copy, so no need to reassign pointers of sister nodes
		if (doubleBlack)
		{
			if (node->parent)
			{
				if (node->parent->left == node)
					parentRelationship = LEFT;
				else
					parentRelationship = RIGHT;
			}
			_redBlackTree_fixDoubleBlack(node, node->parent, parentRelationship);
		}
		else
			node->setColor(BLACK);
		delete tmp;
	}

	void _redBlackTree_simpleRemove_leaf(node_type *node)
	{
		bool doubleBlack = false;
		bool parentRelationship;
		node_type *parent = node->parent;

		if (!parent)
		{
			_root = NULL; // Remove root as leaf: no problem.
			delete node;
			return;
		}
		// Checking if double black will be created
		if (node)
		{
			if (node->getColor() == BLACK)
			{
				doubleBlack = true;
			}
		}
		// Fixing Parent relationship
		if (parent->left == node)
		{
			parent->left = NULL;
			parentRelationship = LEFT;
		}
		else
		{
			parent->right = NULL;
			parentRelationship = RIGHT;
		}
		if (doubleBlack)
		{
			_redBlackTree_fixDoubleBlack(node, parent, parentRelationship);
		}
		delete node;
	}

	void _redBlackTree_simpleRemove(node_type *node)
	{
		if (_redBlackTree_isLeaf(node)) // Case 1 : node deleted is a leaf, even if its the last element (and node->right points to _ghost_node)
			_redBlackTree_simpleRemove_leaf(node);
		else if (this->_redBlackTree_hasOnlyOneChild(node)) // Case 2 : Node to be deleted has only one child
			_redBlackTree_simpleRemove_singleParent(node);
		else if (this->_redBlackTree_hasBothChild(node)) // Case 3 : 2 children
			_redBlackTree_simpleRemove_bothParent(node);
	}

	void _redBlackTree_erase(node_type *node)
	{
		_redBlackTree_detachGhost(); // detach ghost node so we don't have to deal with it :)
		_redBlackTree_simpleRemove(node);
		this->_size--;
		_redBlackTree_reassignGhost();
		// _redBlackTree_debug_printDotTree("ERASE");
	}
};