#!/bin/bash

cd "$(dirname "$0")"/..

algorithms=(
    insertion_sort
    # selection_sort
    # bubble_sort
    # heap_sort
    # merge_sort
    # quick_sort
    # library_sort
    # tim_sort
    # cocktail_sort
    # comb_sort
    # tournament_sort
    # intro_sort
)

testcase_dirs=(
    testcases_1K
    testcases_10K
    testcases_100K
    testcases_1M
)

mkdir -p results

for algo in "${algorithms[@]}"; do
    if [[ ! -x ./$algo ]]; then
        echo "❌ impossible to run './$algo'"
        continue
    fi

    for dir in "${testcase_dirs[@]}"; do
        if [[ ! -d $dir ]]; then
            echo "❌ no directory '$dir' existed"
            continue
        fi

        for input in "$dir"/*.txt; do
            base_name=$(basename "$input" .txt)               # test_asce_1K
            csv="results/${algo}_${base_name}.csv"            # results/library_sort_test_asce_1K.csv

            echo "testcase,time(ms)" > "$csv"
            echo "▶️  $algo on $input"

            TIMEFORMAT="%R"
            time_in_seconds=$( { time ./$algo "$input" > /dev/null; } 2>&1 )
            time_in_ms=$(echo "$time_in_seconds * 1000" | bc)

            echo "$base_name,$time_in_ms" >> "$csv"
        done
    done
done