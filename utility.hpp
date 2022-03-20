#ifndef FTUTILITY_HPP
#define FTUTILITY_HPP

namespace ft {
	struct output_iterator_tag {	};
	struct input_iterator_tag {	};
	struct forward_iterator_tag : public input_iterator_tag {	};
	struct bidirectional_iterator_tag : public forward_iterator_tag {	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {	};

	template < class T, class U >
	struct pair {
		typedef T first_type;
		typedef U second_type;
		first_type first;
		second_type second;

		pair(void) : first(first_type()), second(second_type()) {}

		pair(const T& x, const U& y) : first(x), second(y) {}

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
	pair<T, U> make_pair(const T& x, const U& y) {
		return pair<T, U>(x, y);
	}
	template < class T >
	bool operator!=(const T& x, const T& y) {
		return !( x == y );
	}
	template < class T, class U >
	bool operator!=(const pair<T, U>& x, const pair<T, U>& y) {
		return !( x == y );
	}
	template < class T, class U >
	bool operator==(const pair<T, U>& x, const pair<T, U>& y) {
		return x.first == y.first && x.second == y.second;
	}
	template < class T, class U >
	bool operator<(const pair<T, U>& x, const pair<T, U>& y) {
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}
	template < class T >
	bool operator<=(const T& x, const T& y) {
		return !( y < x );
	}
	template < class T, class U >
	bool operator<=(const pair<T, U>& x, const pair<T, U>& y) {
		return !( y < x );
	}
	template < class T >
	bool operator>(const T& x, const T& y) {
		return y < x;
	}
	template < class T, class U >
	bool operator>(const pair<T, U>& x, const pair<T, U>& y) {
		return y < x;
	}
	template < class T >
	bool operator>=(const T& x, const T& y) {
		return !( x < y );
	}
	template < class T, class U >
	bool operator>=(const pair<T, U>& x, const pair<T, U>& y) {
		return !( x < y );
	}
}

#endif