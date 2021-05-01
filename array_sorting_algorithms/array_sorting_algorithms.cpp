/*
    Tragen47
    20.04.21
    The main project file
*/

#include "array_printing.h"
#include "array_sorting.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <assert.h>

template<typename ...Parameters>
void test_sorting_algorithm(std::vector<size_t>& vector_array, const std::string& algorithmName,
    void(*algorithm)(std::vector<size_t>&, const Parameters...), const Parameters&& ...params)
{
    auto temp_array = vector_array;
    // calculate sorting time
    auto begin = std::chrono::steady_clock::now();
    algorithm(temp_array, params...);
    auto end = std::chrono::steady_clock::now();
    std::cout << algorithmName << ":" << std::endl;
    array_printing::print_array(temp_array);
    std::cout << std::endl;

    // check the sorting algorithm
    std::vector<size_t> testArray = vector_array;
    std::sort(testArray.begin(), testArray.end());
    assert(temp_array == testArray);

    std::cout << "Time spent: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms"
        << std::endl << std::endl;
}

void test_sorting_algorithms(const size_t array_length)
{
    // initialize a vector with 10 random numbers between 0 and 99
    std::vector<size_t> vector_array;
    vector_array.resize(array_length);
    for (size_t i = 0; i < array_length; i++)
        vector_array[i] = std::rand() % 100;

    // print the array
    std::cout << "Unsorted array" << std::endl;
    for (size_t i = 0; i < array_length; i++)
        std::cout << vector_array[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    test_sorting_algorithm(vector_array, "Insertion sort", &array_sorting::insertion_sort);
    test_sorting_algorithm(vector_array, "Bubble sort", &array_sorting::bubble_sort);
    test_sorting_algorithm(vector_array, "Counting sort", &array_sorting::counting_sort,
        /* the max possible value of elements of the array */ static_cast<size_t>(100));
    test_sorting_algorithm(vector_array, "Selection sort", &array_sorting::selection_sort);
    test_sorting_algorithm(vector_array, "Binary insertion sort", &array_sorting::binary_insertion_sort);
    test_sorting_algorithm(vector_array, "Exchange sort", &array_sorting::exchange_sort);
    test_sorting_algorithm(vector_array, "Shaker sort", &array_sorting::shaker_sort);
    test_sorting_algorithm(vector_array, "Hoar sort", &array_sorting::hoar_sort);
    test_sorting_algorithm(vector_array, "Shell sort", &array_sorting::shell_sort);
    test_sorting_algorithm(vector_array, "Merge sort", &array_sorting::merge_sort);
    test_sorting_algorithm(vector_array, "Heap sort", &array_sorting::heap_sort);
    test_sorting_algorithm(vector_array, "Tim sort", &array_sorting::tim_sort);
    test_sorting_algorithm(vector_array, "Gnome sort", &array_sorting::gnome_sort);
}

int main()
{
    // use current time as the seed for the random generator
    std::srand(time(NULL));

    std::cout << "0 elements" << std::endl;
    test_sorting_algorithms(0);
    std::cout << std::endl;

    std::cout << "1 element" << std::endl;
    test_sorting_algorithms(1);
    std::cout << std::endl;

    std::cout << "2 elements" << std::endl;
    test_sorting_algorithms(2);
    std::cout << std::endl;

    std::cout << "10 elements" << std::endl;
    test_sorting_algorithms(10);
    std::cout << std::endl;

    std::cout << "100 elements" << std::endl;
    test_sorting_algorithms(100);
    std::cout << std::endl;

    system("PAUSE");
    return 0;
}