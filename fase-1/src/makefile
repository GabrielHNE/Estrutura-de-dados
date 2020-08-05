
CFLAGS = -g -std=c99 -fstack-protector-all

#change this name later
patter1 = utils.h list.h svg.h figures.h

objects = main.o geo.o qry.o svg.o list.o utils.o figures.o paths.o circle.o rect.o line.o text.o colisions.o

siguel : $(objects)
	gcc -o siguel $(objects) $(CFLAGS) -lm

main.o : main.c utils.h geo.h qry.h svg.h list.h figures.h paths.h
	gcc -c main.c -o main.o

geo.o : geo.c geo.h $(pattern1)
	gcc -c geo.c -o geo.o

qry.o : qry.c qry.h $(pattern1)
	gcc -c qry.c -o qry.o

svg.o : svg.c svg.h utils.h figures.h circle.h rect.h line.h text.h
	gcc -c svg.c -o svg.o

figures.o : figures.c figures.h utils.h list.h circle.h rect.h line.h text.h
	gcc -c figures.c -o figures.o

colisions.o : colisions.c colisions.h circle.h rect.h line.h text.h
	gcc -c colisions.c -o colisions.o

circle.o : circle.c circle.h
	gcc -c circle.c -o circle.o

rect.o : rect.c rect.h
	gcc -c rect.c -o rect.o

text.o : text.c text.h
	gcc -c text.c -o text.o

line.o : line.c line.h
	gcc -c line.c -o line.o

list.o : list.c list.h utils.h
	gcc -c list.c -o list.o

paths.o : paths.c utils.h
	gcc -c paths.c -o paths.o

utils.o : utils.c utils.h
	gcc -c utils.c -o utils.o

#methods
clean : 
	rm siguel *.o

clean_obj:
	rm *.o