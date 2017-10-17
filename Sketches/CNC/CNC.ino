int motorPins[3][4] = {{2, 3, 4, 5},{6, 7, 8, 9},{10, 11, 12, 13}};
int count;
int count2[3] = {0,0,0};
int delayTime;
int val = 0;
int rot=0;
int incomingByte = 0;
int sign=1;
int v = 0;

//Процедура настройки прошивки
void setup() {
 int i;
 Serial.begin(115200);
 Serial.println("128(25%)");
 pinMode(6, OUTPUT); //установка режима работы цифровых pin'ов Ардуино

 for (i=0; i<3; i++) {
  for (count = 0; count < 4; count++) {
   pinMode(motorPins[i][count], OUTPUT); //установка режима работы цифровых pin'ов Ардуино
  }
 }
 delayTime=3; //задержка между шагами 3 мс (2 мс - время реакции ШД на подачу напряжения)
}

//Поворот двигателя с номерм sm на один шаг вперёд
void moveForward(int sm) {
 if ((count2[sm] == 0) || (count2[sm] == 1)) {
  count2[sm] = 16;
 }
 count2[sm]>>=1;
 for (count = 3; count >= 0; count--) {
  digitalWrite(motorPins[sm][count], count2[sm]>>count&0x01);
 }
}

//Поворот двигателя с номерм sm на один шаг назад
void moveBackward(int sm) {
 if ((count2[sm] == 0) || (count2[sm] == 1)) {
  count2[sm] = 16;
 }
 count2[sm]>>=1;
 for (count = 3; count >= 0; count--) {
  digitalWrite(motorPins[sm][3 - count], count2[sm]>>count&0x01);
 }
}

//Одновременный поворот двигателей 0, 1, 2 на x, y, z шагов соответственно
void MoveSM(long x, long y, long z) {
  long c[3], c2[3];
  double c1[3], d[3];
  long m, i;
  boolean flg;
  
  c[0] = x;
  c[1] = y;
  c[2] = z;
  
  m = 1;
  for (i=0; i<3; i++) {
    if (m < abs(c[i])) m = abs(c[i]);
  }
  
  for (i=0; i<3; i++) {
    c1[i] = 0;
    d[i] = 1.0 * c[i] / m;
    c2[i] = 0;
  }

  flg = false;
  for (i=0; i<3; i++) {
    if (abs(c1[i]) < abs(c[i])) flg=true;
  }
  while (flg) {
    flg=false;
    for (i=0; i<3; i++) {
      if (abs(c1[i]) < abs(c[i]))
       c1[i] += d[i];
      if (abs(c1[i]) - abs(c2[i]) >= 0.5) {
       if (c[i]>0) {
        c2[i]++;
        moveForward(i);
       } else if (c[i]<0) {
        c2[i]--;
        moveBackward(i);
       }
      }
      if (abs(c1[i]) < abs(c[i])) flg=true;
    }
    delay(delayTime);
  }
}

//Основной цикл
void loop() {
// if (Serial.available() > 0) { //Пришла команда
//  long c[4]={0,0,0,0};
//  int i;
//  sign=1;
//  i=0;
//  incomingByte = Serial.read();
//  while (incomingByte!=';') { //Читаем входящую строку, признак конца строки знак "точка с запятой"
//   if (c[i]==0) {
//    if (incomingByte=='-')
//     sign=-1;
//   }
//   if (incomingByte==',') {
//    c[i]*=sign;
//    sign=1;
//    i++;
//   } else if (incomingByte>='0' && incomingByte<='9') {
//    c[i]=c[i]*10+incomingByte-'0';
//   }
//   while (Serial.available() == 0) {
//    delay(2);
//   }
//   incomingByte = Serial.read();
//  }
//  c[i]*=sign;
//  MoveSM(c[0],c[1],c[2]); //Вращаем двигатели на заданное число шагов
//  Serial.println("OK");  //Отправляем компьютеру сообщение "OK", значит можно высылать новую команду
// }
// else
// {
//  if(v)
//  {
//    v = 0;
//    digitalWrite(6, HIGH);
//  }
//  else
//  {    
//    v = 1;
//    digitalWrite(6, LOW);
//  }
//  Serial.println("gg");
//  delay(100); //Если ничего не пришло, ждём 1/10 секуды.
// }
    if(v)
  {
    v = 0;
    digitalWrite(6, HIGH);
  }
  else
  {    
    v = 1;
    digitalWrite(6, LOW);
  }
  Serial.print("gg");
  delay(1000); //Если ничего не пришло, ждём 1/10 секуды
}
 


