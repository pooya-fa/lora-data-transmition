import serial
import pynmea2
import sqlite3

ser = serial.Serial('COM11', baudrate=9600, timeout=1)

while True:
    data = ser.readline()
    conn = sqlite3.connect('av.db')
    c = conn.cursor()
    if data.startswith(b'Processed:'):
        msg = pynmea2.parse(data.decode('utf-8'))
        msg = str(msg).split(',')
        module1 = msg[1].split()
        module2 = msg[2].split()
        module3 = msg[3].split()
        module4 = msg[4].split()

        c.execute(
            f"INSERT INTO output (amper1,voltage1,amper2,voltage2,amper3,voltage3,amper4,voltage4) VALUES ({module1[1]},{module1[2]},{module2[1]},{module2[2]},{module3[1]},{module3[2]},{module4[1]},{module4[2]})")
        data = c.execute("SELECT rowid, * FROM output")
        for row in data.fetchall():
            print(row)
            if row[0] > 10:
                data.execute("DELETE FROM output")

        conn.commit()
        conn.close()
        msg.clear()
        module1.clear()
        module2.clear()
        module3.clear()
        module4.clear()
