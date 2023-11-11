/****************************************************************************************
*  ListClient.c
*  Lucais Sanderson - lzsander
*  Test client for List ADT
*****************************************************************************************/

/****************************************************************************************
*  Base of this source file is not mine.
*  Found in examples at:
*  https://people.ucsc.edu/~ptantalo/cse101/Spring23/Examples/pa1/ListClient.c
*  Test client for List ADT
*****************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      assert(length(A)==i);
      prepend(B,i);
      assert(length(B)==i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   assert(index(A)==5);
   insertBefore(A, -1);            // at index 6
   assert(index(A)==6);
   for(i=0; i<9; i++) moveNext(A); // at index 15
   assert(index(A)==15);
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   assert(index(A)==10);
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

// begin my own tests --------------------------------

    // test deleteback and deletefront
    moveFront(A);
    for(i = 0; i < 10; i++){
        append(A, i);
    }
    assert(length(A)==10);
    moveBack(A);
    assert(index(A)==9);
    for(i = 9; i >= 0; i--){
        deleteBack(A);
        assert(length(A)==i);
    }
    clear(A);
    assert(length(A)==0);

    for(i = 0; i < 10; i++){
        append(A, i);
    }
    assert(length(A)==10);
    moveFront(A);
    assert(index(A)==0);
    for(i = 0; i < 10; i++){
        deleteFront(A);
        assert(length(A)==9-i);
    }
    clear(A);
    assert(length(A)==0);

    for(i = 0; i < 10; i++){
        prepend(A, i);
        printList(stdout, A);
        printf("\n");
    }
    printList(stdout, A);
    printf("\n");
    moveBack(A);
    assert(index(A)==9);
    deleteBack(A);
    printList(stdout, A);
    printf("\n");
    assert(index(A)==-1);
    deleteBack(A);
    printList(stdout, A);
    printf("\n");
    assert(index(A)==-1);
    deleteBack(A);
    printList(stdout, A);
    printf("\n");
    assert(index(A)==-1);
    clear(A);

    // test delete
    for(i = 0; i < 10; i++){
        append(A, i);
    }
    moveFront(A);
    delete(A);
    assert(length(A)==9);
    moveBack(A);
    delete(A);
    assert(length(A)==8);



   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/
