/*
 * File: TVJ_Sort.h
 * --------------------
 * 
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: At least C++/11
 * 
 * @version 2.4 2021/06/11
 * - Add the pointer version of heap_sort
 * 
 * @version 2.3 2021/06/10
 * - Add heap_sort
 * 
 * @version 2.2 2021/03/10
 * - Bug Fix (medium now supports pointers)
 * - Improve Heap_Vector class
 * 
 * @version 2.1 2021/03/09
 * - Add functions that support iterators
 * - promote 'int' into 'size_t'
 * 
 * @version 2.0 2021/03/08
 * - Add the template
 * 
 * @version 1.0 2020/11/29
 * - Initial version
 * 
 */

#pragma once

#ifndef _HEAP_VECTOR_
#define _HEAP_VECTOR_

// A simple vector class that supports limited functions.
template<typename ValueType>
class Heap_Vector {
public:
	Heap_Vector(size_t n = 32) : capacity_(n), size_(0), vec_(new ValueType[n]) { }
	~Heap_Vector() // destructor
	{
		delete[] vec_; // free the dynamic array
	}
	// similar to the function of push_back in vector
	void push_back(const ValueType& value)
	{
		if (size_ == capacity_)
		{
			expand();
		}
		vec_[size_++] = value;
	}
	inline const ValueType& operator [](size_t index) const
	{
		return vec_[index];
	}
	inline ValueType& operator [](size_t index)
	{
		return vec_[index];
	}
	inline size_t size() const
	{
		return size_;
	}

private:
	ValueType* vec_;
	size_t capacity_;

protected:
	size_t size_;
	void expand()
	{
		// 1. ask for new space for the array
		ValueType* new_vec = new ValueType[2 * capacity_];
		// 2. copy the values over
		for (size_t i = 0; i != size_; i++)
			new_vec[i] = vec_[i];
		// 3. delete the old array
		delete[] vec_;
		// 4. point vec to new array
		vec_ = new_vec;
		// 5. update capacity (twice the capacity)
		capacity_ *= 2;
	}
};
#endif // !_HEAP_VECTOR_

#ifndef _TVJ_HEAP_
#define _TVJ_HEAP_
#endif

#ifndef _TVJ_SORT_
#define _TVJ_SORT_
#include <string>
#define my_max(i, j) ((i > j) ? i : j)
#define my_min(i, j) ((i < j) ? i : j)
#define radix_index 256
#define radix_binary 8

#if defined (_WIN64) || defined (WIN32)
#include <Windows.h>
#endif // only for Windows

// set alias (C++/11)
template<typename T> using vec_c_iter   =       typename T::const_iterator;
template<typename T> using vec_iter     =       typename T::iterator;
template<typename T> using c_vec_c_iter = const typename T::const_iterator;
template<typename T> using c_vec_iter   = const typename T::iterator;

/**
 * check type
 * Used to check if it is an STL coantainer.
 * return bool
 */
template<typename T>
inline bool check_type(const WCHAR* text)
{
	if (   !std::is_same<std::decay<typename T::value_type>::type, char	             >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, short	             >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, int		         >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, long		         >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, long long         >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, unsigned char     >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, unsigned short    >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, unsigned int      >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, unsigned long     >::value
		&& !std::is_same<std::decay<typename T::value_type>::type, unsigned long long>::value)
	{
#if defined (_WIN64) || defined (WIN32)
		MessageBox(NULL, text, L"Error", MB_ICONERROR);
#endif // only for Windows
		return false;
	}
	else return true;
}

/**
 * isUnsigned
 * Used to check if the element type is unsigned.
 * return bool
 */
template<typename T>
inline bool isUnsigned()
{
	if (   std::is_same<std::decay<typename T::value_type>::type, unsigned char     >::value
		|| std::is_same<std::decay<typename T::value_type>::type, unsigned short    >::value
		|| std::is_same<std::decay<typename T::value_type>::type, unsigned int      >::value
		|| std::is_same<std::decay<typename T::value_type>::type, unsigned long     >::value
		|| std::is_same<std::decay<typename T::value_type>::type, unsigned long long>::value)
		return true;
	else return false;
}

/**
 * my_swap
 * Used to swap two numbers more efficiently than in STL.
 * return void
 */
template<typename T>
inline void my_swap(T& i, T& j)
{
	auto temp = j;
	j = i;
	i = temp;
}

/**
 * my_pow
 * Used to have the power of int.
 * return int
 */
int my_pow(int n, int m)
{
	int ret = 1;
	for (int i = 0; i != m; i++)
		ret *= n;
	return ret;
}

/**
 * medium (iterator)
 * return the medium one of the three,
 * used for iterators
 */
template<typename T>
inline auto medium(c_vec_iter<T>& a, c_vec_iter<T>& b, c_vec_iter<T>& c)
{
	if ((*a <= *b && *a >= *c) || (*a >= *b && *a <= *c)) return a;
	else if ((*b <= *a && *b >= *c) || (*b >= *a && *b <= *c)) return b;
	else return c;
}

/**
 * medium (pointer)
 * return the medium one of the three,
 * used for pointers
 */
template<typename T>
inline auto medium(T* a,T* b, T* c)
{
	if ((*a <= *b && *a >= *c) || (*a >= *b && *a <= *c)) return a;
	else if ((*b <= *a && *b >= *c) || (*b >= *a && *b <= *c)) return b;
	else return c;
}

/**
 * bubble sort (iterator)
 * return void
 */
template<typename T>
void bubble_sort(vec_iter<T> i_beg, vec_iter<T> i_end)
{
	auto up = i_beg, k = i_beg;
	while (up < i_end)
	{
		k = i_end;
		for (auto i = i_end - 1; i > up; i--)
		{
			if (*i < *(i - 1))
			{
				my_swap(*i, *(i - 1));
				k = i;
			}
		}
		up = k;
	}
}

/**
 * bubble sort (pointer)
 * return void
 */
template<typename T>
void bubble_sort(T* i_beg, T* i_end)
{
	auto up = i_beg, k = i_beg;
	while (up < i_end)
	{
		k = i_end;
		for (auto i = i_end - 1; i > up; i--)
		{
			if (*i < *(i - 1))
			{
				my_swap(*i, *(i - 1));
				k = i;
			}
		}
		up = k;
	}
}

/**
 * insertion sort (iterator)
 * return void
 */
template<typename T>
void insertion_sort(vec_iter<T> i_beg, vec_iter<T> i_end)
{
	for (auto i = i_beg + 1; i != i_end; i++)
	{
		auto temp = *i;
		// slide elements right to make room for v[i]
		auto j = i;
		while (j >= i_beg + 1 && *(j - 1) > temp)
		{
			*(j--) = *(j - 1);
		}
		*j = temp;
	}
}

/**
 * insertion sort (pointer)
 * return void
 */
template<typename T>
void insertion_sort(T* i_beg, T* i_end)
{
	for (auto i = i_beg + 1; i != i_end; i++)
	{
		auto temp = *i;
		// slide elements right to make room for v[i]
		auto j = i;
		while (j >= i_beg + 1 && *(j - 1) > temp)
		{
			*(j--) = *(j - 1);
		}
		*j = temp;
	}
}

/**
 * quick sort (that takes three arguments)
 * Argument 1: the container
 * Argument 2: the begin iterator
 * Argument 3: the end iterator
 * return void
 */
template<typename T>
void quick_sort(T& vec, vec_iter<T> i, vec_iter<T> j)
{
	if (j - i <= 1) return;
	else
	{
		auto standard_number = *i;
		auto init_begin = i;
		auto init_end = j;

		while (i != j)
		{
			do { --j; } while (*j > standard_number && i < j);
			if (i == j) break;
			else
			{
				do { ++i; } while (*i < standard_number && i < j);
				my_swap(*i, *j);
			}
		}
		my_swap(*init_begin, *i);
		quick_sort(vec, init_begin, i);
		quick_sort(vec, i + 1, init_end);
	}
}

/**
 * quick sort pro (that takes two arguments) (iterator)
 * Argument 1: the begin iterator
 * Argument 2: the end iterator
 * return void
 */
template<typename T>
void quick_sort_pro(vec_iter<T> i, vec_iter<T> j)
{
	if (j - i <= 1) return;
	else if (j - i == 2)
	{
		if (*i > * (j - 1))
		{
			my_swap(*i, *(j - 1));
		}
		return;
	}
	else if (j - i <= 7)
	{
		// If the number is not large,
		// insertion sort can be more efficient.
		insertion_sort<T>(i, j);
		return;
	}
	else
	{
		auto init_begin = i;
		auto init_end = j;

		auto Standard_defined = *init_begin;
		while (i != j)
		{
			do { --j; } while (*j > Standard_defined && i < j);
			if (i == j) break;
			else
			{
				do { ++i; } while (*i < Standard_defined && i < j);
				my_swap(*i, *j);
			}
		}
		my_swap(*init_begin, *i);
		quick_sort_pro<T>(init_begin, i);
		quick_sort_pro<T>(i + 1, init_end);
	}
}

/**
 * quick sort pro (that takes two arguments) (pointer)
 * Argument 1: the begin iterator
 * Argument 2: the end iterator
 * return void
 */
template<typename T>
void quick_sort_pro(T* i, T* j)
{
	if (j - i <= 1) return;
	else if (j - i == 2)
	{
		if (*i > * (j - 1))
		{
			my_swap(*i, *(j - 1));
		}
		return;
	}
	else if (j - i <= 7)
	{
		// If the number is not large,
		// insertion sort can be more efficient.
		insertion_sort<T>(i, j);
		return;
	}
	else
	{
		auto init_begin = i;
		auto init_end = j;

		auto Standard_defined = *init_begin;
		while (i != j)
		{
			do { --j; } while (*j > Standard_defined && i < j);
			if (i == j) break;
			else
			{
				do { ++i; } while (*i < Standard_defined && i < j);
				my_swap(*i, *j);
			}
		}
		my_swap(*init_begin, *i);
		quick_sort_pro<T>(init_begin, i);
		quick_sort_pro<T>(i + 1, init_end);
	}
}

/**
 * quick sort pro safe (that takes two arguments) (iterator)
 * The safe version that can deal with special circumtances better.
 * Argument 1: the begin iterator
 * Argument 2: the end iterator
 * Do not support 'list'.
 * return void
 */
template<typename T>
void quick_sort_pro_safe(vec_iter<T> i, vec_iter<T> j)
{
	if (j - i <= 1) return;
	else if (j - i == 2)
	{
		if (*i > * (j - 1))
		{
			my_swap(*i, *(j - 1));
		}
	}
	else if (j - i <= 7)
	{
		// If the number is not large,
		// insertion sort can be more efficient.
		insertion_sort<T>(i, j);
		return;
	}
	else
	{
		// Choose the medium one of the three numbers,
		// in order to avoid the circumstance that
		// the standard number is too large or too small
		// when quicksort can be reduced from o(nlog(n)) to o(N^2).
		auto standard_number = medium<T>(i, j - 1, i + ((j - i) - 1) / 2);
		auto init_begin = i;
		auto init_end = j;

		auto Standard_defined = *standard_number;
		my_swap(*standard_number, *init_begin);
		while (i != j)
		{
			do { --j; } while (*j > Standard_defined && i < j);
			if (i == j) break;
			else
			{
				do { ++i; } while (*i < Standard_defined && i < j);
				my_swap(*i, *j);
			}
		}
		my_swap(*init_begin, *i);
		quick_sort_pro_safe<T>(init_begin, i);
		quick_sort_pro_safe<T>(i + 1, init_end);
	}
}

/**
 * quick sort pro safe (that takes two arguments) (pointer)
 * The safe version that can deal with special circumtances better.
 * Argument 1: the begin iterator
 * Argument 2: the end iterator
 * return void
 */
template<typename T>
void quick_sort_pro_safe(T* i, T* j)
{
	if (j - i <= 1) return;
	else if (j - i == 2)
	{
		if (*i > * (j - 1))
		{
			my_swap(*i, *(j - 1));
		}
	}
	else if (j - i <= 7)
	{
		// If the number is not large,
		// insertion sort can be more efficient.
		insertion_sort<T>(i, j);
		return;
	}
	else
	{
		// Choose the medium one of the three numbers,
		// in order to avoid the circumstance that
		// the standard number is too large or too small
		// when quicksort can be reduced from o(nlog(n)) to o(N^2).
		auto standard_number = medium<T>(i, j - 1, i + ((j - i) - 1) / 2);
		auto init_begin = i;
		auto init_end = j;

		auto Standard_defined = *standard_number;
		my_swap(*standard_number, *init_begin);
		while (i != j)
		{
			do { --j; } while (*j > Standard_defined && i < j);
			if (i == j) break;
			else
			{
				do { ++i; } while (*i < Standard_defined && i < j);
				my_swap(*i, *j);
			}
		}
		my_swap(*init_begin, *i);
		quick_sort_pro_safe<T>(init_begin, i);
		quick_sort_pro_safe<T>(i + 1, init_end);
	}
}

/**
 * counting sort one
 * Sort one digit of an integer.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void counting_sort_one(T& vec, int n)
{
	if (!check_type<T>(L"counting_sort_one can not be applied to non-integer value types.")) return;
	T bucket[10];
	size_t before_number[10]{ 0 };
	for (const auto& c : vec)
	{
		bucket[c / my_pow(10, n) % 10].push_back(c);
	}
	for (size_t i = 1; i != 10; i++)
	{
		before_number[i] = before_number[i - 1] + bucket[i - 1].size();
	}
	for (size_t i = 0; i != 10; i++)
	{
		for (size_t j = 0; j != bucket[i].size(); j++)
		{
			// store the numbers by sequence
			vec[before_number[i] + j] = bucket[i][j];
		}
	}
}

/**
 * counting sort one pro
 * Sort one digit of an integer in the binary form.
 * Must suppprt [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void counting_sort_one_pro(T& vec, size_t n)
{
	if (!check_type<T>(L"counting_sort_one_pro can not be applied to non-integer value types.")) return;
	T bucket[radix_index];
	size_t before_number[radix_index]{ 0 };
	for (const auto& c : vec)
	{
		bucket[c >> (n * radix_binary) & (radix_index - 1)].push_back(c);
	}
	for (size_t i = 1; i != radix_index; i++)
	{
		before_number[i] = before_number[i - 1] + bucket[i - 1].size();
	}
	for (size_t i = 0; i != radix_index; i++)
	{
		for (size_t j = 0; j != bucket[i].size(); j++)
		{
			// store the numbers by sequence
			vec[before_number[i] + j] = bucket[i][j];
		}
	}
}

/**
 * counting sort one pro heap1
 * One way to sort one digit of an integer in the binary form using HeapVector
 * Must support [].
 * Do not support 'list'.
 * return void
 */
template<typename T>
void counting_sort_one_pro_heap1(T& vec, size_t n)
{
	if (!check_type<T>(L"counting_sort_one_pro_heap1 can not be applied to non-integer value types.")) return;
	if (vec.size() < 7)
	{
		// If the number is not large,
		// insertion sort can be more efficient.
		insertion_sort<T>(vec.begin(), vec.end());
	}
	else
	{
		Heap_Vector<typename T::value_type> bucket[radix_index];
		size_t before_number[radix_index]{ 0 };
		for (const auto& c : vec)
		{
			// equivalent to:
			// bucket[c / my_pow(radix_index, n) % radix_index].push_back(c);
			// but using the operator >> and & can be more efficient
			bucket[c >> (n * radix_binary) & (radix_index - 1)].push_back(c);
		}
		for (size_t i = 1; i != radix_index; i++)
		{
			before_number[i] = before_number[i - 1] + bucket[i - 1].size();
		}
		for (size_t i = 0; i != radix_index; i++)
		{
			for (size_t j = 0; j != bucket[i].size(); j++)
			{
				// store the numbers by sequence
				vec[before_number[i] + j] = bucket[i][j];
			}
		}
	}
}

/**
 * counting sort one pro heap2
 * One way to sort one digit of an integer in the binary form using dynamic array.
 * Must support [].
 * return void
 */
template<typename T>
void counting_sort_one_pro_heap2(T& vec, int n)
{
	if (!check_type<T>(L"counting_sort_ont_pro_heap2 can not be applied to non-integer value types.")) return;
	typename T::value_type** bucket = new typename T::value_type* [radix_index]; // define a dynamic array of arrays
	for (size_t i = 0; i != radix_index; i++)
		bucket[i] = new int[vec.size()];     // define a dynamic array
	size_t element_number[radix_index]{ 0 }; // initialize to 0
	size_t before_number[radix_index]{ 0 };  // initialize to 0
	for (const auto& c : vec)
	{
		// equivalent to:
		// int bucket_number = c / my_pow(radix_index, n) % radix_index;
		// but using the operator >> and & can be more efficient
		auto bucket_number = c >> (n * radix_binary) & (radix_index - 1);
		// increment the element_number at the same time
		bucket[bucket_number][element_number[bucket_number]++] = c;
	}
	for (size_t i = 1; i != radix_index; i++)
	{
		before_number[i] = before_number[i - 1] + element_number[i - 1];
	}
	for (size_t i = 0; i != radix_index; i++)
	{
		for (size_t j = 0; j != element_number[i]; j++)
		{
			// store the numbers by sequence
			vec[before_number[i] + j] = bucket[i][j];
		}
	}
	for (size_t i = 0; i != radix_index; i++)
		delete[] bucket[i]; // free the dynamic arrays
}

/**
 * counting sort multi
 * Sort multi digits of an integer.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void counting_sort_multi(T& vec, size_t n)
{
	if (!check_type<T>(L"counting_sort_multi can not be applied to non-integer value types.")) return;
	T bucket[10];
	size_t before_number[10]{ 0 };
	for (const auto& c : vec)
	{
		bucket[c / my_pow(10, n) % 10].push_back(c);
	}

	if (n)
	{
		for (auto& c : bucket)
		{
			counting_sort_multi<T>(c, n - 1);
		}
	}

	for (size_t i = 1; i != 10; i++)
	{
		before_number[i] = before_number[i - 1] + bucket[i - 1].size();
	}
	for (size_t i = 0; i != 10; i++)
	{
		for (size_t j = 0; j != bucket[i].size(); j++)
		{
			vec[before_number[i] + j] = bucket[i][j]; // store the numbers by sequence
		}
	}
}

/**
 * counting sort multi pro
 * Sort multi digits of an integer in the binary form.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void counting_sort_multi_pro(T& vec, size_t n)
{
	if (!check_type<T>(L"LSD_sort_pro_heap1 can not be applied to non-integer value types.")) return;

	T bucket[radix_index];
	size_t before_number[radix_index]{ 0 };
	for (auto c : vec)
	{
		// equivalent to:
		// bucket[c / my_pow(radix_index, n) % radix_index].push_back(c);
		// but using the operator >> and & can be more efficient
		bucket[c >> (n * radix_binary) & (radix_index - 1)].push_back(c);
	}
	if (n)
	{
		for (auto& c : bucket)
		{
			counting_sort_multi_pro<T>(c, n - 1);
		}
	}
	for (size_t i = 1; i != radix_index; i++)
	{
		before_number[i] = before_number[i - 1] + bucket[i - 1].size();
	}
	for (size_t i = 0; i != radix_index; i++)
	{
		for (size_t j = 0; j != bucket[i].size(); j++)
		{
			vec[before_number[i] + j] = bucket[i][j]; // store the numbers by sequence
		}
	}
}

/**
 * LSD sort
 * Used to sort integers.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void LSD_sort(T& vec)
{
	if (!check_type<T>(L"LSD_sort can not be applied to non-integer value types.")) return;
	auto max_one = vec[0], min_one = vec[0];
	for (const auto& c : vec)
	{
		max_one = my_max(max_one, c);
		min_one = my_min(min_one, c);
	}
	if (!isUnsigned<T>())
	{
		max_one -= min_one; // every number is no less than zero now
		for (auto& c : vec)
		{
			c -= min_one;
		}
	}
	for (int i = 0; i != std::to_string(max_one).length(); i++)
	{
		counting_sort_one<T>(vec, i);
	}
	for (auto& c : vec)
	{
		// return the elements to the original value
		c += min_one;
	}
}

/**
 * LSD sort pro
 * Used to sort integers.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void LSD_sort_pro(T& vec)
{
	if (!check_type<T>(L"LSD_sort_pro can not be applied to non-integer value types.")) return;
	auto max_one = vec[0], min_one = vec[0];
	for (const auto& c : vec)
	{
		max_one = my_max(max_one, c);
		min_one = my_min(min_one, c);
	}
	if (!isUnsigned<T>())
	{
		max_one -= min_one; // every number is no less than zero now
		for (auto& c : vec)
		{
			c -= min_one;
		}
	}
	// If max_one is zero, log(max_one) will be illegal.
	// But this time, it is already sorted
	// as all the elements are equal.
	if (max_one)
	{
		for (int i = 0; i != static_cast<typename T::value_type>(log(max_one) / log(radix_index)) + 1; i++)
		{
			counting_sort_one_pro<T>(vec, i);
		}
	}
	if (!isUnsigned<T>())
	{
		for (auto& c : vec)
		{
			// return the elements to the original value
			c += min_one;
		}
	}
}

/**
 * MSD sort
 * Used to sort integers.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void MSD_sort(T& vec)
{
	if (!check_type<T>(L"MSD_sort can not be applied to non-integer value types.")) return;
	auto max_one = vec[0], min_one = vec[0];
	for (const auto& c : vec)
	{
		max_one = my_max(max_one, c);
		min_one = my_min(min_one, c);
	}

	max_one -= min_one; // every number is no less than zero now
	for (auto& c : vec)
	{
		c -= min_one;
	}

	counting_sort_multi<T>(vec, std::to_string(max_one).length() - 1);
	for (auto& c : vec)
	{
		// return the elements to the original value
		c += min_one;
	}
}

/**
 * MSD sort pro
 * Used to sort integers.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void MSD_sort_pro(T& vec)
{
	if (!check_type<T>(L"MSD_sort_pro can not be applied to non-integer value types.")) return;
	auto max_one = vec[0], min_one = vec[0];
	for (const auto& c : vec)
	{
		max_one = my_max(max_one, c);
		min_one = my_min(min_one, c);
	}
	if (!isUnsigned<T>())
	{
		max_one -= min_one; // every number is no less than zero now
		for (auto& c : vec)
		{
			c -= min_one;
		}
	}
	// If max_one is zero, log(max_one) will be illegal.
	// But this time, it is already sorted
	// as all the elements are equal.
	if (max_one) // if (max_one != 0)
	{
		counting_sort_multi_pro<T>(vec, static_cast<int>(log(max_one) / log(radix_index)));
	}
	if (!isUnsigned<T>())
	{
		for (auto& c : vec)
		{
			// return the elements to the original value
			c += min_one;
		}
	}
}

/**
 * LSD sort pro heap1
 * Used to sort integers.
 * Must support [].
 * Do not support 'list'.
 * return void
 */
template<typename T>
void LSD_sort_pro_heap1(T& vec)
{
	if (!check_type<T>(L"LSD_sort_pro_heap1 can not be applied to non-integer value types.")) return;
	auto max_one = vec[0], min_one = vec[0];
	for (const auto& c : vec)
	{
		max_one = my_max(max_one, c);
		min_one = my_min(min_one, c);
	}
	if (!isUnsigned<T>())
	{
		max_one -= min_one; // every number is no less than zero now
		for (auto& c : vec)
		{
			c -= min_one;
		}
	}
	// If max_one is zero, log(max_one) will be illegal.
	// But this time, it is already sorted
	// as all the elements are equal.
	if (max_one)
	{
		for (int i = 0; i != static_cast<typename T::value_type>(log(max_one) / log(radix_index)) + 1; i++)
		{
			counting_sort_one_pro_heap1<T>(vec, i);
		}
	}
	if (!isUnsigned<T>())
	{
		for (auto& c : vec)
		{
			// return the elements to the original value
			c += min_one;
		}
	}
}

/**
 * LSD sort pro heap2
 * Used to sort integers.
 * Must support [].
 * Do not support 'list' and 'array'.
 * return void
 */
template<typename T>
void LSD_sort_pro_heap2(T& vec)
{
	if (!check_type<T>(L"MSD_sort_pro_heap2 can not be applied to non-integer value types.")) return;
	auto max_one = vec[0], min_one = vec[0];
	for (const auto& c : vec)
	{
		max_one = my_max(max_one, c);
		min_one = my_min(min_one, c);
	}
	if (!isUnsigned<T>())
	{
		max_one -= min_one; // every number is no less than zero now
		for (auto& c : vec)
		{
			c -= min_one;
		}
	}
	// If max_one is zero, log(max_one) will be illegal.
	// But this time, it is already sorted
	// as all the elements are equal.
	if (max_one) // if (max_one != 0)
	{
		for (int i = 0; i != static_cast<int>(log(max_one) / log(radix_index)) + 1; i++)
		{
			counting_sort_one_pro_heap2<T>(vec, i);
		}
	}
	if (!isUnsigned<T>())
	{
		for (auto& c : vec)
		{
			// return the elements to the original value
			c += min_one;
		}
	}
}

/**
 * heap adjust
 * adjust [i_beg, i_end) into max heap
 * when [i_beg + 1, i_end) is already adjusted
 * return void
 */
template<typename T>
void heap_adjust(std::vector<T>& vec, size_t i_beg, size_t i_end)
{
	auto rc = vec[i_beg];
	for (size_t i = 2 * i_beg; i < i_end; i *= 2)
	{
		if (i + 1 != i_end && vec[i] < vec[i + 1]) i++; // i is now the larger one of two children
		if (rc >= vec[i]) break;                   // at the right place
		vec[i_beg] = vec[i];
		i_beg = i;
	}
	vec[i_beg] = rc; // insert the element here
}

/**
 * create heap
 * create the heap (adjust all)
 * return void
 */
template<typename T>
void create_heap(std::vector<T>& vec)
{
	auto vec_size = vec.size();
	for (auto i = vec_size / 2; i != 0; i--)
	{
		heap_adjust(vec, i - 1, vec_size);
	}
}

/**
 * heap sort
 * Argument 1: the begin iterator
 * Argument 2: the end iterator
 * return void
 */
template<typename T>
void heap_sort(vec_iter<T> i, vec_iter<T> j)
{
	std::vector<typename T::value_type> heap(i, j);
	create_heap(heap);
	for (size_t index = heap.size(); index > 0; index--)
	{
		my_swap(heap[0], heap[index - 1]); // swap the top element with the last element
		heap_adjust(heap, 0, index - 1);   // adjust the remaining elements of heap into max heap
	}
	auto heap_iter = heap.begin();
	for (auto iter = i; iter != j; iter++, heap_iter++)
	{
		*iter = *heap_iter;
	}
}

/**
 * heap sort
 * Argument 1: the begin pointer
 * Argument 2: the end pointer
 * return void
 */
template<typename T>
void heap_sort(T* i, T* j)
{
	std::vector<T&> heap;
	for (auto iter = i; i != j; iter++)
	{
		heap.push_back(*iter);
	}
	create_heap(heap);
	for (size_t index = heap.size(); index > 0; index--)
	{
		my_swap(heap[0], heap[index - 1]); // swap the top element with the last element
		heap_adjust(heap, 0, index - 1);   // adjust the remaining elements of heap into max heap
	}
}

/**
 * bubble sort
 * Only for containers with iterators
 * return void
 */
template<typename T>
void bubble_sort(T& vec)
{
	bubble_sort<T>(vec.begin(), vec.end());
}

/**
 * insertion sort
 * Only for containers with iterators
 * return void
 */
template<typename T>
void insertion_sort(T& vec)
{
	insertion_sort<T>(vec.begin(), vec.end());
}

/**
 * quick sort
 * Only for containers with iterators
 * return void
 */
template<typename T>
void quick_sort(T& vec)
{
	quick_sort<T>(vec, vec.begin(), vec.end());
}

/**
 * quick sort pro
 * Only for containers with iterators
 * return void
 */
template<typename T>
void quick_sort_pro(T& vec)
{
	quick_sort_pro<T>(vec.begin(), vec.end());
}

/**
 * quick sort pro safe
 * Only for containers with iterators
 * return void
 */
template<typename T>
void quick_sort_pro_safe(T& vec)
{
	quick_sort_pro_safe<T>(vec.begin(), vec.end());
}

/**
 * heap sort
 * Only for containers with iterators
 * return void
 */
template<typename T>
void heap_sort(T& vec)
{
	heap_sort<T>(vec.begin(), vec.end());
}

#endif // !_TVJ_SORT_

// ALL RIGHTS RESERVED (C) 2021 Teddy van Jerry