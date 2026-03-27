#!/bin/bash

echo "algorithm,scenario,graph_type,n,m,edges,run,runtime_ms" > tarjan_results.csv

for n in 250 500 1000 2000 4000
do
  edges=$((8*n))
  file="benchmark_data/scc/scc_${n}.dat"

  for graph_type in linked matrix
  do
    for run in 1 2 3 4 5
    do
      runtime=$(./graph_scc --$graph_type --silent "$file" | grep "Runtime_ms" | awk '{print $2}')
      echo "scc,standard,$graph_type,$n,,$edges,$run,$runtime" >> tarjan_results.csv
    done
  done
done