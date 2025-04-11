#!/bin/bash

cd "$(dirname "$0")"/..

algorithms=(
    bubble_sort
    # insertion_sort
    # selection_sort
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
    executable="./$algo"
    if [[ ! -x "$executable" ]]; then
        echo "❌ Cannot execute '$executable'"
        continue
    fi

    for dir in "${testcase_dirs[@]}"; do
        if [[ ! -d $dir ]]; then
            echo "❌ Testcase directory '$dir' not found"
            continue
        fi

        csv="results/${algo}_${dir}.csv"
        echo "testcase,time(ms)" > "$csv"

        for input in $dir/*.txt; do
            name=$(basename "$input" .txt)
            echo "▶️  $algo on $input"

            TIMEFORMAT="%R"
            time_in_seconds=$( { time "$executable" "$input" > /dev/null; } 2>&1 )
            time_in_ms=$(echo "$time_in_seconds * 1000" | bc)

            echo "$name,$time_in_ms" >> "$csv"
        done
    done
done
