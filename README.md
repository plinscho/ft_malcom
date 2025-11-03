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




