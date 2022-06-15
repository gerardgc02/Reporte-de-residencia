#include "Wire.h" 
const int MPU_ADDR1 = 0x68;
const int MPU_ADDR2 = 0x69;


String mpu_data(int direccion){
  ///////////////////////////////////////////////////////////////////////////////
          //Variables de los datos del sensor
          int16_t accelerometer_x, accelerometer_y, accelerometer_z;
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
          case MPU_ADDR1/* constant-expression */:
            AcSensor = String(" s1 X ");
          break;
          case MPU_ADDR2:
          AcSensor = String(" s2 X ");
          break;
          }
          
          AcSensor +=accelerometer_x;
          AcSensor += String(" Y ");
          AcSensor +=accelerometer_y;
          AcSensor += String(" Z ");
          AcSensor +=accelerometer_z;
          AcSensor +=String(" t_us ");
          AcSensor +=tiempo2;
          return AcSensor;
}

String signal_to_server(String dato1,String dato2){
  String final = dato1 + dato2;
  final = final.length() + final;
  return final;
}



void setup() {
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

}

void loop() {
  Serial.println(signal_to_server(mpu_data(MPU_ADDR1),mpu_data(MPU_ADDR2)));
}
