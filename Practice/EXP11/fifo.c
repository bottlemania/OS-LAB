#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

void printFrames(int frames[],int fcount){
    for(int i=0;i<fcount;i++){
        if(frames[i]==-1)   printf( " - " );
        else    printf(" %d ",frames[i]);
    }
    printf("\n");
}

int isPageInFrames(int frames[],int fcount,int page){
    for(int i=0;i<fcount;i++) 
        if(frames[i]==page) return 1;
    return 0;
}

void fifo(int pages[],int pcount,int frames[],int fcount){
    int faults=0,hit=0,oldestPage=0;
    for(int i=0;i<pcount;i++){
        printf("Reference: %d - Frames:",pages[i]);
        printFrames(frames,fcount);
        if(!isPageInFrames(frames,fcount,pages[i])){
            frames[oldestPage]=pages[i];
            oldestPage=(oldestPage+1)%fcount;
            faults++;
            printf("Page Fault!\n");
        }
        else{
            hit++;
            printf("Page Hit!\n");
        }
    }
    float hitRatio = (float)hit/pcount;
    float missRatio = (float)faults/pcount;
    printf("\nNo of page faults: %d \n",faults);
    printf("No of hits: %d \n",hit);
    printf("Hit Ratio : %.2f \n",hitRatio*100);
    printf("Miss Ratio : %.2f \n",missRatio*100);
}

int main(){
    int pages[]={1, 3, 0, 3, 5, 6, 3};
    int pcount=sizeof(pages)/sizeof(pages[0]);
    int fcount=MAX_FRAMES;
    int frames[fcount];
    for (int i=0;i<fcount;i++)  frames[i]=-1;
    fifo(pages,pcount,frames,fcount);
}