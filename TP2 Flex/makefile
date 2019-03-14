all:
	flex ex1.l
	gcc lex.yy.c -o x1
	flex ex2.l
	gcc lex.yy.c -o x2
	flex ex3.l
	gcc lex.yy.c -o x3
	flex ex4.l
	gcc lex.yy.c -o x4
	

run1:
	./x1 < lp.bib

run2:
	./x2 < lp.bib
  
run3:
	./x3 < lp.bib

run4:
	./x4 < indiceAutores.txt
		
toGraph:
	echo "}" >> autor.dot 
	sed -i '1idigraph { ' autor.dot
	xdot autor.dot	


clean:
	rm x1
	rm x2
	rm x3
	rm x4
