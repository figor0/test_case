#pragma once
#include <ostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

using x = int;
using y = int;
using sequence = std::vector<std::pair<x, y>>;

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& stream, const std::pair<First, Second>& value)
{
	stream << '(' << value.first << ", " << value.second << ')';
	return stream;
}

template <template<typename> typename Container, typename Item>
std::ostream& operator<<(std::ostream& stream, const Container<Item>& container)
{
	if (container.empty())
		return stream;
	auto preend_it = prev(container.end());
	for (auto it = container.begin(); it != preend_it; it++)
	{
		stream << *it << ", ";
	}
	stream << *preend_it;
	return stream;
}

template <typename Container>
void filtering(Container& container, const int n)
{
	int counter = n - 1;
	if ( container.empty() || container.size() == 1)
		return;
	for (auto it = next(container.begin()); it != prev(container.end()); it++ ){
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
