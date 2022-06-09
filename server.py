from os import device_encoding
import socket #importamos la librería sockets, la cual nos permite comunicarnos vía tcp/ip
from typing import ByteString
import datetime
import pandas as pd
import time

def funcion_datos():
    datos = {'Sensor':[],'X':[],'acx':[],'y':[],'acy':[],'Z':[],'acz':[],'tiempo':[],'tiempo_uS':[],'Sensor2':[],'X2':[],'acx2':[],'y2':[],'acy2':[],'Z2':[],'acz2':[],'tiempo2':[],'tiempo_uS2':[]}
    #creando dataframes para los datos:
    sensor1_dataframe =pd.DataFrame(datos)
    formato = "utf-8"
    s = socket.socket()
    #Asignamos la dirección Ip del host,así como el puerto que vamos
    s.bind(('0.0.0.0', 8090)) 
    #ocupar para iniciar la comunicación
    s.listen(0)
    client, addr = s.accept()

    while(1):
        print('ejecutando...')
        texto = ""
        tamano =client.recv(2).decode(formato)
        if len(tamano) ==0:
            break
        else:
            tamano = int(tamano)
            contador = 0

            while contador<tamano:
                texto = texto + client.recv(1).decode(formato)
                contador = contador +1
            ##Convertimos en lista la cadena que acabamos de recibir:
            lista = texto.split()
            sensor1_dataframe.loc[len(sensor1_dataframe)] = lista

    if(sensor1_dataframe.empty == False):
        print("Closing connection")
        client.close()
        tiempo = datetime.datetime.now()
        archivo =tiempo.strftime('%d-%m-%Y %H %M %S ') + "datos sensor.csv"
        sensor1_dataframe.to_csv(archivo,header=False, index=False)
        print(tiempo)
while True:
    time.sleep(1)
    funcion_datos()
