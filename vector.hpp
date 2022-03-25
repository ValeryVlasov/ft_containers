#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP

#include <vector>
#include <iterator>

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