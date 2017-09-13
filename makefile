test-compile : 
	gcc -w -I$HOME/local/include tests.c persistence.c parser.c rest.c -L$HOME/local/lib -lcunit -ljson-c
	
test-run : 
	./a.out
	
unit-test : test-compile test-run

server-compile:
	gcc -w -I$HOME/local/include main.c persistence.c parser.c rest.c -L$HOME/local/lib -lcunit -ljson-c -lmicrohttpd

acceptance-test-run:
	./acceptance-test.sh
	
acceptance-test: server-compile acceptance-test-run