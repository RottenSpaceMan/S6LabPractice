# Aim
To implement and analyze the Stop-and-Wait protocol using sockets in C.

# Theory
- Stop-and-Wait is a simple error control protocol for reliable data transmission.
    - Sender sends one frame to the receiver
    - Waits for an acknowledgment (ACK) from the receiver
    - If ACK is received, sender sends the next frame
    - If ACK is not received within a certain time (timeout), sender retransmits the same frame
    - This process continues until all frames are successfully transmitted

## Types of Stop-and-Wait Protocols
### Stop-and-Wait for Flow Control
- Used to control the flow of data between sender and receiver
- Ensures that the sender does not overwhelm the receiver with too much data
- Receiver sends an ACK only when it is ready to receive the next frame
### Stop-and-Wait ARQ (Automatic Repeat reQuest) for Error Control
- Adds error handling to the Stop-and-Wait protocol
- Uses ACK and NAK (negative acknowledgment) to indicate successful or failed transmission
- If the sender receives a NAK, it retransmits the lost or corrupted frame

## Advantages
- Simple
- Reliable
- Works well in low-speed networks

## Disadvantages
- Low efficiency
- High latency
- Wastes bandwidth

# Example scenario
- Sender sends a frame to the receiver
    1. Sender sends frame 1
    2. Sender waits for ACK from receiver
    3. Receiver receives frame 1 and sends ACK
    4. Sender receives ACK and sends frame 2
    5. Repeat
- If the sender does not receive ACK within a certain time, it retransmits the same frame
    1. Sender sends frame 1
    2. Sender waits for ACK from receiver
    3. Timeout occurs
    4. Sender retransmits frame 1
    5. Receiver receives frame 1 and sends ACK
    6. Sender receives ACK and sends frame 2
    7. Repeat