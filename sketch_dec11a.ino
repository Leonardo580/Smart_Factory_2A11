#define PIN_LED 13
int sensorThres = 300;
int smokeA0 = A5;
char data=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW); 
  pinMode(11,OUTPUT);
  digitalWrite(11, LOW);

 pinMode(PIN_LED , OUTPUT);
 pinMode(smokeA0, INPUT);
}
char in='2';
void loop() {
    {
    in =(char) Serial.read();
    while(in=='1'){
      if (Serial.available())
      in =Serial.read();
      if (in=='\n') in='1';
      tone(12, 1000, 500);
      digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW);
    delay(500);
    }
    
    if (in=='2'){
      noTone(12);
      digitalWrite(11, LOW);
      Serial.println(in);
      }
    }
     
  // put your main code here, to run repeatedly:
 
  //if(Serial.available())
  int analogSensor = analogRead(smokeA0);

int count=0;
if(data!='3')
 {
if (analogSensor > sensorThres)
{
   data='3';
  Serial.write(data);
  
   
} 
 }
 if(Serial.available())
{  
  data=Serial.read();
         
  if(data=='1')
  
  {  
     while(count<3)
     {
       digitalWrite(PIN_LED , HIGH);
       delay(1000);
       digitalWrite(PIN_LED , LOW);    
       delay(1000);
            /*  Serial.write('1');*/

       count++;
     } 

       if(count==3)
       {
        count =0;
       }
     

      Serial.write('1');
  }
  else if (data=='0')
  {
    digitalWrite(13, LOW);
   
    Serial.write('0');
  }
  

  
}

    
  
  delay(2000);
}
