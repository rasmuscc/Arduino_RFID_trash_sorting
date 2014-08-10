# -*- coding: cp1252 -*-
# Arduino læs serial com. og skriv til mysql.
# Teknologi sommer
# Magnus, Simon Rasmus - 29-03

import serial
import MySQLdb

ser = serial.Serial("COM5", 9600)
# Opret db connection
db = MySQLdb.connect("0.0.0.0","root","xxx","data" )
# Cursor objekt
cursor = db.cursor()

while True:
    shit = ser.readline()
    
    # '\r\n' er fordi arduino bruger funktionen println() og ikke write()
    if shit == "1\r\n":
        print "tag 1"
        try:
            cursor.execute("UPDATE edata SET saldo=saldo +3 WHERE username='xxx'")
            db.commit()
        except:
            print "Error writing to mysql. Rolling back..."
            db.rollback()
                    
    elif shit == "2\r\n":
        print "tag 2"
        try:
            cursor.execute("UPDATE edata SET saldo=saldo +3 WHERE username='yyy'")
            db.commit()
        except:
            print "Error writing to mysql. Rolling back..."
            db.rollback()
                    
    else:
        print "kunne ikke genkende input:", (shit)
