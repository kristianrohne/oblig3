import csv
from collections import defaultdict

input_file = "benchmark_results.csv"
output_file = "benchmark_averages.csv"

groups = defaultdict(list)

with open(input_file, newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        # Skip rows with empty runtime_ms
        if not row["runtime_ms"].strip():
            continue
        
        key = (
            row["algorithm"],
            row["scenario"],
            row["graph_type"],
            row["n"],
            row["m"],
            row["edges"],
        )
        groups[key].append(float(row["runtime_ms"]))

with open(output_file, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow([
        "algorithm", "scenario", "graph_type",
        "n", "m", "edges", "avg_runtime_ms"
    ])

    for key in sorted(groups, key=lambda x: (
        x[0], x[1], x[2], int(x[3]), int(x[4]) if x[4] else -1, int(x[5]) if x[5] else -1
    )):
        avg = sum(groups[key]) / len(groups[key])
        writer.writerow([*key, f"{avg:.6f}"])

print(f"Saved averages to {output_file}")