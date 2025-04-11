#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int INF = INT_MAX;

int winner(int pos1, int pos2, const std::vector<int>& tmp, int n)
{
    int u = pos1 >= n ? pos1 : tmp[pos1];
    int v = pos2 >= n ? pos2 : tmp[pos2];
    return (tmp[u] <= tmp[v]) ? u : v;
}

void create_tree(std::vector<int>& arr, std::vector<int>& tmp, int& value)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
        tmp[n + i] = arr[i];

    for (int i = 2 * n - 1; i > 1; i -= 2) {
        int k = i / 2;
        int j = i - 1;
        tmp[k] = winner(i, j, tmp, n);
    }

    value = tmp[tmp[1]];
    tmp[tmp[1]] = INF;
}

void recreate(std::vector<int>& arr, std::vector<int>& tmp, int& value)
{
    int n = arr.size();
    int i = tmp[1];

    while (i > 1) {
        int j, k = i / 2;
        if (i % 2 == 0 && i < 2 * n - 1)
            j = i + 1;
        else
            j = i - 1;
        tmp[k] = winner(i, j, tmp, n);
        i = k;
    }

    value = tmp[tmp[1]];
    tmp[tmp[1]] = INF;
}

void tournament_sort(std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> tmp(2 * n, 0);
    int value;
    create_tree(arr, tmp, value);

    std::vector<int> sorted(n);
    for (int i = 0; i < n; i++) {
        sorted[i] = value;
        recreate(arr, tmp, value);
    }
    arr = sorted;
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

    // Tournament sort
    tournament_sort(unsorted_list);

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
