pr2: UI.o llist.o
	g++ -o pr2 UI.o llist.o
UI.o: UI.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -c UI.cpp
llist.o: llist.cpp record.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
pr2debug: UIdebug.o llistdebug.o
	g++ -o pr2debug -D debug UI.cpp llist.cpp
UIdebug.o: UI.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -c UI.cpp
llistdebug.o: llist.cpp record.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
