void go_home(){


  int capteur =  analogRead(A0);
  pos = stepper.currentPosition();

Serial.print("capteur ");
  Serial.println(capteur);

if (capteur > limit_capteur){
if(stepper.distanceToGo() == 0){
if ((limit_init>0)and(limit_init<600)){
  limit_init+=100;
 
}
if ((limit_init<0)and(limit_init>-600)){
  limit_init-=100;
 
}

limit_init=limit_init*-1;
 
stepper.moveTo(limit_init);
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
check_temps=0;
Serial.print( "home ");
Serial.println(check_home);
  }

  
}
