testreadtree: testreadtree.c readtree.o hashtree.o hashtreelist.o
	gcc -Wall -ansi -pedantic -g -o testreadtree testreadtree.c readtree.o hashtree.o hashtreelist.o
readtree.o: readtree.c readtree.h hashtreelist.o hashtree.o
	gcc -Wall -ansi -pedantic -g -o readtree.o -c readtree.c
testhashtreelist: testhashtreelist.c hashtree.o hashtreelist.o
	gcc -Wall -ansi -pedantic -g -o testhashtreelist testhashtreelist.c hashtree.o hashtreelist.o
hashtreelist.o: hashtree.o hashtreelist.h hashtreelist.c
	gcc -Wall -ansi -pedantic -g -o hashtreelist.o -c hashtreelist.c
testhashtree: testhashtree.c hashtree.o
	gcc -Wall -ansi -pedantic -g -o testhashtree testhashtree.c hashtree.o
hashtree.o: hashtree.c hashtree.h lonesha256.h
	gcc -Wall -pedantic -ansi -g -o hashtree.o -c hashtree.c