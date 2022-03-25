#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP

#include <vector>
#include <iterator>
#include "utility.hpp"

namespace ft {

	template < class T, class Allocator >
	class ft_iterator
	{
	public:
		typedef T value_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::difference_type difference_type;
		typedef random_access_iterator_tag iterator_category;
	protected:
		pointer _current;
	public:
		ft_iterator() : _current(nullptr) {}
		explicit ft_iterator(pointer ptr) : _current(ptr) {}
		~ft_iterator();

		template<class U>
		ft_iterator(const ft_iterator<U, Allocator>& u) : _current(u.base()) {}

		pointer base(void) const { return _current; }

		template < class It >
		ft_iterator& operator=(const ft_iterator<It, Allocator>& other) {
			this->_current = other.base();
			return *this;
		}

		reference operator*() const { return *this->_current; }
		reference operator->() const { return this->_current; }


		reference operator[](difference_type n) { return &(*this + n); }
		const reference operator[](difference_type n) const { return &(*this + n); }
		ft_iterator& operator++() {
			++_current;
			return *this;
		}
		ft_iterator& operator--() {
			--_current;
			return *this;
		}
		ft_iterator operator--(int) {
			ft_iterator _it = *this;
			--_current;
			return _it;
		}
		ft_iterator operator++(int) {
			ft_iterator _it = *this;
			++_current;
			return _it;
		}
		ft_iterator operator-(difference_type n) const { return ft_iterator(_current - n); }
		ft_iterator operator+(difference_type n) const { return ft_iterator(_current + n); }
		ft_iterator& operator-=(difference_type n) const { _current -= n; return *this; }
		ft_iterator& operator+=(difference_type n) const { _current += n; return *this; }

		template < class Iterator2 >
		bool operator==(const ft_iterator<Iterator2, Allocator>& other) { return this->base() == other.base(); }

		template < class Iterator2 >
		bool operator!=(const ft_iterator<Iterator2, Allocator>& other) { return !(this->base() == other.base()); }

		template < class Iterator2 >
		bool operator>=(const ft_iterator<Iterator2, Allocator>& other) { return !(this->base() < other.base()); }

		template < class Iterator2 >
		bool operator<=(const ft_iterator<Iterator2, Allocator>& other) { return !(other.base() < this->base()); }

		template < class Iterator2 >
		bool operator>(const ft_iterator<Iterator2, Allocator>& other) { return other.base() < this->base(); }

		template < class Iterator2 >
		bool operator<(const ft_iterator<Iterator2, Allocator>& other) { return this->base() < other.base(); }

	};

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	protected:

	public:
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft_iterator<value_type, allocator_type>			iterator;
		typedef ft_iterator<const value_type, allocator_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	private:
		size_type		_size;
		size_type		_capacity;
		pointer			_data;
		allocator_type	alloc;
	public:
		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		vector(const vector& x);
		~vector();

		vector &operator=(const vector& another);

		/*      		Element access			 */
		reference			at(size_type pos)  {
			if (!(pos < size())) throw std::out_of_range("Out of range!");
			return *(begin() + pos);
		}
		const_reference		at(size_type pos) const {
			if (!(pos < size())) throw std::out_of_range("Out of range!");
			return *(begin() + pos);
		}

		reference			operator[](size_type pos) { return *(begin() + pos); }
		const_reference		operator[](size_type pos) const { return *(begin() + pos); }
		reference			front(void) { return *begin(); }
		const_reference		front(void) const { return *begin(); }
		reference			back(void) { return *(end() - 1); }
		const_reference		back(void) const { return *(end() - 1); }
		value_type			*data() { return begin(); }
		const value_type	*data() const { return begin(); }//TODO::first?

		/*      		Element access			 */

		/*      		Capacity			 */

		bool empty() const { return size() == 0; }
		size_type size() const { return ft::distance(begin(), end()); }
		size_type max_size() const {  }
		void reserve(size_type new_cap) {
			if (new_cap > max_size()) throw std::length_error();
		}
		size_type capacity() const { return this->_capacity; }


		/*      		Capacity			 */

		/*      		Iterators			 */
		iterator				begin() { return this->_data; }
		const_iterator			begin() const { return this->_data; }
		iterator				end() { return this->_data + this->size(); }
		const_iterator			end() const { return this->_data + this->size(); }
		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator	rbegin() const { return reverse_iterator(this->end()); }
		reverse_iterator		rend() { return reverse_iterator(this->begin(); }
		const_reverse_iterator	rend() const { return reverse_iterator(this->begin(); }
		/*      		Iterators			 */

		/*      		Modifiers			 */
		void clear() { erase(begin(), end()); }

		/*      		Modifiers			 */

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

	template < class T, class A >
	void swap(vector<T, A>& x, vector<T, A>& y) {
		x.swap(y);
	}
}

#endif