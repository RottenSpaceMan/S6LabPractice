# Aim
To implement and understand the working of the Leaky Bucket Algorithm for congestion control in a network

# Theory
It ensures smooth flow of data packets by controlling the rate at which packets are retransmitted into the network

# Advantages
- Prevents bursty traffic
- Controls congestion effectively
- Ensures smooth data transmission

# Disadvantages
- Can cause packet loss if the incoming data rate is too high
- Fixed output rate may lead to delays in high-speed networks

# Algorithm
1. Initialize the bucket size and transmission rate
2. For each incoming packet:
   - Check if the bucket has enough space
   - If yes, add the packet to the bucket
   - If no, drop the packet
3. At regular intervals, transmit packets from the bucket at the specified rate
4. Repeat until all packets are transmitted