#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5
#define LINE_MAX 1024


struct linkedList {
	
    	int Name; //Name
    	int bTime; //Brust Time
    	int aTime; //Arrival Time
    	int wTime; //Waiting Time
    	int pr; //Priority    	
    	int sr; //Show Result
}
linkedList;
void FCFserve(struct linkedList process[]){
    FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
    struct linkedList *temp;
    	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i;
   	 	int totalWaiting=0;
    	double averageWaiting;
for(i=0;i<SIZE;i++)
        temp[i]=process[i];

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) 
		
		{
            if (temp[b].aTime > temp[b + 1].aTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            
            }
        }
         }

    totalWaiting = temp[0].wTime = 0;

    for(i = 1; i < SIZE; i++){
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        
        totalWaiting += temp[i].wTime;
    }
    
    	averageWaiting = (double)totalWaiting/SIZE;
    		fprintf(fptr, "%s" ,"\nScheduling Method : First Come First Served\nProcess Waiting Times:\n");

    for(i = 0; i < SIZE; i++) 
	{
		
        fprintf(fptr,"\nP%d: %d ms", i+1, temp[i].wTime);
    
	}

    fprintf(fptr, "\nAverage waiting time: %f ms\n",averageWaiting);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}
