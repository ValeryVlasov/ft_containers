#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP

#include <vector>
#include <iterator>

namespace ft {

	template < class T, class Allocator >
	class ft_iterator
	{
	protected:

	private:
		typedef T value_type;
		typedef typename Allocator::reference Reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::difference_type difference_type;
		typedef random_access_iterator_tag
	public:

	};

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	protected:

	private:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
	public:

	};

	template < class T, class A >
	bool operator==(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return !( lhs == rhs );
	}
	template < class T, class A >
	bool operator!=(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return ( lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()) );
	}
	template < class T, class A >
	bool operator<(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template < class T, class A >
	bool operator<=(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return !( rhs < lhs );
	}
	template < class T, class A >
	bool operator>(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return ( rhs < lhs );
	}
	template < class T, class A >
	bool operator>=(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return !( lhs < rhs );
	}
}

#endif