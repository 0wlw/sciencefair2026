from serial.tools import list_ports
import csv
import serial
import time

ports = list_ports.comports()
for port in ports: print(port)

f = open("ytest23.csv", "w", newline='')
f.truncate()

writer = csv.writer(f, delimiter=",")

serial_port = serial.Serial("/dev/cu.usbserial-1420", 9600)

serial_port.setDTR(False)
time.sleep(1)
serial_port.flushInput()
serial_port.setDTR(True)

start_time = time.time()

maximum = 500
#writer.writerow("time,light,source,transmittance")
for point in range(maximum):
    try:
        bytes = serial_port.readline()

        decoded = bytes.decode("utf-8").strip("\r\n")
        values = decoded.split(",")

        print(values)
        writer.writerow(values)
    except:
        print("ERROR LINE ", point, " NOT RECORDED")

end_time = time.time()
#print(end_time - start_time)


f.close()
