#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <iterator>

namespace ft {
	struct output_iterator_tag {	};
	struct input_iterator_tag {	};
	struct forward_iterator_tag : public output_iterator_tag, public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag {	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {	};

	template < bool B, class T = void >
	struct enable_if {};

	template <class T >
	struct enable_if< true, T > {
		typedef T type;
	};

	template < class Iterator >
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template < class T >
	struct iterator_traits< T* >
	{
		typedef ptrdiff_t 						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

//	template < class T >
//	struct iterator_traits < const T* >
//	{
//		typedef size_t							difference_type;
//		typedef T								value_type;
//		typedef const T*						pointer;
//		typedef const T&						reference;
//		typedef std::random_access_iterator_tag	iterator_category;
//	};

	template < class Iter >
	class reverse_iterator
	{
	public:
		typedef Iter													iterator_type;
		typedef typename std::iterator_traits<Iter>::pointer				pointer;
		typedef typename std::iterator_traits<Iter>::reference			reference;
		typedef typename std::iterator_traits<Iter>::value_type			value_type;
		typedef typename std::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename std::iterator_traits<Iter>::iterator_category	iterator_category;
	protected:
		iterator_type current;
	public:
		reverse_iterator() : current(0) {}
		explicit reverse_iterator(Iter _It) : current(_It) {}
		template < class U >
		reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {}

		~reverse_iterator() {}

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
		reference operator[](difference_type n) { return *(this->current + n); }
		const reference operator[](difference_type n) const { return *(this->current + n); }
		reverse_iterator& operator++() {
			--current;
			return *this;
		}
		reverse_iterator& operator--() {
			++current;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			--current;
			return tmp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			++current;
			return tmp;
		}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
		reverse_iterator& operator+=(difference_type n) { this->current -= n; return *this; }
		reverse_iterator& operator-=(difference_type n) { this->current += n; return *this; }
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it - n);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return reverse_iterator<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		return (rhs.base() - lhs.base());
	}

	template < class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }

	template < class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return !(lhs.base() == rhs.base()); }

	template < class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return !(lhs.base() < rhs.base()); }

	template < class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return !(rhs.base() < lhs.base()); }

	template < class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return rhs.base() < lhs.base(); }

	template < class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }

	template < class InputIt >
	typename std::iterator_traits<InputIt>::difference_type Distance(const InputIt& first, const InputIt& last, ft::random_access_iterator_tag) {
		return (last - first);
	}


	template < class InputIt , class Category>
	typename std::iterator_traits<InputIt>::difference_type Distance(InputIt first, InputIt last, Category &) {
		typename std::iterator_traits<InputIt>::difference_type result = 0;
		while (first != last)
		{
			first++;
			result++;
		}
		return result;
	}

	template < class InputIt >
	typename std::iterator_traits<InputIt>::difference_type distance(const InputIt& first, const InputIt& last) {
		typename std::iterator_traits<InputIt>::iterator_category category;
		return ft::Distance(first, last, category);
	}

	template < class T, bool v >
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }

	};

	template < class T >
	struct is_integral : public integral_constant<T, false> {};

	template <>
	struct is_integral<bool> : public integral_constant<bool, true> {};

	template <>
	struct is_integral<char> : public integral_constant<char, true> {};

	template <>
	struct is_integral<char16_t> : public integral_constant<char16_t, true> {};

	template <>
	struct is_integral<char32_t> : public integral_constant<char32_t, true> {};

	template <>
	struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};

	template <>
	struct is_integral<signed char> : public integral_constant<signed char, true> {};

	template <>
	struct is_integral<short int> : public integral_constant<short int, true> {};

	template <>
	struct is_integral<int> : public integral_constant<int, true> {};

	template <>
	struct is_integral<long int> : public integral_constant<long int, true> {};

	template <>
	struct is_integral<long long int> : public integral_constant<long long int, true> {};

	template <>
	struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};

	template <>
	struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};

	template <>
	struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};

	template <>
	struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};

	template <>
	struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};




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
			if (! (*first1 == *first2 )) return false;
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
}//ft

#endif