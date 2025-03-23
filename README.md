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

´
We are typecasting `server_addr` to the struct pointer `struct sockaddr *` ,i.e, whatever `addr` is pointing to, act like a `sockaddr`

📖 **Man page:** `man 2 bind`

---

## 3 - Listen

### 3.1 - Listening for Connections

Once bound, we need to listen for incoming connections using `listen()`.
`listen()` marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests.

#### `listen()`

```c
listen(socketfd, SOMAXCONN)
```

📖 **Man page:** `man 2 listen`

---

## 4 - Accept

### 4.1 - Accepting Connections

When a client connects, we accept it using `accept()`.
`accept()` extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.

#### `accept()`

```c
accept(socketfd, (struct sockaddr *restrict)&server_addr, (socklen_t *restrict)&server_addrlen)
```

📖 **Man page:** `man 2 accept`

---

## 5 - Receive & Send

### 5.1 - Receiving Data (`recv()`)

```c
char buffer[1024];
recv(connection, buffer, BUFFER_SIZE, 0);
```

📖 **Man page:** `man 2 recv`

### 5.2 - Sending Data (`send()`)

```c
char resp[] = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
send(connection, resp, sizeof(resp), 0);
```

📖 **Man page:** `man 2 send`

---
