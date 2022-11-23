void go_home(){

  if (mode==0){
     vitesse_home=100;}
  else if (mode==1){
    
    vitesse_home=-100;
  }
  stepper.setMaxSpeed(vitesse_home);
stepper.setSpeed(vitesse_home);
  int capteur =  analogRead(A0);
  pos = stepper.currentPosition();

Serial.print("capteur ");
  Serial.println(capteur);
Serial.print("pos ");
  Serial.println(pos);
  if (capteur > limit_capteur){
    stepper.runSpeed();
    if (abs(pos)> 800){
      vitesse_home=vitesse_home*-1;
      if (mode==0){
      stepper.setCurrentPosition(799);
      pos=799;}
    else{
            stepper.setCurrentPosition(-799);
      pos=-799;
    }
      mode=-1;
 
    }
    
  
  }
  else{
    check_home=1;
    pos=0;
    stepper.setCurrentPosition(0);
Serial.print( "home ");
Serial.println(check_home);
  }

  
}
