#include <EEPROM.h>
#include <AccelStepper.h>


AccelStepper stepper (1, 3, 4); 
int vitesse=200, vitesse_home=100;
int check_fin_course =0;

int pos=0, mode=-1,duration;
int check_home=1;
int check_temps=0;
int pos_offset;
long temps=0;

const int BUFFER_SIZE = 5;
char data[BUFFER_SIZE];

void setup()
{  
  Serial.begin(9600);
  // Change these to suit your stepper if you want

  stepper.setAcceleration(200);
  

  Serial.setTimeout(100);
pos_offset = EEPROM.read(0);
Serial.print( "home ");
Serial.println(0);

Serial.print( "offset ");
Serial.println(pos_offset);

}

void loop()
{

if (check_home==0){
  go_home();
}


else{
  if (Serial.available() > 0) {


    
    Serial.readBytes(data,BUFFER_SIZE);
   
    pos = (  ((data[1] & 0xFF) << 8) + (data[0] & 0xFF));
    mode = data[2];
    duration =(  ((data[4] & 0xFF) << 8) + (data[3] & 0xFF));
    temps=millis();

Serial.print( "pos ");
Serial.println(pos);

Serial.print( "duration ");
Serial.println(duration);

vitesse= abs(pos-(stepper.currentPosition()-pos_offset))/duration;

switch (mode) {
case 0 :
check_home=0;
Serial.print( "home ");
Serial.println(check_home);
Serial.print( "mode ");
Serial.println(mode);
break;

case 1 :
check_home=0;
Serial.print( "home ");
Serial.println(check_home);
Serial.print( "mode ");
Serial.println(mode);
break;

case 2 :
stepper.moveTo(pos+pos_offset);
stepper.setMaxSpeed(200);
check_temps=0;
break;

case 3 :
pos_offset=stepper.currentPosition();
EEPROM.update(0, pos_offset);
Serial.print( "offset ");
Serial.println(pos_offset);
mode=-1;
break;

case 4 :
stepper.moveTo(pos+pos_offset);
stepper.setMaxSpeed(vitesse);
check_temps=0;
break;

case 5 :
stepper.stop();
break;



}
  }

    if ((check_temps==0)&&(stepper.distanceToGo() == 0)){
      Serial.print("temps ");
      Serial.println(millis()-temps);
      check_temps=1;
    }


stepper.run();

}

}
