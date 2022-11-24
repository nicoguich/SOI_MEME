void go_home(){


  stepper.setMaxSpeed(vitesse_home);
stepper.setSpeed(vitesse_home);
  int capteur =  analogRead(A0);
  pos = stepper.currentPosition();

Serial.print("capteur ");
  Serial.println(capteur);

  if (capteur > limit_capteur){
    stepper.runSpeed();
    if (abs(pos)>= limit_init){
      vitesse_home=vitesse_home*-1;
      if (limit_init<=600){
      limit_init+=100;}
      mode=-1;
 
    }
    
  
  }
  else{
    delay(2000);
    check_home=1;
    pos=0;
    limit_init=100;
    stepper.setCurrentPosition(0);
    stepper.moveTo(pos_offset);
    Serial.print( "offset ");
Serial.println(pos_offset);
stepper.setMaxSpeed(100);
check_temps=0;
Serial.print( "home ");
Serial.println(check_home);
  }

  
}
