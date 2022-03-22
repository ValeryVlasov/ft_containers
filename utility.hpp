#ifndef FTUTILITY_HPP
#define FTUTILITY_HPP

namespace ft {
	struct output_iterator_tag {	};
	struct input_iterator_tag {	};
	struct forward_iterator_tag : public input_iterator_tag {	};
	struct bidirectional_iterator_tag : public forward_iterator_tag {	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {	};

	typedef < bool B, class T >
	struct enable_if {};

	typedef < bool B, class T >
	struct enable_if< true, T > {
		typedef T type;
	};

	template < class Iterator >
	class iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template < class T >
	class iterator_traits< T* >
	{
		typedef typename size_t						difference_type;
		typedef typename T							value_type;
		typedef typename T*							pointer;
		typedef typename T&							reference;
		typedef typename random_access_iterator_tag	iterator_category;
	};

	template < class T >
	class iterator_traits < const T* >
	{
		typedef typename size_t						difference_type;
		typedef typename T							value_type;
		typedef typename const T*					pointer;
		typedef typename const T&					reference;
		typedef typename random_access_iterator_tag	iterator_category;
	};

	template < class Category, class T, class Distance = size_t, class pointer = T*, class Reference = T& >
	class iterator;

	template < class Iter >
	class reverse_iterator
	{
	private:
		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	protected:
		iterator_type current;
	public:
		reverse_iterator() : current(nullptr) {}
		explicit reverse_iterator(Iter _It) : current(_It) {}
		~reverse_iterator() {}

		template<class U>
		reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {}

		template < class It > reverse_iterator& operator=(const reverse_iterator<It>& other) {
			this->current = other.base();
			return *this;
		}
		iterator_type base() const { return current; }
		reference operator*() const {
			iterator_type _it = this->current;
			return *--_it;
		}
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) { return &(*this + n); }
		const reference operator[](difference_type n) const { return &(*this + n); }
		reverse_iterator& operator++() {
			--current;
			return *this;
		}
		reverse_iterator& operator--() {
			++current;
			return *this;
		}
		reverse_iterator operator++(int) {
			iterator_type _it = *this;
			--current;
			return _it;
		}
		reverse_iterator operator--(int) {
			iterator_type _it = *this;
			++current;
			returen _it;
		}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
		reverse_iterator& operator+=(difference_type n) const { current -= n; return *this; }
		reverse_iterator& operator-=(difference_type n) const { current += n; return *this; }
	};

	template < class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }

	template < class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return !(lhs.base() == rhs.base(); }

	template < class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return !(lhs.base() < rhs.base()); }

	template < class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return !(rhs.base() < lhs.base()); }

	template < class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return rhs.base() < lhs.base(); }

	template < class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }

	template < class Iter >
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return rhs.base() - lhs.base();
	}

	template < class T, bool v >
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }

	};

	typedef < class T >
	struct is_integral : public integral_constant<T, false> {};

	typedef <>
	struct is_integral : public integral_constant<bool, true> {};

	typedef <>
	struct is_integral : public integral_constant<char, true> {};

	typedef <>
	struct is_integral : public integral_constant<char16_t, true> {};

	typedef <>
	struct is_integral : public integral_constant<char32_t, true> {};

	typedef <>
	struct is_integral : public integral_constant<wchar_t, true> {};

	typedef <>
	struct is_integral : public integral_constant<signed char, true> {};

	typedef <>
	struct is_integral : public integral_constant<short int, true> {};

	typedef <>
	struct is_integral : public integral_constant<int, true> {};

	typedef <>
	struct is_integral : public integral_constant<long int, true> {};

	typedef <>
	struct is_integral : public integral_constant<long long int, true> {};

	typedef <>
	struct is_integral : public integral_constant<unsigned char, true> {};

	typedef <>
	struct is_integral : public integral_constant<unsigned short int, true> {};

	typedef <>
	struct is_integral : public integral_constant<unsigned int, true> {};

	typedef <>
	struct is_integral : public integral_constant<unsigned long int, true> {};

	typedef <>
	struct is_integral : public integral_constant<unsigned long long int, true> {};

	template < class T, class U >
	struct pair {
		typedef T	first_type;
		typedef U	second_type;
		first_type	first;
		second_type	second;

		pair(void) : first(first_type()), second(second_type()) {}

		pair(const T& lhs, const U& rhs) : first(lhs), second(rhs) {}

		template< class V, class W >
			pair(const pair<V, W>& pr) : first(pr.first), second(pr.second) {}

		~pair(void) {}

		pair& operator=(const pair& another) {
			this->first = another.first;
			this->second = another.second;
			return *this;
		}
	};

	template < class T, class U >
	pair<T, U> make_pair(const T& lhs, const U& rhs) {
		return pair<T, U>(lhs, rhs);
	}

	template < class T >
	bool operator!=(const T& lhs, const T& rhs) {
		return !( lhs == rhs );
	}

	template < class T, class U >
	bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return !( lhs == rhs );
	}

	template < class T, class U >
	bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T, class U >
	bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template < class T >
	bool operator<=(const T& lhs, const T& rhs) {
		return !( rhs < lhs );
	}

	template < class T, class U >
	bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return !( rhs < lhs );
	}

	template < class T >
	bool operator>(const T& lhs, const T& rhs) {
		return rhs < lhs;
	}

	template < class T, class U >
	bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return rhs < lhs;
	}

	template < class T >
	bool operator>=(const T& lhs, const T& rhs) {
		return !( lhs < rhs );
	}

	template < class T, class U >
	bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return !( lhs < rhs );
	}


	template< class InIt1, class InIt2 >
	bool lexicographical_compare(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2) {
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template< class InIt1, class InIt2, class Pred >
	bool lexicographical_compare(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, Pred pr) {
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (pr(first1, first2)) return true;
			if (pr(first2, first1)) return false;
		}
		return first1 == last1 && first2 != last2;
	}


	template < class InIt1, class InIt2 >
	bool equal(InIt1 first1, InIt1 last1, InIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if !( *first1 == *first2 ) return false;
		}
		return true;
	}
	template < class InIt1, class InIt2, class Pred >
	bool equal(InIt1 first1, InIt1 last1, InIt2 first2, Pred pr) {
		for (; first1 != last1; ++first1, ++first2) {
			if (pr(first1, first2)) return false;
		}
		return true;
	}
}

#endif