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

	void _redBlackTree_fixDoubleBlack(node_type *u_doubleBlack, node_type *doubleBlackParent, bool parentRelationship)
	{
		/***********
		 *	3 cases:
		 *	- If sibling s is black and at least one of sibling’s children is red.
		 *	- If sibling is black and its both children are black.
		 *	- If sibling is red.
		 */
		node_type *sibling = NULL;
		bool siblingColor = BLACK;
		bool oneSiblingChildrenIsRed = false;
		bool redSiblingSide = LEFT;

		if (doubleBlackParent)
		{
			if (parentRelationship == LEFT)
			{
				if (doubleBlackParent->right)
				{
					sibling = doubleBlackParent->right;
					siblingColor = doubleBlackParent->right->getColor();
					if (_redBlackTree_oneRed(doubleBlackParent->right->left, doubleBlackParent->right->right))
					{
						oneSiblingChildrenIsRed = true;
						redSiblingSide = _redBlackTree_whichRedChild(doubleBlackParent->right);
					}
				}
			}
			else
			{
				if (doubleBlackParent->left)
				{
					sibling = doubleBlackParent->left;
					siblingColor = doubleBlackParent->left->getColor();
					if (_redBlackTree_oneRed(doubleBlackParent->left->left, doubleBlackParent->left->right))
					{
						oneSiblingChildrenIsRed = true;
						redSiblingSide = _redBlackTree_whichRedChild(doubleBlackParent->left);
					}
				}
			}
		}
		if (this->_root == u_doubleBlack)
		{
			u_doubleBlack->setColor(BLACK); // Black height of complete tree reduces by 1
			return;
		}
		else if (siblingColor == BLACK && oneSiblingChildrenIsRed == true)
		{
			// Left Left Case
			if (parentRelationship != LEFT && redSiblingSide == LEFT)
			{
				sibling->setColor(doubleBlackParent->getColor());
				doubleBlackParent->setColor(BLACK);
				_redBlackTree_rotate_right(doubleBlackParent);
				sibling->left->setColor(BLACK);
			}

			// Left Right Case
			if (parentRelationship != LEFT && redSiblingSide == RIGHT)
			{
				_redBlackTree_rotate_left(sibling);
				_redBlackTree_rotate_right(doubleBlackParent);
				sibling->setColor(BLACK);
				sibling->parent->setColor(BLACK);
			}

			// Right Right Case
			if (parentRelationship != RIGHT && redSiblingSide == RIGHT)
			{
				sibling->setColor(doubleBlackParent->getColor());
				doubleBlackParent->setColor(BLACK);
				_redBlackTree_rotate_left(doubleBlackParent);
				sibling->right->setColor(BLACK);
			}

			// Right Left Case
			if (parentRelationship != RIGHT && redSiblingSide == LEFT)
			{
				_redBlackTree_rotate_right(sibling);
				_redBlackTree_rotate_left(doubleBlackParent);
				sibling->setColor(BLACK);
				sibling->parent->setColor(BLACK);
			}
		}
		else if (siblingColor == BLACK && oneSiblingChildrenIsRed == false)
		{
			sibling->setColor(RED);
			if (doubleBlackParent->getColor() == RED)
			{
				doubleBlackParent->setColor(BLACK);
				return;
			}

			bool parentGrandParentRelationship;
			if (doubleBlackParent->parent)
			{
				if (doubleBlackParent->parent->left == doubleBlackParent)
					parentGrandParentRelationship = LEFT;
			}
			else
				parentGrandParentRelationship = RIGHT;

			if (doubleBlackParent->getColor() == BLACK)
				_redBlackTree_fixDoubleBlack(doubleBlackParent, doubleBlackParent->parent, parentGrandParentRelationship);
		}
		else if (siblingColor == RED)
		{
			// Left Case
			if (parentRelationship != LEFT)
			{
				_redBlackTree_rotate_right(doubleBlackParent);
				sibling->setColor(BLACK);
				doubleBlackParent->setColor(RED);
				_redBlackTree_fixDoubleBlack(u_doubleBlack, doubleBlackParent, RIGHT);
			}
			if (parentRelationship != RIGHT)
			{
				_redBlackTree_rotate_left(doubleBlackParent);
				sibling->setColor(BLACK);
				doubleBlackParent->setColor(RED);
				_redBlackTree_fixDoubleBlack(u_doubleBlack, doubleBlackParent, LEFT);
			}
		}
	}
};