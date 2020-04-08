# CS330-Project
# Name: Kristen Tam
# Student Number: 200342137
# Topic: Sockets
Description:
This project is on sockets. The code for the server also includes threads. The server code keeps track of how many clients are connected to it. The threading allows multiple clients to be connected all at the same time. 
Once a client is connected, the server will send a file to the client over the socket and the contents of the file will be shown on the client's terminal. The file contains a list of options for the user to choose from. The client terminal will prompt the user. If the user chooses either option 1 (HTML file), 2(CSS file), or 3(JS file), a file will be written to the socket on the server side and read on the client side. The client will write the file into a new file saved to the current directory. The client will then open the file on a default browser. After the client has opened it on the browser, the client process will end. 
The other options given are "chat" and "exit". If a user chooses "chat", then this should allow the user to chat with other clients connected to the server. If a user chooses "exit", this will close the client side.
Challenges:
# Instructions:
Step 1. Click on the "clone or download" button on github and download the ZIP file to your computer
Step 2. Open a terminal and log onto Hercules
Step 3. Log onto a Linux machine using:
- cs_clients CL115
- ssh a0498##
Step 4. Make a directory to store the project files in
- ex. mkdir cs330project
Step 5. Copy 6 files that you got from github into your directory made in step 4 (do NOT need the README file)
Files that should be copied into directory:
- list.bbs.file
- simple.css
- simple.html
- simple.js
- project_servercode.c
- project_clientcode.c
Step 6. Compile the code using the following commands:
- gcc project_servercode.c -o server -pthread
- gcc project_clientcode.c -o client
Step 7. Open 3 more terminals and log all of them onto Hercules
Step 8. With the other 3 terminals log onto the same Linux machine used in step 3 and go into the directory made in step 4
Step 9. In one terminal execute the server:
./server
- The server will give a port number for the client to enter
Step 10. In the other 3 terminals execute the client:
./client
To test the multiple clients on the server, execute the client on the 3 servers. Enter the hostname, which is the number of the Linux machine you are using (ex. a0498##) and then enter the port number given by the server.
This will show on the server that there are 3 clients connected to it.

- Have client 1 select option 1 
- Have client 2 select option 2
- Have client 3 select option 3
- When selecting these options it will close the client program
- Then close the server by pressing control c into the terminal running the server program

Rerun the all the code again with 1 terminal running the server and the 3 other terminals running the client.
For the "chat" to work, all client terminals need to enter "chat" in the prompt. Then the user may type anything on the client terminal
