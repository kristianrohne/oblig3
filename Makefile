folder = oblig3

<<<<<<< HEAD
common_srcs = graph.cpp node_edge.cpp MatrixGraph.cpp tarjans.cpp diamonds.cpp graph_from_cmd.cpp
common_objs = $(patsubst %.cpp,%.o,$(common_srcs))

binary_oblig2 = graph_oblig2
binary_scc    = graph_scc
binary_diamond = graph_diamond

all: $(binary_oblig2) $(binary_scc) $(binary_diamond)

$(binary_oblig2): main_oblig2.o $(common_objs)
	g++ -g3 -o $@ $^

$(binary_scc): main_tarjans.o $(common_objs)
	g++ -g3 -o $@ $^

$(binary_diamond): main_diamond.o $(common_objs)
=======
# Source files that do NOT contain a main() function
common_srcs = graph.cpp node_edge.cpp MatrixGraph.cpp tarjans.cpp diamonds.cpp
common_objs = $(patsubst %.cpp,%.o,$(common_srcs))

# Two separate executables: one for oblig2 demos, one for oblig3
binary_oblig3 = graph_program
binary_oblig2 = graph_oblig2

# Default: build both programs
all: $(binary_oblig3) $(binary_oblig2)

# Oblig 3 program (Tarjan's SCC, problem 3.1)
$(binary_oblig3): main.o $(common_objs)
	g++ -g3 -o $@ $^

# Oblig 2 program (graph basics, problems 2.2 and 2.5)
$(binary_oblig2): main_oblig2.o $(common_objs)
>>>>>>> 747e2f3 (Add demo mains for 2.2/2.5/3.1/3.2, update Makefile, ER diagram and report)
	g++ -g3 -o $@ $^

# Compile any .cpp file to a .o object file
%.o: %.cpp
	g++ -g3 -c -o $@ $<

<<<<<<< HEAD
pro22: $(binary_oblig2)
	@echo "=== Problem 2.2 demo: Basic Graph Operations ==="
	./$(binary_oblig2)
	@echo "=== Done ==="

pro25: $(binary_oblig2)
	@echo "=== Problem 2.5 demo: Matrix Graph Operations ==="
	./$(binary_oblig2)
	@echo "=== Done ==="

pro31: $(binary_scc)
	@echo "=== Problem 3.1: Tarjan SCC demo ==="
	./$(binary_scc) --verbose data/scc02.dat
	@echo "=== Done ==="

pro32: $(binary_diamond)
	@echo "=== Problem 3.2: Diamond path query demo ==="
	./$(binary_diamond) --verbose data/scc02.dat data/query.dat
	@echo "=== Done ==="

=======
# -------------------------------------------------------
# Demo targets (problem 3.3)
# -------------------------------------------------------

# Problem 2.2: File input/output demo
pro22: $(binary_oblig2)
	@echo "=== Problem 2.2: File I/O demo ==="
	./$(binary_oblig2)
	@echo "=== Done ==="

# Problem 2.5: Disconnect and remove_node demo
pro25: $(binary_oblig2)
	@echo "=== Problem 2.5: Disconnect and remove_node demo ==="
	./$(binary_oblig2)
	@echo "=== Done ==="

# Problem 3.1: Tarjan's strongly connected components demo
pro31: $(binary_oblig3)
	@echo "=== Problem 3.1: Tarjan's SCC demo (linked structure, verbose) ==="
	./$(binary_oblig3) --linked --verbose data/scc02.dat
	@echo "=== Done ==="

# Problem 3.2: Diamond path query demo
# NOTE: Update the paths below when the diamond query main is ready
pro32: $(binary_oblig3)
	@echo "=== Problem 3.2: Diamond path query demo ==="
	@echo "(Not yet implemented - update this target when diamonds main is ready)"
	@echo "=== Done ==="

# -------------------------------------------------------
# Utility targets
# -------------------------------------------------------

run: $(binary_oblig3)
	./$(binary_oblig3)

>>>>>>> 747e2f3 (Add demo mains for 2.2/2.5/3.1/3.2, update Makefile, ER diagram and report)
clean:
	rm -f *.o

clear: clean
<<<<<<< HEAD
	rm -f *.zip $(binary_oblig2) $(binary_scc) $(binary_diamond) *.bmp data2.txt

zip: clear
	zip $(folder) Makefile *.cpp *.h
=======
	rm -f *.zip $(binary_oblig3) $(binary_oblig2) *.bmp data2.txt

zip: clear
	zip $(folder) Makefile *.cpp *.h
>>>>>>> 747e2f3 (Add demo mains for 2.2/2.5/3.1/3.2, update Makefile, ER diagram and report)
