#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define TX 1
#define RX 3
char auth[]="UlNeO8UVIgWZq_GjOIMYUQPxqXDFwoBW";
char ssid[]="ANHTUAN";
char pass[]="11111111";
unsigned int gas_value[3];
byte rdata[9];
byte temp[9];
int gas;
int threshold;
boolean lock;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(pinValue==0)
  {
    Serial.write('A');
    Serial.println("nut nhan dg tat");
    lock = false;
  }
  else 
  {   
    Serial.println("nut nhan dg bat");
    lock = true;
  }
  // process received value
}
void loop() 
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  Serial.readBytes(temp,9);
  Serial.println(temp[0]);
  Serial.println(temp[1]);
  Serial.println(temp[2]);
  Serial.println(temp[3]);
  Serial.println(temp[4]);
  Serial.println(temp[5]);
  Serial.println(temp[6]);
  if(temp[0]==15)
  {
    rdata[0]=temp[1];//gas
    rdata[1]=temp[2];//gas
    rdata[2]=temp[3];//temp
    rdata[3]=temp[4];//humi
    rdata[4]=temp[5];//trehold
    rdata[5]=temp[6];//trehold
    Serial.print("Gas Value:");
    //Serial.println(rdata[0]);
    // Serial.println(rdata[1]);
    gas = (rdata[0]*100 + rdata[1]);
    Serial.println(gas);
    Serial.print("Temprature:");
    Serial.println(rdata[2]);
    Serial.print("Huminity:");
    Serial.println(rdata[3]);
    Serial.print("Threshold:");
    threshold = (rdata[4]*100 + rdata[5]);
    Serial.println(threshold);
    Blynk.virtualWrite(V1, gas);
    Blynk.virtualWrite(V2, rdata[2]);
    Blynk.virtualWrite(V3, rdata[3]);
    Blynk.virtualWrite(V4, threshold);
    if(gas >  threshold)
    {
      if(lock)Blynk.virtualWrite(V0, 1);
      else Blynk.virtualWrite(V0, 0); 
      Serial.println(String(lock));
    }
  }
  else
  {
    rdata[0]=0;//gas
    rdata[1]=0;//gas
    rdata[2]=0;//temp
    rdata[3]=0;//humi
    rdata[4]=0;//threshold
    rdata[5]=0;//threshold
  }
}
