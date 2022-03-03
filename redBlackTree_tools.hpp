#pragma once

#include <iostream>
#include <string>

#include "_redBlackTree.hpp"

#include "../commons/commons.hpp"
#include "../tools/tools.hpp"

#include "../redBlackTree/_redBlackTree.hpp"

namespace ft
{

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_checkLastNode(node_type *node)
	{
		if (!this->_comp(node->data, this->_ghost_node->parent->data)) // Comparing pair(for map) or key for Set
			return (true);
		return (false);
	}

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_relationshipFinder(node_type *parent, node_type *child)
	{
		if (parent->left == child)
		{
			return (LEFT);
		}
		else
		{
			return (RIGHT);
		}
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_replaceNode(node_type *replacer, node_type *node, bool keep_color)
	{

		// Checking nodes are not linked.
		bool linked_nodes = false;
		if (node->left == replacer || node->right == replacer)
			linked_nodes = true;

		node_type *node_parent = node->parent;
		node_type *node_left = node->left;
		node_type *node_right = node->right;
		bool node_color = node->_color;
		bool node_relationship = LEFT;
		if (node_parent)
			node_relationship = _redBlackTree_relationshipFinder(node_parent, node);

		node_type *replacer_parent = replacer->parent;
		node_type *replacer_left = replacer->left;
		node_type *replacer_right = replacer->right;
		bool replacer_color = replacer->_color;
		bool replacer_relationship = LEFT;
		if (replacer_parent)
			replacer_relationship = _redBlackTree_relationshipFinder(replacer_parent, replacer);

		if (node_parent)
		{
			if (node_relationship == LEFT)
				node_parent->left = replacer;
			else
				node_parent->right = replacer;
		}
		else
			_root = replacer;
		replacer->parent = node->parent;

		if (linked_nodes)
		{
			if (replacer_relationship == LEFT)
			{
				replacer->left = node;
				node->parent = replacer;
				replacer->right = node_right;
				if (node_right)
					node_right->parent = replacer;
			}
			else
			{
				replacer->right = node;
				node->parent = replacer;
				replacer->left = node_left;
				if (node_left)
					node_left->parent = replacer;
			}
		}
		else
		{
			replacer->right = node_right;
			node_right->parent = replacer;
			replacer->left = node_left;
			node_left->parent = replacer;
			node->parent = replacer_parent;
			if (replacer_parent)
			{
				if (replacer_relationship == LEFT)
					replacer_parent->left = node;
				else
					replacer_parent->right = node;
			}
		}

		// Set node childrens
		node->left = replacer_left;
		node->right = replacer_right;

		// Set node childrens->parent
		if (node->left)
		{
			node->left->parent = node;
		}
		if (node->right)
		{
			node->right->parent = node;
		}

		// Set Color
		if (keep_color)
			node->_color = replacer_color;
		if (keep_color)
			replacer->_color = node_color;
	}

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_whichRedChild(node_type *parent)
	{
		// Only Call if sure that theres a red child!
		if (parent->left)
		{
			if (parent->left->_color == RED)
				return (LEFT);
		}
		return (RIGHT);
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_detachGhost(void)
	{
		node_type *last_node = this->_ghost_node->parent;

		last_node->right = NULL;
		this->_ghost_node->parent = NULL;
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_reassignGhost(void)
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

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_oneRed(node_type *node_a, node_type *node_b)
	{

		if (node_a)
			if (node_a->_color == RED)
				return (true);
		if (node_b)
			if (node_b->_color == RED)
				return (true);
		return (false);
	}

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_bothBlack(node_type *node_a, node_type *node_b)
	{
		return (!_redBlackTree_oneRed(node_a, node_b));
	}

	template <class node_type, class value_compare>
	node_type *redBlackTree<node_type, value_compare>::_redBlackTree_inOrderPredecessor(node_type *node)
	{
		return (max_node(node->left));
	}

	template <class node_type, class value_compare>
	node_type *redBlackTree<node_type, value_compare>::_redBlackTree_inOrderSuccessor(node_type *node)
	{
		return (min_node(node->right));
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_copyNode(node_type *node_1, node_type *node_2, bool copy_parent)
	{
		node_1->data = node_2->data;

		node_1->left = node_2->left;
		node_1->right = node_2->right;
		if (copy_parent)
			node_1->parent = node_2->parent;

		node_1->_color = node_2->_color;
	}

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_hasBothChild(node_type *node)
	{
		if (node->left && node->right)
			return (true);
		return (false);
	}

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_hasOnlyOneChild(node_type *node)
	{
		if (!node->left && node->right)
			return (true);
		if (node->left && (!node->right || (node->right == this->_ghost_node)))
			return (true);
		return (false);
	}
	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_isLeaf(node_type *node)
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
	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_rotate_left(node_type *node)
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
	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_rotate_right(node_type *node)
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

	template <class node_type, class value_compare>
	node_type *redBlackTree<node_type, value_compare>::_redBlackTree_getGrandParent(node_type *newNode)
	{
		if (newNode->parent == NULL) // Check node has a parent
			return (NULL);
		if (newNode->parent->parent == NULL) // Check node has a grandparent
			return (NULL);
		return (newNode->parent->parent);
	}

	template <class node_type, class value_compare>
	bool redBlackTree<node_type, value_compare>::_redBlackTree_triangleRelationship(node_type *newNode, node_type *grandParent)
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

	template <class node_type, class value_compare>
	node_type *redBlackTree<node_type, value_compare>::_redBlackTree_getUncle(node_type *newNode, node_type *grandParentNode)
	{
		if (grandParentNode)
		{
			if (grandParentNode->left == newNode->parent)
				return (grandParentNode->right);
			return (grandParentNode->left);
		}
		return (NULL);
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_clear(node_type *node)
	{
		// Recursive clear of right/left nodes
		if (node != NULL)
		{
			this->_redBlackTree_clear(node->left);
			if (node->right != this->_ghost_node)
				this->_redBlackTree_clear(node->right);

			delete node;
		}
	}
	template <class node_type, class value_compare>
	typename redBlackTree<node_type, value_compare>::iterator redBlackTree<node_type, value_compare>::lower_bound(node_type *k)
	{
		iterator ite = this->begin();
		iterator end = this->end();

		while (ite != end)
		{
			if (!this->_comp(ite.node_ptr()->data, k->data))
				break;
			ite++;
		}
		return (ite);
	}

	template <class node_type, class value_compare>
	typename redBlackTree<node_type, value_compare>::iterator redBlackTree<node_type, value_compare>::upper_bound(node_type *k)
	{
		iterator ite = this->begin();
		iterator end = this->end();

		while (ite != end)
		{
			if (this->_comp(k->data, ite.node_ptr()->data))
				break;
			ite++;
		}
		return (ite);
	}

};