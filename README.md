Simple echo TCP server
=====

```bash
Usage: ./server -p <port> [-a <ip>]
  -a  --allow <ip>   Allow the IPs to send data to the server
  -p  --port  <port> Listening port
Examples:
./server -p 1234 
./server -p 1234 -a 192.168.1.1-8 
./server -p 1234 -a 192.168.1.* 
./server -p 1234 -a 192.168.1.1,4,19
```

Connect to server:

```bash
$ nc -vv localhost 1234
```

Useful for testing TCP applications


