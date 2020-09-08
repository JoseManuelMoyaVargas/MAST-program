# MAST-program
C++ program that solves the problem know in IT as Maximum agreement subtree problem ([MAST](https://en.wikipedia.org/wiki/Maximum_agreement_subtree_problem)).

## Explanation of the problem

MAST-program consists of the implementation of an algorithm that reads a set of n rooted trees in the NEWICK format, and then for each of n(n-1)/2 pairs of trees calculates the minimum number of leaves whose removal from both trees will make them isomorphic. 
Here are two examples of trees, each containing 10 identical leaves labeled from 1 to 10:

(4,(8,1,(5,3)),(9,2,(10,(7,6))));
(10,(8,(9,(5,4)),(6,2,3)),(7,1));

The trees have been saved in the computer's memory in the form of general trees, using one pointer per son, one per brother and one per parent. The figure below shows such a general representation of both trees.
![image1]( https://github.com/JoseManuelMoyaVargas/MAST-program/blob/master/sources/image1.png)

The pointers (arrows) down are the relation son and to the right is the relation brother. Pointers directed up (the relation parent) are not drawn in the first figure for the sake of clarity. 

## How have we implemented the solution?

We have created internal vertices identifiers for the trees visible above.
![image3]( https://github.com/JoseManuelMoyaVargas/MAST-program/blob/master/sources/image1.png)

