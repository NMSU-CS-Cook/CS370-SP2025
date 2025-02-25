//
// Hash table with Linked Lists example in plain C
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListElement
{
   int id;
   char* val;
   struct ListElement * next;
} ListElement;  // new type name

// "constructor" of a ListElement
ListElement* newListElement(int id, char* val)
{
    ListElement* newElem;
    newElem = (ListElement*) malloc(sizeof(ListElement));
    newElem->id = id;
    newElem->val = val;
    newElem->next = NULL;
    return newElem;
}

// think of this as "elems->printElements()"
void printElements(ListElement * elems)
{
   while (elems != NULL) {
       printf("%d: (%s)\n", elems->id, elems->val);
       elems = elems->next;
   }
}



int main(int argc, char* argv[])
{
   int i;
   ListElement* argtable[3] = {NULL};  // hash table
   ListElement * newElem = NULL;
   for (i=0; i < argc; i++) {
      printf("argv[%d] = (%s)\n", i, argv[i]);
      newElem = newListElement(100+i, argv[i]);
      // hash to table index
      int h = argv[i][0] % 3;
      // attach to table list
      if (argtable[h] == NULL) 
         argtable[h] = newElem;
      else {
         newElem->next = argtable[h];
         argtable[h] = newElem;
      }
   }
   printf("list 0:\n");
   printElements(argtable[0]);
   printf("list 1:\n");
   printElements(argtable[1]);
   printf("list 2:\n");
   printElements(argtable[2]);
   return 0;
}









