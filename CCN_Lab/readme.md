# Viva Questions
## 1. Basics of Network Configuration Files and Networking Commands in Linux
1. Purpose of the /etc/network/interfaces file in linux
    - It is used to configure network interfaces, including IP addresses, gateways and DNS settings
2. Which command is used to check network interface details?
    - ifconfig or ip addr show
3. How do you check active network connections on a Linux machine?
    - netstat -tuln or ss -tuln
4. Which command is used to test connectivity on a remote server?
    - ping <IP>
5. How do you trace the route packets take to reach a destination
    - traceroute <IP>

## 2. System Calls for Network Programming in Linux
6. What are system calls
    - They are functions provided by the OS kernel that allows user-space programs to request services
7. Which system call is used to create a socket
    - socket()
8. What is the purpose of the bind() system call
    - It binds a socket to a specific address and port
9. Which system call is used to estabish a connection on a client-side socket
    - connect()
10. What is the purpose of the listen() system call
    - It allows a socket to listen for incoming connections on the server-side

## 3. Client-Server Communication using TCP
11. What is the main difference between TCP and UDP
    - TCP is connection-oriented and reliable, while UDP is connectionless and does not guarantee delivery
12. How does a TCP server accept client connections
    - By using the accept() system call after calling listen()
13. Which system call is used to send data in a TCP connection
    - send()
14. Which system call is used to receie data from a TCP socket
    - recv()
15. What happens if a client sends data but the server is not accepting connections?
    - The client's connect() call fails with error

## 4. Client-Server Communication using UDP
16. What is the main difference between TCP and UDP socket programming
    - UDP does not require connection establishment using connect() and accept()
17. Which system call is used to send a UDP message?
    - sendto()
18. Which system call is used to receive a UDP message?
    - recvfrom()
19. Why is UDP faster that TCP?
    - It has a lower overhead as it does not require connection setup, ACK, or retransmission
20. What happens if a UDP packet is lost?
    - It is not retransmitted, and the application must handle the loss

## 5. Stop and Wait Protocol
21. What is the Stop and Wait protocol?
    - It is a simple ARQ protocol where the sender sends one frame and waits for an ACK before sending the next
22. What happens if an ACK is lost in Stop and Wait?
    - The sender will timeout and retransmit the last frame
23. What is the main disadvantage of Stop and Wait?
    - It has low efficiency due to waiting time between transmissions
24. How can the efficiency of Stop and Wait be improved?
    - By using a sliding window protocol or increasing the frame size
25. What is the role of timers in Stop and Wait?
    - Timers are used to detect packet loss and trigger retransmissions

## 6. Stop and Wait Protocol with ARQ
26. What is ARQ(Automatic Repeat reQuest)?
    - A mechanism for error control where lost or corrupted packets are retransmitted
27. What is the main difference between Stop and Wait and Stop and Wait with ARQ?
    - Stop and Wait with ARQ includes error detection and retransmission of lost packets or NACKs
28. What happens if a packet is received with errors in Stop and Wait with ARQ?
    - The receiver discards it and sends a NACK to request retransmission of the corrupted packet
29. How duplicate packet detection handled?
    - By using sequence numbers or checksums
30. What protocol improvement reduces the impact of long propagation delays?
    - Sliding window protocol

## 7. Leaky Bucket Algorithm for Congestion Control
31. What is congestion control
    - It prevents excessive traffic from overloading network resources
32. How does the Leaky Bucket algorithm work?
    - It shapes traffic by allowing packets to exit at a fixed rate, smoothing bursty traffic
33. What is the difference between Leaky Bucket and Token Bucket algorithms?
    - Leaky Bucket uses a fixed rate for packet transmission, while Token Bucket allows bursty traffic up to a limit
34. How does Leaky Bucket help prevent congesion
    - It prevents bursts from overwhelming network buffers
35. What happens if the input rate exceeds bucket's capacity
    - Excess packets are dropped

## 8. Sliding Window Flow Control Protocols
36. What is sliding window flow control?
    - A technique to send multiple frames before waiting for an ACK
37. What is the difference between Go-Back-N and Selective Repeat protocols?
    - Go-Back-N retransmits all frames after a lost frame, while Selective Repeat only retransmits the lost frame
38. What is the role of the window size in Sliding Window protocols?
    - It determines how many packets can be sent before waiting for an ACK
39. How does Go-Back-N handle lost packets?
    - It retransmits the lost packet and all subsequent packets
40. Which protocol is more efficient: Go-Back-N or Selective Repeat?
    - Selective Repeat, since it reduces unnecessary retransmissions

## 9. Distance Vector Routing and Link State Routing
41. What is the main difference between Distance Vector and Link State routing?
    - Distance Vector uses hop count to determine the best path, while Link State considers the entire network topology
42. Which algorithm does Distance Vector routing use?
    - Bellman-Ford algorithm
43. Which algorithm does Link State routing use?
    - Dijkstra's shortest path algorithm
44. What is the count-to-infinity problem in Distance Vector routing?
    - A slow convergence issue where routes keep increasing their hop count indefinitely
45. How does Link State routing avoid count-to-infinity?
    - By sharing complete topology information and calculating shortest paths
46. What is the main advantage of Link State over Distance Vector?
    - Faster convergence and better scalability
47. What is a routing table?
    - A table storing paths to different network destinations
48. What is meant by convergence in routing protocols?
    - The time taken by routes to update and stabilze routes after a change
49. What is the purpose of sequence numbers in Link State routing?
    - To prevent old or duplicate information from being used
50. Which type of routing protocol is OSPF?
    - Link State routing protocol
