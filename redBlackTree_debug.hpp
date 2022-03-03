#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "_redBlackTree.hpp"

#include "../commons/commons.hpp"
#include "../tools/tools.hpp"

#define DEBUG_MODE false

namespace ft
{
	template <class node_type, class value_compare>
	std::string redBlackTree<node_type, value_compare>::_redBlackTree_debug_printDotNode(node_type *node)
	{
		std::stringstream sstream;

		if (node == this->_ghost_node)
		{
			return ("_end");
		}
		else
		{
			sstream
				<< "\"["
				<< node->data.first
				<< "]"
				<< "["
				<< node->data.second
				<< "]\"";
		}
		return (sstream.str());
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_debug_printDotTree(const std::string &str)
	{
		std::stringstream filename;
		filename << "tree_output/tree_" << str << "_" << this->_size << ".dot";

		std::ofstream output_file(filename.str());

		// Style Declaration
		std::string style_root_link = "[ color = green ]";
		std::string style_root = "[ shape = house ]";
		std::string style_end = "[ color = grey, fontcolor = grey]";

		std::string style_node_black = "[ fontcolor=white fillcolor=black  style=filled]";
		std::string style_node_red = "[ fontcolor=red1, fillcolor=firebrick4, style=filled ]";
		std::string style_node_parent_link = "[ style=dashed, color=grey ]";

		std::string style_null_link = "[ shape=plaintext label = \"NULL\" fontcolor=slategray4 ]";

		std::string warning_node = "[ fillcolor=darkolivegreen color=red style=filled ]";

		// Diagram first line
		output_file << "digraph graphname {" << std::endl;
		output_file << "label = "
					<< "\"" << str << "_" << this->_size << "\"" << std::endl;

		// Root
		output_file << "_root" << style_root << std::endl;
		output_file << "_root ->" << _redBlackTree_debug_printDotNode(this->_root) << style_root_link << std::endl;

		// Nodes
		node_type *current_node;
		std::stringstream sstream;
		std::string newNull_1 = "";
		std::string newNull_2 = "";

		iterator begin = this->begin();
		iterator end = this->end();

		while (begin != end)
		{
			current_node = begin.node_ptr();

			// Print node + style
			output_file << _redBlackTree_debug_printDotNode(current_node) << "								";
			if (current_node->_color == RED)
				output_file << style_node_red << std::endl;
			else
				output_file << style_node_black << std::endl;

			// Print node links
			output_file << _redBlackTree_debug_printDotNode(current_node) << "		->	{";
			if (current_node->left)
				output_file << _redBlackTree_debug_printDotNode(current_node->left);
			else
			{
				sstream << "\"NULL_" << current_node->data.first << "_left\"";
				newNull_1 = sstream.str();
				output_file << newNull_1;
				sstream.str("");
			}
			output_file << ", ";

			if (current_node->right)
				output_file << _redBlackTree_debug_printDotNode(current_node->right);
			else
			{
				sstream << "\"NULL_" << current_node->data.first << "_right\"";
				newNull_2 = sstream.str();
				output_file << newNull_2;
				sstream.str("");
			}
			output_file << "}";
			output_file << std::endl;

			// Styling NULLS if created
			if (newNull_1 != "")
				output_file << newNull_1 << style_null_link << std::endl;
			if (newNull_2 != "")
				output_file << newNull_2 << style_null_link << std::endl;
			output_file << std::endl;
			newNull_1 = "";
			newNull_2 = "";

			// Print parent link
			if (current_node->parent)
			{
				output_file << _redBlackTree_debug_printDotNode(current_node) << " -> " << _redBlackTree_debug_printDotNode(current_node->parent) << style_node_parent_link << std::endl;
			}
			else if (current_node != _root)
			{
				output_file << _redBlackTree_debug_printDotNode(current_node) << "								";
				std::cout << "WARNING: no parent for node: " << _redBlackTree_debug_printDotNode(current_node) << std::endl;
			}
			begin++;
		}

		// Print end node

		// Ghost node && end
		output_file << "_ghost_node" << style_root << std::endl;
		output_file << "_end" << style_end << std::endl;
		output_file << "_ghost_node	->	_end" << style_root_link << std::endl;

		// Diagram last line
		output_file << "}" << std::endl;

		// Close
		output_file.close();
		return;
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_debug_printNodeData(node_type *node)
	{
		if (DEBUG_MODE)
		{
			if (!node)
			{
				std::cout << "(NULL)";
				return;
			}
			if (node == this->_ghost_node)
			{
				std::cout << "👻 ";
				return;
			}
			else
				std::cout << "[ " << node->data.first << " ][ " << node->data.second << " ]";
		}
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_debug_printNode(node_type *node)
	{
		if (DEBUG_MODE)
		{
			std::cout
				<< "*****************" << std::endl
				<< "* NODE: ";
			_redBlackTree_debug_printNodeData(node);
			std::cout
				<< std::endl
				<< "*---------------" << std::endl;
			if (node)
			{
				if (node->_color == RED)
					std::cout << "* Color: "
							  << " RED" << std::endl;
				else
					std::cout << "* Color: "
							  << " BLACK" << std::endl;

				std::cout << "* Left: ";
				if (node->left)
					_redBlackTree_debug_printNodeData(node->left);
				else
					std::cout << "NULL";
				std::cout << std::endl;

				std::cout << "* Right: ";
				if (node->right)
					_redBlackTree_debug_printNodeData(node->right);
				else
					std::cout << "NULL";
				std::cout << std::endl;

				std::cout << "* Parent: ";
				if (node->parent)
					_redBlackTree_debug_printNodeData(node->parent);
				else
					std::cout << "NULL";
				std::cout << std::endl;
				std::cout
					<< "*****************" << std::endl;
			}
		}
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_debug_printTree(void)
	{
		if (DEBUG_MODE)
		{
			std::cout << "____________________" << std::endl;
			std::cout << "| PRINTING ALL NODE!" << std::endl;
			std::cout << "| _size: " << this->_size << std::endl;
			std::cout << "| _root: ";
			_redBlackTree_debug_printNodeData(this->_root);
			std::cout << std::endl;
			std::cout << "––––––––––––––––––––" << std::endl;

			iterator begin = this->begin();
			iterator end = this->end();

			while (begin != end)
			{
				_redBlackTree_debug_printNode(begin.node_ptr());
				std::cout << std::endl;
				begin++;
			}
			std::cout << "––––––––––––––––––––" << std::endl;
			std::cout << "| END" << std::endl;
			std::cout << "____________________" << std::endl;
		}
	}

	template <class node_type, class value_compare>
	void redBlackTree<node_type, value_compare>::_redBlackTree_debug_message(const std::string &str) const
	{
		if (DEBUG_MODE)
			std::cout << "DEBUG: " << str << std::endl;
	}
};