#

btree: btree_final.c btree_insert.h N.h string_gen.h
	gcc btree_final.c -o btree

bst: bst_main.c bst.h N.h string_gen.h
	gcc bst_main.c -o bst

clean: 
	rm btree bst 

clr: 	
	rm  search.txt
