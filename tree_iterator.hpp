#pragma once

#include <iostream>
#include <string>

#include "../commons/commons.hpp"

#include "iterator_traits.hpp"
#include "iterator_categories.hpp"

namespace ft
{

	template <typename type_ite, typename node_type>
	class tree_iterator
	{
	private:
		typedef typename ft::iterator_traits<type_ite *> _iterator_traits;

	protected:			 // making value accessible by subclasses
		node_type *node; // pointer to node
						 // Pointer to right value type;

		/***************************************************************
		 *	Typedefs:
		 *	Iterator typedefs are inherited from iterator_traits
		 */

	public:
		typedef typename _iterator_traits::value_type value_type;
		typedef typename _iterator_traits::difference_type difference_type;
		typedef typename _iterator_traits::pointer pointer;
		typedef typename _iterator_traits::reference reference;
		typedef typename _iterator_traits::reference const &const_reference;
		typedef ft::bidirectional_iterator_tag iterator_category;

		/***************************************************************
		 *	Constructors:
		 */
		tree_iterator(void) : node(NULL)
		{
			return;
		}; // Default Constructor.

		tree_iterator(const tree_iterator &src) { *this = src; }; // Copy Constructor. Making sure the iterator is working on the same datatype

		tree_iterator(node_type *src_node) : node(src_node){}; // Copy Constructor using node ptr

	public:
		/***************************************************************
		 *	Destructor:
		 */
		virtual ~tree_iterator(){}; // Virtual for inheritance

		/***************************************************************
		 *	Assignment operator overload:
		 */

		tree_iterator &operator=(const tree_iterator &rhs)
		{
			if (this != &rhs)
				this->node = rhs.node;
			return (*this);
		};

		/***************************************************************
		 *	Capacity:
		 */
		node_type *node_ptr(void) const { return (this->node); }

		/***************************************************************
		 *	Arithmetic operators:
		 */
		// Increment / Decrement
		// ++ and -- can be before AND after iterator:
		tree_iterator<type_ite, node_type> &operator++(void)
		{ // ++ before
			if (this->node->right != NULL)
			{
				this->node = min_node(this->node->right);
			}
			else
			{
				node_type *tmp = this->node;

				this->node = this->node->parent;
				while (this->node != NULL && tmp == this->node->right) // should segfault if done on last element!!
				{
					tmp = this->node;
					this->node = this->node->parent;
				}
			}
			return (*this);
		};

		tree_iterator<type_ite, node_type> operator++(int)
		{ // ++ after
			tree_iterator<type_ite, node_type> tmp(*this);
			++(*this);
			return (tmp);
		};

		tree_iterator<type_ite, node_type> &operator--(void)
		{ // -- before
			if (this->node->left != NULL)
				this->node = max_node(this->node->left);
			else
			{
				node_type *tmp = this->node;
				this->node = this->node->parent;
				while (this->node != NULL && tmp == this->node->left) // should segfault if done on last element!!
				{
					tmp = this->node;
					this->node = this->node->parent;
				}
			}
			return (*this);
		};
		tree_iterator<type_ite, node_type> operator--(int)
		{ // -- after
			tree_iterator<type_ite, node_type> tmp(*this);
			--(*this);
			return (tmp);
		};

		/*******************************
		 *	Accessors:
		 */

		reference operator*() const { return (this->node->data); };
		pointer operator->() const { return (&this->node->data); };

		/***************************************************************
		 * 	Relational operators :
		 */
		bool operator==(const tree_iterator &rhs) const { return (this->node == rhs.node); };
		bool operator!=(const tree_iterator &rhs) const { return (this->node != rhs.node); };

		/***************************************************************
		 * 	Const cast
		 */
		operator tree_iterator<const type_ite, node_type>(void) const { return tree_iterator<const type_ite, node_type>(this->node); };
	};

};
