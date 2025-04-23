# Aim
To implement a simple File Transfer Protocol (FTP) using socket programming in Linux, where a client sends a file to the server

# Theory
FTP transfers files over TCP/IP

# Algorithm
## Server
1. Create a socket using `socket()`
2. Bind the socket to a port using `bind()`
3. Listen for incoming connections using `listen()`
4. Accept a connection using `accept()`
5. Receive the file name from the client
6. Close the connection

## Client
1. Create a socket using `socket()`
2. Connect to the server using `connect()`
3. Open the file to be sent
4. Read the file and send data using `send()`
5. Close the connection