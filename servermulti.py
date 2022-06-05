import socket
import os
from _thread import *
from os import device_encoding
from typing import ByteString
import datetime
import pandas as pd
import time

ServerSocket = socket.socket()
host = '0.0.0.0'
port = 8090
ThreadCount = 0

try:
    ServerSocket.bind((host, port))
except socket.error as e:
    print(str(e))

print('Waiting for a Connection..')
ServerSocket.listen(5)

def threaded_client(connection):
    datos = {'Sensor':[],'X':[],'acx':[],'y':[],'acy':[],'Z':[],'acz':[],'tiempo':[],'tiempo_uS':[],'Sensor2':[],'X2':[],'acx2':[],'y2':[],'acy2':[],'Z2':[],'acz2':[],'tiempo2':[],'tiempo_uS2':[]}
    #creando dataframes para los datos:
    sensor_dataframe =pd.DataFrame(datos)
    #print(sensor1_dataframe)
    formato = "utf-8"
    while(1):
        #print('ejecutando...')
        texto = ""
        tamano =connection.recv(2).decode(formato)
        if len(tamano) ==0:
            connection.close()
            break
        else:
            #print("tamano: "+ tamano + "from " + address[0])
            tamano = int(tamano)
            contador = 0

            while contador<tamano:
                texto = texto + connection.recv(1).decode(formato)
                contador = contador +1
            ##Convertimos en lista la cadena que acabamos de recibir:    
            lista = texto.split()
            sensor_dataframe.loc[len(sensor_dataframe)] = lista

    if(sensor_dataframe.empty == False):
        print("Closing connection from:"+ address[0] + "\n")
        connection.close()
        tiempo = datetime.datetime.now()
        archivo1 =address[0] + " " + tiempo.strftime('%d-%m-%Y %H %M %S ') + "datos sensor1.csv"
        sensor_dataframe.to_csv(archivo1,header=False,index=False)
        print(tiempo)
        sensor1_dataframe = 0
    else:
        print("no data from " + address[0] + "\n")

while True:
    Client, address = ServerSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]) + "\n")
    start_new_thread(threaded_client, (Client, ))
    #ThreadCount += 1
    #print('Thread Number: ' + str(ThreadCount))
ServerSocket.close()