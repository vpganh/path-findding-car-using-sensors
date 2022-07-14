#define enA 5 
#define inA1 6 //Định nghĩa chân in1 của động cơ A
#define inA2 7 //Định nghĩa chân in2 của động cơ A
#define inB1 9 //Định nghĩa chân in1 của động cơ B
#define inB2 8 //Định nghĩa chân in2 của động cơ B
#define enB 10



#define out1 4 //chan output hong ngoai

#define out2 13


int pre=1;
int go=1;
int wait=1;
int waitForTurn=5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(inA1, OUTPUT);//Set chân in1 của dc A là output
  pinMode(inA2, OUTPUT);//Set chân in2 của dc A là output
  pinMode(inB1, OUTPUT);//Set chân in1 của dc B là output
  pinMode(inB2, OUTPUT);//Set chân in2 của dc B là output
  pinMode(enB, OUTPUT);
  pinMode(out1, INPUT_PULLUP);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(out2,INPUT_PULLUP);
  digitalWrite(12,LOW);
  digitalWrite(11,HIGH); 
  //delay(5000);
  robotMover ( inA1, inA2, inB1, inB2, 1);
}

void loop() {

/*  analogWrite(enB, 255); 
  analogWrite(enA, 255);
  robotMover ( inA1, inA2, inB1, inB2, 1);
  delay(2000);
  analogWrite(enB, 10); 
  analogWrite(enA, 10);
  delay(2000);*/
  pathFinding();
}

void pathFinding()
{
  if((digitalRead(out1) == 1) && digitalRead(out2) == 1)
  {
    switch(pre)
    {
      case 1:
        robotMover ( inA1, inA2, inB1, inB2, 1);
        pre=1;
        delay(go);
        robotMover ( inA1, inA2, inB1, inB2, 0);
        delay(wait);
        break;
      case 5:
        robotMover ( inA1, inA2, inB1, inB2, 6);
        pre=6;
        delay(go);
        robotMover ( inA1, inA2, inB1, inB2, 0);
        delay(wait);
        break;
      case 6:
        robotMover ( inA1, inA2, inB1, inB2, 5);
        pre=5;
        delay(go);
        robotMover ( inA1, inA2, inB1, inB2, 0);
        delay(wait);
        break; 
    }
    
    
    
  }
  if((digitalRead(out1) == 1) && digitalRead(out2) == 0) //đen phải
  {
    robotMover ( inA1, inA2, inB1, inB2, 6);
    delay(go);
    pre=6;
    robotMover ( inA1, inA2, inB1, inB2, 0);
    delay(wait);
  }
  if((digitalRead(out1) == 0) && digitalRead(out2) == 1)//đen trái
  {
    robotMover( inA1, inA2, inB1, inB2, 5);
    pre=5;
    delay(go);
    robotMover ( inA1, inA2, inB1, inB2, 0);
    delay(wait);
  }
  if((digitalRead(out1) == 0) && digitalRead(out2) == 0)
  {
    robotMover( inA1, inA2, inB1, inB2, 6);
    pre=5;
    delay(go);
    robotMover ( inA1, inA2, inB1, inB2, 0);
    delay(waitForTurn);
  }
  
    
}

void motorControlNoSpeed (byte in1, byte in2, byte direct)
{
  // in1 and in2 are 2 signal pins to control the motor
  // en is the enable pin
  // the defauspeed is the highest
  // direct includes:
  //    0:Stop
  //    1:Move on 1 direct
  //    2:Move on another direct
  switch (direct)
  {
    case 0:// Dừng không quay
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      break;
    case 1:// Quay chiều thứ 1
    for(int i=150;i<=255;i++){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enB, i); 
      analogWrite(enA, i);
      
    }
      break;
    case 2:// Quay chiều thứ 2
    for(int i=255;i>=0;i--){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enB, i); 
      analogWrite(enA, i); 
    }
      break;
      //default:
  }
}

void goStop(){
      digitalWrite(inA1, HIGH);
      digitalWrite(inA2, LOW);
      digitalWrite(inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enB, 0); 
      analogWrite(enA, 0);  
}

void goStraight(){
    for(int i=70;i<=255;i++){
      digitalWrite(inA1, HIGH);
      digitalWrite(inA2, LOW);
      digitalWrite(inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enB, i); 
      analogWrite(enA, i);  
      delay(100);
    }
    
}
void goLeft(){
      digitalWrite(inA1, HIGH);
      digitalWrite(inA2, LOW);
      digitalWrite(inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enB, 192); 
      analogWrite(enA, 256); 
  
}

void robotMover (byte inR1, byte inR2, byte inL1, byte inL2, byte action)
{
  /*
  inR1 inR2 là 2 chân tín hiệu động cơ bên phải
  inL1 inL2 là 2 chân tín hiệu động cơ bên trái
  action= 0 đứng yên
  action =1 đi thẳng
  action =2 lùi lại
  action =3 quay trái
  action =4 quay phải
  action =5 rẽ trái
  action =6 rẽ phải

  */
  switch (action)
  {
    case 0:// không di chuyển
      motorControlNoSpeed(inR1, inR2, 0);
      motorControlNoSpeed(inL1, inL2, 0);
      break;
    case 1://đi thẳng
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    case 2:// lùi lại
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    case 3:// quay trái
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    case 4:// quay phải
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    case 5:// rẽ trái
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 0);
      break;
    case 6:// rẽ phải
      motorControlNoSpeed(inR1, inR2, 0);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    default:
      action = 0;
      
  }
}
