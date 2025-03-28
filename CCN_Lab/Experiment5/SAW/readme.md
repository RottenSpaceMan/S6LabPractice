# Aim
Stop and wait protocol
# Algorithm

## Sender
1. Create a TCP socket using `socket()`.
2. Create a `sockaddr_in` structure to hold the server address.
3. Establish a connection to the server using `connect()`.
4. Send messages to the server using `send()`.
5. Wait for an ACK or response from the server using `recv()`.
6. If no response is received within a certain time, retransmit the same message.
7. Close the socket using `close()`.

## Receiver
1. Create a TCP socket using `socket()`.
2. Create a `sockaddr_in` structure to hold the server address.
3. Bind the socket to a port using `bind()`.
4. Listen for incoming connections using `listen()`.
5. Accept a connection from the sender using `accept()`.
6. Receive messages from the sender using `recv()`.
7. Send an ACK or response back to the sender using `send()`.
8. Close the connection and the socket using `close()`.
