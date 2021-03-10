# TVJ_Sort
It provides many kinds of sort functions for STL library containers and arrays.

## Functions
The table below provides the table of parameters functions support.
|Functions|Normal Array Pointers|STL Containers|STL Containers iterators|STL Containers and their iterators|
|-|:-:|:-:|:-:|:-:|
|`bubble_sort`|$\bullet$|$\circ$|$\circ$|$\times$|
|`insertion_sort`|$\bullet$|$\circ$|$\circ$|$\times$|
|`quick_sort`|$\bullet$|$\circ$|$\times$|$\circ$|
|`quick_sort_pro`|$\bullet$|$\circ$|$\circ$|$\times$|
|`quick_sort_pro_safe`|$\bullet$|$\circ$|$\circ$|$\times$|
|`LSD_sort`|$\times$|$\circ$|$\times$|$\times$|
|`LSD_sort_pro`|$\times$|$\circ$|$\times$|$\times$|
|`LSD_sort_pro_heap1`|$\times$|$\circ$|$\times$|$\times$|
|`LSD_sort_pro_heap2`|$\times$|$\circ$|$\times$|$\times$|
|`MSD_sort`|$\times$|$\circ$|$\times$|$\times$|
|`MSD_sort-pro`|$\times$|$\circ$|$\times$|$\times$|
|(`STL sort`)|$\bullet$|$\times$|$\circ$|$\times$|

> Note: $\bullet$ means support, $\times$ means no support, $\circ$ means support some.

The following table gives the STL container that functions support.

|Functions|vector|deque|list|forward_list|array|
|-|:-:|:-:|:-:|:-:|:-:|
|`bubble_sort`|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|
|`insertion_sort`|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|
|`quick_sort`|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|
|`quick_sort_pro`|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|
|`quick_sort_pro_safe`|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|
|`LSD_sort`|$\bullet$|$\bullet$|$\times$|$\times$|$\times$|
|`LSD_sort_pro`|$\bullet$|$\bullet$|$\times$|$\times$|$\times$|
|`LSD_sort_pro_heap1`|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|
|`LSD_sort_pro_heap2`|$\bullet$|$\bullet$|$\times$|$\times$|$\times$|
|`MSD_sort`|$\bullet$|$\bullet$|$\times$|$\times$|$\times$|
|`MSD_sort-pro`|$\bullet$|$\bullet$|$\times$|$\times$|$\times$|
|(`STL sort`)|$\bullet$|$\bullet$|$\times$|$\times$|$\bullet$|

> Note: $\bullet$ means support, $\times$ means no support.

## Note
* `LSD_sort`, `LSD_sort_pro`, `LSD_sort_pro_heap1`, `LSD_sort_pro_heap2`, `MSD_sort`, `MSD_sort-pro` only supports integer elements (Including `int`, `long long`, `unsigned char` and etc.).
* Using STL container iterators, container element has to be specified in the function.
* Here are two sample `.cpp` files, which can be an easy introduction to TVJ_Sort.
* This project uses TVJ_Timer.h in my repository [TVJ_Timer](https://github.com/Teddy-van-Jerry/TVJ_Timer).