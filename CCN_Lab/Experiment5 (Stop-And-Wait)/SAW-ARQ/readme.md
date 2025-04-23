# Aim
Stop-and-Wait (ARQ) using UDP

# Algorithm
## Sender
1. Create a UDP socket
2. Set a timeout for the socket
3. Send frame one by one and wait for ACK
4. If ACK is received, send the next frame
5. If ACK is not received, resend the frame
6. Close the socket
## Receiver
1. Create a UDP socket
2. Bind the socket to a port
3. Simulate random ACK loss
4. Receive frames and send ACK
5. Close the socket
