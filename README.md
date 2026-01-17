#Indexing Techniques for Database System.

***This Project  tries to study various Indexing techniques used in database systems.
by Implementing B-Tree and BST datastructure we are trying to compare
Time taken by both datastructure for some specific number of records***

<p>Hence we come to the point that B-Trees are widely used for Indexing in Database Systems.</p>
<hr></hr>

*commands for making executable*

- ```make bst```
- ```make btree```


####Run executables
1. ```./bst```
2. ```./btree```

###Working:
- We are trying to create indexing on records of 'sample.txt' file where we are assuming 'name' field(first) as key of Node of B-Tree and BST.
- both executable tries to extract records from the 'sample.txt' file which contains 1000000 records. 
- you can change no.of insertion of records by changing the value 'N' from file 'N.h' which should 1<=N<=1000000.
- after running those executable you are able to see the time taken by both datastructure for same 'N' no.of records varies.
	and then you can differentiate which one is better.
- for increasing the minimum degree of B-Tree change the value of 't' from file 'btree_insert.h' which will increase it's efficiency.
- in 'search.txt' file you can see search records from 'sample.txt' file.


Pattern of file 'sample.txt'=>

Name| age | city
----|-----|----
abc | 23  | kkr

____
Author:
Krushna Dhawade.
