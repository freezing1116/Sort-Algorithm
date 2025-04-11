#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Ascending is default. For descending, put second argument true
vector<int> generate_sorted_data(int n, bool descending = false)
{
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1); // 1 ~ n

    if (descending) {
        std::reverse(nums.begin(), nums.end());
    }

    return nums;
}

// Create a Mersenne Twister random engine
mt19937 get_random_engine()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}

// Generate n random numbers array
vector<int> generate_random_data(int n, int lb, int ub)
{
    mt19937 rng = get_random_engine();
    uniform_int_distribution<int> dist(lb, ub);

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        nums[i] = dist(rng);
    }

    return nums;
}

// Generate a partially sorted array, default = 50%
vector<int> generate_partially_sorted_data(int n, double percent_unsorted = 0.5)
{
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1); // sorted

    int swap_count = static_cast<int>(n * percent_unsorted);

    mt19937 rng = get_random_engine();
    uniform_int_distribution<int> dist(0, n - 1);

    for (int i = 0; i < swap_count; ++i) {
        int a = dist(rng);
        int b = dist(rng);
        if (a != b)
            swap(nums[a], nums[b]);
    }

    return nums;
}

// Save a vector to a file
void save_vector_to_file(const vector<int>& nums, const string& filename)
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Cannot open file: " << filename << endl;
        return;
    }

    for (int x : nums)
        fout << x << "\n";

    fout.close();
    cout << "Saved vector to " << filename << ".\n";
}

int main()
{
    int option, n, lb, ub;
    string fname;

    cout << "Which type of input sequence?\n"
         << "1. Sorted Data\n"
         << "2. Random Data\n"
         << "3. Reverse Sorted Data\n"
         << "4. Partially Sorted Data\n"
         << "Option: ";
    cin >> option;

    cout << "How many random numbers do you want to generate? ";
    cin >> n;

    cout << "Enter the output file name: ";
    cin >> fname;

    if (option == 1) {
        vector<int> sorted = generate_sorted_data(n);
        save_vector_to_file(sorted, fname);
    } else if (option == 2) {
        cout << "What is the lower bound of the numbers? ";
        cin >> lb;

        cout << "What is the upper bound of the numbers? ";
        cin >> ub;

        vector<int> random = generate_random_data(n, lb, ub);
        save_vector_to_file(random, fname);
    } else if (option == 3) {
        vector<int> reverse_sorted = generate_sorted_data(n, true);
        save_vector_to_file(reverse_sorted, fname);
    } else if (option == 4) {
        vector<int> partially_sorted = generate_partially_sorted_data(n);
        save_vector_to_file(partially_sorted, fname);
    }

    return 0;
}
