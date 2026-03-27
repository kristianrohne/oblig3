import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("benchmark_averages.csv")

# Convert to numeric (important)
df["n"] = pd.to_numeric(df["n"])
df["avg_runtime_ms"] = pd.to_numeric(df["avg_runtime_ms"])

# --- 1. SCC plot ---
plt.figure()

for graph_type in ["linked", "matrix"]:
    subset = df[(df["algorithm"] == "scc") & (df["graph_type"] == graph_type)]
    subset = subset.sort_values("n")
    plt.plot(subset["n"], subset["avg_runtime_ms"], marker='o', label=graph_type)

plt.xlabel("Number of nodes (n)")
plt.ylabel("Runtime (ms)")
plt.title("SCC (Tarjan) Runtime Scaling")
plt.legend()
plt.grid()
plt.savefig("scc_plot.png")
plt.close()


# --- 2. Diamond fixed m ---
plt.figure()

for graph_type in ["linked", "matrix"]:
    subset = df[(df["algorithm"] == "diamond") &
                (df["scenario"] == "fixed_m") &
                (df["graph_type"] == graph_type)]
    subset = subset.sort_values("n")
    plt.plot(subset["n"], subset["avg_runtime_ms"], marker='o', label=graph_type)

plt.xlabel("Number of nodes (n)")
plt.ylabel("Runtime (ms)")
plt.title("Diamond Query (Fixed m)")
plt.legend()
plt.grid()
plt.savefig("diamond_fixed.png")
plt.close()


# --- 3. Diamond growing m ---
plt.figure()

for graph_type in ["linked", "matrix"]:
    subset = df[(df["algorithm"] == "diamond") &
                (df["scenario"] == "growing_m") &
                (df["graph_type"] == graph_type)]
    subset = subset.sort_values("n")
    plt.plot(subset["n"], subset["avg_runtime_ms"], marker='o', label=graph_type)

plt.xlabel("Number of nodes (n)")
plt.ylabel("Runtime (ms)")
plt.title("Diamond Query (Growing m)")
plt.legend()
plt.grid()
plt.savefig("diamond_growing.png")
plt.close()

print("Plots saved!")