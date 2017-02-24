all: obj LAB4

obj:
	mkdir obj

LAB4: obj/main.o obj/point.o obj/line.o obj/rectangle.o obj/triangle.o obj/circle.o obj/rhombus.o obj/ellipse.o
	g++ obj/*.o -lglut -lX11 -lGL -lGLU -O3 -o LAB4

obj/main.o: main.cpp
	g++ -c main.cpp -o obj/main.o

obj/point.o: point.cpp
	g++ -c point.cpp -o obj/point.o

obj/line.o: line.cpp
	g++ -c line.cpp -o obj/line.o

obj/rectangle.o: rectangle.cpp
	g++ -c rectangle.cpp -o obj/rectangle.o

obj/triangle.o: triangle.cpp
	g++ -c triangle.cpp -o obj/triangle.o

obj/circle.o: circle.cpp
	g++ -c circle.cpp -o obj/circle.o

obj/rhombus.o: rhombus.cpp
	g++ -c rhombus.cpp -o obj/rhombus.o

obj/ellipse.o: ellipse.cpp
	g++ -c ellipse.cpp -o obj/ellipse.o

clean:
	rm -r obj LAB4
