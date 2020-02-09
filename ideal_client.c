#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> // for inet_addr
#include <string.h>
#include "zconf.h"
#include <stdlib.h>
#include <pthread.h>
#include<sys/types.h>
#include<netinet/in.h>



char user_id[1000];
void *sendMessage(void *sock_desc) {
    //Send some data
    while (1) {
      sleep(1);
        char input_command[2000]="";
        char message[100];
        printf("Enter command:\n");
          scanf("%[^\n]%*c", input_command);
        //gets(input_command);
      //  printf("Enter message:\n");
        //scanf("%s\n",message);
        strcpy(message,user_id);
        strcat(message,"-");
        strcat(message,input_command);

        //printf("%s","> ");


       //fflush(stdin);

        if (send(*((int *) sock_desc),message,strlen(message) + 1, 0) < 0) {
            puts("Send failed");
        }
    }
}

void *receiveMessage(void *sock_desc) {
     int i =0;
    while (1) {
    sleep(1);
  char server_reply[2000],reply[50][10000];

         if(recv(*((int *) sock_desc), server_reply,sizeof(server_reply), 0)>0){

           strcpy(reply[i],server_reply);
           //Receive a reply from the server
           printf("\t\t----------------------------------------------------\n");
           printf("\t\tResult:\t %s\n",reply[i]);
           printf("\t\t----------------------------------------------------\n");
           //printf("\t\t\033[32;1m %s \033[0m\n",server_reply);
         }
         else{
             puts("recv failed");
         }

    }
}

int main(int argc, char *argv[]) {




    int sock;
    struct sockaddr_in server;
    //char               message[2000], server_reply[2000];

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    //to connect over a network uncomment the code below.
    int port_no = atoi(argv[2]);
    //server.sin_addr.s_addr = inet_addr(argv[1]);
 // server.sin_port        = htons(port_no);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
   server.sin_port        = htons(9006);
  server.sin_family      = AF_INET;
    //Connect to remote server
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Connection failed. Error");
        return 1;
    }

    puts("******Connected to server******\n");
    printf("Enter your user id:\n");
    scanf("%[^\n]%*c", user_id);
    printf("Enter the command to perform the jobs in the formats below:\n");
    printf("1: To double word;     Double sara\n");
    printf("2: To reverse word;    Reverse sara\n");
    printf("3: To delete letters;  Delete chair 1,2\n");
    printf("4: To replace letters; Replace middle 1-h, 2-u, 3-s, 4-t \n");
    printf("5: To encrypt word;    Encrypt zoo \n");
    printf("6: To decypt word;     Decrypt 2y1Hp76 \n");
    printf("Enter stop to exit the program\n");
    printf("*(Please enter a string of not more than 50 characters else it will not be worked apon!)*\n");
  //  printf("Enter your command from the above list::\n");
    int *new_sock;

    new_sock = malloc(1);
    *new_sock = sock;
    //keep communicating with server


    pthread_t send_thread, receive_thread;
    pthread_create(&receive_thread, NULL, receiveMessage, (void *) new_sock);
    pthread_create(&send_thread, NULL, sendMessage, (void *) new_sock);


     pthread_join(send_thread, NULL);
     pthread_join(receive_thread, NULL);
     printf("AFTER the Threads\n");



    close(sock);
    return 0;
}
