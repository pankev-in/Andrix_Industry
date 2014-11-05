#define Maximum_steps 32250	          //Maximum steps
#define Axis_length 4950			        //Maximum Length
#define Touch_sensor_pin 7            //Touch Sensor(init) pin
#define Clock_pin	9                   //Clock(Tacks) CLK+ pin
#define Direction_pin	8               //Direction CW+ pin
#define Clock_impuls 100 			        //Microsecond

int Current_position = 0;			        //Milimeter
float Step_resolution = 0.15349;      //Stepmotor step-resolution in mm
String inputString = "";              // a string to hold incoming data
boolean stringComplete = false;       // whether the string is complete
int delayOfMotor = 0 ;
boolean motor_enable;

void setup() {
  Serial.begin(9600);
  Serial.println("########################################");
  Serial.println("Stepper Motor controller v1.0");
  Serial.println("\tAuthor: Kevin Pan - PRIA");
  Serial.println("\tLast change: 28.10.2014");
  Serial.println("\tContact: kpan@student.tgm.ac.at");
  Serial.println("########################################");
  Serial.println("SYSTEM: Initializing ...");
  _init();
  Serial.println("SYSTEM: Initialization done.");
  Serial.println("SYSTEM: Ready & waiting for commands ...");
}

void loop() {
  if (stringComplete) {
    String command=inputString.substring(0,3);
    Serial.print("Input Command:\t");Serial.println(command);
    if(command=="ENA"){
      Serial.println("motor enabled");
      motor_enable=true;
    }
    else if(command=="DIS"){
      Serial.println("motor disabled");
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

void _init(){                   //Initailizing Pin setups
    inputString.reserve(32);
    motor_enable=true;
    pinMode(Direction_pin, OUTPUT);
    pinMode(Clock_pin, OUTPUT);
    pinMode(Touch_sensor_pin,INPUT);
    digitalWrite(Direction_pin, LOW);
    digitalWrite(Clock_pin, LOW);
    reset();
    motor_enable=false;
}

void reset(){                   //RESET THE POSITION BACK TO 0 USING SENSOR
  if(motor_enable==true){
    digitalWrite(Direction_pin, HIGH);
    while(!digitalRead(Touch_sensor_pin)){
      digitalWrite(Clock_pin, HIGH);
      delayMicroseconds(Clock_impuls);
      digitalWrite(Clock_pin, LOW);
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
      digitalWrite(Direction_pin, LOW);
    }
    else if(diff<0){
      digitalWrite(Direction_pin, HIGH);
      diff=-diff;
    }
    else {
      return;
    }

    //If the position is going back to zero:(will be repalced with a digital button)
    if(x_position==0){
      int k = (int)(Current_position/Step_resolution);
      for(int i=1;i<=k; i++){
        digitalWrite(Clock_pin, HIGH);
        delayMicroseconds(Clock_impuls);
        digitalWrite(Clock_pin, LOW);
        delayMicroseconds(Clock_impuls);
        delay(delayOfMotor);
      }
      Current_position =0;
      return;
    }

    int steps = (int)(diff/Step_resolution);
    for(int i=1;i<=steps; i++){
      digitalWrite(Clock_pin, HIGH);
      delayMicroseconds(Clock_impuls);
      digitalWrite(Clock_pin, LOW);
      delayMicroseconds(Clock_impuls);
      delay(delayOfMotor);
    }
    Current_position = x_position;
}
