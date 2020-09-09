# MAST-program
C++ program that solves the problem known in IT as Maximum agreement subtree problem ([MAST](https://en.wikipedia.org/wiki/Maximum_agreement_subtree_problem)).

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
![image3]( https://github.com/JoseManuelMoyaVargas/MAST-program/blob/master/sources/image3.png)

We first fill in this array by inserting ones for all the leaves of one and then the other tree. Only one label is associated with a given leaf. If the leaf or the inner vertex of the other tree has a leaf with a corresponding label, then we type 1 otherwise 0. The most important part of the algorithm begins when comparing the inner vertices of one tree with another. First of all, it should be done in the right order: reverse Breadth-first_search or Post-order. We consider three cases for each pair and the one with the highest score should be selected. We assume that we compare two internal vertices of AX with Bx:
1.	one of the sons of the AX node can be identified with the BX node
2.	AX node can be identified as one of the sons of the BX node
3.	identify the sons of the AX node with the sons of the BX node (not necessarily all) so that the sum of identical nodes is as large as possible
We implemented the subpoint 3 with a brute force algorithm, browsing the full space of possible solutions and selecting the best result. When completing the comparison of the two roots we gets the final result, which is our |l|.

![image5]( https://github.com/JoseManuelMoyaVargas/MAST-program/blob/master/sources/image5.png)


In the table above, we see the filled array after the algorithm has run. As we can see F1 after mapping with E2 gave an optimal result |l| = 4. In the next step, by mapping F1 with F2, the vertex E2 was selected as the best selection from the above 3 conditions. The result is 6. We interpret it in such a way that it is the minimum number of leaves required for removal in each of the compared trees to be isomorphic. We need to remove the leaves: 1,3,5,7,9,10. After deleting them, we receive the following agreement subtree:
![image4]( https://github.com/JoseManuelMoyaVargas/MAST-program/blob/master/sources/image4.png)

## Input format

The value of n denotes the size of the set of n rooted trees.
n rooted trees in NEWICK format.

## Output format

n(n-1)/2 comparisons of input trees (each with each). The order of comparison: 1-2, 1-3, ..., 1-n, 2-3, 2-4, ..., 2-n, ..., (n-1) -n.

## Input example

4   
(1,5,(10,6,3),(2,(8,7)),(9,4));  
((7,(3,(4,9,(1,2)))),8,(5,(10,6)));  
(7,((6,(9,5),(8,3)),(1,(2,10,4))));  
(7,(8,3,4,6,1),(9,5,10),2);  

## Output example

5
7
6
6
6
6




