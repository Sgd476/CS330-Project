/* code from CS 330 lab on sockets is being reused and modified */
/* below is the description of the original code */
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

/* Use port number 0 so that we can dynamically assign an unused
 * port number. */
#define PORTNUM         0

#define LIST_FILE       "./list.bbs.file"

/* Display error message on stderr and then exit. */
#define OOPS(msg)       {perror(msg); exit(1);}

#define MAXLINE 1024

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
  int lf;
  int num_char = MAXLINE;
  pid_t fork_return;
  
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

  /* Tell socket to wait for input.  Queue length is 1. */
  if(listen(s,1) != 0)
    OOPS("listen");
  
  /* Loop indefinately and wait for events. */
  for(;;)
  {
    /* Wait in the 'accept()' call for a client to make a connection. */
    sfd = accept(s, NULL, NULL);
    if (sfd == -1)
    {
      OOPS("accept");
    }
    /* else client connection is made and will send a list of options the client 
    can select from */
    
    lf = open(LIST_FILE, O_RDONLY);
    if (lf == -1)
    {
      write(sfd, "No options.\n", strlen("No options.\n"));
    }
    /* Read from file, write to socket */
    else
    {
      while ((num_char = read(lf, ch, MAXLINE)) > 0) 
      {
        if (write(sfd, ch, num_char) < num_char)
        {
          OOPS("Writing");
        }
      }
      close(lf);
    }
    close(sfd);
  }
    
  return 0;
}
 
  
