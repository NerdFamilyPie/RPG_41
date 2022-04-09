a.out: main.cc map.h actor.h
	g++ main.cc -lcurl -lncurses -g

clean:
	rm -rf a.out core *.o
