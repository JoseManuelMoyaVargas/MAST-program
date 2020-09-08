//
//  main.cpp
//  Created by Jose Manuel Moya Vargas on 12/04/2020.
//  Copyright © 2020 Jose Manuel Moya Vargas. All rights reserved.
//
#include <iostream>
#include <vector>
using namespace std;


int charToInt(char c){
    int ia;
    ia =c-'0';
    return ia;
}

class node
{
  int key_value;
  node *parent;//Arrow up
  node *son;//Arrow down
  node *brother;//Arrow to the right
  
  int indexInMatrix;
  int * indexesSons;
  int numOfSons;

 public:
    node(int key){
        key_value=key;
        parent=nullptr;//Un nodo puede ser parent de mas de un nodo.Es una relacion de 1 a muchos.
        son=nullptr;
        brother=nullptr;
        indexInMatrix=-1;
        numOfSons=0;
    }
    ~node(){
        parent=nullptr;
        son=nullptr;
        brother=nullptr;
       //delete [] indexesSons;
    }

    int getValue(){
        return key_value;
    }
    void setParent(node * p){
        parent=p;
    }
    void setBrother(node * b){
        brother =b;
        b->parent=parent;//If we add a brother to a node, then the brother has the same parent.
    }
    void setSon(node * s){
        son=s;
        s->setParent(this);
    }
    node * getParent(){
        return parent;
    }
    node * getSon(){
        return son;
    }
    node * getBrother(){
        return brother;
    }
    void setIndexInMatrix(int value){
        indexInMatrix=value;
    }
    int getIndexInMatrix(){
        return indexInMatrix;
    }
    void calculateIndexesSons2(){
        int numSonsAdded=0;
        indexesSons = new int[numOfSons];
        node * n = son;
        while(n!=nullptr){
            indexesSons[numSonsAdded]=n->getIndexInMatrix();
            n = n->getBrother();
            numSonsAdded++;
        }
    }
    int * getIndexesSons(){
        return indexesSons;
    }
    void incrementSons(){
        numOfSons++;
    }
    int getNumberOfSons(){
        return numOfSons;
    }
};

class tree
{
private:
    node * root;
    int * indexesLeaves;
    
    node * *  nodes;
    int numOfNodes;
    node * * leaves;
    int numOfLeaves;
    node * *  internalVertices;
    int numOfInternalVertices;
    
    
public:
    tree(){
        root=nullptr;
        numOfNodes=0;
        numOfLeaves=0;
        numOfInternalVertices=0;
    }
    ~tree(){
        root=nullptr;
        for(int i=0;i<numOfNodes;i++){
            delete nodes[i];
        }
        delete [] nodes;
        delete [] leaves;
        delete [] internalVertices;
    }

void readNewick(char * newickDefinition){
    int numOfNodesAdded=0;
    int numOfLeavesAdded=0;
    int numOfInternalVerticesAdded=0;
    
    int i=1;
    int indexInMatrix=0;
    int emptyValue=-1;
    char  input1;
    char input2;
    node * node1=nullptr;
    node * node2=nullptr;
    int value;
    /**First element*/
    node1 = new node(emptyValue);
    internalVertices[numOfInternalVerticesAdded]=node1;
    numOfInternalVerticesAdded++;
    emptyValue--;
    root = node1;
    input2='(';
    node2=node1;
    
    input1=newickDefinition[i];
    while(input1!=';'){
        switch (input1) {
            case '(':
                node1 = new node(emptyValue);
                internalVertices[numOfInternalVerticesAdded]=node1;
                numOfInternalVerticesAdded++;
                emptyValue--;
                break;
            case ')':
                node1 = node1->getParent();
                break;
            case ';':
                
            break;
            case ',':
                
            break;
            default:
                if(newickDefinition[i]=='1'&& newickDefinition[i+1]=='0'){
                    node1 = new node(10);
                    i++;
                }else{
                    value = charToInt(input1);
                    node1 = new node(value);
                }
                leaves[numOfLeavesAdded]=node1;
                numOfLeavesAdded++;
            break;
        }
        
        switch (input2) {
            case '(':
                node2->setSon(node1);
                if(node1->getParent()!=nullptr)
                    node1->getParent()->incrementSons();
                break;
            case ')':
                
                break;
            case ';':
                
            break;
            case ',':
                node2->setBrother(node1);
                if(node1->getParent()!=nullptr)
                    node1->getParent()->incrementSons();
                
            break;
            default:
            
            break;
        }
        input2=input1;
        node2=node1;
        i++;
        input1=newickDefinition[i];
    }

    for(int i=0;i<numOfLeaves;i++){
        leaves[i]->setIndexInMatrix(i);
        nodes[numOfNodesAdded]=leaves[i];
        numOfNodesAdded++;
    }
    for(int i=numOfLeaves,j=0;i<numOfNodes;j++,i++){
        internalVertices[j]->setIndexInMatrix(i);
        nodes[numOfNodesAdded]=internalVertices[j];
        numOfNodesAdded++;
    }
    /**Nuevo*/
   
    for(int n=0;n<numOfInternalVertices;n++){
        internalVertices[n]->calculateIndexesSons2();
    }

    indexesLeaves = new int[numOfLeavesAdded];
    for(int i =0;i<numOfLeaves;i++){
        indexesLeaves[leaves[i]->getValue()-1]=i;
    }
}
    void countElements(char * newickDefinition){
        int i=1;
        int numeroNodos=0;
        int numeroHojas=0;
        int numeroDeVerticesInternos=0;
        char  input1;
        numeroDeVerticesInternos++;
        numeroNodos++;
        input1=newickDefinition[i];
        while(input1!=';'){
            switch (input1) {
                case '(':
                    numeroNodos++;
                    numeroDeVerticesInternos++;
                    break;
                case ')':
                    
                    break;
                case ';':
                break;
                case ',':
                break;
                default:
                   if(newickDefinition[i]=='1'&& newickDefinition[i+1]=='0'){
                       i++;
                   }
                    numeroNodos++;
                    numeroHojas++;
                   
                break;
            }
            i++;
            input1=newickDefinition[i];
            
        }
        numOfNodes=numeroNodos;
        numOfLeaves=numeroHojas;
        numOfInternalVertices=numeroDeVerticesInternos;
        
        nodes = new node *[numOfNodes];
        leaves = new node * [numOfLeaves];
        internalVertices = new node * [numOfInternalVertices];
    
    }
    int getNumOfNodes(){
        return numOfNodes;
    }
    int getNumOfLeaves(){
        return numOfLeaves;
    }
    node * * getAllNodes(){
        return nodes;
    }
    int getIndexOfLeave(int valueLeave){
        return indexesLeaves[valueLeave-1];
    }
    void printNode(node * node){
        if(node!=nullptr){
            cout<<"### NODE ###"<<endl;
            cout<<"value: "<<node->getValue()<<endl;
            /*
            cout<<"parent: ";
            if(node->getParent()!=nullptr){
                cout<<node->getParent()->getValue()<<endl;
            }else{
                cout<<"nullptr"<<endl;
            }
            cout<<"brother: ";
            if(node->getBrother()!=nullptr){
                cout<<node->getBrother()->getValue()<<endl;
            }else{
                cout<<"nullptr"<<endl;
            }
            
            cout<<"son: ";
            if(node->getSon()!=nullptr){
                cout<<node->getSon()->getValue()<<endl;
            }else{
                cout<<"nullptr"<<endl;
            }
             */
            
            cout<<"Number of sons"<<endl;
            cout<<node->getNumberOfSons()<<endl;
            cout<<"Indexes sons"<<endl;
            node->calculateIndexesSons2();
            int * indexesSons=node->getIndexesSons();
            for(int i =0;i<node->getNumberOfSons();i++){
                cout<<indexesSons[i]<<" ";
                
            }
            
            cout<<"### --- ###"<<endl<<endl;
            printNode(node->getSon());
            printNode(node->getBrother());
        }
    }
    
    void printTree(){
        printNode(root);
    }
    };


class matrix{
private:
    tree * tree1;
    node * * nodesTree1;
    tree * tree2;
    node ** nodesTree2;
    
    int ** m;
    int numRowsMatrix;
    int finalResult;
public:
    
    matrix(tree * t1,tree * t2){
        tree1=t1;
        tree2=t2;
        int numRows=tree1->getNumOfNodes();
        numRowsMatrix=numRows;
        int numColumns=tree2->getNumOfNodes();
        
        m = new int * [numRows];
        for(int i = 0; i < numRows; ++i)
            m[i] = new int[numColumns];

        nodesTree1 = tree1->getAllNodes();
        nodesTree2= tree2->getAllNodes();
        
        
        for(int i=0;i<numRows;i++){
            for(int j=0;j<numColumns;j++){
                m[i][j]=7;
            }
        }
        finalResult=0;
    }
    ~matrix(){
    
        tree1=nullptr;
        nodesTree1=nullptr;
        tree2=nullptr;
        nodesTree2=nullptr;
        for(int i=0;i<numRowsMatrix;i++){
            delete m[i];
        }
        delete [] m;
    
    }
    
    void fillLeavesColumnsAndRows(){
        for(int i=0;i<tree1->getNumOfLeaves();i++){
            for(int j=0;j<tree2->getNumOfLeaves();j++){
                if(nodesTree1[i]->getValue()==nodesTree2[j]->getValue()){//If row is equal to columnn then we put a 1.
                    m[i][j]=1;
                }else{
                     m[i][j]=0;
                }
            }
        }
    }
    void constructSubMatrixExternalVertices(){
        node * p;
        int valueNode;
        for(int i =0;i<tree1->getNumOfLeaves();i++){
            for(int j=tree2->getNumOfLeaves();j<tree2->getNumOfNodes();j++){
                valueNode = nodesTree1[i]->getValue();
                p=nodesTree2[tree2->getIndexOfLeave(valueNode)]->getParent();
                while(p!=nullptr){
                    if(nodesTree2[j]==p){
                        m[i][j]=1;
                        break;
                    }else{
                         m[i][j]=0;
                    }
                    p=p->getParent();
                }
            }
        }
        for(int j=0;j<tree2->getNumOfLeaves();j++){
            for(int i=tree1->getNumOfLeaves();i<tree1->getNumOfNodes();i++){
                valueNode=nodesTree2[j]->getValue();
                p=nodesTree1[tree1->getIndexOfLeave(valueNode)]->getParent();
                while(p!=nullptr){
                    if(nodesTree1[i]==p){
                           m[i][j]=1;
                            break;
                       }else{
                             m[i][j]=0;
                        }
                    p=p->getParent();
                }
            }
        }
    }
    
    void buildFirstMatrices(){
        fillLeavesColumnsAndRows();
        constructSubMatrixExternalVertices();
    }

    
    int compareTwoInternalVerticesForm1and2(node * n1,node *n2){
        //node1 is from tree1 and is a row. node 2 is from tree2 and is a column.
        int maxValue=0;
        int indexNode1=n1->getIndexInMatrix();
        int * indexesSonsNode1 = n1->getIndexesSons();
        int indexNode2=n2->getIndexInMatrix();
        int  * indexesSonsNode2=n2->getIndexesSons();
        for(int i=0;i<n2->getNumberOfSons();i++){
            if(m[indexNode1][indexesSonsNode2[i]]>maxValue){
                maxValue=m[indexNode1][indexesSonsNode2[i]];
            }
        }
        //Now we compare n2 with the sons of n1.
        for(int i=0;i<n1->getNumberOfSons();i++){
            if(m[indexesSonsNode1[i]][indexNode2]>maxValue){
                maxValue=m[indexesSonsNode1[i]][indexNode2];
            }
        }
        return maxValue;
    }
    void calculateMaxSUMmoreColumnsThanRows(int** matrix,int numRows ,int numColumns, int * columnsVisited,int row, int suma,int * result){
        row++;//We move to the next row.
        if(row>=numRows){
            //If we a achieve the final then we have finish the rows.
            if(suma>*result){
                *result=suma;
            }
        }else{
            for(int i =0;i<numColumns;i++){
                if(columnsVisited[i]==0){
                    columnsVisited[i]=1;
                    suma = suma+ matrix[row][i];
                    calculateMaxSUMmoreColumnsThanRows(matrix, numRows,numColumns, columnsVisited, row, suma, result);
                    suma = suma - matrix[row][i];//We go backwards.
                    columnsVisited[i]=0;
                }
            }
        }
        
    }

    void calculateMaxSUMmoreRowsThanColumns(int** matrix, int numRows,int numColumns, int * rowsVisited,int column, int suma,int*result){
        column++;//We move to the next column
        if(column>=numColumns){
            if(suma>*result){
                *result=suma;
            }
        }else{
            for(int i =0;i<numRows;i++){
                if(rowsVisited[i]==0){//We look the next row that has not been visited
                    rowsVisited[i]=1; //We visit it
                    suma = suma + matrix[i][column]; //We add the number
                    calculateMaxSUMmoreRowsThanColumns(matrix, numRows,numColumns, rowsVisited, column, suma, result); //Now we continue looking the next row and column free-->We call other time the function so colum ++ and the we look the next row free until we reach the last column free.
                    suma = suma- matrix[i][column];//When we reach the last column free with the combination of last rows we quit to the intermediate sum the value of last element, and we look the next element in the same column but the next row.
                    rowsVisited[i]=0;
                    
                }
            }
        }
  
    }
    

    int calculateMaxSumOfMATRIX(int** matrix, int numRows,int numColumns ){
        int suma=0; // Variable to store the
        int result=0;
        /* -The number of operands will be the smaller num.
            For example if numRows=2 and numColumns=3, then sums will have 2 operands because we cant choose more than two elements from different rows.*/
        int * rowsVisited = new int [numRows];
        int * columnsVisited =new int[numColumns];
        if(numRows>=numColumns){
          
            for(int i=0;i<numRows;i++){
                //We restart everything
                suma=0;
                for(int r=0;r<numRows;r++){
                    rowsVisited[r]=0;
                }
                rowsVisited[i]=1;
                suma=suma+matrix[i][0];//We pick the first operand from the first row and the row i.
                calculateMaxSUMmoreRowsThanColumns(matrix,  numRows,numColumns, rowsVisited, 0,suma, &result);
               
            }
        }else if(numRows<numColumns){
         
            for(int j =0;j<numColumns;j++){
                //We restart everything
                suma=0;
                for(int c=0;c<numColumns;c++){
                    columnsVisited[c]=0;;
                }
                columnsVisited[j]=1;
                suma=suma+matrix[0][j];//We pick the first operand from the first row and the column j.
                calculateMaxSUMmoreColumnsThanRows(matrix, numRows,numColumns, columnsVisited, 0, suma, &result);
                
            }
        }
        return result;
    }

    
    int compareTwoInternalVerticesForm3(node * n1,node *n2){
         int * indexesNode1 = n1->getIndexesSons();
         int rows = n1->getNumberOfSons();
         int * indexesNode2 = n2->getIndexesSons();
         int columns = n2 ->getNumberOfSons();
         int ** ma=new int * [rows];
         for(int i = 0; i < rows; i++)
             ma[i] = new int[columns];
     
         for(int i = 0 ;i<rows; i++){
             for(int j=0;j<columns;j++){
                 ma[i][j]=m[indexesNode1[i]][indexesNode2[j]];
             }
         }
         
        int maxSum;
        maxSum=calculateMaxSumOfMATRIX(ma,rows,columns);
       

         for(int i = 0; i < rows; i++)
             delete ma[i];
         delete []ma;
    
         return maxSum;
     }
    
    
    void constructMatrix(){
        //
        fillLeavesColumnsAndRows();
        constructSubMatrixExternalVertices();
        buildFirstMatrices();
        int maxValue;
        int valueForm3;
        for(int i=tree1->getNumOfNodes()-1;i>=tree1->getNumOfLeaves();i--){
            for(int j=tree2->getNumOfNodes()-1;j>=tree2->getNumOfLeaves();j--){
             
                maxValue=compareTwoInternalVerticesForm1and2(nodesTree1[i], nodesTree2[j]);
                valueForm3=compareTwoInternalVerticesForm3(nodesTree1[i],nodesTree2[j]);
                if(valueForm3>maxValue){
                    maxValue=valueForm3;
                }
                m[i][j]=maxValue;
                if(maxValue>finalResult){
                    finalResult=maxValue;
                }
                
            }
        }
    }
    
    int getFinalResult(){
        return tree1->getNumOfLeaves()-finalResult;
    }
};


int main(int argc, const char * argv[]) {
     int numOfNumbers=0;
     int numsAdded=0;
     
     cin>>numOfNumbers;
     tree * * arrayTrees = new tree *[numOfNumbers];
    
     char input[256];

     while(numsAdded<numOfNumbers){
         cin>>input;
         arrayTrees[numsAdded] = new tree();
         arrayTrees[numsAdded]->countElements(input);
         arrayTrees[numsAdded]->readNewick(input);
         numsAdded++;
    }
    
    for(int i=0;i<numOfNumbers;i++){
        for(int j=i+1;j<numOfNumbers;j++){
            matrix * m = new matrix(arrayTrees[i],arrayTrees[j]);
            m->constructMatrix();
            cout<<m->getFinalResult()<<endl;
            delete m;
        }
    }
    
    for(int i=0;i<numOfNumbers;i++){
        delete arrayTrees[i];
    }
    delete  [] arrayTrees;
  

    return 0;
}


