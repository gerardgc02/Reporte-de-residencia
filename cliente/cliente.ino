#include <WiFi.h>
// WiFi network info.
//datos de mi casa

const char* ssid = "Guzman";
const char* password =  "7r2r-ta94-to3p";
 
const uint16_t port = 8090;
const char * host = "192.168.0.15";
/*
const char* ssid = "residencia2022";
const char* password =  "electronica2022";
 
const uint16_t port = 8090;
const char * host = "192.168.0.198";
*/

#include "Wire.h" 
const int MPU_ADDR1 = 0x68;
const int MPU_ADDR2 = 0x69;
int16_t accelerometer_x, accelerometer_y, accelerometer_z,accelerometer_x2, accelerometer_y2, accelerometer_z2; 


String AcSensor1;//string donde almacenamos los valores del acelerómetro.
String AcSensor2;
unsigned int tamano; //tamaño del string datos

//////////////////////
unsigned long tiempo1, tiempo_sensor1, tiempo_sensor2;


void setup(){
  pinMode(2,OUTPUT);

 //configurando el puerto serie
  Serial.begin(115200);

//prueba de comunicación del puerto i2c
    Wire.begin(19,22);
    Wire.beginTransmission(MPU_ADDR1); // Begins a transmission to the I2C slave (GY-521 board)
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR2); // Begins a transmission to the I2C slave (GY-521 board)
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
  
    //iniciamos el wifi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      //conectando
        Serial.println("...");
      delay(500);//tiempos     
    }

    Serial.println("WiFi conectado a IP: ");//Texto
    Serial.println(WiFi.localIP());
    delay(500);
}
 
void loop()
  {

    WiFiClient client;
 
    if (!client.connect(host, port)) {
        Serial.print("estado: ");
        Serial.println(client.connect(host, port));
        Serial.println("conexion fallida");//Texto
        return;
    }
        Serial.println("enviando datos");//Texto
        
    
      
      for(int i = 0; i<=2000;i++){
          digitalWrite(2,HIGH);
          tiempo1 = micros();
          Wire.beginTransmission(MPU_ADDR1);
          Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
          Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
          Wire.requestFrom(MPU_ADDR1, 7*2, true); // request a total of 7*2=14 registers

          accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
          accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
          accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
          tiempo_sensor1 =micros() -tiempo1;
          ///////////////////////////////////////////////////////////////////////////////
          
          tiempo1= micros();
          Wire.beginTransmission(MPU_ADDR2);
          Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
          Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
          Wire.requestFrom(MPU_ADDR2, 7*2, true); // request a total of 7*2=14 registers

          accelerometer_x2 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
          accelerometer_y2 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
          accelerometer_z2 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
         tiempo_sensor2 = micros() -tiempo1;
         //////////////////////////////////////////////////////////////////////////////////
          
          
          tamano = 0;
          AcSensor1 = String(" s1 X ");
          AcSensor1 +=accelerometer_x;
          AcSensor1 += String(" Y ");
          AcSensor1 +=accelerometer_y;
          AcSensor1 += String(" Z ");
          AcSensor1 +=accelerometer_z;
          AcSensor1 +=String(" t_us ");
          AcSensor1 +=tiempo_sensor1;
          //tamano = AcSensor1.length();
          //AcSensor1 = tamano + AcSensor1;
          //Serial.print(AcSensor1);
          //client.print(AcSensor1);
           
          AcSensor2=String(" s2 X ");
          AcSensor2 +=accelerometer_x2;
          AcSensor2 += String(" Y ");
          AcSensor2 +=accelerometer_y2;
          AcSensor2 += String(" Z ");
          AcSensor2 +=accelerometer_z2;
          AcSensor2 +=String(" t_us ");
          AcSensor2 +=tiempo_sensor2;
          AcSensor2=AcSensor1+AcSensor2;
          tamano = AcSensor2.length();
          AcSensor2 = tamano + AcSensor2;
          //Serial.println(AcSensor2);
          client.print(AcSensor2);
          
          AcSensor1= String("");
          AcSensor2= String("");
        }
    digitalWrite(2,LOW);
    Serial.println("Disconnecting...");
    client.stop();

    Serial.println("terminado");//Textoç
    Serial.print("estado: ");
    Serial.println(client.connect(host, port));

}
