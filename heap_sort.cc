#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// To heapify a subtree rooted with node i which is an index in arr[]
void heapify(std::vector<int>& arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heap_sort(std::vector<int>& arr)
{
    int n = arr.size();

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
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

    // Heap sort
    heap_sort(unsorted_list);

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
