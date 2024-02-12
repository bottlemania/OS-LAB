#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 10
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;
    // ftok to generate unique key
    key = ftok("progfile", 65);
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    //message.mesg_type = 1;
    printf("Writing Data : ");
    printf("\nEnter the message:");
    scanf("%s",message.mesg_text);

    do
    {
    printf("\nEnter the type for message:");
    scanf("%ld",&message.mesg_type);
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
    // display the message
    //printf("Data send is : %s \n", message.mesg_text);
    printf("\nEnter the message:");
    scanf("%s",message.mesg_text);
    }while(strcmp(message.mesg_text,"end")!=0);
    
    return 0;
}
