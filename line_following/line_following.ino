#define S1 PA0
#define S2 PA1
#define S3 PA2
#define S4 PA3
#define S5 PA4
#define S6 PA5
#define S7 PA6
#define S8 PA7

#define BUTTON PB10

#define PWMA PA8
#define AIN1 PA15
#define AIN2 PA12
#define STBY PB3
#define BIN2 PB5
#define BIN1 PB4
#define PWMB PA11

const int sensorNumber = 8;
int sensorADC[sensorNumber];
int threshold = 240;   
int sumSensor;
int sumWeight;
int weightValue[sensorNumber] = {10, 20, 30, 40, 50, 60, 70, 80};

float currPos;
float cenPos = 45;   // trung tâm
float ePrev = 0;
float eCurr;  
float u;
float dE;
float eSum = 0;

int maxSpeed = 255;   // tốc độ tối đa
int minSpeed = 220;   // tốc độ tối thiểu
float Kp = 10;
float Kd = 1.5;
float Ki = 0.009;
float kReduce = 2.7;   // hệ số giảm tốc khi sai số lớn
int xuly=0;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON, INPUT_PULLUP);


  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(STBY, LOW); // bật driver
  digitalWrite(BUTTON, HIGH);
}

void motor(int LPWM, int RPWM) {
  LPWM = constrain(LPWM, -255, 255);
  RPWM = constrain(RPWM, -255, 255);

  if (LPWM >= 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  } else {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }

  if (RPWM >= 0) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }

  analogWrite(PWMA, abs(LPWM));
  analogWrite(PWMB, abs(RPWM));
}

void read_black_line() {
  sumSensor = 0;
  sumWeight = 0;

  for (int i = 0; i < sensorNumber; i++) {
    sensorADC[i] = analogRead(S1 + i);
    int val = (sensorADC[i] < threshold) ? 1 : 0;
    sumSensor += val;
    sumWeight += val * weightValue[i];
  }
}

void PID_control() {
 
  if (sumSensor > 0) {
    currPos = (float)sumWeight / sumSensor;
    eCurr = cenPos - currPos;

    dE = eCurr - ePrev;
    eSum += eCurr;

    u = Kp * eCurr + Kd * dE + Ki * eSum;

    // Dynamic speed control
    int dynamicSpeed = maxSpeed - kReduce * abs(eCurr);
    dynamicSpeed = constrain(dynamicSpeed, minSpeed, maxSpeed);

    int leftSpeed  = dynamicSpeed - u;
    int rightSpeed = dynamicSpeed + u;

    motor(leftSpeed, rightSpeed);

    ePrev = eCurr;
  }
}

void loop() {
 if(xuly==0)
 {
  int but=digitalRead(BUTTON);
  if(but==0){
    delay(1000);
    digitalWrite(STBY,HIGH);
    xuly++;
    motor(200,200);
    delay(400);
  }
 }
  read_black_line();
  PID_control();
  delay(1);  
}