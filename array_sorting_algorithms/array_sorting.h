/*
	Tragen47
	20.04.21
	Implementation of array sorting algorithms
*/

#pragma once

#include <iostream>
#include <vector>

namespace array_sorting {
	// tag dispatching
	template<typename T>
	struct is_vector : public std::false_type {};

	template<typename T, typename A>
	struct is_vector<std::vector<T, A>> : public std::true_type {};

// function overloads for static array and vector
#define INITIALISE_ALGORITHM_FUNCTION(sorting_algorithm)\
	template <typename T, size_t length>\
	constexpr std::enable_if_t<std::is_array<T>::value> sorting_algorithm(T (&source_array)[length])\
	/*
		Template for static arrays
	*/\
	{\
		if (!length) return;\
		SortingAlgorithm(source_array, length);\
	}\
	\
	template <typename T>\
	constexpr std::enable_if_t<is_vector<T>::value> sorting_algorithm(T& source_array)\
	/*
		Template for vectors
	*/\
	{\
		if (!source_array.size()) return;\
		sorting_algorithm(source_array, source_array.size());\
	}

	template<typename T>
	void insertion_sort(T&& source_array, const size_t leftIndex, const size_t rightIndex)
	{
		for (size_t i = leftIndex + 1; i <= rightIndex; ++i) {
			auto key = source_array[i];
			size_t j;
			/*
				Move array elements, which are
				greater than key, to one position ahead
				of their current position
			*/
			for (j = i - 1; j < SIZE_MAX /* SIZE_MAX stands after decrementing of 0 value */ &&
				j >= leftIndex && source_array[j] > key; --j)
				source_array[j + 1] = source_array[j];
			source_array[j + 1] = key;
		}
	}

	template<typename T>
	constexpr void insertion_sort(T&& source_array, const size_t length)
	{
		insertion_sort(source_array, 0, length - 1);
	}

	template<typename T>
	void bubble_sort(T&& source_array, const size_t length)
	{
		// set the rightmost index
		for (size_t rightIndex = length - 1; rightIndex >= 1; rightIndex--)
			for (size_t i = 1; i <= rightIndex; ++i)
				if (source_array[i - 1] > source_array[i])
					std::swap(source_array[i - 1], source_array[i]);
	}

	template<typename T>
	void counting_sort(T&& source_array, const size_t length, /* the max possible value of elements of the array */ const size_t max)
	{
		// allocate a temp array with indexes from 0 to max value and fill it with zeroes
		size_t* temp = new size_t[max + 1]();

		// calculate the elements quantity in the source array
		for (size_t i = 0; i < length; ++i)
			++temp[source_array[i]];

		size_t counter = 0; // counter for the source array

		// iterate through the temp array
		for (size_t i = 0; i <= max; ++i)
			for (size_t j = 0; j < temp[i]; ++j)
				// fill the source array in the ascending order
				source_array[counter++] = i;

		delete[] temp;
	}

	inline void counting_sort(size_t* source_array, /* the max value of an element of the array */ const size_t max)
	/*
		Template for dynamic arrays
	*/
	{
		counting_sort(source_array, _msize(source_array) / sizeof(size_t), max);
	}

	inline void counting_sort(std::vector<size_t>& source_array, /* the max value of an element of the array */ const size_t max)
	/*
		Template for static arrays
	*/
	{
		counting_sort(source_array, source_array.size(), max);
	}

	template<size_t length>
	constexpr void counting_sort(size_t source_array[length], /* the max value of an element of the array */ const size_t max)
	/*
		Template for vectors
	*/
	{
		counting_sort(source_array, length, max);
	}

	template<typename T>
	void selection_sort(T&& source_array, const size_t length)
	{
		for (size_t left_index = 0; left_index < length - 1; ++left_index) {
			size_t min_index = left_index; // an index of the min element

			// find the min element
			for (size_t i = left_index + 1; i < length; ++i)
				if (source_array[i] < source_array[min_index])
					min_index = i;

			// set the min element in the beginning of the array to the left border
			std::swap(source_array[left_index], source_array[min_index]);
		}
	}

	template<typename T>
	void binary_insertion_sort(T&& source_array, const size_t length)
	{
		for (size_t left_index = 0; left_index < length - 1; ++left_index) {
			size_t left = 0;
			size_t right = left_index;

			while (left < right) {
				size_t mid = left + (right - left) / 2;

				if (source_array[mid] > source_array[left_index + 1])
					right = mid;
				else
					left = mid + 1;
			}

			// if new element on the right is lower than the element in the sorted part
			if (source_array[left_index + 1] < source_array[left]) {
				// then insert the new element in the appropriate place
				auto temp = source_array[left_index + 1];
				for (size_t j = left_index; j < SIZE_MAX /* SIZE_MAX stands after decrementing of 0 value */ &&
					j >= left; --j)
					source_array[j + 1] = source_array[j];
				source_array[left] = temp;
			}
		}
	}

	template<typename T>
	void exchange_sort(T&& source_array, const size_t length)
	{
		bool found_dif = true; // the boolean which shows that the elements of the array are not sorted
		while (found_dif) {
			found_dif = false;

			// iterate through the array
			for (size_t i = 1; i < length; ++i)
				// if elements are not sorted
				if (source_array[i - 1] > source_array[i]) {
					found_dif = true;
					std::swap(source_array[i - 1], source_array[i]);
				}
		}
	}

	template<typename T>
	void shaker_sort(T&& source_array, const size_t length)
	{
		size_t left_mark = 1; // the left border
		size_t right_mark = length - 1; // the right border

		// until the left and the right borders intersected
		while (left_mark <= right_mark) {
			// iterate through the array from the right to the left
			for (size_t i = right_mark; i >= left_mark; --i)
				if (source_array[i - 1] > source_array[i])
					std::swap(source_array[i - 1], source_array[i]);
			++left_mark;

			// iterate through the array from the left to the right
			for (size_t i = left_mark; i <= right_mark; ++i)
				if (source_array[i - 1] > source_array[i])
					std::swap(source_array[i - 1], source_array[i]);
			--right_mark;
		}
	}

	template<typename T>
	void hoar_sort(T&& source_array, const size_t first_index, const size_t last_index)
	{
		if (first_index >= last_index) return;

		// pick a pivot element, which is a median of the first, last and middle elements of the array
		auto pivot = std::min(std::max(source_array[first_index],
			source_array[first_index / 2 + last_index / 2 + (first_index % 2 + last_index % 2) / 2]),
			source_array[last_index]);

		// reorder the array so that all the elements with values less than the pivot come before the pivot,
		// while all the elements with values greater than the pivot come after it (equal values can go either way)
		// after this partitioning, the pivot is in its final position
		size_t i = first_index, j = last_index;
		while (i < j && j < SIZE_MAX /* SIZE_MAX stands after decrementing of 0 value */) {
			while (source_array[i] < pivot)
				++i;

			while (source_array[j] > pivot)
				--j;

			if (i <= j)
				std::swap(source_array[i++], source_array[j--]);
		}

		// recursive calls
		if (first_index < j && j < SIZE_MAX /* SIZE_MAX stands after decrementing of 0 value */)
			hoar_sort(source_array, first_index, j);

		if (i < last_index)
			hoar_sort(source_array, i, last_index);
	}

	// quick sort
	template<typename T>
	constexpr void hoar_sort(T&& source_array, const size_t length)
	{
		hoar_sort(source_array, 0, length - 1);
	}

	template<typename T>
	void shell_sort(T&& source_array, const size_t length)
	{
		// set step interval with length equal to the half of the length of the array
		// and halve it with every iteration
		for (size_t step = length / 2; step > 0; step /= 2)
			// compare the elements which are spaced apart with the step interval
			for (size_t i = step; i < length; ++i) {
				auto temp = source_array[i];
				size_t j;

				// move the max element through the step intervals in the beginning
				for (j = i; j >= step && temp < source_array[j - step]; j -= step)
					source_array[j] = source_array[j - step];
				source_array[j] = temp;
			}
	}

	template<typename T>
	void merge_sort(T&& source_array, size_t left, size_t right)
	{
		if (left == right)
			return; // borders interlocked

		size_t mid = left / 2 + right / 2 + (left % 2 + right % 2) / 2; // count the middle index of the array

		// call the function recursively for every half of the array
		merge_sort(source_array, left, mid);
		merge_sort(source_array, mid + 1, right);

		typename std::remove_reference<T>::type temp; // secondary array
		if constexpr (is_vector<std::remove_reference<T>::type>::value)
			temp.resize(right - left + 1);

		if constexpr (std::is_pointer<std::remove_reference<T>::type>::value)
			temp = new typename std::remove_reference<T>::type[right - left + 1];
		
		// for every element of the secondary array
		for (size_t step = 0, i = left /* the beginning of the first iteration loop */,
			j = mid + 1 /* the beginning of the second iteration loop */; 
			step < (right - left + 1); step++)
			
			// insert the min element of two iteration loops into the secondary array
			temp[step] = (j > right) || (i <= mid && source_array[i] <= source_array[j]) ?
				source_array[i++] : source_array[j++];

		// copy the resulted sorted sequence to the source array
		for (size_t step = 0; step < (right - left + 1); step++)
			source_array[left + step] = temp[step];

		if constexpr (std::is_pointer<std::remove_reference<T>::type>::value)
			delete[] temp;
	}

	template<typename T>
	constexpr void merge_sort(T&& source_array, const size_t length)
	{
		merge_sort(source_array, 0, length - 1);
	}

	// the function of the "sifting" through the heap - the allocation of the binary heap (the pyramid)
	template<typename T>
	void sift_down(T&& source_array, const size_t root, const size_t length)
	{
		size_t max_child = root; // an index of the max descendant

		// if the iteration is in the last row
		// record the left descendant
		// else record the index of the max descendant of two
		auto left = root * 2 + 1;
		auto right = root * 2 + 2;

		if (left < length && source_array[left] > source_array[max_child])
			max_child = left;
		if (right < length && source_array[right] > source_array[max_child])
			max_child = right;

		// if the root is not the max_child
		if (root != max_child) {
			std::swap(source_array[root], source_array[max_child]);
			sift_down(source_array, max_child, length);
		}
	}

	template<typename T>
	void heap_sort(T&& source_array, const size_t length)
	{
		if (length <= 1) return;

		// form the lowest row of the heap
		for (int i = (length / 2) - 1; i >= 0; --i)
			sift_down(source_array, i, length);

		// sift other elements through the heap
		for (size_t i = length - 1; i < SIZE_MAX /* SIZE_MAX stands after decrementing of 0 value */; --i) {
			std::swap(source_array[0], source_array[i]);
			sift_down(source_array, 0, i);
		}
	}

	// merge function merges the sorted arrays
	template<typename T>
	void tim_merge_sort(T&& source_array, const size_t left, const size_t middle, const size_t right)
	{
		// original array is divided in two parts left and right array
		const size_t left_array_length = middle - left + 1, right_array_length = right - middle;
		size_t* left_array = new size_t[left_array_length]; size_t* right_array = new size_t[right_array_length];
		for (size_t i = 0; i < left_array_length; ++i)
			left_array[i] = source_array[left + i];
		for (size_t i = 0; i < right_array_length; ++i)
			right_array[i] = source_array[middle + 1 + i];

		size_t i = 0;
		size_t j = 0;
		size_t k = left;

		// after comparing merge those two arrays in a larger sub array
		while (i < left_array_length && j < right_array_length)
			source_array[k++] = (left_array[i] <= right_array[j]) ? left_array[i++] : right_array[j++];

		// copy remaining elements of the left, if any
		while (i < left_array_length)
			source_array[k++] = left_array[i++];

		// copy remaining element of the right, if any
		while (j < right_array_length)
			source_array[k++] = right_array[j++];

		delete[] left_array;
		delete[] right_array;
	}

	const size_t run = 32;

	template<typename T>
	void tim_sort(T&& source_array, const size_t length)
	{
		// sort individual subarrays of run size
		for (size_t i = 0; i < length; i += run)
			insertion_sort(source_array, i, std::min(i + run - 1, length - 1));

		// start merging from size run (or 32)
		// it will merge to form size 64, then 128, 256 and so on
		for (size_t size = run; size < length; size <<= 1) {
			// pick starting point of the left sub array and merge source_array[left..left+size-1] and source_array[left+size, left+2*size-1]
			// after every merge increase the left array by 2*size
			for (size_t left = 0; left < length; left += 2 * size) {
				// find ending point of the left sub array mid+1 which is starting point of the right sub array
				size_t mid = left + size - 1;
				size_t right = std::min(left + 2 * size - 1, length - 1);

				// merge sub array source_array[left.....mid] & source_array[mid+1....right]
				if (mid < right)
					tim_merge_sort(source_array, left, mid, right);
			}
		}
	}

	template<typename T>
	void gnome_sort(T&& source_array, const size_t length)
	{
		if (length <= 1) return;
		size_t index = 0;

		while (index < length) {
			if (index == 0)
				++index;
			
			// if the current array element is larger than or equal to the previous array element then go one step right
			if (source_array[index] >= source_array[index - 1])
				++index;

			// if the current array element is smaller than the previous array element then swap these two elements and go one step backward
			else {
				std::swap(source_array[index], source_array[index - 1]);
				--index;
			}
		}
	}

	INITIALISE_ALGORITHM_FUNCTION(insertion_sort)
	INITIALISE_ALGORITHM_FUNCTION(bubble_sort)
	INITIALISE_ALGORITHM_FUNCTION(selection_sort)
	INITIALISE_ALGORITHM_FUNCTION(binary_insertion_sort)
	INITIALISE_ALGORITHM_FUNCTION(exchange_sort)
	INITIALISE_ALGORITHM_FUNCTION(shaker_sort)
	INITIALISE_ALGORITHM_FUNCTION(hoar_sort)
	INITIALISE_ALGORITHM_FUNCTION(shell_sort)
	INITIALISE_ALGORITHM_FUNCTION(merge_sort)
	INITIALISE_ALGORITHM_FUNCTION(heap_sort)
	INITIALISE_ALGORITHM_FUNCTION(tim_sort)
	INITIALISE_ALGORITHM_FUNCTION(gnome_sort)
}

// undefine identifier
#undef DECLARE_ALGORITHM_FUNCTION