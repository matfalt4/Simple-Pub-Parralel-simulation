DEBUG = -g -O0
OPT = -O3

CCOMP = gcc 

LINK = gcc 

pub_sym: pub_sym.o 
	$(LINK) -pthread pub_sym.o -o pub_sym


pub_sym.o: pub_sym.c 
	$(CCOMP) $(DEBUG) -c -pthread pub_sym.c 


clean:
	rm -f pub_sym pub_sym.o 

