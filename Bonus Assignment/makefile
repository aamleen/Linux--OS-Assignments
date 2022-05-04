all:
	gcc -pthread fork.c -o fork
	gcc -pthread bowl.c -o bowl
	gcc -pthread bowl_fork.c -o bowl_fork

fork:
	gcc -pthread Q1.c -o fork

bowl:
	gcc -pthread bowl.c -o bowl

bowl_fork:
	gcc -pthread bowl_fork.c -o bowl_fork

clean:
	rm -r bowl fork bowl_fork

