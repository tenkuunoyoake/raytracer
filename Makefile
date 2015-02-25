CC = g++
	
RM = /bin/rm -f 
all: main 
main: raytrace.o 
	$(CC) $(CFLAGS) -o raytrace lodepng.cpp raytrace.o $(LDFLAGS)  
raytrace.o: raytrace.cpp
	$(CC) $(CFLAGS) -c raytrace.cpp -o raytrace.o
clean: 
	$(RM) *.o raytrace