# CS330-Project
# Name: Kristen Tam
# Student Number: 200342137
# Topic: Sockets
Description:
This project is on sockets. The code for the server also includes threads. The server code keeps track of how many clients are connected to it. The threading allows multiple clients to be connected all at the same time. <br/>
Once a client is connected, the server will send a file to the client over the socket and the contents of the file will be shown on the client's terminal. The file contains a list of options for the user to choose from. The client terminal will prompt the user. If the user chooses either option 1 (HTML file), 2(CSS file), or 3(JS file), a file will be written to the socket on the server side and read on the client side. The client will write the file into a new file saved to the current directory. After the client has saved the program as a new file, the client process will end. <br/>
The other option given is "exit". If a user chooses "exit", this will close the client side. <br/>
Challenges:
I originally planned to make a chatroom option that went along with my program but I could not make it work. I tried using the fork option in the thread but it did not work. I also tried added threads to the client code but that didn not seem to work either. In the end I decided to take that option out. I also planned for the client program to be able to run the html, css, and js files on the default browser but I struggled trying to finding a way to do that. Decided to take that out also to have a functioning program that worked. 
Another challenge I had was trying to loop the client code but that did not work and I am not sure of why. Also when you run the server and then run the client code it reads the list options twice on the client and I also didn't know how to fix this.
<br/>
# Instructions:
1. Click on the "clone or download" button on github and download the ZIP file to your computer 
2. Open a terminal and log onto Hercules 
3. Log onto a Linux machine using: 
- cs_clients CL115 
- ssh a0498## 
4. Make a directory to store the project files in and change into that directory
- ex. mkdir cs330project 
- ex. cd cs330 project 
5. Copy 6 files that you got from github into your directory made in step 4 (do NOT need the README file) <br/>
Files that should be copied into directory: 
- list.bbs.file
- simple.css
- simple.html
- simple.js
- project_servercode.c
- project_clientcode.c 
6. Compile the code using the following commands: 
- gcc project_servercode.c -o server -pthread 
- gcc project_clientcode.c -o client 
7. Open 3 more terminals and log all of them onto Hercules 
8. With the other 3 terminals log onto the same Linux machine used in step 3 and go into the directory made in step 4 
9. In one terminal execute the server: <br/>
./server <br/>
- The server will give a port number for the client to enter 
10. In the other 3 terminals execute the client: <br/>
./client <br/>
To test the multiple clients on the server, execute the client on the 3 other terminals. Enter the hostname, which is the number of the Linux machine you are using (ex. a0498##) and then enter the port number given by the server. <br/>
This will show on the server terminal that there are 3 clients connected to it. 
- Have client 1 select option 1 
- Have client 2 select option 2
- Have client 3 select option 3
- When selecting these options it will close the client program
- Then close the server by pressing control c into the terminal running the server program
<br/>

