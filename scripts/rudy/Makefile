
all: clean gset

.PHONY: gset
gset: rudy graphs
	./rudy -rnd_graph 800 6 8001 > graphs/g01.in
	./rudy -rnd_graph 800 6 8002 > graphs/g02.in
	./rudy -rnd_graph 800 6 8003 > graphs/g03.in
	./rudy -rnd_graph 800 6 8004 > graphs/g04.in
	./rudy -rnd_graph 800 6 8005 > graphs/g05.in
	./rudy -rnd_graph 800 6 8001 -random 0 1 8001 -times 2 -plus -1  > graphs/g06.in
	./rudy -rnd_graph 800 6 8002 -random 0 1 8002 -times 2 -plus -1  > graphs/g07.in
	./rudy -rnd_graph 800 6 8003 -random 0 1 8003 -times 2 -plus -1  > graphs/g08.in
	./rudy -rnd_graph 800 6 8004 -random 0 1 8004 -times 2 -plus -1  > graphs/g09.in
	./rudy -rnd_graph 800 6 8005 -random 0 1 8005 -times 2 -plus -1  > graphs/g10.in
	./rudy -toroidal_grid_2D 100 8 -random 0 1 8001 -times 2 -plus -1 > graphs/g11.in
	./rudy -toroidal_grid_2D 50 16 -random 0 1 8002 -times 2 -plus -1 > graphs/g12.in
	./rudy -toroidal_grid_2D 25 32 -random 0 1 8003 -times 2 -plus -1 > graphs/g13.in
	./rudy -planar 800 99 8001 -planar 800 99 8002 + > graphs/g14.in
	./rudy -planar 800 99 8003 -planar 800 99 8004 + > graphs/g15.in
	./rudy -planar 800 99 8005 -planar 800 99 8006 + > graphs/g16.in
	./rudy -planar 800 99 8007 -planar 800 99 8008 + > graphs/g17.in
	./rudy -planar 800 99 8001 -planar 800 99 8002 + -random 0 1 8001 -times 2 -plus -1 > graphs/g18.in
	./rudy -planar 800 99 8003 -planar 800 99 8004 + -random 0 1 8002 -times 2 -plus -1 > graphs/g19.in
	./rudy -planar 800 99 8005 -planar 800 99 8006 + -random 0 1 8003 -times 2 -plus -1 > graphs/g20.in
	./rudy -planar 800 99 8007 -planar 800 99 8008 + -random 0 1 8004 -times 2 -plus -1 > graphs/g21.in
	./rudy -rnd_graph 2000 1 20001 > graphs/g22.in
	./rudy -rnd_graph 2000 1 20002 > graphs/g23.in
	./rudy -rnd_graph 2000 1 20003 > graphs/g24.in
	./rudy -rnd_graph 2000 1 20004 > graphs/g25.in
	./rudy -rnd_graph 2000 1 20005 > graphs/g26.in
	./rudy -rnd_graph 2000 1 20001 -random 0 1 20001 -times 2 -plus -1 > graphs/g27.in
	./rudy -rnd_graph 2000 1 20002 -random 0 1 20002 -times 2 -plus -1 > graphs/g28.in
	./rudy -rnd_graph 2000 1 20003 -random 0 1 20003 -times 2 -plus -1 > graphs/g29.in
	./rudy -rnd_graph 2000 1 20004 -random 0 1 20004 -times 2 -plus -1 > graphs/g30.in
	./rudy -rnd_graph 2000 1 20005 -random 0 1 20005 -times 2 -plus -1 > graphs/g31.in
	./rudy -toroidal_grid_2D 100 20 -random 0 1 20001 -times 2 -plus -1 > graphs/g32.in
	./rudy -toroidal_grid_2D 80 25 -random 0 1 20002 -times 2 -plus -1 > graphs/g33.in
	./rudy -toroidal_grid_2D 50 40 -random 0 1 20003 -times 2 -plus -1 > graphs/g34.in
	./rudy -planar 2000 99 20001 -planar 2000 99 20002 + > graphs/g35.in
	./rudy -planar 2000 99 20003 -planar 2000 99 20004 + > graphs/g36.in
	./rudy -planar 2000 99 20005 -planar 2000 99 20006 + > graphs/g37.in
	./rudy -planar 2000 99 20007 -planar 2000 99 20008 + > graphs/g38.in
	./rudy -planar 2000 99 20001 -planar 2000 99 20002 + -random 0 1 20001 -times 2 -plus -1 > graphs/g39.in
	./rudy -planar 2000 99 20003 -planar 2000 99 20004 + -random 0 1 20002 -times 2 -plus -1 > graphs/g40.in
	./rudy -planar 2000 99 20005 -planar 2000 99 20006 + -random 0 1 20003 -times 2 -plus -1 > graphs/g41.in
	./rudy -planar 2000 99 20007 -planar 2000 99 20008 + -random 0 1 20004 -times 2 -plus -1 > graphs/g42.in
	./rudy -rnd_graph 1000 2 10001 > graphs/g43.in
	./rudy -rnd_graph 1000 2 10002 > graphs/g44.in
	./rudy -rnd_graph 1000 2 10003 > graphs/g45.in
	./rudy -rnd_graph 1000 2 10004 > graphs/g46.in
	./rudy -rnd_graph 1000 2 10005 > graphs/g47.in
	./rudy -toroidal_grid_2D 50 60 > graphs/g48.in
	./rudy -toroidal_grid_2D 30 100 > graphs/g49.in
	./rudy -toroidal_grid_2D 25 120 > graphs/g50.in
	./rudy -planar 1000 100 10001 -planar 1000 100 10002 + > graphs/g51.in
	./rudy -planar 1000 100 10003 -planar 1000 100 10004 + > graphs/g52.in
	./rudy -planar 1000 100 10005 -planar 1000 100 10006 + > graphs/g53.in
	./rudy -planar 1000 100 10007 -planar 1000 100 10008 + > graphs/g54.in

rudy: rudy.c gb_lib.c
	gcc -w gb_lib.c rudy.c -lm -o rudy

rudy.c:
	wget http://web.stanford.edu/~yyye/yyye/Gset/rudy.c

gb_lib.c:
	wget http://web.stanford.edu/~yyye/yyye/Gset/gb_lib.c

graphs:
	mkdir graphs

test_graphs: rudy
	mkdir test_graphs
	./rudy -clique 2 -random 1 1 51 -times 2 -plus -1 > test_graphs/complete_2.in
	./rudy -clique 5 -random 0 1 51 -times 2 -plus -1 > test_graphs/complete_5.in

.PHONY: mostlyclean
mostlyclean:
	rm -rf gset
	rm -rf test_graphs
	rm -rf rudy

.PHONY: clean
clean: mostlyclean
	rm -rf *.c
	