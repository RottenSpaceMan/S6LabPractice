# Aim
Using UDP to perform Matrix Multiplication using Socket programming

# Theory
- We are using UDP, which is a fast and connectionless protocol

## Matrix Multiplication
- Matrix multiplication is only possible if the matrix A(m x n) and matrix B(o x p) share the same value of n number of columns and o number of rows respectively.

## Program Description
### Server side
- A socket() is created with AF_INET, and SOCK_DGRAM(UDP)
    - int file_discriptor = socket(AF_INET, SOCK_DGRAM, 0);
- The server binds the socket to a port using bind()
    - bind(file_discriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
- The server listens for incoming messages using recvfrom()
    - recvfrom(file_discriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
- The server receives the matrix dimensions(r1, c1, r2, c2) and the matrices A and B from the client
- The server performs the matrix multiplication and sends the result back to the client using sendto()
    - sendto(file_discriptor, result, sizeof(result), 0, (struct sockaddr *)&client_addr, addr_len);

### Client side
- A socket() is created with AF_INET, and SOCK_DGRAM(UDP)
    - int file_discriptor = socket(AF_INET, SOCK_DGRAM, 0);
- The client takes user input from the user for dimension and elements
- The client sends matrix dimensions and elements to the server using sendto()
    - sendto(file_discriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, addr_len);
- The client receives the result from the server using recvfrom()
    - recvfrom(file_discriptor, result, sizeof(result), 0, (struct sockaddr *)&server_addr, &addr_len);
- The client prints the result

# Algorithm
## Server side
1. Create a UDP socket using socket()
2. Create a sockaddr_in structure to hold the server address
3. Bind the socket to a port using bind()
4. Listen for incoming messages using recvfrom()
5. Perform matrix multiplication
    - Initiliaze all elements of the result as 0
    - Use nested loops to compute product
6. Send the result back to the client using sendto()
7. Close the socket using close()

## Client side
1. Create a UDP socket using socket()
2. Create a sockaddr_in structure to hold the server address
3. Take user input for matrix dimensions and elements
4. Send the matrix dimensions and elements to the server using sendto()
5. Receive the result from the server using recvfrom()
6. Print the result
7. Close the socket using close()

# Functions Used
1. socket()
    - int socket(int domain, int type, int protocol)
2. bind()
    - int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
3. sendto()
    - ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
4. recvfrom()
    - ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
5. memset()
    - void *memset(void *string, int value, size_t num)
    - Initializes a block of memory to a specific value
6. close()
    - int close(int fd)
