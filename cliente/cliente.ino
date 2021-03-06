#include <WiFi.h>
// WiFi network info.
//datos de mi casa
/*
const char* ssid = "Guzman";
const char* password =  "7r2r-ta94-to3p";
 
const uint16_t port = 8090;
const char * host = "192.168.0.19";
*/
const char* ssid = "residencia2022";
const char* password =  "electronica2022";
 
const uint16_t port = 8090;
//mi pc ip
//const char * host = "192.168.0.198";
//Raspberry pi ip
const char * host = "192.168.0.20";


#include "Wire.h" 
const int MPU_ADDR1 = 0x68;
const int MPU_ADDR2 = 0x69;


//Variables del filtro pasabajas de tipo flotante:
float Ams2antS1[2];
float Ams2S1[2];

float Ams2antS2[2];
float Ams2S2[2];

String mpu_data(int direccion){
  ///////////////////////////////////////////////////////////////////////////////
          //Variables de los datos del sensor
          int16_t accelerometer_x, accelerometer_y, accelerometer_z;
          
          const float T =100;
          const float RC = 628.32;
          String AcSensor; 
          unsigned long tiempo1, tiempo2;
          tiempo1= micros();
          //solicitando al sensor los datos de aceleración
          Wire.beginTransmission(direccion);
          Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
          Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
          Wire.requestFrom(direccion, 6, true); // request a total of 6 registers
          //Leyendo los datos
          accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
          accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
          accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
          tiempo2 = micros() -tiempo1;
          
          
         //////////////////////////////////////////////////////////////////////////////////
          switch (direccion)
          {
          case MPU_ADDR1:
            Ams2S1[0] = accelerometer_x*(9.81/16384.0);
            Ams2S1[1] = accelerometer_y*(9.81/16384.0);
            Ams2S1[2] = accelerometer_z*(9.81/16384.0);
            //filtrando datos:
            //Salida = (T/(T+RC))*senal actual + (RC/(T+RC))*dato anterior
          
            for(int i = 0;i<3;i++){
              Ams2S1[i] = (T/(T+RC))*Ams2S1[i] + (RC/(T+RC))*Ams2antS1[i];
              Ams2antS1[i] = Ams2S1[i];
            }
            AcSensor = String(" s1 X ");
          break;
          case MPU_ADDR2:
            Ams2S2[0] = accelerometer_x*(9.81/16384.0);
            Ams2S2[1] = accelerometer_y*(9.81/16384.0);
            Ams2S2[2] = accelerometer_z*(9.81/16384.0);
            //filtrando datos:
            //Salida = (T/(T+RC))*senal actual + (RC/(T+RC))*dato anterior
          
            for(int i = 0;i<3;i++){
              Ams2S2[i] = (T/(T+RC))*Ams2S2[i] + (RC/(T+RC))*Ams2antS2[i];
              Ams2antS2[i] = Ams2S2[i];
            }
          AcSensor = String(" s2 X ");
          break;
          }
          
          AcSensor +=Ams2[0];
          AcSensor += String(" Y ");
          AcSensor +=Ams2[1];
          AcSensor += String(" Z ");
          AcSensor +=Ams2[2];
          AcSensor +=String(" t_us ");
          AcSensor +=tiempo2;
          return AcSensor;
}

String signal_to_server(String dato1,String dato2){
  String final = dato1 + dato2;
  final = final.length() + final;
  return final;
}

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
    
    Wire.begin(19,22);
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

    //Loop para el envio de datos
    for(int i = 0; i<=5000;i++){
          client.print(signal_to_server(mpu_data(MPU_ADDR1),mpu_data(MPU_ADDR2)));
    }

    Serial.println("Disconnecting...");
    client.stop();

    Serial.println("terminado");//Texto
    Serial.print("estado: ");
    Serial.println(client.connect(host, port));
}
