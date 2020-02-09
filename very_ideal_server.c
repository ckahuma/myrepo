#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<stdint.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<ctype.h>
#include <sys/file.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
#define MAX_CLIENTS 5

//declaring a globl array to assign the letters in the alphabet to integer indexes starting from a=1,b=2 etc
char letters[]={'.','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};

char* itoa(int value, char *result, int base);
char get_character(int position);
int assign_letters(char letter);
void append(char subject[], const char insert[], int pos);
void Reverse(char str[]);
char* assign_priority(char str[],int num);
int get_min(int array[],int size);
void taskProcessor(char jobs[]);
void DeleteLine(int line_num);
int my_counter =-1;

//the thread function
void *new_connection_handler(void *);

int is_blank_line(const char *line)
{
    const char accept[]=" \t\r\n"; /* white space characters (fgets stores \n) */
    return (strspn(line, accept) == strlen(line));
}



FILE *CreateLogFile()
{
    return fopen("myfile.txt","r"); // allocates a FILE object and returns a pointer to it
}

pthread_t thread;

void* priority_thread(void *arg)
{
  char Array_p1[100][200];
  int countp=0;
  char line1[10000];
  int countU001;
  int countU002;
  int stringlen=-1;
  int arry_of_lengths[100];
  char *ptntr,*ptntr1;
  char result[100];


  char MANYJOBS[200][1000],AllCommands[100][1000];

  char * zeropriority[100];
  char * onepriority[100];
  char * twopriority[100];
  char * threepriority[100];
  char * fourpriority[100];
  char * fivepriority[100];
  char * sixpriority[100];
  char BigArrayCommands[100][1000];
  int ai;
  int aa,ab,ac,ad,ae,af,ag,ah;
  int ba,bb,bc,bd,be,bf,bg,bh;
  int ca,cb,cc,cd,ce,cf,cg,ch;

  char outpt4[]="#0";
  char outpt3[]="#3";
int freq=0;
  char line22[1000];
//  while (1) {
    //sleep(30);
//STARTS HERE

FILE *fpnt = CreateLogFile();

   if (fpnt!=NULL)
                 {

// it's safe to return a pointer from a func

while (!feof(fpnt)){

    fgets(line22,sizeof(line22),fpnt);

    if (is_blank_line(line22))
    {
      printf("I am a blanc.In my text_file..%s\n",line22);

        continue;
    }
    strcpy(MANYJOBS[freq],line22);

    freq++;
}
fclose(fopen("myfile.txt","w"));
//fclose(fpnt);
            }
//fpnt = NULL;

//loop through the MANYJOBS array while assigning priorities.
for(int countt=0;countt<freq;countt++){

strcpy(line1,MANYJOBS[countt]);
printf("After copying job: %s from MANYJOBS[%d]\n",line1,countt);
     //check if replace job and increase priority_number(#No.) by 3 else set initial priority to zero.
      if(strstr(line1,"Replace")!=NULL)
        {


      //    strcat(line1,outpt3);


      //  char outpt3[]="#3";
        //strcat(line1," #");
        int leng_th = strlen(line1);
        leng_th =leng_th-1;
        printf("%s\n",line1);
        append(line1,outpt3,leng_th);




        }
      else
        {

          //strcat(line1,outpt4);

          //strcat(line1," #");
          //int leng_th = strlen(line1);
          //append(line1,outpt3,leng_th);
          int leng_th = strlen(line1);
          leng_th =leng_th-1;
          printf("%s\n",line1);
          append(line1,outpt4,leng_th);

        //int leng_th = strlen(line1);
          //append(line1,"#0",leng_th);
          //strcat(line1,"#0");
        }
        printf("%s\n",line1);
      strcpy(Array_p1[countp],line1);

      if(strstr(line1,"U001")!=NULL)
        {
          countU001++;
        }
      else if(strstr(line1,"U002")!=NULL)
        {
          countU002++;
        }

           int countp2,countp3;
           for(countp2=0;line1[countp2]!=' ';countp2++);
           for(countp3=countp2;line1[countp3]!='\0';countp3++)
           {
           //count the length of strings to be process and store them in an int array and call get_min() to get position of shortest length.
           stringlen++;
           }

      stringlen=stringlen-28;
      arry_of_lengths[countp]=stringlen;
      printf("The command sent has a length of:%d\n",arry_of_lengths[countp]);
      stringlen=-1;
      countp++;

        }
              printf("User U001 sent:%d jobs\n",countU001);
              printf("User U002 sent:%d jobs\n",countU002);
              printf("Total number of jobs is:%d jobs\n",countp);

      //2ND LOOP STARTS HERE.--Determines userID with highest number of jobs.
  int size = countp;
  for(int i=0;i<countp;i++){
    if((countU001>countU002)&&(strstr(Array_p1[i],"U001")!=NULL)){
          int n=2;
         printf("After considering UOO1 HAVING MOST JOBS:%s\n",assign_priority(Array_p1[i],n));
    }
    else if((countU002>countU001)&&(strstr(Array_p1[i],"U002"))!=NULL){

         int n=2;

          printf("After considering UOO2 HAVING MOST JOBS:%s\n",assign_priority(Array_p1[i],n));
    }

//getting the position of the string with the least length.
    int loc = get_min(arry_of_lengths,size);
    if(i==loc){
      int m=1;

      printf("The job with the shortest length is: %s\n",assign_priority(Array_p1[loc],m));
    }

       strcpy(AllCommands[i],Array_p1[i]);
        }
printf("........................................After Priority assigning....................................................\n");

//Organizing the jobs in their own arrays.

//the for loop goes through the array that ia having commands with priorities
printf("...................NOW ORGANIZING THEM.................................................\n");
for (ai = 0,aa=0,ab=0,ac=0,ad=0,ae=0,af=0,ag=0; ai < freq; ai++)
{

//this code will be checking each priority and assigning them to their arrays where they belong
if(strstr(AllCommands[ai],"#0")!=NULL)
 {
  zeropriority[aa]=AllCommands[ai];
  printf("these have a priority of zero:\t %s\n",zeropriority[aa]);
  aa++;
  continue;
 }
else if(strstr(AllCommands[ai],"#1")!=NULL)
 {
  onepriority[ab]=AllCommands[ai];
  printf("these have a priority of one:\t %s\n",onepriority[ab]);
  ab++;
   continue;
 }
else if(strstr(AllCommands[ai],"#2")!=NULL)
 {
  twopriority[ac]=AllCommands[ai];
  printf("these have a priority of two:\t %s\n",twopriority[ac]);
  ac++;
  continue;

 }
else if(strstr(AllCommands[ai],"#3")!=NULL)
 {
  threepriority[ad]=AllCommands[ai];
  printf("these have a priority of three:\t %s\n",threepriority[ad]);
  ad++;
  continue;

 }
else if(strstr(AllCommands[ai],"#4")!=NULL)
 {
  fourpriority[ae]=AllCommands[ai];
  printf("these have a priority of four:\t %s\n",fourpriority[ae]);
  ae++;
  continue;

 }
else if(strstr(AllCommands[ai],"#5")!=NULL)
 {
  fivepriority[af]=AllCommands[ai];
  printf("these have a priority of five:\t %s\n",fivepriority[af]);
  af++;
  continue;

 }
else if(strstr(AllCommands[ai],"#6")!=NULL)
 {
  sixpriority[ag]=AllCommands[ai];
  printf("these have a priority of six:\t %s\n",sixpriority[ag]);
  ag++;
  continue;
 }
 else{
   printf("Priory Higher than 6 for %s\n",AllCommands[ai]);
   continue;
 }
}

printf("\n \n \n \n//transfer the content of the arrays to a bigger array \n \n \n");
//CHECK THE LOGIC HERE.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
for(ah=0; ah<aa; ah++)
{
    strcpy(BigArrayCommands[ah],zeropriority[ah]);

}

for(ba=ah,ca=0; ba<(ab+ah); ca++,ba++)
{

    strcpy(BigArrayCommands[ba],onepriority[ca]);

}

for(bb=ba,cb=0; bb<(ac+ab+ah); cb++,bb++)
{

    strcpy(BigArrayCommands[bb],twopriority[cb]);

}
for(bc=bb,cc=0; bc<(ad+ac+ab+ah); cc++,bc++)
{

    strcpy(BigArrayCommands[bc],threepriority[cc]);

}
for(bd=bc,cd=0; bd<(ae+ad+ac+ab+ah); cd++,bd++)
{
    strcpy(BigArrayCommands[bd],fourpriority[cd]);

}
for(be=bd,ce=0; be<(af+ae+ad+ac+ab+ah); ce++,be++)
{
    strcpy(BigArrayCommands[be],fivepriority[ce]);

}
for(bf=be,cf=0; bf<(ag+af+ae+ad+ac+ab+ah); cf++,bf++)
{
    strcpy(BigArrayCommands[bf],sixpriority[cf]);

}
printf("............ORGANIZED ARRAY CONTENTS.\n");
//SEND THE JOBS WITH THEIR PRIORITIES INTO BUSY_LIST.
//pthread_mutex_lock(&lock1);
FILE * fp;
fp=fopen("busylist.txt","a+");


for(int count_h=0;count_h<freq;count_h++){

 if(fprintf(fp,"%s\n",BigArrayCommands[count_h])){
   printf("Job %s has successfully been written to the Busyfile\n",BigArrayCommands[count_h]);
   sleep(1);
 }

}
fclose(fp);





//ends HERE.

  //}
  return NULL;
}



char * string1;
//this array will hold the data in the second position on the string1 array
char *longString;
//this array will hold the data in the first position on the string1 array
char * longString2;
//this array will hold the data in the third position on the string1 array
char * longString3;
char single[100];
char *singleJob;
char server_message[1024];//variable to hold all data to be sent to client
char string[100];
//int sock;
char testjob2[1000];

int main(int argc , char *argv[])
{
    pthread_t thread;
    int socket_desc , client_sock;
    struct sockaddr_in server , client;
    socklen_t c = sizeof(client);


    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9006);
    bzero (&server.sin_zero,8);

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }

    //Listen
    listen(socket_desc , MAX_CLIENTS);

    //Accept and incoming connection
    printf("Waiting for incoming connections\n");

 //int my_counter =1;
    c = sizeof(client);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, &c)) )
    {
        printf("Connection accepted");
        pthread_t thread_id;

        if( pthread_create( &thread_id , NULL ,new_connection_handler , (void*) (intptr_t)client_sock)< 0)
        {
            perror("could not create thread");
            return 1;
        }
        //CODE FOR THIRD THREAD.
        printf("Handler assigned\n");
          sleep(1);
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    return 0;
}


void *new_connection_handler(void *socket_desc)
{
    //Get the socket descriptor

     int sock = (intptr_t)socket_desc;
    int read_size = 0;
    char client_message[2000];
    char doubled[100];
    //declaration of variables to be used.
    char *oneJobs;
    char *job;
    char delim=';';
    char command[1000];
    // it will hold the split data in it

    char userID[500];

    char *Individual_Jobs;
    int count1;
    int count2;
    char datandtime[1000];
    int lenofstrn=-1;
    int lenof1strn=-1;
    char mycommd[100];

char testjob1[1000];
  char MANYJOBS[200][1000];

  pthread_mutex_lock(&lock);
my_counter++;
printf("while in the lock %d\n",my_counter);
pthread_mutex_unlock(&lock);
printf("just after the lock %d\n",my_counter);

    //Receive a message from client
    while( (read_size = recv(sock , client_message , sizeof(client_message) , 0)) > 0 ){
//THis is where the processing code goes.


FILE *blacklist;
blacklist=fopen("blacklisted_file.txt","a+");

FILE * blacklistd;
blacklistd=fopen("blacklisted_file.txt","a+");


FILE * fp3;
fp3=fopen("myfile.txt","a+");


  //we get the arrival time and date for the commnds onto the server
  time_t(currentTime);
  time(&currentTime);
  strcpy(datandtime,ctime(&currentTime));

 //PROCESSING CLIENT COMMANDS.
  strcpy(command,client_message);

 //code to check if the user sent many jobs and if so,split by semi-colon(;) and assign the split tokens to string1 pointer
 int freq = 1,flag = 0;
 for (int i = 0; i < strlen(command); i++)
 {
     if (command[i] == delim)
     {
         flag = 1;
         freq++;
     }
 }

 //get the number of jobs sent by user equivalent to the freq and append to each job !!!!!!!!!

 //if it flagged it means user sent many jobs so we process the many jobs we go ahead to split by semi-colon and append time and date and userID and send to busylist
 if (flag)
     {

       //first get the user id
       int caunt;
       for(caunt=0;command[caunt]!='-';caunt++)
        {
          userID[caunt]=command[caunt];
        }
       userID[caunt]='-';
       userID[caunt+1]='\0';
       printf("userID:%s\n",userID);

       job = strtok(command,";");
         int count111 = 0;
         while (job!=NULL)
           {

                   Individual_Jobs=job;
                   printf("Individual_Jobs:%s\n",Individual_Jobs);

                   //get the string length of the string to be Processed

                 int count1,kaunta;
                  for(count1=0;Individual_Jobs[count1]!=' ';count1++);
                  for(kaunta=count1;Individual_Jobs[kaunta]!='\0';kaunta++)
                  {
                  //count the length of string to be process

                  lenofstrn++;

                  }

                   printf("\n%s  has a string to be worked on of length %d\n",Individual_Jobs,lenofstrn);

                  if(lenofstrn>50)
                   {
                     char testjob4[1000];
                     char message_for_blacklistd[1000];
                     //send to blacklisted_file
                     strcpy(testjob4,Individual_Jobs);
                     strcpy(message_for_blacklistd,Individual_Jobs);
                     strcat(message_for_blacklistd,"-has been blacklisted because it has more than 50 characters");

                     //printf("Error: You entered a string of more than 50 characters\n");
                     strcpy(server_message,message_for_blacklistd);

                     send(sock,server_message,sizeof(server_message),0);
                      //handling userID
                      if(strstr(testjob4,userID)!=NULL)
                          {

              //JOB HAS A USERID
                          }
                      else{
                        //ADDING USERID TO JOB
                           printf("Job lacks a userID\n");
                           printf("The userid to append is:%s\n",userID);

                            append(testjob4,userID,0);


                            }

                     //putting into blacklisted file.
                     fprintf(blacklist,"%s",Individual_Jobs);
                     printf("The length of your string is: %d\n",lenofstrn);

                   }

                   else
                   {

                     //append time, date and userID



                       strcpy(testjob1,Individual_Jobs);
                       strcat(testjob1," ");
                       strcat(testjob1,datandtime);

                     //send to busylist
                     printf("\nDear user, you sent %d commands. Please be patient as we work on them \n",freq);
                     //appending a userID to every job
                  //   char testjob[1000];
                    // strcpy(testjob,testjob1);
                     printf("testjob1:%s\n",testjob1);


                     if(strstr(testjob1,userID)!=NULL)
                         {

                         printf("Your job %s has a userID already.\n",testjob1);
                          //PLACE IN MANYJOBS array.
                          strcpy(MANYJOBS[count111],testjob1);
                          printf("job with id inserted in array is :%s in positon: %d\n",MANYJOBS[count111],count111);

                         }
                     else{
                          printf("Job lacks a userID\n");
                          printf("The userid to append is:%s\n",userID);

                           append(testjob1,userID,0);
                           printf("After appending userID..Job to place in array is:%s in position %d\n",testjob1,count111);

                           //PLACE IN MANYJOBS array.
                           strcpy(MANYJOBS[count111],testjob1);

                    }


                   }

                printf("...%s...*\n",MANYJOBS[count111]);
                 lenofstrn =-1;
                 count111++;
                 job = strtok (NULL, ";");

           }

            fclose(blacklist);


            //loop through the MANYJOBS array while WRITing  JOBS TO UNSORTED FILE..
            for(int countt=0;countt<freq;countt++){


                 if(fprintf(fp3,"%s\n",MANYJOBS[countt])){
                   printf("Job %s has successfully been written to the file\n",MANYJOBS[countt]);
                   sleep(1);
                 }

                      }
                  fclose(fp3);


                 printf("Just before creating priority thread my_counter is%d\n",my_counter);
                   if(my_counter==0){
                     //New thread HERE
                     int err;

                         err = pthread_create(&thread,NULL,&priority_thread,NULL);
                         if (err != 0)
                             printf("\ncan't create thread ");
                         else
                             printf("\n Thread created successfully\n");

                     //Up to here.



                     pthread_join(thread,NULL);
                   }



//...........................................................................................................................................
                 //retrieve the jobs from busylist one job at a time while assigning priorities.
                 char line[1000];
                 int filecounterarry[100],f_count=0;
                // sleep(30);
                 FILE *file1;
                 file1=fopen("busylist.txt","r");

                 if (file1!=NULL)
                 {
                     printf(".............................AFTER READING FROM BUSY_LIST..........................\n");

                   while(fgets(line, sizeof(line),file1)!=NULL)
                     {
                 //--PICKING FROM BUSY LIST LINE PER LINE UNTILL THE
                 //in this same loop we assign priorities
                    if(strstr(line,userID)!=NULL)
                    {
                      filecounterarry[f_count]=f_count+1;
                         strcpy(testjob2,line);

                       singleJob=line;

                      printf("The string read from busylist is::%s.......\n",singleJob);
                      strcpy(single,singleJob);
                      taskProcessor(single);
                      strcpy(server_message,single);
                      sleep(1);
                      send(sock,server_message,sizeof(server_message),0);

                    //  DeleteLine(1);
                    //  sleep(1);


                    }
                    f_count++;

                    //  sleep(1);

                     }



                     //When the new code of busy list is implemented plz use this.
                     fclose(fopen("busylist.txt", "w"));//**********it closes by opening a clompletely new file .
                    //fclose(file1);

                  /*  for(int q_count=f_count-1;q_count>-1;q_count--){
                      DeleteLine(filecounterarry[q_count]);
                    }*/
                 }
                 else
                 {
                   perror("busylist.txt");
                 }
}
else
{
//check if command is view status or not and process appropriately.

if(strstr(command,"view status")!=NULL){
//CODE TO CHECK FOR STATUS
int count_st,count_st1;
char id[100];
char UserID[100];
 for(count_st=0;command[count_st]!='-';count_st++){
   UserID[count_st]=command[count_st];
 }

 UserID[count_st]='-';
 UserID[count_st+1]='\0';
 strcpy(id,UserID);
 printf("after copying to Id.:%s\n",id);

 char line22[256];
 FILE *file11;
 file11 = fopen("readylist.txt","r");

 if (!file11) {
     perror("readylist.txt");
 }

 while (!feof(file11)){

     fgets(line22,sizeof(line22),file11);

     if (is_blank_line(line22))
     {
       printf("I am a blanc...%s\n",line22);
         continue;
     }
     else{
       printf("All:%s\n",line22);
       for(count_st1=0;line22[count_st1]!='-';count_st1++){
         id[count_st1]=line22[count_st1];
       }

       id[count_st1]='-';
       id[count_st1+1]='\0';
       printf("Its id is%s\n",id);
       printf("Yet current userID is:%s\n",UserID);




       if(strcmp(UserID,id)==0)
       {
         char currentstatus[100];
         strcpy(currentstatus,"READY_JOB:-");
         strcat(currentstatus,line22);
         strcpy(server_message,currentstatus);
         printf("Job with status is:%s\n",server_message);
         sleep(1);
         send(sock,server_message,sizeof(server_message),0);

       }


     }



 }
fclose(file11);


}
else{

    //when the task is alone and is not view status.
    int count0,kaunta1;
     for(count0=0;command[count0]!=' ';count0++);
     for(kaunta1=count0;command[kaunta1]!='\0';kaunta1++)
     {
     //count the length of string to be process

     lenof1strn++;

    }
    printf("The command sent:%s has a length of %d\n",command,lenof1strn);

    if(lenof1strn>50){
        //send to blacklisted_files
        char message_for_blacklistd[1000];
        strcpy(message_for_blacklistd,command);
        strcat(message_for_blacklistd,"-has been blacklisted because it has more than 50 characters");

        //printf("Error: You entered a string of more than 50 characters\n");
        strcpy(server_message,message_for_blacklistd);

        send(sock,server_message,sizeof(server_message),0);


        printf("Error: You entered a string of more than 50 characters\n");
        fprintf(blacklistd,"%s\n",command);
        printf("The length of your string is: %d\n",lenof1strn);
        fclose(blacklistd);
    }
    else
   {

        //append time, date

          strcpy(testjob2,command);
          strcat(testjob2," ");
          strcat(testjob2,datandtime);
        printf("time and date is:%s\n",testjob2);

       //strcpy(singleJob,testjob2);
       singleJob = testjob2;

      strcpy(single,singleJob);
      taskProcessor(single);
      strcpy(server_message,single);
      send(sock,server_message,sizeof(server_message),0);

     }


  //ENDs  HERE FOR NOW.
}



}


            }


    if(read_size == 0)
    {
        printf("Client disconnected\n");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    return 0;
}


//FUNCTIONS




//the reverse Function
void Reverse(char str[]){
    int i,j;
    char temp[100];
    for(i=strlen(str)-1,j=0; i+1!=0; --i,++j)
    {
        temp[j]=str[i];
    }
    temp[j]='\0';
    strcpy(str,temp);
}

//function to get the character that corresponds to a certain number it was assigned
char get_character(int position){
int counter2;
  for(counter2=0;letters[counter2]!='\0';counter2++){
      if(position==counter2){
        return letters[counter2];
  }
}
}


//Function to get the number that correspond to the letter.

int assign_letters(char letter){
  int counter2;
    for(counter2=0;letters[counter2]!='\0';counter2++){
      if(letter==letters[counter2]){
        return counter2;
      }
    }
}




//function to convert from integer to stri

char* itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


// function to insert characters  and symbols into a specified position of a string
void append(char subject[], const char insert[], int pos)
	{
    char buf[1000] = {};
    strncpy(buf, subject, pos); // copy at most first pos characters
    int len = strlen(buf);
    strcpy(buf+len, insert); // copy all of insert[] at the end
    len += strlen(insert);  // increase the length by length of insert[]
    strcpy(buf+len, subject+pos); // copy the rest
    strcpy(subject, buf);   // copy it back to subject

	}




  //FUNCTION TO assign PRORITY NUMBER BASED ON SHORTEST LENGTH AND ID WITH HIGHEST NUMBER OF JOBS.
  char* assign_priority(char str[],int num) {

    char *longStr,*longStr2;
    char aray2[10];
    char *string1 = strtok(str,"#");
    //counter for the while loop
    int count3=0;
    //looping through the array holding split sections until there is nothing left
    while (string1 != NULL)
        {
          // accessing the second position in the string1 array.
        if(count3==1)
          {
            //assigning the data in second position to a pointer longstring.
            longStr=string1;

          }
        else if(count3==0)
          {
            //assigning the data in the first position to a pointer longString2.
            longStr2=string1;

          }

            //the else part of the if statement
            string1 = strtok (NULL, " ");
            count3++;
      }

      int myint = atoi(longStr);

      if(num==2){
        myint =myint+2;
  itoa(myint,aray2,10);
        strcat(longStr2,"#");
      int len = strlen(longStr2);
      append(longStr2,aray2,len);
        //strcat(longStr2,aray2);

      }
    else{
      myint =myint+1;
  itoa(myint,aray2,10);
      strcat(longStr2,"#");
      int len = strlen(longStr2);
      append(longStr2,aray2,len);

    //  strcat(longStr2,aray2);

    }

  return longStr2;

  }


  //Function to get strind with shortest length.
  int get_min(int array[],int size){

  int location=0,minimum,c;
  minimum = array[0];

  for(c=1;c<size;c++){

  if(array[c]<minimum){

  minimum = array[c];
  location =c;

  }

  }
  return location;
  }


//function to delete line from busy list after it has been read.
  void DeleteLine(int line_num)
  {
  	FILE *fp1, *fp2;
          //consider 40 character string to store filename
          //char filename[40];
          char c;
          int del_line, temp = 1;

        // strcpy(filename,"busylist.txt");
          //open file in read mode
          fp1 = fopen("busylist.txt", "r");
        //  c = getc(fp1);
          //until the last character of file is obtained
        printf("Current contents of busy_list before deleting the currently copied line\n");
          while (c != EOF)
          {

            printf("%c", c);
            //print current character and read next character
            c = getc(fp1);
          }
          //rewind
          rewind(fp1);

         del_line=line_num;
          //open new file in write mode
          fp2 = fopen("copy.c", "w");
          //c = getc(fp1);
          while (c != EOF) {
            c = getc(fp1);
            if (c == '\n')
            temp++;
            //except the line to be deleted
            if (temp != del_line)
            {
              //copy all lines in file copy.c
              putc(c,fp2);
            }
          }
          //close both the files.
          fclose(fp1);
          fclose(fp2);
          //remove original file
          remove("busylist.txt");
          //rename the file copy.c to original name
          rename("copy.c","busylist.txt");
          printf("\n The contents of file after being modified are as  follows:\n");
          fp1 = fopen("busylist.txt","r");
          c = getc(fp1);
          while (c != EOF) {
              printf("%c", c);
              c = getc(fp1);
          }
          fclose(fp1);

  }




  //Function to process the six tasks.
  void taskProcessor(char jobs[]){

      FILE *ready;
      ready = fopen("readylist.txt","a+");

    //THE PROCESSING OF THE SIX TASKS STARTS HERE---------------STOPPED HERE.
        singleJob = jobs;

    //processing for one job
    string1 = strtok (singleJob," ");

    //counter for the while loop
    int count3=0;
    //looping through the array holding split sections until there is nothing left
    while (string1 != NULL)
        {
          // accessing the second position in the string1 array.
        if(count3==1)
          {
            //assigning the data in second position to a pointer longstring.
           longString=string1;

              strcpy(string,longString);
              printf("\n%s\n",string);
              printf("\n%s\n",longString);

          }
        else if(count3==0)
          { //COMMAND AND UserID
            //assigning the data in the first position to a pointer longString2.
            longString2=string1;
            printf("\n%s\n",longString2);
          }
        else if(count3==2)
          {
            longString3=string1;
              printf("\n%s\n",longString3);
          }

            //the else part of the if statement
            string1 = strtok (NULL, " ");
            count3++;
      }


    printf("String is being Processed is::%s\n",longString);

    // To check if the command is a encrypt, and if it is, the  value in longString is encrypted
     if (strstr(longString2,"Encrypt")!=NULL)
       {

            clock_t start,end;
            start=clock();
           char array[100]="",array1[100],array2[100],array3[100],array4[100];
           char encrpted_small_leter,characters_to_insert;
           int letter_equivalent_number,counter,counter1;
           char result1[100]="";
           char final_string[10000]="";
           char array20[100];



           for(counter = 0,counter1=0; counter<strlen(string); counter++,counter1++){
               //get the corresponding number that represents the letter
               letter_equivalent_number = assign_letters(string[counter]);

             if(letter_equivalent_number<=9){
               //get equivalent letter and convert to  corresponding capital letter
             encrpted_small_leter = get_character(letter_equivalent_number+26);
             //convert the character got to a string
             char str7[2]= {encrpted_small_leter,'\0'};
             char encryptd_small[10]="";
             strcpy(encryptd_small,str7);
             strcpy(result1,encryptd_small);

             }
             else{
            //convert the number got to string
            itoa(letter_equivalent_number,array,10);

       /*SKIPPED TILL I GET CODE TO REMOVE THE SPACE
            //insert a space in the second position of the string
            append(array, " ", 1);
            printf("After adding space to the string: %s\n",array);
       */

                if(letter_equivalent_number<=18){

                   //subtract 1 from previous letter holder and get the equivalent letter in lower case and insert it where the space was
                    characters_to_insert = get_character(letter_equivalent_number-1);
                     //convert the character got to a string
                     char str1[2]= {characters_to_insert,'\0'};
                     char str2[5]="";
                     strcpy(str2,str1);
                     append(array,str2,1);


                     characters_to_insert = get_character(letter_equivalent_number-9+26);
                     //convert the character got to a string
                     char str8[2]= {characters_to_insert,'\0'};
                     char str9[5]="";
                     strcpy(str9,str8);
                     append(array,str9,2);
                     strcpy(result1,array);
                     strcat(final_string,result1);
                     continue;
            }
            else if(letter_equivalent_number>18 && letter_equivalent_number<=27){

                    //subtract 1 from previous letter holder and get the equivalent letter in lower case and insert it where the space was
                    characters_to_insert = get_character(letter_equivalent_number-1);
                     //convert the character got to a string
                     char str12[2]= {characters_to_insert,'\0'};
                     char str13[5]="";
                     strcpy(str13,str12);
                     append(array,str13,1);


                   //subtract 9 from the previous letter holder and convert it to a string
                     letter_equivalent_number= letter_equivalent_number - 9;
                     itoa(letter_equivalent_number,array1,10);

                    // subtract 1 from the current lettercorresponding holder and insert the corresponding letter in lower case in the middle of the new string
                     characters_to_insert = get_character(letter_equivalent_number-1);
                     //convert the character got to a string
                     char str3[2]= {characters_to_insert,'\0'};
                     char str4[5]="";
                     strcpy(str4,str3);
                     append(array1,str4,1);


                  //subtract 9 from previous lettter holder and if result is less than 10 get the corresponding letter and insert it in upper case and append it at in the second position of the current string.
                     characters_to_insert = get_character(letter_equivalent_number-9+26);
                     //convert the character got to a stringu7
                     char str5[2]= {characters_to_insert,'\0'};
                     char str6[5]="";
                     strcpy(str6,str5);

                     append(array1,str6,1);

                   //insert the string in array1 into array at position After the small letter.
                    append(array,array1,2);
                    strcpy(result1,array);
                    strcat(final_string,result1);
                    continue;
               }
       else if(letter_equivalent_number>27 && letter_equivalent_number<37){


                    //subtract 9 from the previous letter holder and convert it to a string
                    letter_equivalent_number= letter_equivalent_number - 9;
                    itoa(letter_equivalent_number,array1,10);

                    //subtract 9 from the previous letter holder and convert it to a string
                    letter_equivalent_number= letter_equivalent_number - 9;
                    itoa(letter_equivalent_number,array2,10);

                    array20[0] = array[0];
                    array20[1] = get_character(letter_equivalent_number-1+9+9-26);
                    array20[2] = array1[0];
                    array20[3] = get_character(letter_equivalent_number-1+9);
                    array20[4] = array1[1];
                    array20[5] = get_character(letter_equivalent_number-9+26);//capital letter
                    array20[6] = array2[0];
                    array20[7]=  get_character(letter_equivalent_number-1);
                    array20[8] =  array2[1];
                    array20[9]= array[1];
                    array20[10]='\0';
                    strcpy(result1,array20);
                    strcat(final_string,result1);
                    continue;
       }
       else if(letter_equivalent_number>36 && letter_equivalent_number<46){

                    //subtract 9 from the previous letter holder and convert it to a string
                    letter_equivalent_number= letter_equivalent_number - 9;
                    itoa(letter_equivalent_number,array1,10);

                    //subtract 9 from the previous letter holder and convert it to a string
                    letter_equivalent_number= letter_equivalent_number - 9;
                    itoa(letter_equivalent_number,array2,10);

                    //subtract 9 from the previous letter holder and convert it to a string
                    letter_equivalent_number= letter_equivalent_number - 9;
                    itoa(letter_equivalent_number,array3,10);


                      array20[0] = array[0];
                      array20[1] = get_character(letter_equivalent_number-1+9+9+9-26);
                      array20[2] = array1[0];
                      array20[3] = get_character(letter_equivalent_number-1+9+9-26);
                      array20[4] = array1[1];
                      array20[5] = array2[0];
                      array20[6] = get_character(letter_equivalent_number-9+26);//capital letter
                      array20[7]= get_character(letter_equivalent_number-1+9);
                      array20[8] = array2[1];
                      array20[9]=  array3[0];
                      array20[10]=  get_character(letter_equivalent_number-1);
                      array20[11] =  array3[1];
                      array20[12] = array[1];
                      array20[13] = '\0';
                      strcpy(result1,array20);
                      strcat(final_string,result1);
                      continue;

       }
       else if(letter_equivalent_number>45 && letter_equivalent_number<=52){

                     //subtract 9 from the previous letter holder and convert it to a string
                      letter_equivalent_number= letter_equivalent_number - 9;
                      itoa(letter_equivalent_number,array1,10);

                    //subtract 9 from the previous letter holder and convert it to a string
                      letter_equivalent_number= letter_equivalent_number - 9;
                      itoa(letter_equivalent_number,array2,10);

                    //subtract 9 from the previous letter holder and convert it to a string
                      letter_equivalent_number= letter_equivalent_number - 9;
                      itoa(letter_equivalent_number,array3,10);

                    //subtract 9 from the previous letter holder and convert it to a string
                      letter_equivalent_number= letter_equivalent_number - 9;
                      itoa(letter_equivalent_number,array4,10);


                      array20[0] = array[0];
                      array20[1] = get_character(letter_equivalent_number-1+9+9+9+9-26);
                      array20[2] = array1[0];
                      array20[3] = get_character(letter_equivalent_number-1+9+9+9-26);
                      array20[4] = array1[1];
                      array20[5] =  array2[0];
                      array20[6] =  get_character(letter_equivalent_number-1+9+9-26);
                      array20[7] = array2[1];
                      array20[8] = get_character(letter_equivalent_number-9+26);//capital letter
                      array20[9] =  array3[0];
                      array20[10] = get_character(letter_equivalent_number-1+9);
                      array20[11] = array3[1];
                      array20[12] = array4[0];
                      array20[13] = get_character(letter_equivalent_number-1);
                      array20[14] = array4[1];
                      array20[15] = array[1];
                      array20[16] = '\0';
                      strcpy(result1,array20);
                      strcat(final_string,result1);
                     continue;
                       }

              }
            strcat(final_string,result1);
         }
          end=clock();
          double extime=(double) (end-start)/CLOCKS_PER_SEC;
          //strcat(jobs," *");
          int len = strlen(testjob2);
          len = len -1;
          append(testjob2," *",len);


          char output[50];

          snprintf(output,50,"%f\n",extime);
          int leng = strlen(testjob2);
          leng = leng -1;
          append(testjob2,output,leng);

          if(fprintf(ready,"%s",testjob2)){
              printf("the string written to readyfile is %s\n",testjob2);

          }
          //////write to ready Jobs

          printf("\nExecution time for encryption is %f seconds\n ",extime);
          printf("After the very final Encrytion of: %s \nThe output is: %s\n",string,final_string);

                             char original_command[1000];
                             strcpy(original_command,longString2);
                             strcat(original_command," ");
                             strcat(original_command,longString);
                             strcat(original_command," gives: ");
                             strcat(original_command,final_string);

                             strcpy(jobs,original_command);
                            // send(sock,server_message,sizeof(server_message),0);



     }



    // To check if the command is a delete, and if it is, the value in longString is deleted
    if (strstr(longString2,"Delete")!=NULL)
       {
          printf("The Command is Delete.\n");

                      char strng1[100];
                      char strng2[100];
                      char *str3;
                      char *str4[100];
                      int count99;
                      int counti3=0;

                      clock_t start1,end1;
                      start1=clock();
                      strcpy(strng1,longString);
                      strcpy(strng2,longString3);

                            str3 = strtok(strng2,",");
                            //looping through the array holding split sections until there is nothing left
                            while (str3 != NULL){

                                str4[counti3]=str3;
                              //printf("\nthe string is: %s when counti3 is is %d\n",str4[counti3],counti3);
                                  counti3++;
                                 str3 = strtok(NULL, ",");

                              }
                      //printf("the value of counti3 finally is %d\n",counti3);

                      for(int i=0,j=0;i<counti3;i++){

                      int positn = atoi(str4[i]);

                      char tx = '!';
                      strng1[positn-1] = tx;
                      //printf("After replacing with "" in position %d, the string becomes %s \n",positn,strng1);
                      j=0;

                      }
                      //printf("The final new string after all the replacing is %s\n",strng1);

                      //now we remove any symbol that is not a character
                      int count990 = 0;

                         // Traverse the given string. If current character
                         // is not !, then place it at index 'count++'
                         for (int i = 0; strng1[i]; i++){
                             if (strng1[i] != '!'){
                                 strng1[count990++] = strng1[i]; // here count is
                             }
                        }
                         strng1[count990] = '\0';
                         end1=clock();
                         double extime1=(double) (end1-start1)/CLOCKS_PER_SEC;
                        // strcat(jobs," *");
                        int len = strlen(testjob2);
                        len = len -1;
                        append(testjob2," *",len);


                         char output1[50];

                         snprintf(output1,50,"%f\n",extime1);
                         int leng = strlen(testjob2);
                         leng = leng -1;
                         append(testjob2,output1,leng);


                         //////write to ready Jobs
                        // ready = fopen("readylist.txt","a+");
                         fprintf(ready,"%s",testjob2);
                         printf("\n\tExecution time for deletion is %f seconds\n ",extime1);


                          char original_command[1000];
                          strcpy(original_command,longString2);
                          strcat(original_command," ");
                          strcat(original_command,longString);
                          strcat(original_command," ");
                          strcat(original_command,longString3);

                          strcat(original_command," gives: ");
                          strcat(original_command,strng1);

                          strcpy(jobs,original_command);
                         // send(sock,server_message,sizeof(server_message),0);


                      printf("AFTER THE VERY FINAL DELETION: %s\n",strng1);
                  //    fclose(ready);

       }
    // To check if the command is a , and if it is, the value in longString is reversed
     if (strstr(longString2,"Reverse")!=NULL)
       {
          char str[100];
          clock_t start2,end2;
          start2=clock();

          strcpy(str,longString);
          Reverse(str);
          end2=clock();
          double extime2=(double) (end2-start2)/CLOCKS_PER_SEC;

          //strcat(jobs," *");
          int len = strlen(testjob2);
          len = len -1;
          append(testjob2," *",len);


          char output2[50];

          snprintf(output2,50,"%f\n",extime2);
          int leng = strlen(testjob2);
          leng = leng -1;
          append(testjob2,output2,leng);


          //////write to ready Jobs
        //  ready = fopen("readylist.txt","a+");
          fprintf(ready,"%s",testjob2);

          printf("\n\tExecution time for reversing is %f seconds\n ",extime2);


                             char original_command[1000];
                             strcpy(original_command,longString2);
                             strcat(original_command," ");
                             strcat(original_command,longString);
                             strcat(original_command," gives: ");
                             strcat(original_command,str);

                             strcpy(jobs,original_command);
                            // send(sock,server_message,sizeof(server_message),0);


        printf("AFTER THE VERY FINAL REVERSING: %s\n",str);
        //  fclose(ready);
       }
       // To check if the command is a double, and if it is, the  value in longString is doubled
       if (strstr(longString2,"Double")!=NULL)
          {
                   printf("The Command is Double.\n");
                   char doubled[10000];

                   clock_t start3,end3;
                   start3=clock();
               //Content of longString is copied to array b.
                   strcpy(doubled,longString);

                   int i, j;

               /* i contains length of string in array longString. */
                   for(i=0; doubled[i]!='\0'; ++i);
                   for(j=0; longString[j]!='\0'; ++j, ++i)
                   {
                       doubled[i]=longString[j];
                   }

                   doubled[i]='\0';

                   end3=clock();
                   double extime3=(double) (end3-start3)/CLOCKS_PER_SEC;
                   printf("During processing test job is :%s\n",testjob2);

                   int len = strlen(testjob2);
                   len = len -1;
                   append(testjob2," *",len);

                   char output3[50];

                   snprintf(output3,50,"%f\n",extime3);
                   int leng = strlen(testjob2);
                   leng = leng -1;
                   append(testjob2,output3,leng);
                   printf("Jobs:%s\n",testjob2);

                   //////write to ready Jobs
                //   ready = fopen("readylist.txt","a+");
                   fprintf(ready,"%s",testjob2);
                   printf("\n\tExecution time for doubling is %f seconds\n ",extime3);
                   printf("\n The Double is: %s\n",doubled);

                   char original_command[1000];
                   strcpy(original_command,longString2);
                   strcat(original_command," ");
                   strcat(original_command,longString);
                   strcat(original_command," gives: ");
                   strcat(original_command,doubled);

                   strcpy(jobs,original_command);
                  // send(sock,server_message,sizeof(server_message),0);


                //   fclose(ready);

          }
      // To check if the command is a Replace, and if it is, the  value in longString is replaced
        if (strstr(longString2,"Replace")!=NULL)
         {
                    printf("The Command is Replace.\n");
                    char strig1[100];
                    char strig2[100];
                    char *stri3;
                    char *stri4[100];
                    char *positin;
                    char *lettr;
                    char *stri5;
                    char *stri6[2];
                    int counta3=0;
                    clock_t start4,end4;
                    start4=clock();
                    strcpy(strig1,longString);
                    strcpy(strig2,longString3);


                   stri3 = strtok(strig2,",");
                   //looping through the array holding split sections until there is nothing left
                   while (stri3 != NULL){

                        stri4[counta3]=stri3;
                        counta3++;
                        stri3 = strtok(NULL, ",");

                     }

              for(int i=0,j=0;i<counta3;i++){
               stri5 = strtok(stri4[i],"-");
                   while (stri5!=NULL) {
                     stri6[j]= stri5;
                     j++;
                     stri5 = strtok(NULL,"-");
                           }

                      int positin = atoi(stri6[0]);
                      char character4replacing[2];
                      strcpy(character4replacing,stri6[1]);// - get code that converts a string to a character
                      char mychaar =character4replacing[0];
                      strig1[positin-1] = mychaar;
                      j=0;


              }
              end4=clock();
              double extime4=(double) (end4-start4)/CLOCKS_PER_SEC;

              //strcat(jobs," *");
              int len = strlen(testjob2);
              len = len -1;
              append(testjob2," *",len);


              char output4[50];

              snprintf(output4,50,"%f",extime4);
              int leng = strlen(testjob2);
              leng = leng - 1;
              append(testjob2,output4,leng);


              //////write to ready Jobs
            //  ready = fopen("readylist.txt","a+");
              fprintf(ready,"%s",testjob2);
              printf("\n\tExecution time for replacing is %f seconds\n ",extime4);


                  char original_command[1000];
                  strcpy(original_command,longString2);
                  strcat(original_command," ");
                  strcat(original_command,longString);
                  strcat(original_command," ");
                  strcat(original_command,longString3);

                  strcat(original_command," gives: ");
                  strcat(original_command,strig1);

                  strcpy(jobs,original_command);
                 // send(sock,server_message,sizeof(server_message),0);

              printf("The final new string after all the replacing is %s\n",strig1);
          //    fclose(ready);
         }



     // To check if the command is a decrypt, and if it is, the  value in longString is decypted
     if  (strstr(longString2,"Decrypt")!=NULL)
         {

              char string22[1000];//string to decrypt
              int count;
              char myDecrypt[3]="",myDcyptdchar,finaldecrStr[100];
              int number,j;
              clock_t start5,end5;
              start5=clock();
              strcpy(string22,string);

                for(count = 0,j=0; string22[count]!='\0'; count++,j++){

                  if(string22[count]=='1'){
                      if(((string22[count+3]=='0')||(string22[count+3]=='1')||(string22[count+3]=='2')||(string22[count+3]=='3')||(string22[count+3]=='4')||(string22[count+3]=='5')||(string22[count+3]=='6')||(string22[count+3]=='7')||(string22[count+3]=='8'))&&((string22[count+2]=='A')||(string22[count+2]=='B')||(string22[count+2]=='C')||(string22[count+2]=='D')||(string22[count+2]=='E')||(string22[count+2]=='F')||(string22[count+2]=='G')||(string22[count+2]=='H')||(string22[count+2]=='I')))
                         {
                            //code to decrypt 10 - 18 range [10-18]
                        // printf("Counter comes as positon %d in the range [10-18] \n",count);
                          //get the first and last characters into an array and convert the array content to int data type.
                          myDecrypt[0] = string22[count];
                          myDecrypt[1] = string22[count+3];
                          myDecrypt[2] = '\0';

                          number = atoi(myDecrypt);

                          myDcyptdchar = get_character(number);

                          finaldecrStr[j]= myDcyptdchar;

                          count =count + 3;//skip the next 3 characters

                          //copy to common  char array like   strcpy(result1,array); -but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                          continue;

                         }
                      else{
                            //code to decrypt 19 -27 range[19]

                          myDecrypt[0] = string22[count];
                          myDecrypt[1] = string22[count+6];
                          myDecrypt[2] = '\0';

                          number = atoi(myDecrypt);
                          myDcyptdchar = get_character(number);
                          finaldecrStr[j]= myDcyptdchar;

                          count =count + 6;//skip the next 6 characters
                          //copy to common  char array like   strcpy(result1,array);-but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                          continue;
                         }
                  }
                  else if(string22[count]=='2'){
                      if(((string22[count+6]=='0')||(string22[count+6]=='1')||(string22[count+6]=='2')||(string22[count+6]=='3')||(string22[count+6]=='4')||(string22[count+6]=='5')||(string22[count+6]=='6')||(string22[count+6]=='7'))&&((string22[count+3]=='A')||(string22[count+3]=='B')||(string22[count+3]=='C')||(string22[count+3]=='D')||(string22[count+3]=='E')||(string22[count+3]=='F')||(string22[count+3]=='G')||(string22[count+3]=='H')||(string22[count+3]=='I')))
                          {
                          //code to decrypt 19 - 27 range [20-27]
                          myDecrypt[0] = string22[count];
                          myDecrypt[1] = string22[count+6];
                          myDecrypt[2] = '\0';

                          number = atoi(myDecrypt);
                          myDcyptdchar = get_character(number);
                          finaldecrStr[j]= myDcyptdchar;

                          count =count + 6;//skip the next 6 characters
                        //copy to common  char array like   strcpy(result1,array);-but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                        continue;
                          }
                      else{
                          //code to decrypt 28-36 range[28-29]
                        myDecrypt[0] = string22[count];
                        myDecrypt[1] = string22[count+9];
                        myDecrypt[2] = '\0';

                        number = atoi(myDecrypt);
                        myDcyptdchar = get_character(number);
                        finaldecrStr[j]= myDcyptdchar;

                        count =count + 9;//skip the next 9 characters
                        //copy to common  char array like   strcpy(result1,array); -but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                        continue;
                        }
                    }

                  else if(string22[count]=='3'){
                      if(((string22[count+9]=='0')||(string22[count+9]=='1')||(string22[count+9]=='2')||(string22[count+9]=='3')||(string22[count+9]=='4')||(string22[count+9]=='5')||(string22[count+9]=='6'))&&((string22[count+5]=='A')||(string22[count+5]=='B')||(string22[count+5]=='C')||(string22[count+5]=='D')||(string22[count+5]=='E')||(string22[count+5]=='F')||(string22[count+5]=='G')||(string22[count+5]=='H')||(string22[count+5]=='I')))
                          {
                            //code to decrypt 28-36 range[30-36]
                            myDecrypt[0] = string22[count];
                            myDecrypt[1] = string22[count+9];
                            myDecrypt[2] = '\0';

                            number = atoi(myDecrypt);
                            myDcyptdchar = get_character(number);
                            finaldecrStr[j]= myDcyptdchar;

                           count =count + 9;//skip the next 12characters
                          //copy to common  char array like   strcpy(result1,array);-but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                          continue;
                          }
                      else{
                          //code to decrypt 37-45 range[37-39]
                           myDecrypt[0] = string22[count];
                           myDecrypt[1] = string22[count+12];
                           myDecrypt[2] = '\0';

                           number = atoi(myDecrypt);
                           myDcyptdchar = get_character(number);
                           finaldecrStr[j]= myDcyptdchar;

                           count =count + 12; //skip the next 12 characters
                        //copy to common  char array like   strcpy(result1,array); -but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                          continue;
                          }

                  }

                  else if(string22[count]=='4'){
                      if(((string22[count+12]=='0')||(string22[count+12]=='1')||(string22[count+12]=='2')||(string22[count+12]=='3')||(string22[count+12]=='4')||(string22[count+12]=='5'))&&((string22[count+6]=='A')||(string22[count+6]=='B')||(string22[count+6]=='C')||(string22[count+6]=='D')||(string22[count+6]=='E')||(string22[count+6]=='F')||(string22[count+6]=='G')||(string22[count+6]=='H')||(string22[count+6]=='I')))
                          {
                            //code to decrypt 37-45 range[40-45]
                              myDecrypt[0] = string22[count];
                              myDecrypt[1] = string22[count+12];
                              myDecrypt[2] = '\0';

                              number = atoi(myDecrypt);
                              myDcyptdchar = get_character(number);
                              finaldecrStr[j]= myDcyptdchar;

                           count =count + 12;//skip the next 12 characters
                          //copy to common  char array like   strcpy(result1,array)--but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                           continue;
                          }
                      else{
                          //code to decrypt 46-52 range[46-49]
                              myDecrypt[0] = string22[count];
                              myDecrypt[1] = string22[count+15];
                              myDecrypt[2] = '\0';

                              number = atoi(myDecrypt);
                              myDcyptdchar = get_character(number);
                              finaldecrStr[j]= myDcyptdchar;


                              count =count + 15;//skip the next 15 characters
                              //copy to common  char array like   strcpy(result1,array); -but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                              continue;
                          }

                  }

                  else if(string22[count]=='5'){
                      if(((string22[count+15]=='0')||(string22[count+15]=='1')||(string22[count+15]=='2'))&&((string22[count+8]=='A')||(string22[count+8]=='B')||(string22[count+8]=='C')||(string22[count+8]=='D')||(string22[count+8]=='E')||(string22[count+8]=='F')||(string22[count+8]=='G')||(string22[count+8]=='H')||(string22[count+8]=='I')))
                              {
                                //code to decrypt 46-52 range[50-52]
                              myDecrypt[0] = string22[count];
                              myDecrypt[1] = string22[count+15];
                              myDecrypt[2] = '\0';

                              number = atoi(myDecrypt);
                              myDcyptdchar = get_character(number);

                              finaldecrStr[j]= myDcyptdchar;

                              count =count + 15;//skip the next 15 characters
                              //copy to common  char array like   strcpy(result1,array); -but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                              continue;
                              }

                  }

                 else{

                    //code to decrypt 1- 9
                    number = assign_letters(string22[count]);//getting number that corresponds to capital letter
                    myDcyptdchar = get_character(number-26);//converting to small letter
                    finaldecrStr[j]= myDcyptdchar;

                    //copy to common  char array like   strcpy(result1,array); -but in this case use a char variable e.g char mychaaaar = resultafterDecrption;
                    continue;

                 }

                   }
                   finaldecrStr[j]='\0';
                   end5=clock();
                   double extime5=(double) (end5-start5)/CLOCKS_PER_SEC;

                   //strcat(jobs," *");
                   int len = strlen(testjob2);
                   len = len -1;
                   append(testjob2," *",len);


                   char output5[50];

                   snprintf(output5,50,"%f",extime5);
                   int leng = strlen(testjob2);
                   leng = leng-1;
                   append(testjob2,output5,leng);


                   //////write to ready Jobs
                  // ready = fopen("readylist.txt","a+");
                   fprintf(ready,"%s",testjob2);
                   printf("\n\tExecution time for decrypting is %f seconds\n ",extime5);
                   char original_command[1000];
                   strcpy(original_command,longString2);
                   strcat(original_command," ");
                   strcat(original_command,longString);
                   strcat(original_command," gives: ");
                   strcat(original_command,finaldecrStr);

                   strcpy(jobs,original_command);
                  // send(sock,server_message,sizeof(server_message),0);


         }

         fclose(ready);

  }//processor ends here.
