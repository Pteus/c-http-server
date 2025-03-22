
# Learning to Build a C Web Server

This is my study guide and project for building a basic web server in C.  
Each step includes references to relevant **man pages** and explanations.

---

## 1 - Socket
### 1.1 - Creating a Socket
To start a server, we need to create a socket. This is done using the `socket()` system call.

#### `socket()`
```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
```
- `AF_INET`: IPv4 address family  
- `SOCK_STREAM`: TCP (use `SOCK_DGRAM` for UDP)  
- `0`: Protocol (0 = default for given socket type)  

📖 **Man page:** `man 2 socket`

---
