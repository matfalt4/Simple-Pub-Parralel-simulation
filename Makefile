DEBUG = -g -O0
OPT = -O3

CCOMP = gcc 

LINK = gcc 

pub_sym: pub_sym.o 
	$(LINK) $(DEBUG) pub_sym.o -o pub_sym


pub_sym.o: pub_sym.c 
	$(CCOMP) -c pub_sym.c 


clear:
	rm -f pub_sym pub_sym.o 

