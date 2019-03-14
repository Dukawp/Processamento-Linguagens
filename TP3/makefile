all : 
	flex e.l
	yacc -d -v e.y
	gcc y.tab.c `pkg-config --cflags --libs glib-2.0` -o try

run :
	rm -rf *.html
	./try < exemplo.txt

toGraph:
	dot -Tsvg dot.dot -o grafo.html