//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"


typedef struct MatrixObj{
    
    int size, NNZ;
    List* L;
    
} MatrixObj;


typedef struct EntryObj{
    int col;
    double val;
} EntryObj;

typedef struct EntryObj* Entry;

Entry newEntry(int c, double v) {
    Entry E;
    E = malloc(sizeof(EntryObj));
    E->col = c;
    E->val = v;
        
    return(E);
}






Matrix newMatrix(int n) {
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    M->L = malloc(n * sizeof(List));
    
    M->size = n;
    M->NNZ = 0;
    
    for (int ind = 0; ind < n; ind++) {
        M->L[ind] = newList();
    }
    return (M);
}






void freeMatrix(Matrix* pM) {

    if(pM != NULL && *pM != NULL) {
    makeZero(*pM);
    for (int ind = 0; ind < size(*pM); ind++) {
        freeList(&((*pM))->L[ind]); //free List
    }
    free((*pM)->L); // free * to a list
    free(*pM); // free matrix
    *pM = NULL;
    }
}






void freeEntry(Entry *pE) {
    if(pE!=NULL && *pE!=NULL) {
        free(*pE);
        *pE = NULL;
    }
}






int size(Matrix M) {
    if(M==NULL) {
        printf("Matrix Error: calling int size() on NULL Matrix reference\n");
        exit(1);
    }
    return (M->size);
};






int NNZ(Matrix M) {
    if(M==NULL) {
        printf("Matrix Error: calling int size() on NULL Matrix reference\n");
        exit(1);
    }
    return (M->NNZ);
};






void changeEntry(Matrix M, int i, int j, double x) {

    if (i < 1 || i > M->size) {
    printf("Matrix Error: calling changeEntry() on rows exceeded boundris\n");
    exit(1);
    }
    if (j < 1 || j > M->size) {
    printf("Matrix Error: calling changeEntry() on col exceeded boundris\n");
    exit(1);
    }

    Entry E = newEntry(j,x);
    List L = M->L[i - 1];
  
    
        moveFront(L);
        Entry arrow = NULL;
        while (index(L) > -1) {
            arrow = (Entry)get(L);
            if (arrow->col >= j) {
                break;
            }
            moveNext(L);
        }
        
        if (E==NULL || index(L) == -1) {
            if (x!=0) {
            append(L, E);
            M->NNZ++;
            }
        } else if (arrow->col == j && x == 0) {
            delete(L);
            M->NNZ--;
       } else if (arrow->col == j && x != 0) {
            arrow->val = x;
       }  else if (arrow->col > j && x!=0) {
           insertBefore(L, E);
           M->NNZ++;
       }
}






void printMatrix(FILE* out, Matrix M) {

   if( M==NULL ) {
      printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
      exit(1);
   }
        for (int ind = 0; ind < M->size; ind++) {
            List L = M->L[ind];
            if (length(L) != 0) {
                moveFront(L);
                Entry arrow = (Entry)get(L);
                fprintf(out, "\n%d: ", ind + 1);
                while (index(L) > -1){
                    arrow = (Entry)get(L);
                    fprintf(out, "(%d, %0.1f) ", arrow->col, arrow->val);
                    moveNext(L);
            }
        }
    }
}






Matrix copy(Matrix A) {
    
    Matrix M = newMatrix(A->size);
    
    for (int ind = 0; ind < M->size; ind++) {
        List L = A->L[ind];
        if (length(L) != 0) {
            moveFront(L);
            Entry arrow = (Entry)get(L);
            while (index(L) > -1) {
                arrow = (Entry)get(L);
                changeEntry (M, ind + 1, arrow->col, arrow->val);
                moveNext(L);
            }
        }
    }
    return (M);
}







Matrix scalarMult(double x, Matrix A) {
    
    Matrix M = newMatrix(A->size);
    if (NNZ(A) != 0 && x != 0) {
        for (int ind = 0; ind < M->size; ind++) {
            List L = A->L[ind];
            if (length(L) != 0) {
                moveFront(L);
                Entry arrow = (Entry)get(L);
                while (index(L) > -1) {
                    arrow = (Entry)get(L);
                    changeEntry (M, ind + 1, arrow->col, arrow->val * x);
                    moveNext(L);
                }
            }
        }
    }
    return (M);
}






void makeZero(Matrix M) {
    if( M==NULL ) {
         printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
         exit(1);
      }
   for (int ind = 0; ind < M->size; ind++) {
       List L = M->L[ind];
       moveFront(L);
       while (index(L) > -1) {
           Entry E = (Entry)get(L);
           freeEntry(&E);
           moveNext(L);
       }
       clear(L);
   }
    M->NNZ = 0;
}






Matrix transpose(Matrix A) {
    Matrix M = newMatrix(A->size);
    
    for (int ind = 0; ind < M->size; ind++) {
        List L = A->L[ind];
        if (length(L) != 0) {
            moveFront(L);
            Entry arrow = (Entry)get(L);
            while (index(L) > -1) {
                arrow = (Entry)get(L);
                changeEntry (M, arrow->col, ind + 1, arrow->val);
                moveNext(L);
            }
        }
    }
    return (M);
}





Matrix sum(Matrix A, Matrix B) {

    if (size(A) != size(B)) {
       printf("Matrix Error: calling sum() Matrices with unmatching sizes\n");
       exit(1);
    }

    if(A==NULL || B==NULL) {
       printf("Matrix Error: calling sum() on NULL Matrix reference\n");
       exit(1);
    }
    
    Matrix C = NULL;
    Matrix M = newMatrix(A->size);
    
    if (A == B) {
        C = copy(B);
    } else {
        C = B;
    }
        for (int i = 1; i <= M->size; i++) {
            List L1 = A->L[i - 1];
            List L2 = C->L[i - 1];
            moveFront(L1);
            moveFront(L2);
            
            while (index(L1) >= 0 && index(L2) >=0) {
                Entry E1 = (Entry)get(L1);
                Entry E2 = (Entry)get(L2);
                if (E1->col == E2->col) {
                    changeEntry(M, i, E1->col, (E1->val + E2 ->val));
                    moveNext(L1);
                    moveNext(L2);
                } else if (E1->col < E2->col) {
                    changeEntry(M, i, E1->col, E1->val);
                    moveNext(L1);
                } else if (E1->col > E2->col) {
                    changeEntry(M, i, E2->col, E2->val);
                    moveNext(L2);
                }
            }
            
            while (index(L1) >= 0 && index(L1) != length(L1)) {
                Entry arrow = (Entry)get(L1);
                changeEntry(M, i, arrow->col, arrow->val);
                moveNext(L1);
            }
        
            while (index(L2) >= 0 && index(L2) != length(L2)) {
                Entry arrow = (Entry)get(L2);
                changeEntry(M, i, arrow->col, arrow->val);
                moveNext(L2);
            }
        }
    if (A == B) {
        freeMatrix(&C);
      }
    
    return (M);
}






Matrix diff(Matrix A, Matrix B) {

    if (size(A) != size(B)) {
       printf("Matrix Error: calling diff() Matrices with unmatching sizes\n");
       exit(1);
       }

    if(A==NULL || B==NULL) {
       printf("Matrix Error: calling diff() on NULL Matrix reference\n");
       exit(1);
    }
    
    Matrix C = NULL;
    Matrix M = newMatrix(A->size);
    
    if (A == B) {
         C = copy(B);
     } else {
         C = B;
     }
    
    for (int i = 1; i <= M->size; i++) {
        List L1 = A->L[i - 1];
        List L2 = B->L[i - 1];
        
        moveFront(L1);
        moveFront(L2);
        
        while (index(L1) >= 0 && index(L2) >=0) {
            Entry E1 = (Entry)get(L1);
            Entry E2 = (Entry)get(L2);
            if (E1->val == E2->val) {
                moveNext(L1);
                moveNext(L2);
            } else {
            if (E1->col == E2->col) {
                changeEntry(M, i, E1->col, (E1->val - E2->val));
                moveNext(L1);
                moveNext(L2);
            } else if (E1->col < E2->col) {
                changeEntry(M, i, E1->col, E1->val);
                moveNext(L1);
            } else if (E1->col > E2->col) {
                changeEntry(M, i, E2->col, -1 * E2->val);
                moveNext(L2);
            }
        }
        }
        while (index(L1) >= 0 && index(L1) != length(L1)) {
            Entry arrow = (Entry)get(L1);
            changeEntry(M, i, arrow->col, arrow->val);
            moveNext(L1);
        }
    
        while (index(L2) >= 0 && index(L2) != length(L2)) {
            Entry arrow = (Entry)get(L2);
            changeEntry(M, i, arrow->col, -1 * arrow->val);
            moveNext(L2);
        }
    }
    if (A == B) {
        freeMatrix(&C);
    }
    return (M);
}





            
double dotProduct(List A, List B) {

    double dotP = 0;

    moveFront(A);
    moveFront(B);
    
    while (index(A) > -1 && index(B) > -1) {
        Entry E1 = (Entry)get(A);
        Entry E2 = (Entry)get(B);
        if(E1->col == E2->col) {
            dotP = dotP + (E1->val * E2->val);
            moveNext(A);
            moveNext(B);
        } else if (E1->col < E2->col) {
            moveNext(A);
        } else if (E1->col > E2->col) {
            moveNext(B);
        }
    }
    return (dotP);
}






Matrix product(Matrix A, Matrix B) {
    
     if (size(A) != size(B)) {
         printf("Matrix Error: calling product() Matrices with unmatching sizes\n");
         exit(1);
         }

      if(A==NULL || B==NULL) {
         printf("Matrix Error: calling product() on NULL Matrix reference\n");
         exit(1);
      }
    
    Matrix P = newMatrix(A->size);
    Matrix T = transpose(B);
    
    for (int i = 1; i <= A->size; i++) {
        for (int j = 1; j <= B->size; j++) {
            double dotP = dotProduct(A->L[i - 1], T->L[j - 1]);
            if (dotP != 0) {
                changeEntry(P, i, j, dotP);
            }
        }
    }
    return (P);
}







int equals(Matrix A, Matrix B) {

 if(A==NULL || B==NULL) {
    printf("Matrix Error: calling equals() on NULL Matrix reference\n");
    exit(1);
 }

if (size(A) == size(B) && NNZ(A) == NNZ(B)) {
        for (int i = 1; i <= A->size; i++) {
            List L1 = A->L[i - 1];
            List L2 = B->L[i - 1];
                
            moveFront(L1);
            moveFront(L2);
            if (NNZ(A) == NNZ(B)) {
                if (length(L1) == length(L2)) {
                    while (index(L1) >= 0 && index(L2) >=0) {
                        Entry E1 = (Entry)get(L1);
                        Entry E2 = (Entry)get(L2);
                        if (E1->col == E2->col) {
                            if (E1->val == E2->val) {
                                moveNext(L1);
                                moveNext(L2);
                            }
                        } else if (E1->col < E2->col) {
                                return 0;
                        } else if (E1->col > E2->col) {
                                return 0;
                        }
                        }
                    } else {
                        return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

