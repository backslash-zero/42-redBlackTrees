#pragma once

#include <iostream>
#include <string>
#include <cstddef> //	ptrdiff_t
#include <memory>  // Alloc

// Iterators:
#include "../iterators/tree_iterator.hpp"

// Commons
#include "../commons/commons.hpp"

namespace ft
{
	template <class node_type, class value_compare>
	class redBlackTree
	{

	public:
		// Constuctors
		redBlackTree(void);
		virtual ~redBlackTree(void);

		// Iterator
		typedef ft::tree_iterator<typename node_type::value_type, node_type> iterator;

		// Members
		node_type *_root;
		node_type *_ghost_node;
		size_t _size;
		value_compare _comp;

		// Main functions
		node_type *redBlackTree_add(node_type *newNode);
		void redBlackTree_erase(node_type *newNode);

		// Tool
		void _redBlackTree_clear(node_type *node);

	private:
		// Rotations
		void _redBlackTree_rotate_left(node_type *newNode);
		void _redBlackTree_rotate_right(node_type *newNode);

		// Insertions
		void _redBlackTree_simpleInsert(node_type *newNode);
		void _redBlackTree_rootInsert(node_type *newNode);
		void _redBlackTree_LastElementInsert(node_type *newNode);

		// Deletions
		void _redBlackTree_simpleRemove(node_type *node);
		void _redBlackTree_simpleRemove_leaf(node_type *node);
		void _redBlackTree_simpleRemove_singleParent(node_type *node);
		void _redBlackTree_simpleRemove_bothParent(node_type *node);
		void _redBlackTree_fixDoubleBlack(node_type *u_doubleBlack, node_type *doubleBlackParent, bool parentRelationship);

		// Fixing tree
		void _redBlackTree_fix(node_type *newNode);
		bool _redBlackTree_violation_redParent_redChild(node_type *newNode);
		void _redBlackTree_fix_rearrange(node_type *newNode);

		// Tools
		node_type *_redBlackTree_getGrandParent(node_type *newNode);
		node_type *_redBlackTree_getUncle(node_type *newNode, node_type *grandParent);
		bool _redBlackTree_triangleRelationship(node_type *newNode, node_type *grandParent);
		bool _redBlackTree_isLeaf(node_type *node);
		bool _redBlackTree_hasOnlyOneChild(node_type *node);
		bool _redBlackTree_hasBothChild(node_type *node);
		void _redBlackTree_copyNode(node_type *node_1, node_type *node_2, bool copy_parent);
		node_type *_redBlackTree_inOrderSuccessor(node_type *node);
		node_type *_redBlackTree_inOrderPredecessor(node_type *node);
		bool _redBlackTree_bothBlack(node_type *node_a, node_type *node_b);
		bool _redBlackTree_oneRed(node_type *node_a, node_type *node_b);
		bool _redBlackTree_whichRedChild(node_type *parent);
		bool _redBlackTree_markDoubleBlack(node_type *v_deleted, node_type *u_replacer);
		void _redBlackTree_detachGhost(void);
		void _redBlackTree_reassignGhost(void);
		void _redBlackTree_replaceNode(node_type *replacer, node_type *node, bool keep_color);
		bool _redBlackTree_relationshipFinder(node_type *parent, node_type *child);
		bool _redBlackTree_checkLastNode(node_type *node);

		iterator lower_bound(node_type *k);
		iterator upper_bound(node_type *k);

		iterator begin(void);
		iterator end(void);

		// Debug
		// void _redBlackTree_debug_printNodeData(node_type *node);
		// void _redBlackTree_debug_printNode(node_type *node);
		// void _redBlackTree_debug_printTree(void);
		// void _redBlackTree_debug_message(const std::string &str) const;
		// std::string _redBlackTree_debug_printDotNode(node_type *node);
		// void _redBlackTree_debug_printDotTree(const std::string &str);
	};
}