a.out: main.cc map.h 
	g++ main.cc -lcurl -lncurses

clean:
	rm -rf a.out core *.o
