#include <profile.hpp>
#include <test_runner.hpp>
#include <filter.hpp>

void filtering_test()
{
	{
	 sequence example = {
							{1, 10}, {2, 11}, {3, 11}, {4, 11},
							{5, 11}, {6, 10}, {7, 11}, {8, 11},
							{9, 11}, {10, 11}, {11, 10}
						};
	 sequence n3Right = {
							{1, 10}, {2, 11}, {4, 11}, {5, 11},
							{6, 10}, {7, 11}, {9, 11}, {10, 11},
							{11, 10}
						};
	 sequence n4Right = {
							{1, 10}, {2, 11}, {5, 11}, {6, 10},
							{7, 11}, {10, 11}, {11, 10}
						};
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
	sequence input = {
						{1, 10}, {2, 11}, {3, 11}, {4, 11},
						{5, 11}, {6, 10}, {7, 11}, {8, 11},
						{9, 11}, {10, 11}, {11, 10}
					};
	std::list<std::pair<x, y>> input_list = {
											{1, 10}, {2, 11}, {3, 11},
											{4, 11}, {5, 11}, {6, 10},
											{7, 11}, {8, 11}, {9, 11},
											{10, 11}, {11, 10}
											};
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
	run_tests();
	profileRunner();
	return 0;
}
