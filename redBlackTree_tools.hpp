#pragma once

#include <iostream>
#include <string>

#include "node.hpp"
#include "pair.hpp"

namespace ft
{

	bool _redBlackTree_relationshipFinder(node_type *parent, node_type *child)
	{
		if (parent->left == child)
			return (LEFT);
		else
			return (RIGHT);
	}

	void _redBlackTree_replaceNode(node_type *replacer, node_type *node, bool keep_color)
	{
		node_type tmp(*replacer);

		if (keep_color)
			replacer->setColor(node->getColor());

		// parent assignment
		if (node->parent)
		{
			if (_redBlackTree_relationshipFinder(node->parent, node) == LEFT)
				node->parent->left = replacer;
			else
				node->parent->right = replacer;
			replacer->parent = node->parent;
		}
		else
		{
			replacer->parent = NULL;
			this->_root = replacer;
		}
		if (tmp.parent)
		{
			if (_redBlackTree_relationshipFinder(tmp.parent, &tmp) == LEFT)
				tmp.parent->left = replacer;
			else
				tmp.parent->right = replacer;
			node->parent = tmp.parent;
		}

		// children assignment assignment
		if (node->left)
		{
			replacer->left = node->left;
			replacer->left->parent = replacer;
		}
		if (node->right)
		{
			replacer->right = node->right;
			replacer->right->parent = replacer;
		}

		if (tmp.left)
		{
			node->left = tmp.left;
			node->left->parent = node;
		}
		if (tmp.right)
		{
			node->right = node->right;
			node->right->parent = node;
		}
	}

	bool _redBlackTree_whichRedChild(node_type *parent)
	{
		// Only Call if sure that theres a red child!
		if (parent->left)
		{
			if (parent->left->getColor() == RED)
				return (LEFT);
		}
		return (RIGHT);
	}

	void _redBlackTree_detachGhost(void)
	{
		node_type *last_node = this->_ghost_node->parent;

		last_node->right = NULL;
		this->_ghost_node->parent = NULL;
	}

	void _redBlackTree_reassignGhost(void)
	{
		if (this->_size == 0)
		{
			// If Tree is now empty
			this->_root = this->_ghost_node;
			this->_ghost_node->parent = NULL;
			return;
		}
		node_type *last_node = max_node(this->_root);
		last_node->right = this->_ghost_node;
		this->_ghost_node->parent = last_node;
	}

	bool _redBlackTree_oneRed(node_type *node_a, node_type *node_b)
	{

		if (node_a)
			if (node_a->getColor() == RED)
				return (true);
		if (node_b)
			if (node_b->getColor() == RED)
				return (true);
		return (false);
	}

	bool _redBlackTree_bothBlack(node_type *node_a, node_type *node_b)
	{
		return (!_redBlackTree_oneRed(node_a, node_b));
	}

	node_type *_redBlackTree_inOrderPredecessor(node_type *node)
	{
		return (max_node(node->left));
	}

	node_type *_redBlackTree_inOrderSuccessor(node_type *node)
	{
		return (min_node(node->right));
	}

	void _redBlackTree_copyNode(node_type *node_1, node_type *node_2, bool copy_parent)
	{
		node_1->data = node_2->data;

		node_1->left = node_2->left;
		node_1->right = node_2->right;
		if (copy_parent)
			node_1->parent = node_2->parent;

		node_1->setColor(node_2->getColor());
	}

	bool _redBlackTree_hasBothChild(node_type *node)
	{
		if (node->left && node->right)
			return (true);
		return (false);
	}

	bool _redBlackTree_hasOnlyOneChild(node_type *node)
	{
		if (!node->left && node->right)
			return (true);
		if (node->left && (!node->right || (node->right == this->_ghost_node)))
			return (true);
		return (false);
	}

	bool _redBlackTree_isLeaf(node_type *node)
	{
		if (!node->left && (!node->right || node->right == this->_ghost_node))
			return (true);
		return (false);
	}
	// ROTATIONS
	// Need to check before using if possible.

	// Left-rotate:
	// 		- the rightChild of Node becomes its parent,
	// 		- the rLeftChild of right-child becomes Node's right-child

	void _redBlackTree_rotate_left(node_type *node)
	{
		node_type *nodeParent = node->parent; // NULL if root

		node_type *rightChild = node->right;
		node_type *rLeftChild = node->right->left;

		// Reassign rightChild-node parent relationship
		if (nodeParent == NULL) // case of rotation at root
		{
			this->_root = rightChild;
			rightChild->parent = NULL;
		}
		else
		{
			if (nodeParent->left == node)
				nodeParent->left = rightChild;
			else
				nodeParent->right = rightChild;
			rightChild->parent = nodeParent;
		}
		rightChild->left = node;
		// Reassign rotated-node parent relationship
		node->parent = rightChild;
		node->right = rLeftChild;
		if (rLeftChild)
			rLeftChild->parent = node;
	}

	// Right-rotate:
	// 		- the leftChild of Node becomes its parent,
	// 		- the lRightChild of left-child becomes Node's left-child

	void _redBlackTree_rotate_right(node_type *node)
	{
		node_type *nodeParent = node->parent; // NULL if root

		node_type *leftChild = node->left;
		node_type *lRightChild = node->left->right;

		// Reassign rightChild-node parent relationship
		if (nodeParent == NULL) // case of rotation at root
		{
			this->_root = leftChild;
			leftChild->parent = NULL;
		}
		else
		{
			if (nodeParent->left == node)
				nodeParent->left = leftChild;
			else
				nodeParent->right = leftChild;
			leftChild->parent = nodeParent;
		}
		leftChild->right = node;
		// Reassign rotated-node parent relationship
		node->parent = leftChild;
		node->left = lRightChild;
		if (lRightChild)
			lRightChild->parent = node;
	}

	node_type *_redBlackTree_getGrandParent(node_type *newNode)
	{
		if (newNode->parent == NULL) // Check node has a parent
			return (NULL);
		if (newNode->parent->parent == NULL) // Check node has a grandparent
			return (NULL);
		return (newNode->parent->parent);
	}

	bool _redBlackTree_triangleRelationship(node_type *newNode, node_type *grandParent)
	{
		// making sure grandparent exits???
		if (newNode->parent->left == newNode)
		{

			if (grandParent->right == newNode->parent)
				return (true);
			return (false);
		}
		else
		{
			if (grandParent->left == newNode->parent)
			{
				return (true);
			}
			return (false);
		}
	}

	node_type *_redBlackTree_getUncle(node_type *newNode, node_type *grandParentNode)
	{
		if (grandParentNode)
		{
			if (grandParentNode->left == newNode->parent)
				return (grandParentNode->right);
			return (grandParentNode->left);
		}
		return (NULL);
	}

	void _redBlackTree_clear(node_type *node)
	{
		if (node != NULL)
		{
			this->_redBlackTree_clear(node->left);
			if (node->right != this->_ghost_node)
				this->_redBlackTree_clear(node->right);
			delete node;
		}
	}
};