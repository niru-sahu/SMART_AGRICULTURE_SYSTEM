#include<LiquidCrystal.h>
#include<Servo.h>

int ang = 0;
Servo servo_0;

int trigPin = 10 ;
int echoPin = 8 ;  
int buzzer = 7;
float duration_us, distance_cm;

int tmp36Read;
float voltageOut;
float tempC;
float humidity;



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define motor 6
#define fan 10
#define AOUT_PIN A0
#define AOUTtemp_pin A1 
#define aref_voltage 3.3
#define AOUThumid_pin A2




void setup() 
{   
      Serial.begin(9600);
      
      lcd.begin(16,2); //defining dimension of lcd
      
      analogReference(EXTERNAL);
      //initialising arduino pins for input or output
      pinMode(trigPin, OUTPUT);
     
      pinMode(echoPin, INPUT);
      servo_0.attach(9, 500, 2500);
      pinMode(buzzer, OUTPUT);
      pinMode(AOUTtemp_pin , INPUT);
      pinMode(AOUThumid_pin , INPUT);
      lcd.clear();
    
      lcd.print("AUTOMATIC MODE");
      delay(2000);
      lcd.clear();

      welcome_message();
      lcd.clear();

      air_vent_test();
      delay(4000);
      lcd.clear();
    
}
  
void loop()

  {  
     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigPin, LOW);
     // measure duration of pulse from ECHO pin
     duration_us = pulseIn(echoPin, HIGH);
     // calculate the distance
     distance_cm = 0.017 * duration_us;
     Serial.println("------ SYSTEM DATA ------");
     Serial.print("Distance: ");
     Serial.print(distance_cm);
     Serial.println(" cm");
  
     if(distance_cm >= 0 && distance_cm  < 150)
     {  
      intruder_sense();
     } 
   
     else
     {   
      noTone(buzzer);
    
      temp_humidity_display();
      delay(500);
    
      air_vent_motion();
    
      irrigation();
      delay(500);
     }
      Serial.println("-------------------------\n");
  }
   
 

//checking for intruder if within 1.5 meters of greenhouse
void intruder_sense()
{
     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigPin, LOW);

     // measure duration of pulse from ECHO pin
     duration_us = pulseIn(echoPin, HIGH);
     // calculate the distance
     distance_cm = 0.017 * duration_us;
     
     if(distance_cm < 10000 && distance_cm > 70)
     {
       tone(buzzer, 1000); // Send 1KHz sound signal...
       lcd.print("INTRUDER !!   ");
       lcd.setCursor(0,1);
       lcd.print(distance_cm/100.00);
       lcd.println("m away!!      ");
     }
     else if(distance_cm < 70)
     {
        tone(buzzer, 1500); // Send 1.5KHz sound signal...
        lcd.print("HURRY!!!");
        delay(2000);
        lcd.clear();
        lcd.print("INTRUDER !!   ");
        lcd.setCursor(0,1);
        lcd.print(distance_cm);
        lcd.print(" cms away!!      ");
     }
    // print the value to Serial Monitor
    
    Serial.print("Buzzer: ");
    if(distance_cm < 10000 && distance_cm > 70)
    {
    Serial.println("ON (Normal Alert)");
    }
    else if(distance_cm < 70)
    {
    Serial.println("ON (High Alert)");
    }
    else
    {
    Serial.println("OFF");
    }
}

void temp_humidity_display()
{
     tmp36Read = analogRead(AOUTtemp_pin); 
     voltageOut = (tmp36Read/ 1023.0)*5000; 
     tempC = (voltageOut - 500)* 0.10; 
    
    //humidity sensor
     humidity = (analogRead(AOUThumid_pin)/1023.00)*100.00 ;
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.print(tempC);
    lcd.print(" \xB0"); // prints the degree symbol 
    lcd.print("C");
    lcd.setCursor(3,1);
    lcd.print(humidity);
    lcd.print(" %humid");
  
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
}

//air vent motions controlled according to humidity levels
void air_vent_motion()
{
    if (humidity > 60.00)//if humidity % is above 60, transpiration in plants will be directly affected and therefore water absorption from soil is hindered and therefore healthy growth is affected
    //An ideal humidity range for most mature plants is 50% to 60%.
    {
      //vents open here to allow air passage to control humidity
      
         for ( ang = 0; ang <= 90; ang += 1) 
        {  
          servo_0.write(ang);  
           delay(10);        
        }
      
      //gentle fan for airflow
      
    }
    else
    {
      servo_0.write(0);
    }  
    Serial.print("Vent Status: ");

    if (humidity > 60.00)
    {
    Serial.println("OPEN");
    }
    else
    {
    Serial.println("CLOSED");
}
   
}

//irrigation controlled according to soil moisture levels
void irrigation()
{
    int value = analogRead(AOUT_PIN); // read the analog value from sensor
    float SMoisture = value * 500.0 / 1023.0 ;
    Serial.print("Soil Moisture: ");
    Serial.println(SMoisture);
    
     if (SMoisture < 310)
    { 
     digitalWrite(motor,HIGH);
     lcd.clear();
     delay(1000);
     lcd.setCursor(0,0);
     lcd.print("WATERPUMP is ON ");
     lcd.setCursor(0,1);
     lcd.print(tempC);
     lcd.print(" \xB0"); // prints the degree symbol 
     lcd.print("C");
     delay(1000);
     lcd.setCursor(0,1);
     lcd.print(humidity);
     lcd.print("%humid     ");
     delay(2000);
     lcd.clear();
     Serial.println("WATER PUMP ON");
    }
     else
    {
       digitalWrite(motor,LOW);
       lcd.clear();
       delay(1000);
       lcd.setCursor(0,0);
       lcd.print("WATERPUMP is OFF ");
       lcd.setCursor(0,1);
       lcd.print(tempC);
       lcd.print(" \xB0"); // prints the degree symbol 
       lcd.print("C");
       delay(1000);
       lcd.setCursor(0,1);
       lcd.print(humidity);
       lcd.print("%humid     ");
       delay(2000);
       lcd.clear();
       Serial.println("WATER PUMP OFF");
    }
}

void welcome_message()
{
      lcd.print("HI, WELCOME !!");
      delay(1500);
      lcd.clear();
      lcd.print("check your");
      lcd.setCursor(0,1);
      lcd.print("GreenHouse Stats");
      delay(1000);
      for (int positionCounter = 0; positionCounter < 16; positionCounter++) 
      {
        // scroll one position right:
        lcd.scrollDisplayRight();
        // wait a bit:
        delay(200);
      }
}

void air_vent_test()
{
      lcd.print("air vents test");
      
      for (ang = 0; ang <= 90; ang += 1) 
      {
        // tell servo to go to position in variable 'pos'
        servo_0.write(ang);
        // wait 15 ms for servo to reach the position
        delay(15); // Wait for 15 millisecond(s)
      }
      for (ang = 90; ang >= 0; ang -= 1) 
      {
        // tell servo to go to position in variable 'pos'
        servo_0.write(ang);
        // wait 15 ms for servo to reach the position
        delay(15); // Wait for 15 millisecond(s)
      }
      lcd.setCursor(0,1);
      lcd.print("good to go!");
}


 