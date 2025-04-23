# Aim
To study and implement the Sliding Window Flow Control Protocols, including Go-Back-N and Selective Repeat ARQ, and analyze their performance in ensuring reliable data transmission.

# Theory
## Go-Back-N ARQ
Sender sends multiple frames based on the window size without waiting for acknowledgement for each frame. However, if an error is detected in a frame, all subsequent frames are discarded, and the sender must retransmit from the erroneous frame onwards.
### Steps
1. Sender transmits a set of frames (up to the window size).
2. Receiver checks for errors in each frame and send and ACK for the last correctly received fram
3. If the frame is lost or corrupted, the receiver discards it and all subsequent frames.
4. Sender retransmits the lost or corrupted frame and all subsequent frames when a timeout occurs or a NAK is received
### Advantages
- Simple to implement
- Efficient for low error rates
### Disadvantages
- Inefficient for high error rates, as many frames may need to be retransmitted

## Selective Repeat ARQ
Sender can transmit multiple frames and only retransmit the specific frames that are lost or corrupted. The receiver can accept out-of-order frames and buffer them until the missing frames are received.
### Steps
1. Sender transmits a set of frames (up to the window size).
2. Receiver checks for errors in each frame and sends an ACK for each correctly received frame.
3. If a frame is lost or corrupted, the receiver sends a NAK for that specific frame.
4. Sender retransmits only the lost or corrupted frame when a NAK is received or a timeout occurs.
### Advantages
- Higher efficiency in error prone networks
- Avoids unnecessary retransmissions, improving bandwidth utilization
