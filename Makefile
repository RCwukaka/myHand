CXX	=	arm-linux-g++

main.bin : main.o queue.o serial.o
	$(CXX) -o main.bin main.o queue.o serial.o -lpthread
main.o : main.cpp serial.h
	$(CXX) -c main.cpp -lpthread
queue.o : queue.cpp queue.h public.h
	$(CXX) -c queue.cpp -lpthread
serial.o : serial.cpp serial.h public.h
	$(CXX) -c serial.cpp -lpthread

clean :
	rm -f *.o
