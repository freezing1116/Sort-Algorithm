#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int RUN = 32;

// This function sorts array from left index to right index which is of size atmost RUN
void insertion_sort(std::vector<int>& arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merges the sorted runs
void merge(std::vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Iterative Timsort function to sort the array[0...n-1] (similar to merge sort)
void tim_sort(std::vector<int>& arr, int n)
{

    // Sort individual subarrays of size RUN
    for (int i = 0; i < n; i += RUN)
        insertion_sort(arr, i, std::min((i + RUN - 1), (n - 1)));

    // Start merging from size RUN (or 32)
    // It will merge to form size 64, then 128, 256 and so on ....
    for (int size = RUN; size < n; size = 2 * size) {

        // pick starting point of left sub array. We are going to merge arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we increase left by 2*size
        for (int left = 0; left < n; left += 2 * size) {

            // Find ending point of left sub array mid+1 is starting point of right sub array
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            // merge sub array arr[left.....mid] & arr[mid+1....right]
            if (mid < right)
                merge(arr, left, mid, right);
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

    // Tim sort
    tim_sort(unsorted_list, unsorted_list.size());

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
