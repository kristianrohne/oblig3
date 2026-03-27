#!/bin/bash
set -e

echo "algorithm,scenario,graph_type,n,m,edges,run,runtime_ms" > diamond_fixed_results.csv
echo "algorithm,scenario,graph_type,n,m,edges,run,runtime_ms" > diamond_growing_results.csv

# Fixed m
for n in 250 500 1000 2000 4000
do
  m=10
  graph_file="benchmark_data/diamond_fixed/d_${n}.dat"
  query_file="benchmark_data/diamond_fixed/q_${n}.dat"

  for graph_type in linked matrix
  do
    for run in 1 2 3 4 5
    do
      runtime=$(./graph_diamond --$graph_type --silent "$graph_file" "$query_file" | grep "Runtime_ms" | awk '{print $2}')
      echo "diamond,fixed_m,$graph_type,$n,$m,,$run,$runtime" >> diamond_fixed_results.csv
    done
  done
done

# Growing m
for n in 250 500 1000 2000 4000
do
  case $n in
    250) m=4 ;;
    500) m=6 ;;
    1000) m=8 ;;
    2000) m=10 ;;
    4000) m=12 ;;
  esac

  graph_file="benchmark_data/diamond_growing/dgrow_${n}.dat"
  query_file="benchmark_data/diamond_growing/qgrow_${n}.dat"

  for graph_type in linked matrix
  do
    for run in 1 2 3 4 5
    do
      runtime=$(./graph_diamond --$graph_type --silent "$graph_file" "$query_file" | grep "Runtime_ms" | awk '{print $2}')
      echo "diamond,growing_m,$graph_type,$n,$m,,$run,$runtime" >> diamond_growing_results.csv
    done
  done
done