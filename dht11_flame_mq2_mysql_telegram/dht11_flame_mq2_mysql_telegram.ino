#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "CTBot.h"
CTBot myBot;

#define DHTPIN 2     // Digital pin D4 connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
int Buzzer = D2;        // used for ESP8266
int led = D3;
int Gas_analog = A0;    // used for ESP8266
//int Gas_digital = D1;   // used for ESP8266
int flame = D1;

DHT dht(DHTPIN, DHTTYPE);

//#define SERVER_IP "192.168.140.99" //Alamat Server 

//Nama SSID dan Password WiFi
#ifndef STASSID
#define STASSID "Virus detected"
#define STAPSK  "291106SR"
//#define STASSID "nodemcu"
//#define STAPSK  "sembarang"
#endif
String token = "1832581230:AAG3ViM9k7ViY1qCQU_zMW_q0SKG29kYj1Y";
//const int id = 925607567;
const int id = 1375931977;

const char* host = "192.168.100.190";
int Led_OnBoard = 2;  

WiFiClient client;
HTTPClient http;
TBMessage msg;
void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  pinMode(Led_OnBoard, OUTPUT);
  pinMode(Buzzer, OUTPUT); 
  pinMode(led, OUTPUT);     
  //pinMode(Gas_digital, INPUT);
  pinMode(flame, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  //Koneksi ke WiFi
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(STASSID, STAPSK);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int gassensorAnalog = analogRead(Gas_analog);
    int state = digitalRead(flame);
      
    if (myBot.getNewMessage(msg)) {
     if (msg.text.equalsIgnoreCase("Cek suhu")) {              // if the received message is "LIGHT ON"...
      String suhu = "Suhu : ";
      suhu += float(t);
      suhu += " °C\n";
      suhu += "Kelembaban : ";
      suhu += float(h);
      suhu += " %\n";
      myBot.sendMessage(id, suhu, "");
      Serial.println("Mengirim data sensor ke telegram");
      } 
     else if (msg.text.equalsIgnoreCase("Cek gas")) {              // if the received message is "LIGHT ON"...
        String gas = "Gas : ";
        gas += int(gassensorAnalog);
        gas += "\n";
        gas += "Sensor Flame : ";
        gas += int(state);
        myBot.sendMessage(id, gas, "");
        Serial.println("Mengirim data sensor ke telegram");
        } 
    }
    else {
        sendingsuhu();
        sendinggasflame();
        delay(10000);
      }
}

   void sendingsuhu()
   {
    if (!client.connect(host, 8000)) {
        Serial.println("Gagal Konek");   
        return;
      }

    Serial.println("Tersambung"); 
      float h = dht.readHumidity();
      float t = dht.readTemperature();

      if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    
    String data;
    data = "/dht11?suhu=";
    data += t;
    data += "&kelembaban=";
    data += h;
    
    client.print(String("GET ") + data + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 

    Serial.print("Requesting URL: ");
    Serial.println(data);
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));

    String suhu = (String)t; 
    String kelembaban = (String)h;
    
    if ((t <= 22.00) && (h <= 40.00) ){
      String suhu = "Suhu dan Kelembaban Dingin\n";
      suhu += "Suhu : ";
      suhu += float(t);
      suhu += " °C\n";
      suhu += "Kelembaban : ";
      suhu += float(h);
      suhu += " %\n";
      myBot.sendMessage(id, suhu, "");  
      Serial.println("Mengirim data sensor ke telegram");
    } else if ((t >= 22.00) && (t <= 34.00) && (h >= 41.00) && (h <= 70.00) ) {
      String suhu = "Suhu dan Kelembaban Normal\n";
      suhu += "Suhu : ";
      suhu += float(t);
      suhu += " °C\n";
      suhu += "Kelembaban : ";
      suhu += float(h);
      suhu += " %\n";
      myBot.sendMessage(id, suhu, "");  
      Serial.println("Mengirim data sensor ke telegram");
    } else if ((t >= 33.00) && (h <= 71.00)) {
      String suhu = "Suhu dan Kelembaban Panas\n";
      suhu += "Suhu : ";
      suhu += float(t);
      suhu += " °C\n";
      suhu += "Kelembaban : ";
      suhu += float(h);
      suhu += " %\n";
      myBot.sendMessage(id, suhu, "");  
      Serial.println("Mengirim data sensor ke telegram");
      digitalWrite (Buzzer, HIGH) ; //send tone
      digitalWrite (led, HIGH);
      delay(500);
      digitalWrite (Buzzer, LOW) ;  //no tone
      digitalWrite (led, LOW);
      delay(500);
      digitalWrite (Buzzer, HIGH) ; //send tone
      digitalWrite (led, HIGH);
      delay(500);
      digitalWrite (Buzzer, LOW);
      digitalWrite (led, LOW);
      delay(500);
      digitalWrite (Buzzer, HIGH) ; //send tone
      digitalWrite (led, HIGH);
      delay(500);
      digitalWrite (Buzzer, LOW);
      digitalWrite (led, LOW);
      delay(500);
    }

    

//    while (client.available()) {
//        String line = client.readStringUntil('\r');
//        Serial.print(line);
//      }
//     
//    Serial.println();
//    Serial.println("closing connection");
    
   }

   void sendinggasflame()
   {
      if (!client.connect(host, 8000)) {
        Serial.println("Gagal Konek");   
        return;
      }
      Serial.println("Tersambung"); 
    
      int gassensorAnalog = analogRead(Gas_analog);
      //int gassensorDigital = digitalRead(Gas_digital);
      int state = digitalRead(flame);
      
      String data;
      data = "/mq2?gas=";
      data += gassensorAnalog;
      data += "&flame=";
      data += state;
      
      client.print(String("GET ") + data + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); 

      Serial.print("Requesting URL: ");
      Serial.println(data);
      Serial.print("Gas Sensor: ");
      Serial.print(gassensorAnalog);
      Serial.println("\t");

      
      if (gassensorAnalog > 500) {
        Serial.println("Gas");
        digitalWrite (Buzzer, HIGH) ; //send tone
        delay(1000);
        digitalWrite (Buzzer, LOW) ;  //no tone
        
        String gas = "Gas Terdeteksi Tinggi\n ";
        gas += int(gassensorAnalog);
        myBot.sendMessage(id, gas, "");
        digitalWrite (Buzzer, HIGH) ; //send tone
        digitalWrite (led, HIGH);
        delay(500);
        digitalWrite (Buzzer, LOW) ;  //no tone
        digitalWrite (led, LOW);
        delay(500);
        digitalWrite (Buzzer, HIGH) ; //send tone
        digitalWrite (led, HIGH);
        delay(500);
        digitalWrite (Buzzer, LOW);
        digitalWrite (led, LOW);
        delay(500);
        digitalWrite (Buzzer, HIGH) ; //send tone
        digitalWrite (led, HIGH);
        delay(500);
        digitalWrite (Buzzer, LOW);
        digitalWrite (led, LOW);
        delay(500);
      }
      else {
        Serial.println("No Gas");
        Serial.print("Sensor Flame: ");
        Serial.print(state);
        Serial.println("\t");
      }
      delay(100);
      if(state == LOW){
        Serial.println("Api terdeteksi");
        String api = "Api Terdeteksi\n ";
        myBot.sendMessage(id, api, "");

        digitalWrite (Buzzer, HIGH) ; //send tone
        digitalWrite (led, HIGH);
        delay(500);
        digitalWrite (Buzzer, LOW) ;  //no tone
        digitalWrite (led, LOW);
        delay(500);
        digitalWrite (Buzzer, HIGH) ; //send tone
        digitalWrite (led, HIGH);
        delay(500);
        digitalWrite (Buzzer, LOW);
        digitalWrite (led, LOW);
        delay(500);
        digitalWrite (Buzzer, HIGH) ; //send tone
        digitalWrite (led, HIGH);
        delay(500);
        digitalWrite (Buzzer, LOW);
        digitalWrite (led, LOW);
        delay(500);
      }else{
        digitalWrite(Buzzer, LOW);
        Serial.println("tidak ada api");
      }

      
      
//      unsigned long timeout = millis();
//      while (client.available() == 0) {
//        if (millis() - timeout > 5000) {
//          Serial.println(">>> Client Timeout !");
//          client.stop();
//          return;
//        }
//      }

//      while (client.available()) {
//        String line = client.readStringUntil('\r');
//        Serial.print(line);
//      }
//     
//      Serial.println();
//      Serial.println("closing connection");
      
  
   }
