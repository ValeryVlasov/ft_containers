#ifndef PAIR_HPP_
#define PAIR_HPP_


namespace ft {

	template<class T, class U>
	struct pair {
		typedef T first_type;
		typedef U second_type;
		first_type first;
		second_type second;

		pair(void) : first(first_type()), second(second_type()) {}

		pair(const T &lhs, const U &rhs) : first(lhs), second(rhs) {}

		template<class V, class W>
		pair(const pair<V, W> &pr) : first(pr.first), second(pr.second) {}

		~pair(void) {}

		pair &operator=(const pair &another) {
			this->first = another.first;
			this->second = another.second;
			return *this;
		}
	};

	template<class T, class U>
	pair<T, U> make_pair(const T &lhs, const U &rhs) {
		return pair<T, U>(lhs, rhs);
	}

//	template < class T >
//	bool operator!=(const T& lhs, const T& rhs) {
//		return !( lhs == rhs );
//	}

	template<class T, class U>
	bool operator!=(const pair<T, U> &lhs, const pair<T, U> &rhs) {
		return !(lhs == rhs);
	}

	template<class T, class U>
	bool operator==(const pair<T, U> &lhs, const pair<T, U> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<class T, class U>
	bool operator<(const pair<T, U> &lhs, const pair<T, U> &rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template<class T, class U>
	bool operator<=(const pair<T, U> &lhs, const pair<T, U> &rhs) {
		return !(rhs < lhs);
	}

	template<class T, class U>
	bool operator>(const pair<T, U> &lhs, const pair<T, U> &rhs) {
		return rhs < lhs;
	}

	template<class T, class U>
	bool operator>=(const pair<T, U> &lhs, const pair<T, U> &rhs) {
		return !(lhs < rhs);
	}

//	template<class T>
//	bool operator<=(const T &lhs, const T &rhs) {
//		return !(rhs < lhs);
//	}
//
//	template<class T>
//	bool operator>(const T &lhs, const T &rhs) {
//		return rhs < lhs;
//	}
//
//	template<class T>
//	bool operator>=(const T &lhs, const T &rhs) {
//		return !(lhs < rhs);
//	}



}//ft

#endif