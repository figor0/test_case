#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

#include "profile.h"
#include "test_runner.h"

using namespace std;
using x = int;
using y = int;
using sequence = std::vector<pair<x, y>>;

template <typename First, typename Second>
ostream& operator<<(ostream& stream, const std::pair<First, Second>& value)
{
	stream << '(' << value.first << ", " << value.second << ')';
	return stream;
}

template <typename First, typename Second>
ostream& operator<<(ostream& stream, const std::vector<pair<First, Second>>& container)
{
	for (auto it = container.begin(); it != container.end(); it++){
		stream << *it;
		if ( next(it) != container.end()){
			if ( next(it)->second == it->second ){
				stream << ", ";
			} else{
				stream << " ";
			}
		}
	}
	return stream;
}

template <typename First, typename Second>
ostream& operator<<(ostream& stream, const std::list<pair<First, Second>>& container)
{
	for (auto it = container.begin(); it != container.end(); it++){
		stream << *it;
		if ( next(it) != container.end()){
			if ( next(it)->second == it->second ){
				stream << ", ";
			} else{
				stream << " ";
			}
		}
	}
	return stream;
}

template <typename Container>
void filtering(Container& container, const int n)
{
	int counter = n - 1;
	if ( container.empty())
		return;
	else if (container.size() == 1){
		return;
	}
	for (auto it = next(container.begin()); next(it) != container.end(); it++ ){
		if ( it->second == prev(it)->second){
			counter--;
			if ( counter != 0 && it->second == next(it)->second){
				it = prev(it);
				container.erase(next(it));
			} else{
				counter = n - 1;
			}
		}
	}
}

template <typename Container>
Container copy_filter(const Container& container, const int n){
	Container result = container;
	filtering<Container>(result, n);
	return result;
}

void filtering_test()
{
	{
	 sequence example = {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}};
	 sequence n3Right = {{1, 10}, {2, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {9, 11}, {10, 11}, {11, 10}};
	 sequence n4Right = {{1, 10}, {2, 11}, {5, 11}, {6, 10}, {7, 11}, {10, 11}, {11, 10}};
	 ASSERT( n3Right == copy_filter(example, 3))
	 ASSERT( n4Right == copy_filter(example, 4))
	}
	{
		sequence empty;
		ASSERT( empty == copy_filter(empty, 3))
		ASSERT( empty == copy_filter(empty, 4))
	}
	{
		sequence one_element = {{1, 10}};
		ASSERT(one_element == copy_filter(one_element, 3))
		ASSERT(one_element == copy_filter(one_element, 30))
		ASSERT(one_element == copy_filter(one_element, 300))
		ASSERT(one_element == copy_filter(one_element, 10))
	}
	{
		sequence two_elements = {{1, 10}, {2, 11}};
		sequence equal_y = {{1, 11}, {2, 11}};
		ASSERT(two_elements == copy_filter(two_elements, 3))
		ASSERT( equal_y == copy_filter(equal_y, 3))
	}
}

void run_tests()
{
	TestRunner tr;
	RUN_TEST(tr, filtering_test);
}

void profileRunner()
{
	sequence input = {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}};
	list<pair<x, y>> input_list = {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}};
	const int test_amount = 500000;
	{
		LOG_DURATION("list filtering time count");
		for (int i = 0; i < test_amount; i++){
			auto list_pair = input_list;
			filtering(list_pair, 3);
		}
	}
	{
		LOG_DURATION("vector filtering time count");
		for (int i = 0; i < test_amount; i++){
			auto vector_pair = input;
			filtering(vector_pair, 3);
		}
	}
}

int main()
{
	// N - container size, M - max delete amount,
	// algorithm difficults depends from containers: for example vector - O(M*N), list - O(N)
	// but let compare benchmarks, and winner - vector =)
		run_tests();
	sequence input = {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}};
	cout << "Исходная: " << input << endl;
	cout << "Результат при n = 3: " << copy_filter(input, 3) << endl;
	cout << "Результат при n = 4: " << copy_filter(input, 4) << endl;
	return 0;
}
