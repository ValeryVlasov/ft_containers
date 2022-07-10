#ifndef RED_BLACK_TREE_HPP_
#define RED_BLACK_TREE_HPP_

#include <memory>
#include <utility>
#include <iostream>

#include "pair.hpp"
#include "utility.hpp"

template< class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RedBlackTree;

/*********************		NODE		***********************/

namespace ft {
	enum Color {
		RED,
		BLACK
	};

	template < class T >
	struct Node {
		Node() : key(T()), color(RED), parent(NULL), left(NULL), right(NULL) {}
		Node(const T& k) : key(k), color(RED), parent(NULL), left(NULL), right(NULL) {}
		Node(const Node& another)
			: key(another.key), color(another.color), parent(another.parent),
			left(another.left), right(another.right) {}
		Node(const T &k, Color c, Node *p, Node *l, Node *r)
			: key(k), color(c), parent(p), left(l), right(r) {}

		Node& operator=(const Node& another){
			key = another.key;
			color = another.color;
			left = another.left;
			right = another.right;
			parent = another.parent;

			return *this;
		}


		T key;
		Color color;
		Node<T> *left;
		Node<T> *right;
		Node<T> *parent;
	};
}

/*********************		NODE		***********************/

/*********************				***********************/



/*********************				***********************/


#endif