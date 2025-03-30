# Algorithm
# Selective Repeat ARQ
# Sender
1. Initialize the window size (N) and the sequence number (seq_num).
2. Start sending frames from the sender to the receiver.
3. For each frame sent, increment the sequence number.
4. If the sequence number exceeds the window size, wait for an acknowledgment (ACK) from the receiver.
5. If an ACK is received, slide the window forward and continue sending frames.
6. If a negative acknowledgment (NAK) is received or a timeout occurs, retransmit only the missing frames.
7. Repeat steps 2-6 until all frames are sent and acknowledged.
# Receiver
1. Initialize the expected sequence number (expected_seq_num).
2. Wait for incoming frames from the sender.
3. For each received frame:
   - If the frame is in order (matches expected_seq_num), send an ACK and increment expected_seq_num.
   - If the frame is out of order, store it in a buffer and send a NAK for the expected sequence number.
4. If a NAK is received, request the sender to retransmit only the missing frames.
5. Repeat steps 2-4 until all frames are received and acknowledged.