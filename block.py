import socket

def check_open_ports(host, start_port, end_port):
    open_ports = []
    for port in range(start_port, end_port + 1):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(1)
        result = sock.connect_ex((host, port))
        if result == 0:
            open_ports.append(port)
        sock.close()
    
    return open_ports

def main():
    host = '172.20.10.2'
    start_port = 12344  # Start port number
    end_port = 12345   # End port number (adjust as needed)

    open_ports = check_open_ports(host, start_port, end_port)

    if open_ports:
        print("Warning: Open ports beyond 1024 found:")
        for port in open_ports:
            print(f"Port {port} is open.")
    else:
        print("No open ports beyond 1024 found.")

if __name__ == "__main__":
    main()
