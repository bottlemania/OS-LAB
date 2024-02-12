#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int total=10;
int booked=0;

int server=0,client=0,turn=1;

void* server_process(void* arg){
    while(1){
        server=1;
        turn=0;
        while(client==1&&turn==0);

        //critical
        printf("\nSERVER: Total available seats= %d\t\tBooked Seats= %d",total,booked);
        int choice;
        printf("\nSERVER: 1.Quit  2.Continue  \nYOUR CHOICE:");
        scanf("%d",&choice);

        if(choice=2);
        else if(choice=1)   return NULL;
        else         printf("\nInvalid Choice!\n");

        server=0;
    }
    return NULL;
}

void* client_process(void* arg){
    while(1){
        client=1;
        turn=1;
        while(server==1&&turn==1);
        
        //critical
        printf("\nCLIENT: Total available seats= %d\t\tBooked Seats= %d",total,booked);
        int choice;
        printf("\nCLIENT: 1.Book  2.Cancel    3.Exit  YOUR CHOICE: ");
        scanf("%d",&choice);
        if(choice==3){return NULL;}
        else if(choice==1){
            int count;
            printf("\nEnter number of seats to book:");
            scanf("%d",&count);
            if (count <= total) {
                total -= count;
                booked +=count;
            } else {
                printf("\nClient: Not enough seats to book.\n");
            }            
        }
        else if(choice==2){
        	int count;
            printf("\nEnter number of seats to cancel:");
            scanf("%d",&count);
            if (count <= booked) {
                total += count;
                booked -=count;
            } else {
                printf("\nClient: Invalid cancellation, exceeds booked count.\n");
            }            
        }
        else{
            printf("\nInvalid choice!\n");
        }
        client=0;
    }
    return NULL;    
}

int main(){
    pthread_t server_thread;
    pthread_t client_thread;
    pthread_create(&server_thread,NULL,server_process,NULL);
    pthread_create(&client_thread,NULL,client_process,NULL);
    pthread_join(server_thread,NULL);
    pthread_join(client_thread,NULL);
    return 0;
}