#include <iostream>
#include <vector>

#include <assert.h>
#include "utility.hpp"
#include "vector.hpp"
#include <unistd.h>
#include <iterator>
#include "/Users/tgrounds/Desktop/ft_containers_git/ft_containers-unit-test/sources/system/engine.ipp"
typedef ft::pair<int, char> Pair_ic;
Pair_ic p0;

void print_vec(ft::vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << "size = " << vec.size() << ", cap = " << vec.capacity();
	std::cout << std::endl;
}

void size_test(ft::vector<int> &vec) {
	std::cout << "size: " << vec.size() << std::endl;
}

void empty_test(ft::vector<int> &vec) {
	std::cout << "empty: " << vec.empty() << std::endl;
}

void cap_test(ft::vector<int> &vec) {
	std::cout << "capacity: " << vec.capacity() << std::endl;
}

void data_test(ft::vector<int> &vec) {
	std::cout << "data + *data: " << vec.data() << std::endl;
}

void max_size_test(ft::vector<int> &vec) {
	std::cout << "max_size: " << vec.max_size() << std::endl;
}

void at_test(ft::vector<int> &vec) {
	std::cout << "at: " << vec.at(2) << std::endl;
}

void front_test(ft::vector<int> &vec) {
	std::cout << "front: " << vec.front() << std::endl;
}

void back_test(ft::vector<int> &vec) {
	std::cout << "back: " << vec.back() << std::endl;
}

void pop_back_test(ft::vector<int> &vec) {
	std::cout << "pop_back: ";vec.pop_back(); print_vec(vec);
}

void assignment_test(ft::vector<int> &vec) {
	std::cout << "assignment operator + assign(it1,it2): ";
	ft::vector<int> tmp;
	print_vec(tmp);
	tmp = vec;
	std::cout << "\nvec: "; print_vec(vec);
	std::cout << "tmp: "; print_vec(tmp);
}

void reserve_test(ft::vector<int> &vec) {
	std::cout << "reserve: "; vec.reserve(15); print_vec(vec);
}

void assign_test(ft::vector<int> &vec) {
	std::cout << "assign: "; vec.assign(7, 4); print_vec(vec);
}

void swap_test(ft::vector<int> &vec) {
	ft::vector<int> tmp;
	tmp.assign(3,8);
	std::cout << "swap: \n"; vec.swap(tmp);
	std::cout << "vec: "; print_vec(vec);
	std::cout << "tmp: "; print_vec(tmp);
	vec.swap(tmp);
}

void resize_test(ft::vector<int> &vec) {
	std::cout << "resize: "; vec.resize(12); print_vec(vec);
}

void erase_test(ft::vector<int> &vec) {
	std::cout << "erase: "; vec.erase(vec.end() - 1, vec.end()); print_vec(vec);
}

void erase_full_test(ft::vector<int> &vec) {
	ft::vector<int> tmp(vec);
	std::cout << "erase full: "; tmp.erase(tmp.begin(), tmp.end()); print_vec(tmp);
}

void clear_test(ft::vector<int> &vec) {
	ft::vector<int> tmp(vec);
	std::cout << "clear: "; tmp.clear(); print_vec(tmp);
}

void interval_constructor_test(ft::vector<int> &vec) {
	std::cout << "new_vec(interval parameter): ";
	ft::vector<int> k(vec.begin(), vec.end() - 4);
	print_vec(k);
}

void push_back_test(ft::vector<int> &vec) {
	std::cout << "push_back: "; vec.push_back(33); print_vec(vec);
}

void insert_test(ft::vector<int> &vec) {
	std::cout << "insert: "; vec.insert(vec.begin() + 7, 65); print_vec(vec);
}

void insert_iter_test(ft::vector<int> &vec) {
	ft::vector<int> tmp;
	tmp.push_back(9);
	tmp.push_back(10);
	tmp.push_back(11);
	std::cout << "insert_iter: ";
	vec.insert(vec.begin() + 9, tmp.begin(), tmp.end());
	print_vec(vec);
}

void my_tests(void) {
	ft::vector<int> m(5);
	print_vec(m);
	for (int i = 0; i < 5; i++)
		m[i] = i + 1;
	print_vec(m);
	std::cout << "new vec(copy constructor): ";
	ft::vector<int> n(m);
	print_vec(n);
	for (int i = 0; i < 5; i++)
		n[i] = m[i] + 3;

	std::cout << std::endl;
	size_test(m);
	empty_test(m);
	cap_test(m);
	data_test(m);
	max_size_test(m);
	at_test(m);
	front_test(m);
	back_test(m);
	pop_back_test(m);
	assignment_test(m);
	reserve_test(m);
	assign_test(m);
	swap_test(m);
	resize_test(m);
	erase_test(m);
	erase_full_test(m);
	clear_test(m);

	std::cout << "*begin: " << *m.begin() << std::endl;
	std::cout << "*end: " << *(m.end() - 1) << std::endl;

	push_back_test(m);
	interval_constructor_test(m);
	write(2, "7\n", 2);

	insert_test(m);
	insert_iter_test(m);

	printf("Success\n");
}

void check_equal(std::vector<int> &s_v, ft::vector<int> &f_v) {
	if (s_v.size() == f_v.size() && s_v.capacity() == f_v.capacity()) {
		for (int i = 0; i < s_v.size();++i)
		{
			std::cout << s_v[i] << ", " << f_v[i] << std::endl;
			if (s_v[i] != f_v[i]) std::cout << "0\n";
		}
		std::cout << "1\n";
	}
	else {
		std::cout << "0\n";

	}
	std::cout << "size s_v " << s_v.size() << ", f_v " << f_v.size();
	std::cout << ", cap s_v " << s_v.capacity() << ", f_v " << f_v.capacity() << std::endl;
	std::cout << "\n\n";
}

void test() {
	std::vector<int> s_v;
	ft::vector<int> f_v;

	std::vector<int> tmp_s;
	ft::vector<int> tmp_f;

	s_v.push_back(1);
	s_v.push_back(3);
	s_v.push_back(2);
	f_v.push_back(1);
	f_v.push_back(3);
	f_v.push_back(2);

	try { tmp_s.insert(tmp_s.begin(), s_v.begin(), s_v.end()); }
	catch (...) {
		s_v.push_back(tmp_s.size());
		s_v.push_back(tmp_s.capacity());
	}

	try { tmp_f.insert(tmp_f.begin(), f_v.begin(), f_v.end()); }
	catch (...) {
		f_v.push_back(tmp_f.size());
		f_v.push_back(tmp_f.capacity());
	}

	check_equal(s_v, f_v);
}

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

void test2() {
	std::vector<int> v;
	ft::vector<int> vector;
	ft::vector<int> tmp;
	tmp.assign(2600, 1);
	vector.assign(4200, 1);
	vector.insert(vector.end() - 1000, tmp.begin(), tmp.end());
	v.push_back(vector[3]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());

	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	ft::vector<A> vv;
	ft::vector<B*> v1;

//	v1.push_back(&(*k2));
//	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
		v.push_back(vv.size());
		v.push_back(vv.capacity());
	}
}


int main(int argc, char **argv, char **env)
{


//
	ft::vector<int> my_v;
//	my_v.push_back(1);
//	my_v.push_back(3);
//	my_v.push_back(5);
//	my_v.push_back(7);

	ft::vector<int>::const_iterator it = my_v.begin();
//	ft::vector<int>::const_iterator ite = my_v.end();
//	for (; it != ite; ++it)
//		std::cout << "- " << *it << std::endl;
//


//	test2();
//	std::cout << "yes\n";

//	check_equal(s_v, f_v);
	return 0;
}