in2post.x: in2post.o
	g++ -o in2post.x -std=c++11 in2post.o

in2post.o: in2post.cpp stack.h
	g++ -c -std=c++11 in2post.cpp

clean:
	-rm -f *.o
	-rm -f *.h.gch
	-rm -f *.x
