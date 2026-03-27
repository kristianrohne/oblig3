folder = oblig3

common_srcs = 2_1_graph.cpp 2_1_node_edge.cpp 2_4_MatrixGraph.cpp 3_1_tarjans.cpp 3_2_diamonds.cpp 3_1_graph_from_cmd.cpp
common_objs = $(patsubst %.cpp,%.o,$(common_srcs))

binary_pro22 = graph_pro22
binary_pro25 = graph_pro25
binary_scc    = graph_scc
binary_diamond = graph_diamond

all: $(binary_pro22) $(binary_pro25) $(binary_scc) $(binary_diamond)

$(binary_pro22): 3_3_main_22.o $(common_objs)
	g++ -g3 -std=c++17 -o $@ $^

$(binary_pro25): 3_3_main_25.o $(common_objs)
	g++ -g3 -std=c++17 -o $@ $^

$(binary_scc): 3_1_main_tarjans.o $(common_objs)
	g++ -g3 -std=c++17 -o $@ $^

$(binary_diamond): 3_2_main_diamond.o $(common_objs)
	g++ -g3 -std=c++17 -o $@ $^

# Compile any .cpp file to a .o object file
%.o: %.cpp
	g++ -g3 -std=c++17 -c -o $@ $<

# Demo targets (problem 3.3)

# Problem 2.2: File input/output demo
pro22: $(binary_pro22)
	@echo "=== Problem 2.2: Graph (linked-list) - File I/O demo ==="
	./$(binary_pro22)

# Problem 2.5: Disconnect and remove_node demo
pro25: $(binary_pro25)
	@echo "=== Problem 2.5: MatrixGraph - Disconnect and remove_node demo ==="
	./$(binary_pro25)

# Problem 3.1: Tarjan's strongly connected components demo
pro31: $(binary_scc)
	@echo "=== Problem 3.1: Tarjan's SCC demo (linked structure, verbose) ==="
	./$(binary_scc) --linked --verbose data/scc02.dat
	@echo "=== Done ==="

# Problem 3.2: Diamond path query demo
pro32: $(binary_diamond)
	@echo "=== Problem 3.2: Diamond path query demo ==="
	./$(binary_diamond) --verbose data/scc02.dat data/query.dat
	@echo "=== Done ==="

# Utility targets

clean:
	rm -f *.o

clear: clean
	rm -f *.zip $(binary_pro22) $(binary_pro25) $(binary_scc) $(binary_diamond) *.bmp data2.txt

zip: clear
	zip $(folder) Makefile *.cpp *.h
