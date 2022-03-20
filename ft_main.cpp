#include <iostream>
#include <vector>

#include <assert.h>
#include "utility.hpp"

typedef ft::pair<int, char> Pair_ic;
Pair_ic p0;

int main()
{
//	std::vector<int> vec(3);
//	vec.push_back(5);
//	std::cout << vec.capacity() << std::endl;
//	std::cout << sizeof(vec) << std::endl;
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
	printf("Success\n");
	return 0;
}