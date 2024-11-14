import sqlite3
conn = sqlite3.connect('av.db')
c = conn.cursor()

c.execute("""CREATE TABLE output (
    amper1 integer,
    voltage1 integer,
    amper2 integer,
    voltage2 integer,
    amper3 integer,
    voltage3 integer,
    amper4 integer,
    voltage4 integer
)""")

conn.commit()
conn.close()