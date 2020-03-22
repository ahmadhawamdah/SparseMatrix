//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{ //to rename the struct as node
   void* data; // to show the actual data in the node
   struct NodeObj* before; // points to the node before current
   struct NodeObj* after; //points to the node after current
} NodeObj;

typedef struct NodeObj* Node;

typedef struct ListObj{
   Node front;  // front of the list
   Node back; // back of the list
   Node curser; // the arrow/curser to traverse through the list

   int index; //the location of the chars
   int length; // size of the list
} ListObj;






Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->before = NULL;
   N->after = NULL;

   return(N);
}







void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}






List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->curser = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}






void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while(!isEmpty(*pL)) {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}





int length(List L){
   return(L->length);
}



int index(List L) {
   return(L->index);
}






void* front(List L){
   if(L==NULL){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}






void* back(List L){
   if(L==NULL){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}






void* get(List L){
    if (L == NULL){
        printf("List Error: calling get() on NULL List \n");
        exit(1);
    }
    if (length(L) <= 0){
        printf("List Error: calling get() on empty List \n");
    }
    if (L->curser == NULL){
        printf("List Error: cursor is NULL \n");
    }
    return L->curser->data;
}






int isEmpty(List L){
   if(L==NULL){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}






void clear(List L){
    if (L == NULL){
        printf("List Error: calling clear() on NULL List \n");
    }
    while (length(L) > 0){
        deleteFront(L);
    }
    L->front = NULL;
    L->back = NULL;
    L->curser = NULL;
    L->length = 0;
    L->index = -1;
}






void moveFront(List L){
   if(L==NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
    
    if (length(L) > 0) {
        L->curser = L->front;
        L->index = 0;
    }
}






void moveBack(List L) {
   if(L==NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }

    if (length(L) > 0) {
        L->curser = L->back;
        L->index = L -> length-1;
    }
}






void movePrev(List L){
    if (L == NULL){
        printf("List Error: calling movePrev() on NULL List \n");
        exit(1);
    }
    if(L->index != -1) {
        L->curser = L->curser->before;
        L->index--;
        if(L->curser == NULL){
        L->index = -1;
        }
    }
}






void moveNext(List L){
    if (L == NULL){
        printf("List Error: calling moveNext() on NULL List \n");
        exit(1);
    }

    if (L->index != -1) {
        L->curser = L->curser->after;
        L->index++;
        if(L->curser == NULL){
            L->index = -1;
        }
    }
}






void prepend(List L, void* data){

  if(L==NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
    
    Node N = newNode(data);
     
    if (length(L) == 0){
         L->back = L->front = N;
    } else {
         
         L->front->before = N;
         N->after = L->front;
         L->front = N;
    }
    L->length++;
    
    if(((L->index)) >= 0)
        L->index++;
}






void append(List L, void* data) {

   if(L==NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   
    Node N = newNode(data);
    
       if (length(L) == 0) {
        L->front = L->back = N;
    } else {
        L->back->after = N;
        N->before = L->back;
        L->back = N;
    }
   L->length++;
}






void insertBefore(List L, void* data){
    if (L == NULL){
        printf("List Error: insertBefore() called on NULL List \n");
        exit(1);
    }
    if (L->length == 0){
        printf("List Error: insertBefore() called on empty List \n");
        exit(1);
    }
    
    if (L->index < 0){
        printf("List Error: insertBefore() called on empty List \n");
        exit(1);
    }

    Node N = newNode(data);
    if (L->index == 0){
        L->front->before = N;
        N->after = L->front;
        L->front = N;
    } else {
        N->after = L->curser;
        N->before = L->curser->before;
        L->curser->before->after = N;
        L->curser->before = N;
    }
    L->index++;
    L->length++;
}






void insertAfter(List L, void* data){
    if (L == NULL){
        printf("List Error: insertAfter() called on NULL List \n");
        exit(1);
    }
    if (L->length == 0){
        printf("List Error: insertAfter() called on empty List \n");
        exit(1);
    }
    
    if (L->index < 0){
        printf("List Error: insertAfter() called on empty List \n");
        exit(1);
    }
     Node N = newNode(data);
       
       if (L->index == (L->length) - 1){
           L->back->after = N;
           N->before = L->back;
           L->back = N;
       } else {
           N->before = L->curser;
           N->after = L->curser->after;
           L->curser->after->before = N;
           L->curser->after = N;
       }
       L->length++;
}






void deleteFront(List L){
    if (length(L) == 0){
        printf("List Error: calling deleteFront() on empty List \n");
        exit(1);
    }
    
    if (L == NULL){
        printf("List Error: calling deleteFront() on empty List \n");
        exit(1);
    }

    Node N = NULL;
    if (L->index == 0) {
        L->curser = NULL;
        L->index = -1;
    } else if (L->length > 1) {
        N = L->front;
        L->front = L->front->after;
        L->front->before = NULL;
        L->index--;
    } else {
        N = L->front;
        L->front = L->back = NULL;
        L ->index = -1;
    }
    L -> length--;
    freeNode(&N);
}






void deleteBack(List L){
    if (length(L) == 0){
        printf("List Error: calling deleteBack() on empty List \n");
        exit(1);
    }
    
    if (L == NULL){
        printf("List Error: calling deleteBack() on empty List \n");
        exit(1);
    }

    Node N = NULL;
    if (L->index == (L->length) -1) {
        L->curser = NULL;
        L ->index = -1;
    }
    if (L->length > 1){
        N = L->back;
        L->back = L->back->before;
        L->back->after = NULL;
    } else {
        N = L->back;
        L->front = L->back = NULL;
    }
    freeNode(&N);
    L -> length--;
}






void delete(List L){
    if (length(L) == 0){
        printf("List Error: calling delete() on empty List \n");
        exit(1);
    }
    
    if (L == NULL){
        printf("List Error: calling delete() on empty List \n");
        exit(1);
    }
    
    if (L->index < 0){
        printf("List Error: calling delete() on empty List \n");
        exit(1);
    }
    
    Node N = NULL;
    if(L->index == 0) {
        deleteFront(L);
    } else if(L->index == (L->length) - 1) {
        deleteBack(L);
    } else {
        N = L->curser;
        L->curser = NULL;
        N->before->after = N->after;
        N->after->before = N->before;
        L->length--;
        L->index = -1;
        freeNode(&N);
    }
}






List copyList(List L){
    List B = newList();
    Node N = NULL;
    
    for(N=L->back ; N!=NULL ; N=N->before) {
        prepend(B,N->data);
    }
    return(B);
}


