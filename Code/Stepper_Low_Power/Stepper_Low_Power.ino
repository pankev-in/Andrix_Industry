/*
  Name:            Stepper Motor Controller (Serial Communication) - 3.5A low power version
  Autor:           Alexander Wurm, Kevin Pan
  Discribtion:     Stepper Motor Controller (Serial Communication) - 3.5A low power version
  Last Update:     XX.XX.XXXX
  Contact:         kpan@student.tgm.ac.at, awurm@student.tgm.ac.at
*/

//Pin setups:
#define Sensor_Touch_Sensor_Pin 7                              //Touch Sensor(init) pin
#define Motor_Clock_pin	9                               //Clock(Tacks) CLK+ pin
#define Motor_Direction_pin 8                           //Direction CW+ pin
#define Motor_Enable_pin 10
#define Lcd_D7_pin 2
#define Lcd_D6_pin 3
#define Lcd_D5_pin 4
#define Lcd_D4_pin 5
#define Lcd_Enable_pin 11
#define Lcd_RS_pin 12
#define Lcd_Backlight_pin 6

//Static values:
#define Maximum_steps 32250	                        //Maximum steps
#define Axis_length 4950			        //Maximum Length
#define Clock_impuls 100 			        //Microsecond

//Variables:
int Current_position = 0;			        //Milimeter
float Step_resolution = 0.15349;      //Stepmotor step-resolution in mm
String inputString = "";              // a string to hold incoming data
boolean stringComplete = false;       // whether the string is complete
int delayOfMotor = 0 ;
boolean motor_enable;

void setup() {
  _init();
}

void _init(){                   //Initailizing Pin setups
    inputString.reserve(32);
    motor_enable=true;
    pinMode(Motor_Enable_pin,OUTPUT);
    pinMode(Motor_Direction_pin, OUTPUT);
    pinMode(Motor_Motor_Clock_pin, OUTPUT);
    pinMode(Sensor_Touch_Sensor_Pin,INPUT);
    digitalWrite(Motor_Enable_pin,LOW);
    digitalWrite(Motor_Direction_pin, LOW);
    digitalWrite(Motor_Motor_Clock_pin, LOW);
    reset();
    digitalWrite(Motor_Enable_pin,HIGH);
    motor_enable=false;
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '@') {
      stringComplete = true;
    }
  }
}

void loop() {
  if (stringComplete) {
    String command=inputString.substring(0,3);
    Serial.print("Input Command:\t");Serial.println(command);
    if(command=="ENA"){
      Serial.println("motor enabled");
      digitalWrite(Motor_Enable_pin, LOW);
      motor_enable=true;
    }
    else if(command=="DIS"){
      Serial.println("motor disabled");
      digitalWrite(Motor_Enable_pin,HIGH);
      motor_enable=false;
    }
    else if(command=="RES"){
      Serial.println("Position resets");
      reset();
    }
    else if(command=="GTP"){
      int pos=inputString.substring(3,inputString.length()).toInt();
      Serial.print("Going to position: \t");Serial.println(pos);
      goToPosition(pos);
    }
    else if(command=="SST"){
      int del=inputString.substring(3,inputString.length()).toInt();
      Serial.print("Set delay to: \t");Serial.println(del);
      delayOfMotor=del;
    }
    else if(command=="CTP"){
      String out = String(Current_position) + "@";
      Serial.println(out);
    }
    else if(command=="CTS"){
      if(delayOfMotor==0){
          Serial.println("0@");
        }
      else{
          String out = String(delayOfMotor) + "@";
          Serial.println(out);
        }
    }
    else{
      Serial.println("SYSTEM: Serial input error");
      Serial.print("Input:\t");
      Serial.println(inputString);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void reset(){                   //RESET THE POSITION BACK TO 0 USING SENSOR
  if(motor_enable==true){
    digitalWrite(Motor_Direction_pin, HIGH);
    while(!digitalRead(Sensor_Touch_Sensor_Pin)){
      digitalWrite(Motor_Motor_Clock_pin, HIGH);
      delayMicroseconds(Clock_impuls);
      digitalWrite(Motor_Motor_Clock_pin, LOW);
      delayMicroseconds(Clock_impuls);
      delay(delayOfMotor);
    }
    Current_position = 0;
  }
}

void goToPosition(int x_position){
    if(motor_enable==false){return;}

    //checking if the input value is posible:
    if(x_position<0 || x_position>4950){
      return;
    }

    //calculating the difference:
    int diff = x_position - Current_position;
    if(diff>0){
      digitalWrite(Motor_Direction_pin, LOW);
    }
    else if(diff<0){
      digitalWrite(Motor_Direction_pin, HIGH);
      diff=-diff;
    }
    else {
      return;
    }

    //If the position is going back to zero:(will be repalced with a digital button)
    if(x_position==0){
      int k = (int)(Current_position/Step_resolution);
      for(int i=1;i<=k; i++){
        digitalWrite(Motor_Motor_Clock_pin, HIGH);
        delayMicroseconds(Clock_impuls);
        digitalWrite(Motor_Clock_pin, LOW);
        delayMicroseconds(Clock_impuls);
        delay(delayOfMotor);
      }
      Current_position =0;
      return;
    }

    int steps = (int)(diff/Step_resolution);
    for(int i=1;i<=steps; i++){
      digitalWrite(Motor_Clock_pin, HIGH);
      delayMicroseconds(Clock_impuls);
      digitalWrite(Motor_Clock_pin, LOW);
      delayMicroseconds(Clock_impuls);
      delay(delayOfMotor);
    }
    Current_position = x_position;
}
