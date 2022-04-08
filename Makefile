a.out: main.cc map.h actor.h
	g++ main.cc -lcurl -lncurses

clean:
	rm -rf a.out core *.o
