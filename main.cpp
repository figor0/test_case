#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

#include <filter.hpp>


int main()
{
	// N - container size, M - max delete amount,
	// algorithm difficults depends from containers: for example vector - O(M*N), list - O(N)
	// but let compare benchmarks, and winner - vector =)
	sequence input = {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}};
	std::cout << "Исходная: " << input << std::endl;
	std::cout << "Результат при n = 3: " << copy_filter(input, 3) << std::endl;
	std::cout << "Результат при n = 4: " << copy_filter(input, 4) << std::endl;
	return 0;
}
