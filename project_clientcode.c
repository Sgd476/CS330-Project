/* code from CS 330 lab on sockets is being reused and modified - most of the socket setup code is 
   from the CS 330 lab code used in the exercise
*/
/* below is the description of the original code */

/*****************************************************************
  Sockets Client Program 

  This code is a modified version taken from Nigel Horspool's "The Berkeley
  Unix Environment".

  This client connects to a specified server (host) and receives
  information from it.
*****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>   //needed for open
#include <fcntl.h>      //needed for open

/* Display error message on stderr and then exit. */
#define OOPS(msg)       {perror(msg); exit(1);}

#define MAXLINE 512

int main(int argc, char *argv[])
{
  struct sockaddr_in bba; /* socket information */
  struct hostent *hp;     /* host information */
  int slen;               /* host computer */
  int s;                  /* length socket address */
  int rfd;
  char ch[MAXLINE];       /* character for i/o */
  int num_char=MAXLINE;   /* number of characters */
  int port;               /* port to connect to */

  char portnum[20];
  char hostname[20];
  printf("\n hostname:");
  scanf("%s", hostname);

  printf("\n port number:");
  scanf("%s", portnum);

  /* Clear the data structure (saddr) to 0's. */
  memset(&bba,0,sizeof(bba));

  /* Tell our socket to be of the internet family (AF_INET). */
  bba.sin_family = AF_INET;

  /* Acquire the ip address of the server */
  hp=gethostbyname(hostname);

  /* Acquire the port #. */
  port=atoi(portnum);

  /* Copy the server's address to the socket address data structure. */
  memcpy(&bba.sin_addr, hp->h_addr, hp->h_length);

  /* Convert the integer Port Number to the network-short standard
   * required for networking stuff. This accounts for byte order differences.*/
  bba.sin_port=htons(port);
  
  /* Now that we have our data structure full of useful information,
   * open up the socket the way we want to use it.
   */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
    OOPS("socket");
  if(connect(s,(struct sockaddr *)&bba,sizeof(bba)) != 0)
    OOPS("connect");

  for(;;)
  {
    int n = 0;
    /* Read from socket */
    read(s, ch, sizeof(ch));
    printf("%s", ch);
    printf("Enter : ");

    while((ch[n++] = getchar()) != '\n')
      ;

    /*write to socket */
    write(s, ch, sizeof(ch));

    //if user enters "1", open a new html file and write contents from socket into new html file
    if(strncmp("1", ch, 1) == 0)
    {
      int htmlf;          /*file descriptor for HTML file */

      //open newsimple.html file
      htmlf = open("newsimple.html", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
      if (htmlf == -1)
      {
        perror(NULL);
        exit(1);
      }

      printf("Receiving HTML file... \nSaving as newsimple.html to current directory...\n");

      //write to newsimple.html file
      while((num_char = read(s, ch, MAXLINE)) > 0)
      {
        if (write(htmlf, ch, num_char) < num_char)
        {
            OOPS("writing");
        }
      }

      close(htmlf);
      break;
    }

    //if user enters "2", open a new css file and write contents from socket into new css file
    if(strncmp("2", ch, 1) == 0)
    {
      int cssf;          /*file descriptor for CSS file */

      //open newsimple.html file
      cssf = open("newsimple.css", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
      if (cssf == -1)
      {
        perror(NULL);
        exit(1);
      }

      printf("Receiving CSS file... \nSaving as newsimple.css to current directory...\n");

      //write to newsimple.html file
      while((num_char = read(s, ch, MAXLINE)) > 0)
      {
        if (write(cssf, ch, num_char) < num_char)
        {
            OOPS("writing");
        }
      }

      close(cssf);
      break;
    }

    //if user enters "3", open a new js file and write contents from socket into new js file 
    if(strncmp("3", ch, 1) == 0)
    {
      int jsf;          /*file descriptor for JS file */

      //open newsimple.html file
      jsf = open("newsimple.js", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
      if (jsf == -1)
      {
        perror(NULL);
        exit(1);
      }

      printf("Receiving JS file... \nSaving as newsimple.js to current directory...\n");

      //write to newsimple.html file
      while((num_char = read(s, ch, MAXLINE)) > 0)
      {
        if (write(jsf, ch, num_char) < num_char)
        {
            OOPS("writing");
        }
      }

      close(jsf);
      break;
    }
    
    //if user enters "exit", client has closed session and program will end
    if (strncmp("exit", ch, 4) == 0)
    {
      printf("Client exit...\n");
    	break;
    }
      
  }


  close(s);


  return 0;
}
