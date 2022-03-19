#ifndef STACK_HPP
#define STACK_HPP

namespace ft
{
	template <typename T, typename Container = std::deque >
	class stack<T>
	{
	protected:
		Container C;
	private:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
//		typedef typename Container::reference reference;
//		typedef typename Container::const_reference const_reference;
	public:
		explicit stack (const container_type& ctnr = container_type()) : C(cntr) {}
		bool empty() const { return (C.empty()); }
		size_type size() const { return (C.size()); }
		value_type& top() { return (C.back()); }
		const value_type& top() const { return (C.back()); }
		void push (const value_type& val) { C.push_back(); }
		void pop() { C.pop_back(); }
	};

	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){
		return ( lhs.C == rhs.C );
	}
	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return ( lhs.C != rhs.C );
	}
	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return ( lhs.C < rhs.C );
	}
	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return ( lhs.C <= rhc.C );
	}
	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return ( lhs.C > rhs.C );
	}
	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return ( lhs.C > rhs.C );
	}
}

#endif