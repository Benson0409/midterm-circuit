#include "DHT.h"  //引入函式庫
#define DHT11PIN 14

DHT dht(DHT11PIN, DHT11); //宣告DHT物件
int signalPin = 12;                  //用來trigger及接收echo
long duration, cm, inches;
void setup()
{
  Serial.begin(115200);
  dht.begin();  //DHT物件啟動
  pinMode(27,OUTPUT);
  pinMode(12,INPUT);
  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
}

void loop()
{
  pinMode(signalPin, OUTPUT); //發送超音波時切還為輸出
  digitalWrite(signalPin, LOW);
  delayMicroseconds(5);
  digitalWrite(signalPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(signalPin, LOW);

  pinMode(signalPin, INPUT);             // //讀取超音波時切還為輸入
  duration = pulseIn(signalPin, HIGH);   // 收到高電位時的時間
 
  cm = (duration/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  inches = (duration/2) / 74; 

  Serial.print("Distance : ");  
  Serial.print(inches);
  Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
  float humi = dht.readHumidity();  //DHT讀取濕度
  float temp = dht.readTemperature(); //DHT讀取溫度
  if(temp>=27&&cm<=40){
    digitalWrite(27,HIGH);
    digitalWrite(26,LOW);
    digitalWrite(25,LOW);
  }
  else if(temp<27&&cm<=40){
    digitalWrite(27,LOW);
    digitalWrite(25,HIGH);
    digitalWrite(26,LOW);
  }
  else if(temp>27 && cm>40) {
    digitalWrite(27,LOW);
    digitalWrite(26,HIGH);
    digitalWrite(25,LOW);
  }
  else{
    digitalWrite(27,LOW);
    digitalWrite(26,HIGH);
    digitalWrite(25,HIGH);
  }
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
}
