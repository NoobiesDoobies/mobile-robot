#define MOTOR_L_1 26
#define MOTOR_L_2 25
#define MOTOR_R_1 32
#define MOTOR_R_2 33


const int freq = 5000;
const int resolution = 8;
float pwmL = 0.0;
float pwmR = 0.0;

void motorSetup(){
  pinMode(MOTOR_L_1, OUTPUT);
  pinMode(MOTOR_L_2, OUTPUT);
  pinMode(MOTOR_R_1, OUTPUT);
  pinMode(MOTOR_R_2, OUTPUT);

  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcSetup(3, freq, resolution);


  ledcAttachPin(MOTOR_L_1, 0);
  ledcAttachPin(MOTOR_L_2, 1);
  ledcAttachPin(MOTOR_R_1, 2);
  ledcAttachPin(MOTOR_R_2, 3);
}

void runMotor(bool isLeft, float pwm){
  Serial.print(isLeft);

  if(isLeft){
    if(pwm == 0){
      digitalWrite(MOTOR_L_1, LOW);
      digitalWrite(MOTOR_L_2, LOW);
  Serial.println("\t" + String(pwm));

    }
    else if(pwm > 0){
      ledcWrite(0, pwm*255);
      digitalWrite(MOTOR_L_2, LOW);
    }
    else{
      ledcWrite(1, -pwm*255);
      digitalWrite(MOTOR_L_1, LOW);
    }
  }
  else{
    if(pwm == 0){
      digitalWrite(MOTOR_R_1, LOW);
      digitalWrite(MOTOR_R_2, LOW);
  Serial.println("\t" + String(pwm));

    }
    else if(pwm > 0){
      ledcWrite(2, pwm*255);
      digitalWrite(MOTOR_R_2, LOW);
    }
    else{
      ledcWrite(3, -pwm*255);
      digitalWrite(MOTOR_R_1, LOW);
    }
  }
  // Serial.println("\t" + String(pwm));
}