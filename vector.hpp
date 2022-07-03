#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP

#include <vector>
#include <iterator>
#include "utility.hpp"
#include <unistd.h>

#include <memory>
namespace ft {

	template < class T >
	class ft_iterator : public iterator_traits<T*>
	{
	public:
		typedef T												value_type;
		typedef typename iterator_traits<T*>::pointer			pointer;
		typedef typename iterator_traits<T*>::reference			reference;
		typedef typename iterator_traits<T*>::difference_type	difference_type;
		typedef std::random_access_iterator_tag					iterator_category;
	protected:
		pointer _current;
	public:
		ft_iterator() : _current(0) {}
		ft_iterator(pointer ptr) : _current(ptr) {}
		ft_iterator(const ft_iterator& u) : _current(u.GetPtr()) {}
		~ft_iterator() { this->_current = NULL; }

		pointer GetPtr(void) const { return _current; }

		ft_iterator& operator=(const ft_iterator& other) {
			this->_current = other.GetPtr();
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

		ft_iterator operator-(difference_type n) const {
			ft_iterator tmp(*this);
			return (tmp -= n);
		}

		difference_type operator-(const ft_iterator &other) const { return _current - other.GetPtr(); }

		ft_iterator operator+(difference_type n) const {
			ft_iterator tmp(*this);
			return (tmp += n);
		}

		ft_iterator& operator-=(difference_type n) { _current -= n; return *this; }
		ft_iterator& operator+=(difference_type n) { _current += n; return *this; }

	};

	template < class It1, class It2 >
	bool operator==(const ft_iterator<It1>&lhs, const ft_iterator<It2>& rhs) { return lhs.GetPtr() == rhs.GetPtr(); }

	template < class It1, class It2 >
	bool operator!=(const ft_iterator<It1>&lhs, const ft_iterator<It2>& rhs) { return !(lhs == rhs); }

	template < class It1, class It2 >
	bool operator>=(const ft_iterator<It1>&lhs, const ft_iterator<It2>& rhs) { return !(lhs < rhs); }

	template < class It1, class It2 >
	bool operator<=(const ft_iterator<It1>&lhs, const ft_iterator<It2>& rhs) { return !(rhs < lhs); }

	template < class It1, class It2 >
	bool operator>(const ft_iterator<It1>&lhs, const ft_iterator<It2>& rhs) { return rhs < lhs; }

	template < class It1, class It2 >
	bool operator<(const ft_iterator<It1>&lhs, const ft_iterator<It2>& rhs) { return lhs.GetPtr() < rhs.GetPtr(); }

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	protected:

	public:
		typedef Alloc											allocator_type;
		typedef typename allocator_type::value_type				value_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft_iterator<T>									iterator;// ft::reverse_iterator<ft_iterator<Alloc::value_type>>
		typedef ft_iterator<const T>							const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	private:
		size_type		_size;
		size_type		_capacity;
		pointer			_data;
		allocator_type	alloc;


		void _clearData(iterator begin, iterator end) {
			for (iterator it = begin; it != end; ++it) {
				this->alloc.destroy(it.GetPtr());
			}
		}

		void _fillData(iterator begin, iterator end, const value_type &val) {
			for (iterator it = begin; it != end; ++it)
				this->alloc.construct(it.GetPtr(), val);
		}

		void _reAssignVector(pointer new_data, size_type new_capacity, size_type new_size)
		{
			this->_data = new_data;
			this->_capacity = new_capacity;
			this->_size = new_size;
		}

		void _reAlloc(size_type new_capacity) {
			pointer tmp_alloc = this->alloc.allocate(new_capacity);
			std::copy(this->begin(), this->end(), tmp_alloc);
			this->_clearData(this->begin(), this->end());
			this->alloc.deallocate(this->_data, this->_capacity);
			this->_reAssignVector(tmp_alloc, new_capacity, this->_size);
		}

		int _increasedCapacity(size_type new_capacity) { return static_cast<int>(new_capacity * 2); }

	public:
		explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _data(0), alloc(alloc) {}
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _size(n), _capacity(n), _data(NULL), alloc(alloc) {
			this->_data = this->alloc.allocate(_capacity);
			for (size_type i = 0; i < n; ++i)
				this->alloc.construct(this->_data + i, val);
		}
		template<class InputIt>
		vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		: alloc(alloc) {
			difference_type diff = std::distance(first, last);
			if (diff < 0) throw std::range_error("Error! Wrong iterators range!");
			_size = static_cast<size_type>(diff);
			_capacity = _size;
			this->_data = this->alloc.allocate(_capacity);
			std::copy(first, last, this->begin());
		}
		vector(const vector& another) : alloc(another.alloc), _size(another._size), _capacity(another._capacity) {
			this->_data = this->alloc.allocate(another._capacity);
			std::copy(another.begin(), another.end(), this->begin());
		}

		~vector() { this->clear(); }//CHECK

		vector &operator=(const vector& another) {
			this->clear();
			this->_size = another._size;
			this->_capacity = another._capacity;
			this->alloc = another.alloc;
			this->_data = this->alloc.allocate(another._capacity);

			for (size_type i = 0; i < another._size; ++i){
				this->alloc.construct(_data + i, *(another._data + i));
			}
			return *this;
		}

		/*      		Element access			 */
		reference			at(size_type pos)  {
			if (!(pos >= 0 || pos < size())) throw std::out_of_range("Out of range!");
			return this->_data[pos];
		}
		const_reference		at(size_type pos) const {
			if (!(pos >= 0 || pos < size())) throw std::out_of_range("Out of range!");
			return this->_data[pos];
		}

		reference			operator[](size_type pos) { return *(this->_data + pos); }
		const_reference		operator[](size_type pos) const { return *(this->_data + pos); }
		reference			front(void) { return *begin(); }
		const_reference		front(void) const { return *begin(); }
		reference			back(void) { return *(end() - 1); }
		const_reference		back(void) const { return *(end() - 1); }
		value_type			*data() { return this->_data; }
		const value_type	*data() const { return this->_data; }

		/*      		Element access			 */

		/*      		Capacity			 */

		bool empty() const { return size() == 0; }
		size_type size() const { return this->_size; }
		size_type max_size() const { return this->alloc.max_size(); }
		void	resize(size_type n, value_type val = value_type()) {
			if (n == this->_size) return;
			else if (n < this->_size)
			{
				this->_clearData(this->begin() + n, this->end());
				this->_size = n;
			}
			else
			{
				size_type tmp_dist = _size;
				size_type diff = n - this->_size;
				size_type new_cap;
				if (n < _capacity)
					new_cap = _capacity;
				else if (n < _capacity * 2)
					new_cap = _capacity * 2;
				else
					new_cap = n;
				this->_reAlloc(new_cap);
				this->_size = n;
				this->_fillData(this->begin() + tmp_dist, this->begin() + tmp_dist + diff, val);
			}
		}
		void reserve(size_type new_cap) {
			if (new_cap > max_size()) throw std::length_error("length error");
			if (new_cap > this->_capacity) {
				size_type old_cap = this->_capacity;
				this->_reAlloc(new_cap);
				this->_fillData(this->begin() + old_cap, this->begin() + new_cap, value_type());
			}
		}
		size_type capacity() const { return this->_capacity; }


		/*      		Capacity			 */

		/*      		Iterators			 */
		iterator				begin() { return iterator(this->_data); }
		const_iterator			begin() const { return const_iterator(this->_data); }
		iterator				end() { return iterator(this->_data + this->_size); }
		const_iterator			end() const { return const_iterator(this->_data + this->_size); }
		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator		rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }
		/*      		Iterators			 */

		/*      		Modifiers			 */
		void clear() {
			erase(begin(), end());
			this->alloc.deallocate(this->_data, this->_capacity);
			this->_reAssignVector(0, _capacity, 0);
		}
		iterator erase(iterator pos) { return erase(pos, pos + 1); }
		iterator erase(iterator first, iterator second) {
			this->_clearData(first, second);
			size_type dist = std::distance(first, second);
			if (second == end()) {
				this->_size -= dist;
				return this->end();
			}
			else {
				void *src = reinterpret_cast<void*>(_data + std::distance(this->begin(), first));
				void *dst = reinterpret_cast<void*>(_data + std::distance(this->begin(), first) + dist);
				memmove(src, dst, std::distance(second, this->end()) * sizeof(value_type));
				this->_size -= dist;
				return first;
			}
		}

		void assign(size_type n, const value_type& val) {
			if (n > this->capacity()) {
				this->clear();
				this->_capacity = n;
				this->_data = this->alloc.allocate(n);
			}
			else
				this->_clearData(this->begin(), this->end());
			this->_size = n;
			this->_fillData(this->begin(), this->end(), val);
		}

		template < class InputIterator >
				void assign (const InputIterator &first, const InputIterator &second, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			difference_type diff = std::distance(first, second);
			if (diff < 0)
				throw std::range_error("Error! Wrong iterators range");
			size_type size = static_cast<size_type>(diff);
			if (size >= this->_capacity) {
				this->clear();
				this->_capacity = size;
				this->_data = this->alloc.allocate(size);
			}
			else {
				this->_clearData(this->begin(), this->end());
			}
			this->_size = size;
			std::copy(first, second, this->begin());
		}

		void push_back (const value_type &val) {
			if (this->_size >= this->_capacity)
				this->_reAlloc(_increasedCapacity(this->_size));
			new (this->_data + this->_size) value_type(val);
			++this->_size;
		}

		void pop_back() {
			if (this->_size == 0) return ;
			this->_clearData(this->end() - 1, this->end());//CHECK
			--this->_size;
		}

		iterator insert(iterator pos, const value_type& value) {
			difference_type dist = std::distance(this->begin(), pos);
			insert(pos, 1, value);
			return (this->begin() + dist);
		}

		void insert( iterator pos, size_type count, const value_type& value) {
			if (count + this->_size > this->_capacity) {
				size_type new_size = count + this->_size;
				size_type new_capacity;// = this->_increasedCapacity(new_size);
				if (new_size > this->_capacity * 2)
					new_capacity = new_size;
				else
					new_capacity = this->_increasedCapacity(_capacity);
				pointer new_data = this->alloc.allocate(new_capacity);
				iterator tmp_it = iterator(new_data);
				std::copy(this->begin(), pos, tmp_it);
				tmp_it += std::distance(this->begin(), pos);
				this->_fillData(tmp_it, tmp_it + count, value);
				std::copy(pos, this->end(), tmp_it + count);
				this->clear();
				this->_reAssignVector(new_data, new_capacity, new_size);
			}
			else {
				iterator prev_end = this->end();
				this->_size += count;
				std::copy_backward(pos, prev_end, this->end());
				this->_fillData(pos, pos + count, value);
			}
		}

		template< class InputIt >/*						MEMMOVEEEEEEE								*/
		void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
			difference_type dist = std::distance(first, last);
			if (dist < 0)
				throw std::range_error("Error: Wrong iterators range!");
			size_type count = static_cast<size_type>(dist);
			if (this->_size + count > this->_capacity) {
				size_type new_size = count + this->_size;
				size_type new_capacity;
				if (new_size > this->_capacity * 2)
					new_capacity = new_size;
				else
					new_capacity = this->_increasedCapacity(_capacity);
				pointer new_data = this->alloc.allocate(new_capacity);
				iterator tmp_it = iterator(new_data);
				std::copy(this->begin(), pos, tmp_it);
				tmp_it += std::distance(this->begin(), pos);
				std::copy(first, last, tmp_it);
				std::copy(pos, this->end(), tmp_it + count);
				this->clear();
				this->_reAssignVector(new_data, new_capacity, new_size);
			}
			else {
				iterator prev_end = this->end();
				this->_size += count;
				std::copy_backward(pos, prev_end, this->end());
				std::copy(first, last, pos);//memmove
			}
		}

		void swap(vector &another) {
			size_type		tmp_size = this->_size;
			size_type		tmp_capacity = this->_capacity;
			pointer			tmp_data = this->_data;
			allocator_type	tmp_alloc = this->alloc;
			this->_size = another._size;
			this->_data = another._data;
			this->alloc = another.alloc;
			this->_capacity = another._capacity;
			another._size = tmp_size;
			another._data = tmp_data;
			another.alloc = tmp_alloc;
			another._capacity = tmp_capacity;
		}

		/*      		Modifiers			 */

	};


	template < class T, class Alloc >
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
		typename vector<T, Alloc>::const_iterator it2 = rhs.begin();
		for (; it1 != lhs.end(); ++it1, ++it2) {
			if (*it1 != *it2)
				return false;
		}
		return true;
	}

	template < class T, class Alloc >
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		typename vector<T, Alloc>::const_iterator first1 = lhs.begin();
		typename vector<T, Alloc>::const_iterator first2 = rhs.begin();
		typename vector<T, Alloc>::const_iterator last1 = lhs.end();
		typename vector<T, Alloc>::const_iterator last2 = rhs.end();

		for (; first1 != last1; ++first1, ++first2) {
			if (first2 == last2 || *first1 > *first2)
				return false;
			else if (*first1 < *first2)
				return true;
		}
		return (*first2 != *last2);
	}

	template < class T, class A >
	bool operator!=(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return !( lhs == rhs );
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