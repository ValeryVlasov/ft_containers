#ifndef FT_STACK_HPP_
#define FT_STACK_HPP_

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
	private:
		Container C;
	private:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;

		template< class U, class Cont >
		friend bool operator<( const stack<U, Cont>& lhs, const stack<U, Cont>& rhs );
	public:
		explicit stack (const container_type& cntr = container_type()) : C(cntr) {}
		stack(const stack &other) {
			this->C = other.C;
		}

		stack &operator=(const stack &other) {
			this->C = other.C;
			return *this;
		}
		~stack() {}

		bool empty() const { return (C.empty()); }
		size_type size() const { return (C.size()); }
		value_type& top() { return (C.back()); }
		const value_type& top() const { return (C.back()); }
		void push (const value_type& val) { C.push_back(val); }
		void pop() { C.pop_back(); }




	};

	template< class T, class Cont >
	bool operator==( const stack<T, Cont>& lhs, const stack<T, Cont>& rhs ){
		return !( lhs < rhs || rhs < lhs );
	}
	template< class T, class Cont >
	bool operator!=( const stack<T, Cont>& lhs, const stack<T, Cont>& rhs ) {
		return !( lhs == rhs );
	}
	template< class U, class Cont >
	bool operator<( const stack<U, Cont>& lhs, const stack<U, Cont>& rhs ) {
		return ( lhs.C < rhs.C );
	}
	template< class T, class Cont >
	bool operator<=( const stack<T, Cont>& lhs, const stack<T, Cont>& rhs ) {
		return !( rhs < lhs );
	}
	template< class T, class Cont >
	bool operator>( const stack<T, Cont>& lhs, const stack<T, Cont>& rhs ) {
		return ( rhs < lhs );
	}
	template< class T, class Cont >
	bool operator>=( const stack<T, Cont>& lhs, const stack<T, Cont>& rhs ) {
		return !( lhs < rhs );
	}
}

#endif