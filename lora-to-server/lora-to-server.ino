#include <WiFi.h>
// WiFi network info.
//datos de mi casa

const char* ssid = "residencia2022";
const char* password =  "electronica2022";
 
const uint16_t port = 8090;
const char * host = "192.168.0.198";

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

#define BAND 915E6

String LoRaData;

void setup(){
    Serial.begin(115200);
    Serial.println("LoRa Receiver Test");

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
  
    //SPI LoRa pins
    SPI.begin(SCK, MISO, MOSI, SS);
    //setup LoRa transceiver module
    LoRa.setPins(SS, RST, DIO0);

    if (!LoRa.begin(BAND)) {
        Serial.println("Starting LoRa failed!");
    while (1);
    }

    Serial.println("LoRa Initializing OK!");
}

void loop() {

      WiFiClient client;
 
    if (!client.connect(host, port)) {
        Serial.print("estado: ");
        Serial.println(client.connect(host, port));
        Serial.println("conexion fallida");//Texto
        return;
    }
    Serial.println("enviando datos");//Texto

  for(int i = 0; i<=2000;i++){
  //try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
    //received a packet
    Serial.print("Received packet ");

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.println(LoRaData);
    }
    client.print(LoRaData);
    //print RSSI of packet
    int rssi = LoRa.packetRssi();
    Serial.print(" with RSSI ");    
    Serial.println(rssi);
  

    }


  }
    Serial.println("Disconnecting...");
    client.stop();

    Serial.println("terminado");//Texto
    Serial.print("estado: ");
    Serial.println(client.connect(host, port));

}
