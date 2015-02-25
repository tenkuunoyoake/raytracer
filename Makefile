CC = g++
	
RM = /bin/rm -f 
all: main 
main: raytracer.o 
	$(CC) $(CFLAGS) -o raytracer lodepng.cpp raytracer.o $(LDFLAGS)  
raytracer.o: raytracer.cpp
	$(CC) $(CFLAGS) -c raytracer.cpp -o raytracer.o
clean: 
	$(RM) *.o raytracer
