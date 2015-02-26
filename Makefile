CC = g++
CFLAGS = -Iinclude
HELPER = src/matrix.cpp
	
RM = /bin/rm -f 
all: main 
main: raytracer.o 
	$(CC) $(CFLAGS) -o raytracer src/lodepng.cpp $(HELPER)  raytracer.o $(LDFLAGS) 
raytracer.o: src/raytracer.cpp
	$(CC) $(CFLAGS) -c src/raytracer.cpp -o raytracer.o
clean: 
	$(RM) *.o raytracer
