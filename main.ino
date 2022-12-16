int sensorPin = A0; // for LDR 
int sensorValue = 0; // for LDR 
int currentGroup = 1; // for LDR 

int redValue = 0; // for RGB LEDs
int blueValue = 0;  // for RGB LEDs
int greenValue = 0; // for RGB LEDs

byte command = 0x00;    // stores the voice command byte       

boolean state1 = false; // first column of LEDs (2 LEDs)
boolean state2 = false; // second column of LEDs (3 LEDs)
boolean state3 = false; // third column of LEDs (4 LEDs)
boolean state4 = false; // fourth column of LEDs (6 LEDs)
boolean patternState = true;  // for RGB pattern
boolean voiceCon = false;  // whether the voice control is activated

void setup() {
  
Serial.begin(9600); 
//define pins
#define REDLED1 13 
#define GREENLED1 12
#define BLUELED1 11
#define REDLED2 10  
#define GREENLED2 9  // doesnt work with analogWrite()
#define BLUELED2 8  // doesnt work with analogWrite()
#define REDLED3 7   // doesnt work with analogWrite()
#define GREENLED3 6  // doesnt work with analogWrite()
#define BLUELED3 5
#define REDLED4 4  
#define GREENLED4 3
#define BLUELED4 2


pinMode(REDLED1, OUTPUT);
pinMode(GREENLED1, OUTPUT);
pinMode(BLUELED1, OUTPUT);
pinMode(REDLED2, OUTPUT);
pinMode(GREENLED2, OUTPUT);
pinMode(BLUELED2, OUTPUT);
pinMode(REDLED3, OUTPUT);
pinMode(GREENLED3, OUTPUT);
pinMode(BLUELED3, OUTPUT);
pinMode(REDLED4, OUTPUT);
pinMode(GREENLED4, OUTPUT);
pinMode(BLUELED4, OUTPUT);

//set them to be off initially
digitalWrite(REDLED1, HIGH);
digitalWrite(GREENLED1, HIGH);
digitalWrite(BLUELED1, HIGH);
digitalWrite(REDLED2, HIGH);
digitalWrite(GREENLED2, HIGH);
digitalWrite(BLUELED2, HIGH);
digitalWrite(REDLED3, HIGH);
digitalWrite(GREENLED3, HIGH);
digitalWrite(BLUELED3, HIGH);
digitalWrite(REDLED4, HIGH);
digitalWrite(GREENLED4, HIGH);
digitalWrite(BLUELED4, HIGH);

Serial.write(0xAA);
Serial.write((byte)0x00);//Waiting mode
delay(100);
Serial.write( 0xAA);
Serial.write((byte)0x37);//Compact mode
delay(100);
Serial.write(0xAA);
Serial.write((byte)0x00);//Waiting mode
delay(100);
Serial.write(0xAA);
Serial.write((byte)0x21);//Import group 1

}

void loop() {
 while(voiceCon==false){
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue > 70 && voiceCon==false){ // LEDs turn all off
    analogWrite(REDLED1, 255);
    analogWrite(GREENLED1, 255);
    analogWrite(BLUELED1, 255);
    analogWrite(REDLED2, 255);
    analogWrite(GREENLED2, 255);
    analogWrite(BLUELED2, 255);
    analogWrite(REDLED3, 255);
    analogWrite(GREENLED3, 255);
    analogWrite(BLUELED3, 255);
    analogWrite(REDLED4, 255);
    analogWrite(GREENLED4, 255);
    analogWrite(BLUELED4, 255);
    state1 = false;
    state2 = false;
    state3 = false;
    state4 = false;
  }
  else if(sensorValue<=50 && voiceCon==false){ //LEDs turn all off all on
    analogWrite(REDLED1, 0);
    analogWrite(GREENLED1, 0);
    analogWrite(BLUELED1, 0);
    analogWrite(REDLED2, 0);
    analogWrite(GREENLED2, 0);
    analogWrite(BLUELED2, 0);
    analogWrite(REDLED3, 0);
    analogWrite(GREENLED3, 0);
    analogWrite(BLUELED3, 0);
    analogWrite(REDLED4, 0);
    analogWrite(GREENLED4, 0);
    analogWrite(BLUELED4, 0); 
    state1 = true;
    state2 = true;
    state3 = true;
    state4 = true;
    voiceCon = true;
  }
 }
  while(Serial.available()&& voiceCon == true){
    command = Serial.read(); 
    if(currentGroup==1){
     switch(command){  
      case 0x11:                // turn On
        command = 0x00; 
        voiceCon = true;
        currentGroup = 1;
        state1 = true;
        state2 = true;
        state3 = true;
        state4 = true;
        redValue = 0;
        greenValue = 0;
        blueValue = 0;
        analogWrite(REDLED1, 0);
        analogWrite(GREENLED1, 0);
        analogWrite(BLUELED1, 0);
        analogWrite(REDLED2, 0);
        analogWrite(GREENLED2, 0);
        analogWrite(BLUELED2, 0);
        analogWrite(REDLED3, 0);
        analogWrite(GREENLED3, 0);
        analogWrite(BLUELED3, 0);
        analogWrite(REDLED4, 0);
        analogWrite(GREENLED4, 0);
        analogWrite(BLUELED4, 0);       
      break;
      case 0x12:                //turn off
        command = 0x00; 
        voiceCon = true;
        currentGroup = 1;
        state1 = false;
        state2 = false;
        state3 = false;
        state4 = false;
        redValue = 255;
        greenValue = 255;
        blueValue = 255;
        analogWrite(REDLED1, 255);
        analogWrite(GREENLED1, 255);
        analogWrite(BLUELED1, 255);
        analogWrite(REDLED2, 255);
        analogWrite(GREENLED2, 255);
        analogWrite(BLUELED2, 255);
        analogWrite(REDLED3, 255);
        analogWrite(GREENLED3, 255);
        analogWrite(BLUELED3, 255);
        analogWrite(REDLED4, 255);
        analogWrite(GREENLED4, 255);
        analogWrite(BLUELED4, 255);      
      break;
      case 0x13:                // brightness up
        voiceCon = true; 
        currentGroup = 1;
        brightness();
        command = 0x00; 
      break;
      case 0x14:                // brightness down
        voiceCon = true;
        currentGroup = 1;
        brightness();
        command = 0x00; 
      break;
      case 0x15:                // change the colour
        voiceCon = true;
        currentGroup++;
        command = 0x00;
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x22); // import group 2
        delay(100);       
      break;
     } 
    }
    else if(currentGroup==2){
     switch(command){  
      case 0x11:                  //  turn red       
        colourChangeG2();
        currentGroup = 1;
        command = 0x00; 
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);     
      break;
      case 0x12:                  // turn green       
        colourChangeG2();
        currentGroup = 1;
        command = 0x00;
        Serial.write(0xAA);  
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);
      break;
      case 0x13:                  // turn blue
        colourChangeG2();
        currentGroup = 1; 
        command = 0x00; 
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);       
      break;
      case 0x14:                  // turn magenta
        colourChangeG2();
        currentGroup = 1;
        command = 0x00; 
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);        
      break;
      case 0x15:                  // more colors
        currentGroup++;
        command = 0x00;
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x23); // import group 3
        delay(100);         
      break;
     } 
    }
    else if(currentGroup==3){
     switch(command){  
      case 0x11:                  // turn orange
        colourChangeG3();
        currentGroup = 1;
        command = 0x00; 
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100); 
      break;
      case 0x12:                  // turn yellow
        colourChangeG3();
        currentGroup = 1;
        command = 0x00;
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);       
      break;
      case 0x13:                  // turn pink
        colourChangeG3();
        currentGroup = 1;
        command = 0x00; 
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);
      break;
      case 0x14:                  // turn cyan
        colourChangeG3();
        currentGroup = 1;
        command = 0x00;
        Serial.write(0xAA);
        Serial.write((byte)0x00); // waiting mode
        delay(100);
        Serial.write(0xAA);
        Serial.write((byte)0x21); // import group 1
        delay(100);   
      break;
      case 0x15:                  // RGB Mode pattern
          pattern();
      break;
     } 
    }
  }      
}
void brightness(){
  if(command==0x13){                   //brightness up
    if (state1==false&&state2==false&&state3==false&&state4==false){
      state1=true;
      analogWrite(REDLED1, redValue);
      analogWrite(GREENLED1, greenValue);
      analogWrite(BLUELED1, blueValue);
    }
    else if (state1==true&&state2==false&&state3==false&&state4==false){
      state2=true;
      analogWrite(REDLED2, redValue);
      analogWrite(GREENLED2, greenValue);
      analogWrite(BLUELED2, blueValue);

    }
    else if (state1==true&&state2==true&&state3==false&&state4==false){
      state3=true;
      analogWrite(REDLED3, redValue);
      analogWrite(GREENLED3, greenValue);
      analogWrite(BLUELED3, blueValue);
    }
    else if (state1==true&&state2==true&&state3==true&&state4==false){
      state4=true;
      analogWrite(REDLED4, redValue);
      analogWrite(GREENLED4, greenValue);
      analogWrite(BLUELED4, blueValue);
    }
    else{
    //do nothing  
    }        
  }
  else if(command==0x14){                 //brightness down
    if (state1==true&&state2==true&&state3==true&&state4==true){
      state4=false;
      analogWrite(REDLED4, 255);
      analogWrite(GREENLED4, 255);
      analogWrite(BLUELED4, 255);
    }
    else if (state1==true&&state2==true&&state3==true&&state4==false){
      state3=false;
      analogWrite(REDLED3, 255);
      analogWrite(GREENLED3, 255);
      analogWrite(BLUELED3, 255);
    }
    else if (state1==true&&state2==true&&state3==false&&state4==false){
      state2=false;
      analogWrite(REDLED2, 255);
      analogWrite(GREENLED2, 255);
      analogWrite(BLUELED2, 255);
    }
    else if (state1==true&&state2==false&&state3==false&&state4==false){
      state1=false;
      analogWrite(REDLED1, 255);
      analogWrite(GREENLED1, 255);
      analogWrite(BLUELED1, 255);
    }
    else{
    //do nothing  
    } 
  }
}

void colourChangeG2(){
  //change the colour of group 2
 if (command==0x11){// turn red
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on 
    redValue = 0;
    blueValue = 255;
    greenValue = 255;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ // all 3 rows on
    redValue = 0;
    blueValue = 255;
    greenValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){ // all 2 rows on 
    redValue = 0;
    blueValue = 255;
    greenValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){ // 1st row on
    redValue = 0;
    blueValue = 255;
    greenValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
  }
  else{
    // do nothing
    redValue = 0;
    blueValue = 255;
    greenValue = 255; 
  }
 }
 else if (command==0x12){ // turn green
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on 
    redValue = 255;
    greenValue = 0;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);   
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ // all 3 rows on 
    redValue = 255;
    greenValue = 0;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){ //all 2 rows on
    redValue = 255;
    greenValue = 0;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){ //1st row on
    redValue = 255;
    greenValue = 0;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);    
  }
  else{
    // do nothing
    redValue = 255;
    greenValue = 0;
    blueValue = 255;
  }
 }  
 else if (command==0x13){ // turn blue
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on
    redValue = 255;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);     
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ // all 3 rows on 
    redValue = 255;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);   
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){ //all 2 rows on
    redValue = 255;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){// 1st row on
    redValue = 255;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);  
  }
  else{
    // do nothing
    redValue = 255;
    greenValue = 255;
    blueValue = 0; 
  }
 }  
 else if (command==0x14){ // turn magenta
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on 
    redValue = 0;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);   
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ //
    redValue = 0;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);      
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){
    redValue = 0;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){
    redValue = 0;
    greenValue = 255;
    blueValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);    
  }
  else{
    redValue = 0;
    greenValue = 255;
    blueValue = 0; 
    // do nothing
  }
 }  
}

void colourChangeG3(){
  //change the colour of group 3
  if (command==0x11){ // turn orange
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on 
    redValue = 0;
    greenValue = 200;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);    
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ // 
    redValue = 0;
    greenValue = 200;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);  
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){
    redValue = 0;
    greenValue = 200;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);     
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){
    redValue = 0;
    greenValue = 200;
    blueValue = 255; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);    
  }
  else{
    // do nothing
    redValue = 0;
    greenValue = 200;
    blueValue = 255; 
  }
 }
 else if (command==0x12){ // turn yellow
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on
    redValue = 0;
    blueValue = 255;
    greenValue = 0;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);    
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ // 
    redValue = 0;
    blueValue = 255;
    greenValue = 0;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);    
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){
    redValue = 0;
    blueValue = 255;
    greenValue = 0;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);  
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){
    redValue = 0;
    blueValue = 255;
    greenValue = 0;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
  }
  else{
    // do nothing
    redValue = 0;
    blueValue = 255;
    greenValue = 0;
  }
 }
 else if (command==0x13){ // turn pink
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on
    redValue = 0;
    greenValue = 200;
    blueValue = 65;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);    
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ // 
    redValue = 0;
    greenValue = 200;
    blueValue = 65;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);    
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){
    redValue = 0;
    greenValue = 200;
    blueValue = 65;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);  
  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){
    redValue = 0;
    greenValue = 200;
    blueValue = 65;
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
  }
  else{
    // do nothing
    redValue = 0;
    greenValue = 200;
    blueValue = 65;
  }
 }
 else if (command==0x14){ // turn cyan
  if(state1==true&&state2==true&&state3==true&&state4==true){ //all on 
    redValue = 255;
    blueValue = 0;
    greenValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
    analogWrite(REDLED4, redValue);
    analogWrite(GREENLED4, greenValue);
    analogWrite(BLUELED4, blueValue);       
  }
  else if(state1==true&&state2==true&&state3==true&&state4==false){ 
    redValue = 255;
    blueValue = 0;
    greenValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);
    analogWrite(REDLED3, redValue);
    analogWrite(GREENLED3, greenValue);
    analogWrite(BLUELED3, blueValue);
  }
  else if(state1==true&&state2==true&&state3==false&&state4==false){
    redValue = 255;
    blueValue = 0;
    greenValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
    analogWrite(REDLED2, redValue);
    analogWrite(GREENLED2, greenValue);
    analogWrite(BLUELED2, blueValue);

  }
  else if(state1==true&&state2==false&&state3==false&&state4==false){
    redValue = 255;
    blueValue = 0;
    greenValue = 0; 
    analogWrite(REDLED1, redValue);
    analogWrite(GREENLED1, greenValue);
    analogWrite(BLUELED1, blueValue);
  }
  else{
    // do nothing
    redValue = 255;
    blueValue = 0;
    greenValue = 0;
  }
 }
}

void pattern(){
  //RGB Mode pattern
  redValue = 0; 
  greenValue = 255;
  blueValue = 255;
  //set the intial colours of the pattern
  analogWrite(REDLED1, redValue);
  analogWrite(GREENLED1, greenValue);
  analogWrite(BLUELED1, blueValue);
  
  analogWrite(REDLED2, redValue);
  analogWrite(GREENLED2, 255);
  analogWrite(BLUELED2, 255);
  
  analogWrite(REDLED3, 255);
  analogWrite(GREENLED3, 255);
  analogWrite(BLUELED3, blueValue);
  
  analogWrite(REDLED4, redValue);
  analogWrite(BLUELED4, blueValue);
  analogWrite(GREENLED4, greenValue);

  patternState = true;
  
  while(patternState && currentGroup==3){
    // perform patterm
      for(int i =0; i <= 254; i++){ // green on
        greenValue--;
        analogWrite(GREENLED1, greenValue);
        analogWrite(GREENLED4, greenValue);
        delay(5);
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if(sensorValue <= 30){ // if value is less than 30 then stop the pattern
          patternState = false;
          //break; 
          }
        }
      for(int i =0; i <= 254; i++){ // red off
        redValue++;
        analogWrite(REDLED1, redValue);
        analogWrite(REDLED2, redValue);
        analogWrite(REDLED4, redValue);
        delay(5);
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if(sensorValue <= 30){
          patternState = false;
         // break; 
          }
        }
      for(int i =0; i <= 254; i++){ // blue on
        blueValue--;
        analogWrite(BLUELED1, blueValue);
        analogWrite(BLUELED3, blueValue);
        analogWrite(BLUELED4, blueValue);
        delay(5);
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if(sensorValue <= 30){
          patternState = false;
         // break; 
          }
        }
      for(int i =0; i <= 254; i++){ // green off
        greenValue++;
        analogWrite(GREENLED1, greenValue);
        analogWrite(GREENLED4, greenValue);
        delay(5);
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if(sensorValue <= 30){
          patternState = false;
        //  break; 
          } 
        }
      for(int i =0; i <= 254; i++){ // red on
        redValue--;
        analogWrite(REDLED1, redValue);
        analogWrite(REDLED2, redValue);
        analogWrite(REDLED4, redValue);
        delay(5);
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if(sensorValue <= 30){
          patternState = false;
         // break; 
          }
        }
      for(int i =0; i <= 254; i++){ // blue off
        blueValue++;
        analogWrite(BLUELED1, blueValue);
        analogWrite(BLUELED3, blueValue);
        analogWrite(BLUELED4, blueValue);
        delay(5);
        sensorValue = analogRead(sensorPin);
        Serial.println(sensorValue);
        if(sensorValue <= 30){
          patternState = false;
         // break; 
          }
        }   
  }
}
