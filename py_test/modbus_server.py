import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_tcp

# Create a Modbus TCP server instance
server = modbus_tcp.TcpServer(address="localhost", port=5502)

# Set the server name (optional)
server.set_verbose(True)

# Add a Modbus TCP slave to the server
slave = server.add_slave(1)
slave.add_block("ccc", cst.COILS, 0, 10)

try:
    # Start the Modbus TCP server
    server.start()

    # Run the server indefinitely (you can add your own logic here)
    while True:
        pass

except modbus_tk.modbus.ModbusError as e:
    print(f"Modbus error: {e}")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    # Stop the server and close the connection
    server.stop()
