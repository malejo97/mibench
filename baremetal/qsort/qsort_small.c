#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNLIMIT
#define MAXARRAY 11000//60000 /* this number, if too large, will cause a seg. fault!! */

struct myStringStruct {
  char qstring[16];//25];
};

int compare(const void *elem1, const void *elem2)
{
  int result;
  
  result = strcmp((*((struct myStringStruct *)elem1)).qstring, (*((struct myStringStruct *)elem2)).qstring);

  return (result < 0) ? 1 : ((result == 0) ? 0 : -1);
}


// int
// //main(int argc, char *argv[]) {
// qsort_small(struct myStringStruct *array, size_t size) {

//   //int i=0;

//   //printf("\nSorting %d elements.\n\n",size);
//   qsort(array,size,sizeof(struct myStringStruct),compare);
  
//   //for(i=0;i<size;i++)
//   //  printf("%d - %s\n", i, array[i].qstring);
//   return 0;
// }


struct myStringStruct array[MAXARRAY];
int
// main(int argc, char *argv[]) {
qsort_small() {
  // FILE *fp;
  int i,count=0;
  
  // if (argc<2) {
  //   fprintf(stderr,"Usage: qsort_small <file>\n");
  //   exit(-1);
  // }
  // else {
  //   fp = fopen((const char*) 0x32230000 /*file*/,"r");
    
  //   while((fscanf(fp, "%s", &array[count].qstring) == 1) && (count < MAXARRAY)) {
	//  count++;
  //   }
  // }


  /*** Instead of fscanf ***/
  count=10000;
  char* ptr = (char*) 0x32400000;//0x32240000;
  int j=0;
  while (*ptr != '\n' && j < count) {
    i = 0;
    // Copy characters from ptr to temp[j].qstring
    // while (*ptr != '\n' && *ptr != '\0' && i < 24) 
    while (*ptr != 0x0A && *ptr != 0xFF && *ptr != 0x0) 
    {
////////////      printf("%c", *ptr);
      array[j].qstring[i++] = *(ptr++);
    }
////////////    printf("\n");
    array[j].qstring[i] = '\0'; // Terminate the string with the null character
    j++;
  	if (j==10000) break;
    if (*ptr == '\n') {
      ptr++; // Move past the newline character
    }
  }
  /******/


/////////////  printf("\nSorting %d elements.\n\n",count);
  qsort(array,count,sizeof(struct myStringStruct),compare);
  
/////////////  for(i=0;i<count;i++)
/////////////    printf("%s\n", array[i].qstring);
  return 0;
}
