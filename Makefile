folder = oblig3

common_srcs = graph.cpp node_edge.cpp MatrixGraph.cpp tarjans.cpp diamonds.cpp
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
	g++ -g3 -o $@ $^

%.o: %.cpp
	g++ -g3 -c -o $@ $<

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

clean:
	rm -f *.o

clear: clean
	rm -f *.zip $(binary_oblig2) $(binary_scc) $(binary_diamond) *.bmp data2.txt

zip: clear
	zip $(folder) Makefile *.cpp *.h