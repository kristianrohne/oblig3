binary = graph_program
folder = oblig3
objects = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

$(binary): $(objects)
	g++ -g3 -o $@ $^

run: $(binary)
	./$(binary)

%.o: %.cpp
	g++ -g3 -c -o $@ $<

clean:
	rm -f *.o

clear: clean
	rm -f *.zip $(binary) *.bmp

zip: clean
	zip $(folder) Makefile *.cpp *.h *.pxl