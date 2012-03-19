LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui
CC = g++
all: main.o MeanShift.o
	$(CC) main.o MeanShift.o -o main $(LIBS)
main.o: main.cpp
	$(CC) -c main.cpp $(LIBS)
MeanShift.o: MeanShift.cpp MeanShift.h
	$(CC) -c MeanShift.cpp $(LIBS)
clean:
	rm *.o main
