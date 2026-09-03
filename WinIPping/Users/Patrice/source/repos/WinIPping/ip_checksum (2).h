extern USHORT ip_checksum(USHORT* buffer, int size);
/*
Footnotes

1. The traceroute utility ("tracert.exe") works by setting the TTL field to 1, sending a ping, waiting for the reply, setting TTL to 2...and so on. By looking at the addresses returned in the ICMP_TTL_EXPIRE replies, you can "trace" a route through the Internet. Eventually, you’ll get an ICMP_ECHO reply, which lets you know when you’ve completed the route to the host. (Incidentally, many Unix traceroute utilities use UDP instead of ICMP, which if nothing else doesn’t require that you use raw sockets.)

2. Finding the next hop on the network can be useful, because it allows you to discover a gateway to another network, such as the Internet. To do this, set the TTL field to 1, send the ping and see who responds with ICMP_TTL_EXPIRE. This isn’t reliable, but it can be useful in some situations.

This space intentionally left blank. :)
<< Ping: ICMP.DLL Method
	Passing Sockets Between Processes >>
Updated Mon Sep 22 2014 20:57 MDT 	  	Go to my home page*/
