#ifndef FTVECTOR_HPP
#define FTVECTOR_HPP

#include <vector>
#include <iterator>
#include "utility.hpp"
#include <unistd.h>

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class ft_iterator
	{
	public:
		typedef T value_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::difference_type difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	protected:
		pointer _current;
	public:
		ft_iterator() : _current(nullptr) {}
		explicit ft_iterator(pointer ptr) : _current(ptr) {}
		~ft_iterator() {}

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
		ft_iterator operator-(difference_type n) const {
			ft_iterator tmp(*this);
			return (tmp -= n);
		}
		difference_type operator-(const ft_iterator &other) const { return _current - other._current; }
		ft_iterator operator+(difference_type n) const {
			ft_iterator tmp(*this);
			return (tmp += n);
		}
		ft_iterator& operator-=(difference_type n) { _current -= n; return *this; }
		ft_iterator& operator+=(difference_type n) { _current += n; return *this; }

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
		typedef Alloc											allocator_type;
		typedef typename allocator_type::value_type				value_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft_iterator<value_type>							iterator;// ft::reverse_iterator<ft_iterator<Alloc::value_type>>
		typedef const ft_iterator<value_type>					const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	private:
		size_type		_size;
		size_type		_capacity;
		pointer			_data;
		allocator_type	alloc;


		void _clearData(iterator begin, iterator end) {
			for (iterator it = begin; it != end; it++) {
				this->alloc.destroy(it.base());
			}
		}

		void _fillData(iterator begin, iterator end, const value_type &val) {
			for (iterator it = begin; it != end; it++)
				this->alloc.construct(it.base(), val);
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
		explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _data(nullptr), alloc(alloc) {}
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _size(n), _capacity(n), _data(NULL), alloc(alloc) {
			this->_data = this->alloc.allocate(_capacity);
			for (size_type i = 0; i < n; i++)
				this->alloc.construct(this->_data + i, val);
		}
		template<class InputIt>
		vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		: alloc(alloc) {
//			std::cerr << "1242412341234" << std::endl;
//			difference_type diff = std::distance(first, last);
//			std::cerr << "diff = " << diff << std::endl;
//			if (diff < 0) throw std::range_error("Error! Wrong iterators range!");
//			size_type new_size = static_cast<size_type>(diff);
//			size_type new_capacity = this->_increasedCapacity(new_size);
//			this->_data = this->alloc.allocate(new_capacity);
//			std::copy(first, last, this->begin());
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

			for (size_type i = 0; i < another._size; i++){
				this->alloc.construct(_data + i, *(another._data + i));
			}
			return *this;
		}

		/*      		Element access			 */
		reference			at(size_type pos)  {
			if (!(pos < size())) throw std::out_of_range("Out of range!");
			return this->_data[pos];
		}
		const_reference		at(size_type pos) const {
			if (!(pos < size())) throw std::out_of_range("Out of range!");
			return this->_data[pos];
		}

		reference			operator[](size_type pos) { return *(this->_data + pos); }
		const_reference		operator[](size_type pos) const { return *(this->_data + pos); }
		reference			front(void) { return *begin(); }//+
		const_reference		front(void) const { return *begin(); }//+
		reference			back(void) { return *(end() - 1); }//+
		const_reference		back(void) const { return *(end() - 1); }//+
		value_type			*data() { return this->_data; }//+
		const value_type	*data() const { return this->_data; }//+

		/*      		Element access			 */

		/*      		Capacity			 */

		bool empty() const { return size() == 0; }//+
		size_type size() const { return this->_size; }//+   std::distance(begin(), end()
		size_type max_size() const { return this->alloc.max_size(); }//+
		void	resize(size_type n, value_type val = value_type()) {//+
			if (n == this->_size) return;
			else if (n < this->_size)
			{
				this->_clearData(this->begin() + n, this->end());
				this->_size = n;
			}
			else
			{
				iterator tmp = this->end();
				size_type diff = n - this->_size;
				this->_reAlloc(this->_increasedCapacity(n));
				this->_size = n;
				this->_fillData(tmp, tmp + diff, val);
			}
		}
		void reserve(size_type new_cap) {//+
			if (new_cap > max_size()) throw std::length_error("length error");
			if (new_cap > this->_capacity) {
				this->_reAlloc(new_cap);
			}
		}
		size_type capacity() const { return this->_capacity; }//+


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
		void clear() {//+
			erase(begin(), end());
			this->alloc.deallocate(this->_data, this->_capacity);
			this->_reAssignVector(nullptr, 0, 0);
		}
		iterator erase(iterator pos) { return erase(pos, pos + 1); }//+
		iterator erase(iterator first, iterator second) {//+
			this->_clearData(first, second);
			if (second == end()) {
				this->_size -= std::distance(first, second);
				return this->end();
			}
			else {
				std::copy(second, this->end(), first);
				this->_size -= std::distance(first, second);
				return first;
			}
		}

		void assign(size_type n, const value_type& val) {//+
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
				void assign (const InputIterator &first, const InputIterator &second, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {//+
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

		void push_back (const value_type &val) {//+
			if (this->_size < this->_capacity)
				this->_data[this->_size] = val;
			else
			{
				this->_reAlloc(_increasedCapacity(this->_size + 1));
				this->_data[this->_size] = val;
			}
			this->_size++;
		}

		void pop_back() {//+
			if (this->_size == 0) return ;
			this->_clearData(this->end() - 1, this->end());//CHECK
			this->_size--;
		}

		iterator insert(iterator pos, const value_type& value) {//+
			difference_type dist = std::distance(this->begin(), pos);
			insert(pos, 1, value);
			return (this->begin() + dist);
		}

		void insert( iterator pos, size_type count, const value_type& value) {//+
			if (count + this->_size > this->_capacity) {
				size_type new_size = count + this->_size;
				size_type new_capacity = this->_increasedCapacity(new_size);
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

		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {//+
			difference_type dist = std::distance(first, last);
			size_type dst = static_cast<size_type>(dist);
			if (this->_size + dst > this->_capacity) {
				size_type new_size = dst + this->_size;
				size_type new_capacity = this->_increasedCapacity(new_size);
				pointer new_data = this->alloc.allocate(new_capacity);
				iterator tmp_it = iterator(new_data);
				std::copy(this->begin(), pos, tmp_it);
				tmp_it += std::distance(this->begin(), pos);
				std::copy(first, last, tmp_it);
				std::copy(pos, this->end(), tmp_it + dst);
				this->clear();
				this->_reAssignVector(new_data, new_capacity, new_size);
			}
			else {
				iterator prev_end = this->end();
				this->_size += dst;
				std::copy_backward(pos, prev_end, this->end());
				std::copy(first, last, pos);
			}
		}

		void swap(vector &another) {//+
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

	template < class T, class A >
	bool operator!=(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return !( lhs == rhs );
	}
	template < class T, class A >
	bool operator==(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return ( lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()) );
	}
	template < class T, class A >
	bool operator<(const vector<T, A>& lhs, const vector<T, A>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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