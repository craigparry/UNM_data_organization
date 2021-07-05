treetest: studenttreetest.c  binarytree.o
	gcc -ansi -Wall -pedantic -o treetest studenttreetest.c linkedlist.o binarytree.o
linkedlist.o: linkedlist.c linkedlist.h
	gcc -ansi -Wall -pedantic -o linkedlist.o -c linkedlist.c
binarytree.o: linkedlist.o binarytree.c binarytree.h
	gcc -ansi -Wall -pedantic -o binarytree.o -c binarytree.c
listtest: linkedlist.o studentlisttest.c
	gcc -ansi -Wall -pedantic -o listtest studentlisttest.c linkedlist.o