#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int GAP = INT_MAX;

// Binary search excluding gaps
int binary_search_gapless(std::vector<int>& arr, int key)
{
    // Store elements into temp vector with no gaps
    std::vector<int> temp;
    for (int val : arr)
        if (val != GAP)
            temp.push_back(val);

    auto it = std::lower_bound(temp.begin(), temp.end(), key);
    return it - temp.begin();
}

// Find actual insert position in unsorted list with gaps
int find_insert_index(std::vector<int>& arr, int logical_index)
{
    int cnt = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != GAP) {
            if (cnt == logical_index)
                return i;
            cnt++;
        }
    }
    return arr.size();
}

void insert(std::vector<int>& arr, int key)
{
    int logical_pos = binary_search_gapless(arr, key);
    int insert_pos = find_insert_index(arr, logical_pos);

    // Find the pos to insert
    int pos = insert_pos;
    while (pos < arr.size() && arr[pos] != GAP)
        pos++;

    if (pos == arr.size())
        arr.push_back(GAP);

    for (int i = pos; i > insert_pos; --i)
        arr[i] = arr[i - 1];

    arr[insert_pos] = key;
}

// Add gaps to original array
void rebalance(std::vector<int>& arr, int begin, int end)
{
    std::vector<int> rebalanced((end - begin + 1) * 2, GAP);
    int r = end;
    int w = (end - begin) * 2;

    while (r >= begin) {
        rebalanced[w] = arr[r];
        rebalanced[w + 1] = GAP;
        r--;
        w -= 2;
    }

    arr = rebalanced;
}

void library_sort(std::vector<int>& arr)
{
    if (arr.empty())
        return;

    int n = arr.size();
    std::vector<int> S; // new array of n gaps
    S.push_back(arr[0]);

    int inserted = 1;
    int level = 1;

    while (inserted < n) {
        int start = std::pow(2, level - 1);
        int end = std::min((int)std::pow(2, level), n);

        rebalance(S, 0, S.size() - 1);

        for (int i = start; i < end && inserted < n; ++i) {
            insert(S, arr[inserted]);
            inserted++;
        }

        level++;
    }

    // Remove gaps and put sorted list to original array
    arr.clear();
    for (int val : S) {
        if (val != GAP)
            arr.push_back(val);
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

    // Library sort
    library_sort(unsorted_list);

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
