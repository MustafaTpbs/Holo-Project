#include <SoftwareSerial.h>
#define capteur A0
SoftwareSerial hc06(8, 6);

String cmd="";
bool zero=1;
int ordre,i;
int data [2];
double LEDs[2][3]={2,0,0,4,0,0};

void setup_pos(){
  while(zero!=0){
    if(digitalRead(capteur)==0){
      zero=0;
    }
  }
}

void setup_led_pos(int x, int y){
  LEDs[0][1]=x;
  LEDs[0][2]=4100*LEDs[0][1]/360;

  LEDs[0][2]+=2050;
  if(LEDs[0][2]>4100)
  {
    LEDs[0][2]-=4100;
  }
  LEDs[1][1]=y;
  LEDs[1][2]=4100*LEDs[1][1]/360;


  if(LEDs[0][2]<LEDs[1][2]){
    ordre=0;
  }
  else if (LEDs[0][2]==LEDs[1][2]){
    ordre=1;
  }
  else{
    ordre=2;
  }
}

void get_bt_data(){
  while(data[1]==-1)
  {
    i=0;
  while(hc06.available()>0){
    cmd=hc06.readStringUntil(',');
    if(cmd!=""){
      data[i]=cmd.toInt();
    }
    cmd="";
    
  Serial.println(data[i]);
    i++;
  }
  }

  
}


void setup() {
  
  
  data[1]=-1;

  pinMode(LEDs[0][0],OUTPUT);
  pinMode(LEDs[1][0],OUTPUT);
  pinMode(capteur,INPUT);

  digitalWrite(2, 0);
  digitalWrite(4, 0);

  Serial.begin(115200);
  hc06.begin(115200);
  //setup angles allumage
  
  get_bt_data();
  setup_led_pos(data[0],data[1]);
  setup_pos();
}

void loop() {
 
    if(ordre==0){
      //LED 1
      delay(LEDs[0][2]);
      digitalWrite(LEDs[0][0],HIGH);
      delay(10);
      digitalWrite(LEDs[0][0],LOW);

      //LED2
      delay(LEDs[1][2]-LEDs[0][2]);
      digitalWrite(LEDs[1][0],HIGH);
      delay(10);
      digitalWrite(LEDs[1][0],LOW);
      
      delay(4100-LEDs[1][2]);
    }

    if(ordre==1){
      //LEDs 1 et 2
      delay(LEDs[0][2]);
      digitalWrite(LEDs[0][0],HIGH);
      digitalWrite(LEDs[1][0],HIGH);
      delay(10);
      digitalWrite(LEDs[0][0],LOW);
      digitalWrite(LEDs[1][0],LOW);

      delay(4100-LEDs[0][2]);
    }
    if(ordre==2){
      //LED 1
      delay(LEDs[1][2]);
      digitalWrite(LEDs[1][0],HIGH);
      delay(10);
      digitalWrite(LEDs[1][0],LOW);

      //LED2
      delay(LEDs[0][2]-LEDs[1][2]);
      digitalWrite(LEDs[0][0],HIGH);
      delay(10);
      digitalWrite(LEDs[0][0],LOW);
      
      delay(4100-LEDs[0][2]);
    }
  
}