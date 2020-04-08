/* code from CS 330 lab on sockets is being reused and modified - most of the socket setup code is 
   from the CS 330 lab code used in the exercise
*/
/* below is the description of the original code */
/* code on threading is credit to https://gist.github.com/Abhey/47e09377a527acfc2480dbc5515df872
   Abhey Rana, Multiple Client Chat Description [Source Code]
*/
/*****************************************************************
 Sockets Daemon Program

  This code was modified from Nigel Horspools, "The Berkeley
  Unix Environment".

  A daemon process is started on some host.  A socket is acquired
  for use, and it's number is displayed on the screen.  For clients
  to connect to the server, they muse use this socket number.
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

/* Use port number 0 so that we can dynamically assign an unused
 * port number. */
#define PORTNUM         0

#define LIST_FILE       "./list.bbs.file" //This file contains the options for the user to pick from
#define HTML_FILE       "simple.html"
#define CSS_FILE        "simple.css"
#define JS_FILE         "simple.js"

/* Display error message on stderr and then exit. */
#define OOPS(msg)       {perror(msg); exit(1);}

#define MAXLINE 1024

/* 
Title: Multiple Client Chat Description
Author: Abhey Rana
https://gist.github.com/Abhey/47e09377a527acfc2480dbc5515df872
*/
//initialize the clientCount
int clientCount = 0;

struct client_info
{
 int index;
 int sockID;
 struct sockaddr_in clientAddr;
 int length;
};

struct client_info Client[1024];
pthread_t thread[1024];

void *sendInfo(void * client_detail)
{
 int lf; //file descriptor for list.bbs.file
 int num_char = MAXLINE; 
 char ch[MAXLINE]; //character for i/o
 
 //enter the client info that is being passed into a struct called clientDetail
 struct client_info* clientDetail = (struct client_info*) client_detail;
 int index = clientDetail -> index;
 int clientSocket = clientDetail -> sockID;
 
 printf("Client %d connected.\n", index + 1);
 
 for(;;)
  {

    /* Open file containing list options */
    lf = open(LIST_FILE, O_RDONLY);
    if (lf == -1)
    {
      write(clientSocket, "No options.\n", strlen("No options.\n"));
    }

    //Read from the list file and write to the socket
    while ((num_char = read(lf, ch, MAXLINE)) > 0) 
    {
      if (write(clientSocket, ch, num_char) < num_char)
      {
       OOPS("Writing");
      }
    }
    close(lf);

    //erase the data in ch
    bzero(ch, sizeof(ch));

    //Read from the socket
    read(clientSocket, ch, sizeof(ch));

    //if user enters "1", open HTML file, write HTML file to socket
    if (strncmp("1", ch, 1) == 0)
    {
      //erase the data in ch
      bzero(ch, sizeof(ch));
      int htmlf;       /* file descriptor for html file */

      htmlf = open(HTML_FILE, O_RDONLY);
      if (htmlf == -1)
      {
        write(clientSocket, "No HTML file.\n", strlen("No HTML file.\n"));
      }

      printf("Sending HTML file to Client %d...\n", index + 1);

      while ((num_char = read(htmlf, ch, MAXLINE)) > 0) 
      {
        if (write(clientSocket, ch, num_char) < num_char)
        {
          OOPS("Writing");
        }
      }
      close(htmlf);
      break;
    }

    //else if user enters "2", open CSS file, write CSS file to socket
    else if (strncmp("2", ch, 1) == 0)
    {
      //erase the data in ch
      bzero(ch, sizeof(ch));
      int cssf;       /* file descriptor for css file */

      cssf = open(CSS_FILE, O_RDONLY);
      if (cssf == -1)
      {
        write(clientSocket, "No CSS file.\n", strlen("No CSS file.\n"));
      }

      printf("Sending CSS file to Client %d...\n", index + 1);

      while ((num_char = read(cssf, ch, MAXLINE)) > 0) 
      {
        if (write(clientSocket, ch, num_char) < num_char)
        {
          OOPS("Writing");
        }
      }
      close(cssf);
      break;
    }

    //else if user enters "3", open JS file, write JS file to socket
    else if (strncmp("3", ch, 1) == 0)
    {
      //erase the data in ch
      bzero(ch, sizeof(ch));
      int jsf;       /* file descriptor for js file */

      jsf = open(JS_FILE, O_RDONLY);
      if (jsf == -1)
      {
        write(clientSocket, "No JS file.\n", strlen("No JS file.\n"));
      }

      printf("Sending JS file to Client %d...\n", index + 1);

      while ((num_char = read(jsf, ch, MAXLINE)) > 0) 
      {
        if (write(clientSocket, ch, num_char) < num_char)
        {
          OOPS("Writing");
        }
      }
      close(jsf);
      break;
    }

    //else if user enters "chat"
    else if (strncmp("chat", ch, 4) == 0)
    {
      for (;;)
      {
        //erase the data in ch
        bzero(ch, sizeof(ch));

        //read from client socket
        read(clientSocket, ch, sizeof(ch));

        //write to all other clients
        int i = 1;
        while (i < clientCount)
        {
          if (i != index)
          {
            write(Client[i].sockID, ch, sizeof(ch));
          }
        }
      }
    }

    //else if user enters "exit", client has closed the session
    else if (strncmp("exit", ch, 4) == 0)
    {
      printf("Client %d has exited the session....\n", index + 1);
      break;
    }

    //If user enters an invalid response. Nothing happens to server
    else
    {
      printf("\n");
    }

  }

  close(clientSocket);
}


/*
CS330 Lab Sockets
*/

int main()
{
  struct sockaddr_in saddr; /* socket information */
  struct hostent *hp; /* host information */
  char hostname[256];     /* host computer */
  socklen_t slen;         /* length socket address */
  int s;                  /* socket return value */
  int sfd;                /* socket descriptor returned from accept() */
  char ch[MAXLINE];       /* character for i/o */
  FILE *sf;               /* various file descriptors */
  int lf;                 /* file descriptor for list file */
  int num_char = MAXLINE;
  
  /*
  * Build up our network address. Notice how it is made of machine name + port.
  */

  /* Clear the data structure (saddr) to 0's. */
  memset(&saddr,0,sizeof(saddr));

  /* Tell our socket to be of the internet family (AF_INET). */
  saddr.sin_family = AF_INET;

  /* Aquire the name of the current host system (the local machine). */
  gethostname(hostname,sizeof(hostname));

  /* Return misc. host information.  Store the results in the
   * hp (hostent) data structure.  */
  hp = gethostbyname(hostname);

  /* Copy the host address to the socket data structure. */
  memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);

  /* Convert the integer Port Number to the network-short standard
   * required for networking stuff. This accounts for byte order differences.*/
  saddr.sin_port = htons(PORTNUM);
  
  /*
   * Now that we have our data structure full of useful information,
   * open up the socket the way we want to use it.
   */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
    OOPS("socket");

  /* Register our address with the system. */
  if(bind(s,(struct sockaddr *)&saddr,sizeof(saddr)) != 0)
    OOPS("bind");

  /* Display the port that has been assigned to us. */
  slen = sizeof(saddr);
  getsockname(s,(struct sockaddr *)&saddr,&slen);
  printf("Socket assigned: %d\n",ntohs(saddr.sin_port));

  /* Tell socket to wait for input.  Queue length is 5. */
  if(listen(s,5) != 0)
    OOPS("listen");


  /* accept */
  sfd = accept(s, NULL, NULL);
  if (sfd == -1)
    OOPS("accept");
  

/* 
Title: Multiple Client Chat Description
Author: Abhey Rana
https://gist.github.com/Abhey/47e09377a527acfc2480dbc5515df872
*/
  /* Loop indefinately and wait for events. */
  for(;;)
    {
    /* Wait in the 'accept()' call for a client to make a connection. */
    Client[clientCount].sockID = accept(s, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
    if (Client[clientCount].sockID == -1)
    {
      OOPS("accept");
    }

    Client[clientCount].index = clientCount;

    pthread_create(&thread[clientCount], NULL, sendInfo, (void *) &Client[clientCount]);
    
    clientCount++;
  }

  int i = 0;
  while (i < clientCount)
  {
    pthread_join(thread[i], NULL);
    i++;
  }


    
  return 0;
}
 
  
