#!/usr/bin/env bash
set -euo pipefail

OUT_CSV="benchmark_results.csv"
TMP_DIR="benchmark_data"

# Binaries
GEN_SCC="./gen_scc"
GEN_DIAMOND="./gen_diamond"
BIN_SCC="./graph_scc"
BIN_DIAMOND="./graph_diamond"

REPEATS=5

mkdir -p "$TMP_DIR"

echo "algorithm,scenario,graph_type,n,m,edges,run,runtime_ms" > "$OUT_CSV"

extract_runtime() {
    awk -F': ' '/Runtime_ms/ {print $2}' | tail -n 1
}

run_scc_case() {
    local n="$1"
    local edges="$2"
    local run_id="$3"

    local graph_file="${TMP_DIR}/scc_n${n}_e${edges}_r${run_id}.dat"

    "$GEN_SCC" "$n" "$edges" "$graph_file" >/dev/null

    for graph_type in linked matrix; do
        runtime=$("$BIN_SCC" "--${graph_type}" --silent "$graph_file" | extract_runtime)
        echo "scc,standard,$graph_type,$n,,$edges,$run_id,$runtime" >> "$OUT_CSV"
    done
}

run_diamond_case() {
    local scenario="$1"
    local n="$2"
    local m="$3"
    local run_id="$4"

    local graph_file="${TMP_DIR}/diamond_${scenario}_n${n}_m${m}_r${run_id}.dat"
    local query_file="${TMP_DIR}/diamond_${scenario}_n${n}_m${m}_r${run_id}.query"

    "$GEN_DIAMOND" "$n" "$m" "$graph_file" "$query_file" >/dev/null

    for graph_type in linked matrix; do
        runtime=$("$BIN_DIAMOND" "--${graph_type}" --silent "$graph_file" "$query_file" | extract_runtime)
        echo "diamond,$scenario,$graph_type,$n,$m,,$run_id,$runtime" >> "$OUT_CSV"
    done
}

echo "Running SCC benchmarks..."
for n in 250 500 1000 2000 4000; do
    edges=$((8 * n))
    for run_id in $(seq 1 "$REPEATS"); do
        run_scc_case "$n" "$edges" "$run_id"
    done
done

echo "Running diamond benchmarks, fixed m..."
for n in 250 500 1000 2000 4000; do
    m=10
    for run_id in $(seq 1 "$REPEATS"); do
        run_diamond_case "fixed_m" "$n" "$m" "$run_id"
    done
done

echo "Running diamond benchmarks, growing m..."
for pair in "250 4" "500 6" "1000 8" "2000 10" "4000 12"; do
    set -- $pair
    n="$1"
    m="$2"
    for run_id in $(seq 1 "$REPEATS"); do
        run_diamond_case "growing_m" "$n" "$m" "$run_id"
    done
done

echo "Done. Results saved to $OUT_CSV"