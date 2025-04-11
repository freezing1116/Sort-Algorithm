#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Sorts array a[0..n-1] using Cocktail sort
void cocktail_sort(std::vector<int>& a, int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        // reset the swapped flag on entering the loop, because it might be true from a previous iteration
        swapped = false;

        // loop from left to right same as the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it can be used in the next stage
        swapped = false;

        // move the end point back by one, because item at the end is in its rightful spot
        --end;

        // from right to left, doing the same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
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

    // Cocktail sort
    cocktail_sort(unsorted_list, unsorted_list.size());

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
