## Introduction
Even it wasnt hard to accomplish, some of sources that I found on net werent not working. Therefore, I uploaded my code with  here if someone needs.
## Compile
**Compile client.cpp** 
```bash
$ g++ -pthread -o client client.cpp
```
**Compile server.cpp**
```bash
$ g++ -pthread -o client client.cpp
```
## Run
**Run client** 
```bash
$ ./client
```
Additionally, in order to start connection between 2 different computer ip of the server computer needs to be passed to client as argument.Like shown below.
```bash
$ ./client 192.168.1.105
```
**Run server** 
```bash
$ ./server
```
Connection can be terminated with `exit` word.
## Demonstration
<img src=https://user-images.githubusercontent.com/45767042/116830898-184c0e80-abb5-11eb-9142-c6e02c114e15.png>
## Reference
https://www.geeksforgeeks.org/socket-programming-cc/
