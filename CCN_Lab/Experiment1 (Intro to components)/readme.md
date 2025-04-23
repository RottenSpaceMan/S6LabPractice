# Aim
Familiarisation of Networking commands and config files

# Commands
- ipaddr : set or display the IP address and netmask of a network interface.
- ping : sends ICMP Echo requests to a server and awaits response
- nslookup : queries DNS servers to fetch server IP
- traceroute : determines packet travel path and hops
- host : finds domain name associated with IP or IP address associated with hostname
- netstat : displays routing table, connection information, status of ports, etc.(ie the /proc/net file)
- dig : queries DNS servers about DNS records, mainly for troubleshooting
- route : shows and manipulates ip routing table

# Network Config Files
- /etc/hosts : registry of IP addresses and hostnames known to the system
- /etc/hostname.if_name : used in some OS's to configure network interfaces at boot time
- /etc/services : list of network ports and services that correspond to those ports
- /etc/resolv.conf : specifies DNS servces that the system should use to resolve domain names
- /etc/nsswitch.conf : configures the order of name services lookups
- /etc/networks : maps network names with network addresses