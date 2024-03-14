# Chit_Chat-Application

# Server Terminal
* This C++ code implements a simple TCP server using the Winsock library. The server listens on a specified port for incoming client connections and facilitates communication among connected clients.
# Prerequisites and IDE
* Visual Studio 2022
* Windows operating system
* Winsock library
# How to Use
* Compile the code using a C++ compiler that supports the Winsock library.
* Run the compiled executable.
# Initialization
* The 'Intialize' function initializes the Winsock library using 'WSAStartup'.

# Client Interaction
* The 'InteractWithClient' function is executed for each connected client in a separate thread. It receives messages from a client and broadcasts them to all other connected clients.
# Main Function
* Initializes Winsock using 'Intialize'.
* Creates a socket using 'socket'.
* Sets up the server address structure and binds it to the 'socket'.
* Listens on the socket for incoming connections.
* Accepts incoming connections and spawns a new thread for each client using 'InteractWithClient'.
* Continues to listen for new connections in an infinite loop.

# Client Terminal
* This C++ code implements a simple TCP client using the Winsock library. The client connects to a specified server and allows users to send and receive messages in a basic chat-like interface.

# Prerequisites
* Windows operating system
* Winsock library
# How to Use
* Compile the code using a C++ compiler that supports the 'Winsock library'.
* Run the compiled executable.
* Enter a chat name when prompted.
* Use the console to send and receive messages.
# Code Overview
# Initialization
T* he Intialize function initializes the Winsock library using 'WSAStartup'.

# Message Sending and Receiving
* The SendMsg function allows the user to enter messages and sends them to the server using the established 'socket connection'. Entering "quit" will stop the application.
The ReceiveMsg function continuously listens for incoming messages from the server and prints them to the console. If the server disconnects, it notifies the user.
# Main Function
* Initializes Winsock using 'Intialize'.
* Creates a socket using 'socket'.
* Sets up the server address structure and connects to the server.
* Spawns two threads - one for sending messages '(senderthread)' and one for receiving messages '(receiver)'.
* 'Joins' the threads to wait for their completion.
* Closes the socket and cleans up Winsock resources.
