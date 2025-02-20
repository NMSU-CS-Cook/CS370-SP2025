//
// Linked List example in plain C
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int feet;
typedef int inches;
inches x;

typedef struct ListElement
{
   int id;
   char* val;
   struct ListElement * next;
} ListElement;

void printElements(ListElement * elems, int count)
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
      newElem = (struct ListElement *) malloc(sizeof(ListElement));
      newElem->id = 100+i;
      newElem->val = argv[i];
      newElem->next = NULL;
      // attach to list
      if (args == NULL) 
         args = newElem;
      else {
         newElem->next = args;
         args = newElem;
      }
   }
   printElements(args,argc);
   return 0;
}









