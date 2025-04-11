#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int partition(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[high]; // Choose the pivot
    int i = low; // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }

    // Move pivot after smaller elements and return its position
    std::swap(arr[i], arr[high]);
    return i;
}

int median_of_three(std::vector<int>& arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])
        std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high])
        std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high])
        std::swap(arr[mid], arr[high]);
    std::swap(arr[mid], arr[high]); // Move median to end
    return arr[high];
}

void quick_sort(std::vector<int>& arr, int low, int high)
{
    while (low < high) {
        int pivot = median_of_three(arr, low, high);
        int pi = partition(arr, low, high); // Can still reuse your partition

        // Recurse into smaller half to limit stack depth
        if (pi - low < high - pi) {
            quick_sort(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quick_sort(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "You need a file with unsorted numbers" << std::endl;
        return 1;
    }

    std::string unsorted_file_name = argv[1];

    std::ifstream unsorted_file(unsorted_file_name);
    if (!unsorted_file.is_open()) {
        std::cerr << "Cannot open the file" << std::endl;
        return 1;
    }

    std::vector<int> unsorted_list;
    int num;
    while (unsorted_file >> num) {
        unsorted_list.push_back(num);
    }

    std::vector<int> sorted_list = unsorted_list;
    std::sort(sorted_list.begin(), sorted_list.end());

    // Quick sort
    quick_sort(unsorted_list, 0, unsorted_list.size() - 1);

    // Check if it's correctly sorted
    if (unsorted_list == sorted_list) {
        std::cout << "Correctly sorted" << std::endl;
    } else {
        std::cout << "Expected output: " << std::endl;
        for (int i = 0; i < sorted_list.size(); i++)
            std::cout << sorted_list[i] << ' ';

        std::cout << '\n'
                  << "Actual output: " << std::endl;
        for (int i = 0; i < unsorted_list.size(); i++)
            std::cout << unsorted_list[i] << ' ';

        std::cout << '\n';
    }

    return 0;
}
