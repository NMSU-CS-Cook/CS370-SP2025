//
// Linked List example in plain C
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
   ListElement * args = NULL;
   ListElement * newElem = NULL;
   for (i=0; i < argc; i++) {
      printf("argv[%d] = (%s)\n", i, argv[i]);
      newElem = newListElement(100+i, argv[i]);
      // attach to list
      if (args == NULL) 
         args = newElem;
      else {
         newElem->next = args;
         args = newElem;
      }
   }
   printElements(args);
   return 0;
}









