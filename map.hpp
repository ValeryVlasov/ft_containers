#ifndef FT_MAP_HPP_
#define FT_MAP_HPP_

#include "utility.hpp"
#include "pair.hpp"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>,
	        class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef typename ft::pair<const Key, T>						value_type;
		typedef unsigned long										size_type;
		typedef ptrdiff_t											difference_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef value_type&											reference;
		typedef typename Alloc::pointer								pointer;
		typedef typename Alloc::const_pointer						const_pointer;
		typedef ft::bidirectional_iterator_tag						iterator;
		typedef ft::bidirectional_iterator_tag						const_iterator;
		typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	private:

	public:


	};

}//ft

#endif