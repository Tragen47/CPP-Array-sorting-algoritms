/*
	Tragen47
	20.04.21
	Implementation of array printing methods
*/

#pragma once

#include <iostream>
#include <vector>

namespace array_printing {
	template<typename T>
	struct is_vector : public std::false_type {};
	
	template<typename T, typename A>
	struct is_vector<std::vector<T, A>> : public std::true_type {};

	template<typename T>
	void print_array(T&& source_array, const size_t length)
	{
		for (size_t i = 0; i < length; ++i)
			std::cout << source_array[i] << " ";
	}

	template <typename T, size_t length>
	constexpr std::enable_if_t<std::is_array<T>::value> print_array(const T(&source_array)[length])
	/*
		Template for static arrays
	*/
	{
		print_array(source_array, length);
	}

	template <typename T>
	constexpr std::enable_if_t<is_vector<T>::value> print_array(const T& source_array)
	/*
		Template for vectors
	*/
	{
		print_array(source_array, source_array.size());
	}
}