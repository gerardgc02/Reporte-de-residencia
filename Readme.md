# Reporte: Sistema de medición de sismos para el IoT

## Abstract:

 La ciudad de Oaxaca se encuentra en una zona con mucha actividad sísmica, ya que cerca de las cosas del Estado de Oaxaca hay una
unión de dos placas tectónicas.

## Introducción

Situaciones de emergencia

Sismos en Oaxaca

Instituto tecnológico de Oaxaca

La tecnología actual nos permite generar dispositivos interconectados entre ellos, haciendo uso de los distintos medios de comunicación digitales, tal como el Wifi, tecnología que está presente en un gran porcentaje de los edificios de la ciudad de Oaxaca

El objetivo de este trabajo es desarrollar una serie de sensores que nos permita detectar, medir y analizar cómo se propagan los sismos en el edificio del departamento de ingeniería electrónica del Instituto tecnológico de Oaxaca, para esto utilizaremos una propuesta de arquitectura de IoT, haciendo uso de una red wifi para la comunicación entre los sensores que se proponen.

## Software:

* Arduino IDE

* VS Code

* PlatformIO

* Python 3

## Materiales

* Tarjeta de desarrollo ESP32 Dev Kit.

Está construida a partir de los chips SoC
Tensilica Xtensa LX6 el cual tiene soporte de bluetooth, wifi 2.4 GHz, puertos
de comunicación RS232, I2C, SPI, así como entradas y salidas de propósito
general, salidas de PWM, 2 ADC de 12 bits y un DAC de 8 bits.

* Acelerómetros MPU6050

Este módulo contiene 3 acelerómetros
inerciales y 3 giroscopios los cuales entregan datos de 16 bits, se comunican
con cualquier dispositivo que soporte el protocolo i2c.

* Raspberry para el servidor.

## Desarrollo

El proyecto  se desarollará en Fedora Linux como el sistema principal de mi computadora y en Raspberry pi OS como sistema del servidor.

### Primera parte Configuración de Arduino IDE

Para poder utilizar la tarjeta de desarrollo ESP32 es necesario instalar las herramientas proporcionadas por ESPRESIFF para poder compilar y grabar el código en la memoria del dispositivo. Todas estas herramientas se encuentran disponibles en el siguiente link:

 [https://dl.espressif.com/dl/package_esp32_index.json]()

Éste link debe ser pegado en el gestor de URL de tarjetas adicionales del IDE de arduino

IMAGEN

![](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Arduino-config%20(3).png?raw=true)

Instalar las herramientas en el gestor de tarjetas

![](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Arduino-config%20(4).png?raw=true)

En la barra de búsqueda escribir ESP32 y seleccionar la versión más reciente para instalar. El proceso de instalación tarda unos minutos y es necesario que exista conexión a internet.

![](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Arduino-config%20(5).png?raw=true)

En linux existe un error generado por la falta de permisos de seguridad y de una dependencia de python llamada `pyserial` 

![](https://raw.githubusercontent.com/gerardgc02/imagenes-proyecto/main/Arduino-config%20(10).png)

 Instalar la dependencia de python utilizando el comando:

`pip install pyserial`

para asignarle los permisos se utilizan los comando:

`sudo usermod -a -G dialout "usuario"`

`sudo chmod a+rw /dev/"puerto COM`

i![magen](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Arduino-config%20(11).png?raw=true)

Esto permite grabar el código en la memoria de la tarjeta

![Imagen](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Arduino-config%20(1).png?raw=true)

### Segunda parte Instalar VS Code

Visual Studio Code es un editor de texto con complementos que permiten el desarrollo de código de forma completa. Para descargar el programa hay que ingresar en el siguiente enlace y seleccionar la versión acorde al sistema, en este caso es Fedora Linux de 64bits.

[Download Visual Studio Code - Mac, Linux, Windows](https://code.visualstudio.com/download)

![](https://github.com/gerardgc02/imagenes-proyecto/blob/main/vscode-config%20(1).png?raw=true)

al terminar la descarga, escribir en una terminal el siguiente comando para instalar el paquete.

`sudo rpm -i paquete.rpm`

Se instalan los complementos del lenguaje a utilizar:

![](https://github.com/gerardgc02/imagenes-proyecto/blob/main/vscode-config%20(4).png?raw=true)

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/vscode-config%20(6).png?raw=true" title="" alt="" data-align="center">

complemento para el desarrollo remoto (SSH)

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/vscode-config%20(5).png?raw=true" title="" alt="" data-align="center">

### Tercera parte: Configuración de la Raspberry



### Cuarta parte: Configuración del AP

El AP que se utiliza es un TP link y requiere de configuración para funcionar de forma correcta con el proyecto.
obtener la ip del AP

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(6).png?raw=true" title="" alt="im" data-align="center">

acceder a la IP `192.168.0.1` del router desde el navegador, aquí se escribe el usuariio y la contraseña por defecto del dispositivo.

<img title="" src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(7).png?raw=true" alt="im" data-align="center">

Seleccionar la zona horaria del país, en este caso, México

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(12).png?raw=true" title="" alt="io" data-align="center"> 

configurar el tipo de conexión de área local

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(14).png?raw=true" title="" alt="im" data-align="center">

configurar la conexión a internet

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(21).png?raw=true" title="" alt="im" data-align="center">

Configurar nombre de la red y contraseña

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(22).png?raw=true" title="" alt="sd" data-align="center">

Resumen de configuración

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(25).png?raw=true" title="" alt="d" data-align="center">configuración terminada

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(27).png?raw=true" title="" alt="m" data-align="center">

Cambio de idioma

<img src="https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(28).png?raw=true" title="" alt="@" data-align="center">

Para que no tengamos problemas de conexión con el servidor es  necesario asignar una IP estática a la Raspberry, esto se hará desde el router. Es necesario conocer la dirección MAC de la raspberry, la cual la obtenemos con el comando `ifconfig`

en la configuración del router debemos agregar la dirección MAC  y asignarle una IP

`Avanzado > red > Reservación de direcciones`

![im](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(47).png?raw=true)

al terminar debe aparecer lo siguiente:

![am](https://github.com/gerardgc02/imagenes-proyecto/blob/main/Router-config%20(58).png?raw=true)

### Quinta parte Desarrollo del sistema

### Prototipo del sensor

### Funcionamiento del sistema

### Anexos

### Código del Cliente

### Código del servidor