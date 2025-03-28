# Aim
To familiarize and understand the use and functioning of system calls used for programming in linux

Tip : IF YOU FORGET SOME IN THE MIDDLE OF EXAMS, you can type `man <thing>` for a detailed explanation for most things
`man man` to know more about the manual
`man 2 <thing>` gives information about system calls(socket, bind, accept, send, recv)
`man 3 <thing>` gives information about library functions(htons, inet_pton)
`man 5 <thing>` info about file formats and conventions(protocols, services)
some man pages have examples at the end, espcially in `man 5`
`man 7 unix`
most of the time, the numbers dont really need to be used, just check if the NAME section matches your interest

# Theory
- int socket(int domain, int type, int protocol) : creates a socket, a communication endpoint, and returns a file descriptor
    - domain : AF_INET usually(communication domain)
    - type : SOCK_STREAM for TCP, SOCK_DGRAM for UDP
    - protocol : set as 0 usually

- int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) : assigns IP and port number to a socket
    - sockfd : file descriptor for socket
    - *addr : a pointer to a struct sockaddr that contains address to bind the socket to
        - struct sockaddr_in addr;
            - addr.sin_family = AF_INET - An address family(eg., IPv4)
            - addr.sin_port = htons(PORT) - Port number
            - addr.sin_addr.s_addr = INADDR_ANY - Accept from any network interface(WiFi, ethernet, etc)
    - addrlen : size of *addr, usually `sizeof(addr)`
    - It returns 0 on success, -1 on failure

- int listen(int sockfd, int backlog) : listens for incoming connections(for servers)
    - sockfd : file descriptor for socket
    - backlog : maximum length of queue of pending connections
    - It returns 0 on success, -1 on failure

- int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) : accepts a connection from clients, and creates a socket for it
    - sockfd : file descriptor for socket
    - *addr : a pointer to a struct sockaddr that contains address of the client
    - *addrlen : size of *addr, usually `sizeof(addr)`
    - It returns a new file descriptor for the accepted socket, -1 on failure

- int connect(int sockfd, const struct sockadrr * addr, socklen_t addrlen) : Used by a client to establish a connection to a server, it requires the server address and port number to initiate the connection
    - sockfd : file descriptor for socket
    - *addr : a pointer to a struct sockaddr that contains address of the server
    - addrlen : size of *addr, usually `sizeof(addr)`
    - It returns 0 on success, -1 on failure

- int send(int sockfd, const void *buf, size_t len, int flags) : sends data on a connected socket(TCP)
    - sockfd : file descriptor for socket
    - *buf : pointer to the data to be sent
    - len : length of the data
    - flags : usually 0
    - It returns the number of bytes sent, -1 on failure

- int recv(int sockfd, void *buf, size_t len, int flags) : receives data from a connected socket(TCP)
    - sockfd : file descriptor for socket
    - *buf : pointer to the buffer to store the data
    - len : length of the buffer
    - flags : usually 0
    - It returns the number of bytes received, -1 on failure

- int close(int sockfd) : closes the socket

- select() and poll() are used for handling multiple file descriptors to determine their readiness for I/O operations, such as reading or writing

# Example Model of Client-Server Communication
## Server
1. Create a socket using `socket()`
2. Assign an address using `bind()`
3. Listen for incoming connections using `listen()`
4. Accept a connection using `accept()`
5. Send and receive data using `send()` and `recv()`
6. Close the socket using `close()`

## Client
1. Create a socket using `socket()`
2. Establish a connection to the server using `connect()`
3. Send and receive data using `send()` and `recv()`
4. Close the socket using `close()`