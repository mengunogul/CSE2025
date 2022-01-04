// Author Berkay Mengunogul
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//max macro
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// node structure for linked list
typedef struct node{
    int value;
    int height;
    int positionInDepthLevel;
    struct node* leftChild; 
    struct node* rightChild; 
} node;


// for sorting the nodes by their values by descending order
void insertionSort(node *array, int numOfElements){
    node key;
    for(int i=0; i < numOfElements; i++){
        key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j].value < key.value) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// right rotate
node *rightRotate(node *y) {
  node *x = y->leftChild;
  node *T2 = x->rightChild;

  x->rightChild = y;
  y->leftChild = T2;

  y->height = MAX(y->leftChild->height, y->rightChild->height) + 1;
  x->height = MAX(x->leftChild->height, x->rightChild->height) + 1;

  return x;
}

// left rotate
node *leftRotate(node *x) {
  node *y = x->rightChild;
  node *T2 = y->leftChild;

  y->leftChild = x;
  x->rightChild = T2;

  x->height = MAX(x->leftChild->height, x->rightChild->height) + 1;
  y->height = MAX(y->leftChild->height, y->rightChild->height)+ 1;

  return y;
}

// Get the balance factor
int checkBalance(node *N) {
  if (N == NULL)
    return 0;
  return N->leftChild->height - N->rightChild->height;
}

// Insert node
node *insertAVL(node *curNode, node *newNode) {
  // Find the correct position to insertNode the node and insertNode it
  if (curNode == NULL)
    return (newNode);

   if (newNode->value < curNode->value)
    curNode->leftChild = insertAVL(curNode->leftChild, newNode);
  else if (newNode->value > curNode->value)
    curNode->rightChild = insertAVL(curNode->rightChild, newNode);
  else
    return curNode;

  // Update the balance factor of each node and
  // Balance the tree
  curNode->height = 1 + MAX(curNode->leftChild->height,
               curNode->rightChild->height);

  int balance = checkBalance(curNode);
  if (balance > 1 && newNode->value < curNode->leftChild->value)
    return rightRotate(curNode);

  if (balance < -1 && newNode->value > curNode->rightChild->value)
    return leftRotate(curNode);

  if (balance > 1 && newNode->value > curNode->leftChild->value) {
    curNode->leftChild = leftRotate(curNode->leftChild);
    return rightRotate(curNode);
  }

  if (balance < -1 && newNode->value < curNode->rightChild->value) {
    curNode->rightChild = rightRotate(curNode->rightChild);
    return leftRotate(curNode);
  }

  return curNode;
}
 node *insertBST(node *curNode, node *newNode){
   if (curNode == NULL){
     return newNode;
   }
   if(newNode->value > curNode->value){
     curNode->rightChild = insertBST(curNode->rightChild, newNode);
   }else if(newNode->value < curNode->value){
     curNode->leftChild = insertBST(curNode->leftChild, newNode);
   }
 }

node *minValuenode(node *N) {
  node *current = N;

  while (current->leftChild != NULL)
    current = current->leftChild;

  return current;
}

void printOutput(int numOfNodes){
  int numberOfFullDepthLevels = (int)floor(log2(numOfNodes));
  int numberOfDepthLevels = 3*floor(log(numOfNodes)/log(4));
  int numberOfAccesiveNodes = numOfNodes - (int)pow(2, floor(log2(numOfNodes)))+1-numberOfDepthLevels+numberOfFullDepthLevels+1;
  int remainingNodes = numOfNodes-(int)pow(2, numberOfFullDepthLevels)+1-numberOfAccesiveNodes;
  printf("Output:\n");
  printf("Depth level of BST is %d\n", numberOfDepthLevels);
  int depthLevel;
  printf("full\n");
  for (depthLevel = 0; depthLevel< numberOfFullDepthLevels; depthLevel++){
    printf("Depth level %d -> %d\n", depthLevel, (int)pow(2,depthLevel));
  }
  printf("accces\n");
  printf("Depth level %d -> %d\n", depthLevel++, numberOfAccesiveNodes);
  printf("rest\n");
  while(remainingNodes>0){
    printf("Depth level %d -> %d\n", depthLevel++, 1);
    remainingNodes--;
  }
  
}

node findKey(node *root, int key){
  

}

int main(void){
    FILE *inputFilePtr;
    node* root = NULL;
    int countnodes = 0;
    char currentNumber[11];

    node *arrayOfnodes = calloc(2, sizeof(node));

    // main function gets the dir of input file from command line
    if ((inputFilePtr = fopen("input.txt", "r")) != NULL) {

        // creates a linked list for multiplicand from input
        while (fscanf(inputFilePtr, " %10s", currentNumber) == 1)
        {   
            // check node, if less than zero
            if(atoi(currentNumber) < 0){
                printf("Input file contains values less than zero.\n");
                return -1;
            }
            // check node, if replicate node occurs
            for(int i=0; i < countnodes; i++){
                if (arrayOfnodes[i].value == atoi(currentNumber)){
                    printf("Input file contains replicated keys.\n");
                    return -1;
                }
            }

            node newnode;
            newnode.value = atoi(currentNumber);
            arrayOfnodes[countnodes] = newnode; 
            countnodes++;
            arrayOfnodes = realloc(arrayOfnodes, countnodes+1 * sizeof(node));
        }
        // check number of nodes, give error if less than 16.
        if (countnodes < 16){
          printf("Input file contains less than 16 elements.\n");
          return -1;
        }

        // sort the array in descending order.
        insertionSort(arrayOfnodes, countnodes);


        for (int i = 0; i < countnodes; i++)
        {
            //root = insertAVL(root, &arrayOfnodes[i]);
            printf("node %d\n", arrayOfnodes[i].value);
        }

        printOutput(countnodes);
        
    }
    free(arrayOfnodes);
    return 0;
}