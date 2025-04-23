# Aim
Implementation of Client-Server communication using Socket Programming and TCP as transport layer protocol.

# Objective
Client sends a string to the server using TCP. The server reverses the string and returns it to the client.

# Theory
## Steps For Client
1. Creation of socket
    - int socket(AF_INET, SOCK_STREAM, 0);
2. Fill the fields of the server address structure
    - struct sockaddr_in server_addr;
    - server_addr.sin_family = AF_INET;
    - server_addr.sin_port = htons(PORT);
    - We can assign server_addr.sin_addr using inet_pton()
    - inet_pton(AF_INET, "IP address", &server_addr.sin_addr);
3. Binding of client socket
    - Not necessary for client
    - bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
4. Connection of client to the server
    - connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
5. Reading from socket
    - read(client_socket, buffer, sizeof(buffer));
6. Writing to socket
    - write(client_socket, buffer, sizeof(buffer));
7. Closing the socket
    - close(int sd);

## Steps for server
1. Creating a listening socket
    - int server_socket = socket(AF_INET, SOCK_STREAM, 0);
2. Binding to a local port
    - int bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
3. Listening for incoming connections
    - listen(server_socket, 5);
4. Accepting a connection
    - int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
5. Reading from socket
    - read(client_socket, buffer, sizeof(buffer));
6. Writing to socket
    - write(client_socket, buffer, sizeof(buffer));
7. Closing the socket
    - close(int sd);

# Brief Steps
## Server
1. Create a socket using socket()
2. Bind the socket to an address using bind()
3. Listen for incoming connections using listen()
4. Accept the connection using accept()
5. Read the string from the client using read()
6. Reverse the string and send it back to the client using write()
7. Close the socket using close()

## Client
1. Create a socket using socket()
2. Fill the server address structure
3. Connect to the server using connect()
4. Send the string to the server using write()
5. Read the reversed string from the server using read()
6. Close the socket using close()
