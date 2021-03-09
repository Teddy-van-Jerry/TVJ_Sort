/*
 * File: Sample1.cpp
 * --------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: At least C++/11
 *
 * @version 2021/03/09
 * - Modify to fit the new TVJ_Sort.h
 *
 * @version 2020/11/29
 * - Initial version
 * 
 * @note: This sample tests the speed of sorting using 'int'.
 *
 */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include "TVJ_Sort.h"
#include "TVJ_Timer.h"
using namespace std;

void random(size_t n, int min_one, int max_one, vector<int>& ran)
{
	uniform_int_distribution<int> u(min_one, max_one);
	default_random_engine e;
	for (size_t i = 0; i != n; i++)
	{
		ran.push_back(u(e));
	}
}

// tset whether the sort is correct
void checkSorted(vector<int> to_test, int ck)
{
	int ck_now = 0;
	for (auto iter = to_test.cbegin(); iter != to_test.cend() - 1; iter++)
	{
		if (*iter > * (iter + 1))
		{
			cerr << "(failed) ";
			return;
		}
	}
	for (const auto& c : to_test)
		ck_now ^= c;
	if (ck_now != ck)
	{
		cerr << "(failed) ";
		return;
	}
	cout << "(succeeded) ";
}

int main(int argc, int** argv)
{
	TVJ_Timer timer("s.9");
	size_t length;
	vector<int> ran;
	int ck = 0;
	long long MIN_one = -1000000, MAX_one = 1000000;
	cout << "This is the sorting programme.\nDesigned by Teddy van Jerry.\n" << endl;
	cout << "Please input the range of random numbers: ";
	cin >> MIN_one >> MAX_one;
	cout << "Please input the length you want to sort: ";
	cin >> length;
	random(length, MIN_one, MAX_one, ran);
	for (const auto& c : ran)
		ck ^= c; // calculate the initial result

	// standard algorithm sort defined in C++ library
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "STL_sort: ";
		timer.restart();
		sort(temp_vec.begin(), temp_vec.end());
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// LSD sort pro heap1
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "LSD_sort_pro_heap1: ";
		timer.restart();
		LSD_sort_pro_heap1(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// LSD sort pro heap2
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "LSD_sort_pro_heap2: ";
		if (length > 20000000)
		{
			cout << "(skipped) The number of elements is too large." << endl;
		}
		else
		{
			timer.restart();
			LSD_sort_pro_heap2(temp_vec);
			double duration_time = timer.durationTimeDouble();
			checkSorted(temp_vec, ck);
			cout << duration_time << " seconds." << endl;
		}
	}

	// LSD sort pro
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "LSD_sort_pro: ";
		timer.restart();
		LSD_sort_pro(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// LSD sort
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "LSD_sort: ";
		timer.restart();
		LSD_sort(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// MSD sort pro
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "MSD_sort_pro: ";
		timer.restart();
		MSD_sort_pro(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// MSD sort
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "MSD_sort: ";
		timer.restart();
		MSD_sort(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// quick sort pro safe
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "Quick_sort_pro_safe: ";
		timer.restart();
		quick_sort_pro_safe(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// quick sort pro
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "Quick_sort_pro: ";
		timer.restart();
		quick_sort_pro(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// quick sort
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "Quick_sort: ";
		timer.restart();
		quick_sort(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// insertion sort
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "Insertion_sort: ";
		timer.restart();
		insertion_sort(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	// bubble sort
	{
		vector<int> temp_vec = ran;
		cout << setw(21) << "Bubble_sort: ";
		timer.restart();
		bubble_sort(temp_vec);
		double duration_time = timer.durationTimeDouble();
		checkSorted(temp_vec, ck);
		cout << duration_time << " seconds." << endl;
	}

	return 0;
}

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry