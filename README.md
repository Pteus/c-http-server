# Learning to Build a C Web Server

This is my study guide and project for building a basic web server in C.  
Each step includes references to relevant **man pages** and explanations.

---

## 1 - Socket

### 1.1 - Creating a Socket

To start a server, we need to create a socket. This is done using the `socket()` system call.

#### `socket()`

```c
int socketfd = socket(AF_INET, SOCK_STREAM, 0);
```

- `AF_INET`: IPv4 address family
- `SOCK_STREAM`: TCP (use `SOCK_DGRAM` for UDP)
- `0`: Protocol (0 = default for given socket type)

📖 **Man page:** `man 2 socket`

---

## 2 - Bind

### 2.1 - Binding the Socket

Before accepting connections, the socket must be bound to an address and port using `bind()`.

#### `bind()`

```c
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = htons(INADDR_ANY);

bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr);
```

We are typecasting server_addr to the struct pointer struct sockaddr \* ,i.e, whatever addr is pointing to, act like a sockaddr

📖 **Man page:** `man 2 bind`

---
