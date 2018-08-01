# traceroute
Simple traceroute program that displays the route (path) and measuring transit delays of packets to the target IP. This implementation sends ICMP echo requests instead of UDP packets. 

## Usage
```make``` to compile.  
```make clean``` cleans folder temporary objects (such as * *.o* files).  
```make distclean``` cleans all compiled programs and leaves only source files.  
  
```
sudo ./main valid_ip_addres
```
root privileges are required due to the use of raw sockets.

## Sample
