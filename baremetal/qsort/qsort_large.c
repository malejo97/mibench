#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define UNLIMIT
#define MAXARRAY 60000 /* this number, if too large, will cause a seg. fault!! */

struct my3DVertexStruct {
  int x, y, z;
  double distance;
};

int compare(const void *elem1, const void *elem2)
{
  /* D = [(x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2]^(1/2) */
  /* sort based on distances from the origin... */

  double distance1, distance2;

  distance1 = (*((struct my3DVertexStruct *)elem1)).distance;
  distance2 = (*((struct my3DVertexStruct *)elem2)).distance;

  return (distance1 > distance2) ? 1 : ((distance1 == distance2) ? 0 : -1);
}


  struct my3DVertexStruct array[MAXARRAY];
int
//main(int argc, char *argv[]) {
qsort_large() {
  //FILE *fp;
  int i,count=0;
  int x, y, z;
  
  // if (argc<2) {
  //   fprintf(stderr,"Usage: qsort_large <file>\n");
  //   exit(-1);
  // }
  // else {
  //   fp = fopen(argv[1],"r");
    
  //   while((fscanf(fp, "%d", &x) == 1) && (fscanf(fp, "%d", &y) == 1) && (fscanf(fp, "%d", &z) == 1) &&  (count < MAXARRAY)) {
	//  array[count].x = x;
	//  array[count].y = y;
	//  array[count].z = z;
	//  array[count].distance = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	//  count++;
  //   }
  // }

  // struct my3DVertexStruct *data = 0x31830000;
	char *ptr;
	ptr = (char*) 0x32400000;
	int /*j=0,*/ stage = 0;

	while (*ptr != '\n' && count < 50000/*QSORT_LARGE*/) 
  {
    int i = 0;
    char qstring[25];
        // Copy characters from ptr to temp[count].qstring
    while (*ptr != '\n' && *ptr != '\0' && i < 24 ) {
		  if (*ptr == 0x9) {ptr++; break;}
      qstring[i++] = *(ptr++);
    }

    qstring[i] = '\0'; // Terminate the string with the null character
		switch (stage){
			case 0: 
				array[count].x = atoi(qstring);
				// printf ("x = %d\n", array[count].x);
				break;
			case 1:
				array[count].y = atoi(qstring);
				// printf ("y = %d\n", array[count].y);
				break;
			case 2:
				array[count].z = atoi(qstring);
				array[count].distance = sqrt(pow(array[count].x, 2) + pow(array[count].y, 2) + pow(array[count].z, 2));
				stage = -1;
				// printf ("z = %d\n", array[count].z);
				// printf ("dist = %f\n", array[count].distance);
        count++; 
				break;
		}

    stage++;
		
    if (count==50000) break;		// TBD
      if (*ptr == '\n') {
        ptr++; // Move past the newline character
      }
  }
  
//////  printf("\nSorting %d vectors based on distance from the origin.\n\n",count);
  qsort(array,count,sizeof(struct my3DVertexStruct),compare);
  
//////  for(i=0;i<count;i++)
//////    printf("%d %d %d\n", array[i].x, array[i].y, array[i].z);
  return 0;
}
