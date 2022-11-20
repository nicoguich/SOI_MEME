void go_home(){
     stepper.setSpeed(vitesse_home);
   stepper.setMaxSpeed(100);


  vitesse=100;
  int capteur =  analogRead(A0);
  pos = stepper.currentPosition();

//Serial.println(pos);
  //Serial.println(capteur);

  if (capteur < 820){
    stepper.runSpeed();
    if (abs(pos)> 800){
      vitesse_home=vitesse_home*-1;
 
    }
    
  
  }
  else{
    check_home=1;
    pos=0;
    stepper.setCurrentPosition(0);
Serial.print( "home ");
Serial.println(1);
  }

  
}
