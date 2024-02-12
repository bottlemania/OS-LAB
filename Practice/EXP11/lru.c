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

int findlruIndex(int counter[],int fcount){
    int min=counter[0];
    int minIndex=0;
    for(int i=0;i<fcount;i++){
        if(counter[i]<min){
            min=counter[i];
            minIndex=i;
        }
    }
    return minIndex;
}

void lru(int pages[],int pcount,int frames[],int fcount){
    int faults=0,hit=0;
    int counter[MAX_FRAMES];
    int time=0;
    for (int i=0;i<fcount;i++){
        frames[i]=-1;
        counter[i]=0;
    }
    for(int i=0;i<pcount;i++){
        printf("Reference: %d - Frames:",pages[i]);
        printFrames(frames,fcount);
        if(!isPageInFrames(frames,fcount,pages[i])){
            int lruIndex=findlruIndex(counter,fcount);
            frames[lruIndex]=pages[i];
            counter[lruIndex]=++time;
            faults++;
            printf("Page Fault!\n");
        }
        else{
            for(int j=0;j<fcount;j++){
                if(frames[j]==pages[i]){
                    counter[j]=++time;
                    break;
                }
            }
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
    lru(pages,pcount,frames,fcount);
}