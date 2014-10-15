  #include <Wire.h> 
  #include <Servo.h>
  #include <LiquidCrystal_I2C.h>
  
  #define trigPin1 A0
  #define echoPin1 A1
  #define trigPin2 A2
  #define echoPin2 A3
  
  #define LED 13
  #define RANG 40
  #define DELAYTIME 1000
  
  LiquidCrystal_I2C lcd(0x27,16,2);  
  Servo servo;
  
  long duration1, distance1;
  long duration2, distance2;
  
  int cound=20, car=0, i=0, m=0;
  
  void setup()
  {
    
    lcd.init();   
    lcd.backlight();
    servo.attach(9);
    
    Serial.begin (9600);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    
    pinMode(LED, OUTPUT);
    servo.write(15);   
    delay(DELAYTIME);
  }
  
  void loop()
  {
        
    lcd.home();
    lcd.print("Max Car :");
    lcd.print(" 20 ");
    lcd.setCursor(0,1);
    lcd.print("Car : ");
    lcd.print(cound);
    lcd.print("      ");
    
    checkin();
    checkout();
    
    /***********************  Check Car Full  **********************/
    if(cound <=0)    
    {
      digitalWrite(LED, HIGH);
      m=1;
    }
      while(m==1)
      {
        lcd.setCursor(0,1);
        lcd.print("Car : ");
        lcd.print(" FULL  ");
        checkout();
      }
      
    if(cound == 1)
    {
      checkin();
    }
    /***************************************************************/

  }
  
  void check1()
  {
    digitalWrite(trigPin1, LOW);   
    delayMicroseconds(2); 
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);  

    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1/2) / 29.1;
  }
  
  void check2()
  {  
    digitalWrite(trigPin2, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin2, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2/2) / 29.1;
  }
  
  /********  Check Car OUT ************************/
  void checkout()
  {
    check1();
    check2();
    if(distance1 >= RANG && distance2 <= RANG)
    {
      i=1;  
    }
    while(i == 1)
    {
      check1();
      check2();
      servo.write(90);
      
      if(distance2 >= RANG)
      {
        servo.write(15);
        delay(500);
        i=0;
      }
      if(distance1 <= RANG && distance2 <= RANG)
      {
        i=2;
      }
    }
    while(i == 2)
    {
      check1();
      check2();
      if(distance1 >= RANG && distance2 >= RANG)
      {
        servo.write(15);
        delay(500);
        i=0;
      }
      if(distance1 <= RANG && distance2 >= RANG)
      {
        i=3;
      }
    }
    while(i == 3)
    {
      check1();
      check2();
      if(distance1 >= RANG && distance2 >= RANG)
      {
        cound++;
        lcd.home();
        lcd.print("Max Car :");
        lcd.print(" 20 ");
        lcd.setCursor(0,1);
        lcd.print("Car : ");
        lcd.print(cound);
        lcd.print("     ");
        lcd.setCursor(10,1);
        lcd.print("OUT  ");
        delay(DELAYTIME);
        servo.write(15);
        i=0;m=0;
      }
    }
  }
  
  /********  Check Car Enter ************************/
  void checkin()
  {
    check1();
    check2();
    if(distance1 <= RANG && distance2 >= RANG)
    {
      i=1;  
    }
    while(i == 1)
    {
      check1();
      check2();
      servo.write(90);
      
      if(distance1 >= RANG)
      {
        servo.write(15);
        delay(500);
        i=0;
      }
      if(distance1 <= RANG && distance2 <= RANG)
      {
        i=2;
      }
    }
    while(i == 2)
    {
      check1();
      check2();
      if(distance1 >= RANG && distance2 >= RANG)
      {
        servo.write(15);
        delay(500);
        i=0;
      }
      if(distance1 >= RANG && distance2 <= RANG)
      {
        i=3;
      }
    }
    while(i == 3)
    {
      check1();
      check2();
      if(distance1 >= RANG && distance2 >= RANG)
      {
        cound--;
        lcd.home();
        lcd.print("Max Car :");
        lcd.print(" 20 ");
        lcd.setCursor(0,1);
        lcd.print("Car : ");
        lcd.print(cound);
        lcd.print("     ");
        lcd.setCursor(10,1);
        lcd.print("IN  ");
        delay(DELAYTIME);
        servo.write(15);
        i=0; m=0;
      }
    } 
  }
