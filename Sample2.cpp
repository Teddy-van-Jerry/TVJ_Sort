/*
 * File: Sample2.cpp
 * --------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: At least C++/11
 *
 * @version 2021/03/09
 * - Initial version
 *
 * @note: This sample tests the use of TVJ_Sort
 *
 */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <list>
#include <deque>
#include <array>
#include "TVJ_Sort.h"
#include "TVJ_Timer.h"
using namespace std;

template<typename T>
void print(const T& container)
{
	for (const auto& c : container)
	{
		cout << c << ' ';
	}
	cout << endl;
}

int main(int argc, char** argv)
{
	// Example 1
	deque<double> deque_{ 1.2, 3.5, 6.23, -1, 1.2, 0 };
	// You have to specify its type here.
	quick_sort_pro_safe<deque<double>>(deque_.begin(), deque_.end() - 2);
	print(deque_);

	// Example 2
	vector<string> vector_{ "AA", "Ab", "Teddy", "van", "Jerry", "a", "AA" };
	quick_sort_pro_safe(vector_);
	print(vector_);

	// Example 3
	double arr1[7]{ 1.2, -3, 0.43, 120, -21, -3, 12 };
	insertion_sort(arr1, arr1 + 5);
	print(arr1);

	// Example 4
	unsigned long long arr2[5]{ 1000000, 200000, 3000000000000, 120, 32222222000000 };
	bubble_sort(begin(arr2), end(arr2));
	print(arr2);

	// Example 5
	array<char, 4> arr3 = { 'a', 'b', 'A', '0' };
	LSD_sort_pro_heap1(arr3);
	print(arr3);
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry