CXX		=	g++
CPPFLAGS	=	-I./include
LIBS		=	-L/usr/local/fcgi/lib -lfcgi -lcgi -lpthread -ldl

smartHome.fcgi : main.o  func.o
	$(CXX) -o smartHome.fcgi main.o func.o -I./include  $(LIBS)
	cp smartHome.fcgi /opt/smartHome/

main.o : main.cpp main.h
	$(CXX) -c main.cpp -I./include  $(LIBS)

func.o : func.cpp func.h
	$(CXX) -c func.cpp

#fcgi_middle.o : fcgi_middle.cpp public.h fcgi_middle.h func.h
#	$(CXX) -c fcgi_middle.cpp

clean:
	rm -f *.o

