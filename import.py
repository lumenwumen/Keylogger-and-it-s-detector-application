import socket

HOST = '172.20.10.2'  # Use '0.0.0.0' to accept connections from any IP
PORT = 12345

# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to a specific address and port
server_socket.bind((HOST, PORT))

# Listen for incoming connections
server_socket.listen(1)
print(f"Server listening on {HOST}:{PORT}")

# Accept a connection
client_socket, addr = server_socket.accept()
print(f"Connection accepted from {addr}")

# Receive and print data from the client
data = client_socket.recv(1024)
print(f"Received data: {data.decode('utf-8')}")

# Close the sockets
client_socket.close()
server_socket.close()
