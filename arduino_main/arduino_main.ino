#include <EEPROM.h>
#include <AccelStepper.h>


AccelStepper stepper (1, 3, 4); 
int vitesse=200, vitesse_home=100;
int check_fin_course =0;
int limit_capteur=260;

int pos=0, mode=-1;
int duration;
int check_home=0;
int check_temps=0;
int pos_offset;
long temps=0;
int limit_init=100;

const int BUFFER_SIZE = 5;
char data[BUFFER_SIZE];

void setup()
{  
  Serial.begin(9600);
  // Change these to suit your stepper if you want

  stepper.setAcceleration(50);
  

  Serial.setTimeout(100);


pinMode(6,OUTPUT);

  
  byte byte1 = EEPROM.read(0);
  byte byte2 = EEPROM.read(1);
  pos_offset =int( (byte1 << 8) + byte2);
Serial.print( "home ");
Serial.println(0);

stepper.setMaxSpeed(vitesse_home);
stepper.moveTo(limit_init);

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
    duration =float((  ((data[4] & 0xFF) << 8) + (data[3] & 0xFF)));
    temps=millis();

Serial.print( "pos ");
Serial.println(pos);
Serial.print( "mode ");
Serial.println(mode);

Serial.print( "duration ");
Serial.println(duration);

vitesse= (abs(pos-(stepper.currentPosition()-pos_offset))/duration)*100;
Serial.print( "vitesse ");
Serial.println(vitesse);

switch (mode) {

case 1 :
check_home=0;
Serial.print( "home ");
Serial.println(check_home);
Serial.print( "mode ");
Serial.println(mode);
stepper.setCurrentPosition(0);
stepper.setAcceleration(50);
stepper.setMaxSpeed(vitesse_home);
stepper.moveTo(limit_init);
break;

case 2 :
stepper.moveTo(pos+pos_offset);
stepper.setMaxSpeed(200);
check_temps=0;
break;

case 3 :
pos_offset=stepper.currentPosition();

  EEPROM.write(0, byte(pos_offset >> 8));
  delay(200);
  EEPROM.write( 1, byte(pos_offset & 0xFF));
delay(200);
Serial.print( "offset ");
Serial.println(pos_offset);

break;

case 4 :
stepper.moveTo(pos+pos_offset);
stepper.setMaxSpeed(vitesse);
check_temps=0;
Serial.print("receive ");
Serial.println(1);
break;

case 5 :
stepper.stop();
break;


case 6 :
  stepper.setAcceleration(pos);
break;

case 7 :
  analogWrite(6,pos);
  Serial.print("led ");
  Serial.println(pos);
break;


}
  }

    if ((check_temps==0)&&(stepper.distanceToGo() == 0)){
Serial.print( "offset ");
Serial.println(pos_offset);

Serial.print( "pos ");
Serial.println(pos);

Serial.print( "duration ");
Serial.println(duration);
      check_temps=1;
    }

}


stepper.run();



}
