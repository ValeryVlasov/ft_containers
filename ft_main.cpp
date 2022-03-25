#include <iostream>
#include <vector>

#include <assert.h>
#include "utility.hpp"
#include "vector.hpp"
#include <iterator>

typedef ft::pair<int, char> Pair_ic;
Pair_ic p0;

int main()
{
	Pair_ic p1 = p0, p2(3, 'a');
	assert(p1.first == 0);
	assert(p1.second == 0);
	assert(p2.first == 3);
	assert(p2.second == 'a');
	assert( p1 != p2);
	assert( p2 > p1);
	assert(p2 <= p2);
	assert(p2 >= p2);
	assert(p2 == ft::make_pair( (Pair_ic::first_type) 3, (Pair_ic::second_type) 'a'));
	assert(p2 < ft::make_pair( (Pair_ic::first_type) 4, (Pair_ic::second_type) 'a'));
	assert(p2 < ft::make_pair( (Pair_ic::first_type) 3, (Pair_ic::second_type) 'b'));
	std::vector<int> vec(0);
	std::vector<int> vec2(0);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(7);
	vec2.push_back(1);
	vec2.push_back(3);
	vec2.push_back(5);
	vec2.push_back(7);
	std::cout << "Start of vec:";
	for (auto it : vec)
		std::cout << it << " ";
	std::cout << "\nEnd of vec.\n";
	std::cout << "Start of vec2:";
	for (auto it : vec2)
		std::cout << it << " ";
	std::cout << "\nEnd of vec2.\n";
	std::cout << "ft::comp: " << ft::lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end()) << std::endl;
	std::cout << "std::comp: " << std::lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end()) << std::endl;
	std::cout << "ft::equal: " << ft::equal(vec.begin(), vec.end(), vec2.begin()) << std::endl;
	std::cout << "std::equal: " << std::equal(vec.begin(), vec.end(), vec2.begin()) << std::endl;
	std::cout << "ft::dist: " << ft::distance(vec.begin(), vec.end()) << std::endl;
	std::cout << "std::dist: " << std::distance(vec.begin(), vec.end()) << std::endl;
	printf("Success\n");
	return 0;
}