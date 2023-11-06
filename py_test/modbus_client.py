import modbus_tk.defines as mbdef
import modbus_tk.modbus_tcp as mbtcp

_IP = '127.0.0.1'
_PORT = 5502

master = mbtcp.TcpMaster(host=_IP, port=_PORT)
master.set_timeout(1.0)
master.set_verbose(True)
master.open()

# resp = master.execute(slave=1, function_code=mbdef.WRITE_MULTIPLE_COILS,
#                       starting_address=0, quantity_of_x=1, output_value=[1])
# print(resp[0], hex(resp[1]))
# print(master.execute(1, mbdef.READ_COILS, 0, 1))
print(master.execute(1, mbdef.READ_DISCRETE_INPUTS, 0, 1))
# slave.execute(1, mbdef.WRITE_MULTIPLE_COILS, 0, 1, output_value=1)
