# ft_malcom
An introduction to network security with Man In The Middle attack


In this first project of network security, you will implement the Address Resolution Protocol spoofing/poisoning method, which is one of the most basic Man In The Middle attacks. This attack is possible using a vulnerability present in the the way the ARP protocol works and interacts in a network.

https://en.wikipedia.org/wiki/Address_Resolution_Protocol
https://www.rfc-editor.org/rfc/rfc826
https://www.rfc-editor.org/rfc/rfc7042

To get started and grasp the main concept you want to check this first
https://www.youtube.com/watch?v=cn8Zxh9bPio

________________________________________________

What is the difference between a IP adress and a MAC address?

An IP address is used to locate a device on a network, this address might change
depending on the protocol used to get one. DHCP is a popular protocol where
an IP is assigned automatically, but it can also be written manually.

A MAC address is a physical address that identifies the device. It's a globally
unique number that is assigned to every network interface card.
When a device wants to connect to another device in a Local Network, it needs
this address. 

Devices use ARP to adquire the MAC address from a device, so we could understand
it like a IP to MAC address translator.
Imagine we want to communicate from computer A to computer B.
To start, computer A will first look at its internal list, where it will check if the computerB ip has already a matching MAC address.

________________________________________________

So, what is the difference between a Ethernet Header and the information stored in a sockaddr_ll struct?

Just like sockaddr_in identifies an IP address and port, sockaddr_ll indentifies a link-layer address and protocol. In the case of raw AF_PACKET sockets, the term "address" might be confusing, since we aren't really talking about IP/MAC or whatever other address, but we are talking about an interface (e.g. a physical network device) and a protocol.

An Ethernet header contains metadata about the Ethernet frame, and indicates which protocol (EtherType field) is being encapsulated in the payload. A sockaddr_ll can be used to match or to identify a certain interface and protocol (fields .sll_ifindex and .sll_protocol):

When a packet socket is bound to a sockaddr_ll, it will only receive packets from the specified interface (.sll_ifindex) and of the specified protocol (.sll_protocol) determined by the kernel from the EtherType field of the Ethernet header.
When receiving (recvfrom or recvmsg), a sockaddr_ll structure, which identifies the interface on which the packet was received and the protocol, is populated by the kernel for the user.
When sending (sendto or sendmsg), a sockaddr_ll structure is used to specify on which interface to send the packet and which protocol to set in the Ethernet header (EtherType field).



