unsigned long lasTime = 0, sampleTime = 0;
double lastinput = 0;

float t = 0.0, error = 0.0, alfa = 0.0, k =0.0, Ki = 0, Ite = 0;
double lastsensorValue = 0.0, lastsensorValue2 = 0.0;

float Pt = 0.0,Dt = 0.0,It = 0.0;

float outMax = 0.0, outMin = 0.0;
float u = 0.0;

const byte In1 = 6;
const byte In2 = 7;
const byte Ena = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode (A0,INPUT);
  pinMode (A1,INPUT);
  pinMode (In1,OUTPUT);
  pinMode (In2,OUTPUT);
  pinMode (Ena,OUTPUT);
  
  sampleTime = 100;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis()- lasTime >= sampleTime){
    lasTime=millis();
    alfa = 0.7;
        
    int sensorValue = analogRead(A0);
    sensorValue = map(sensorValue, 0, 1023, -180, 180 );
    sensorValue = alfa*(sensorValue)+(1-alfa)*lastsensorValue;

    int sensorValue2 = analogRead(A1);
    sensorValue2 = map(sensorValue2, 0, 1023, -180, 180 );
    sensorValue2 = alfa*(sensorValue2)+(1-alfa)*lastsensorValue2;

    Serial.print("sensorValue: ");Serial.print(sensorValue);Serial.print(",");
    Serial.print("sensorValue2: ");Serial.print(sensorValue2);Serial.print(",");
    Serial.println();

    k = 2.0; //ganancia
    Ki = 0.5;
    error = sensorValue-sensorValue2;
    Pt = error;
    Ite += error*sampleTime;
    outMax = 255;
    outMin = -255;
    if (Ite>outMax)Ite = outMax;else if(Ite<outMin)Ite = outMin;
    
    u = k*Pt+Ki*Ite;
 

  if (u >0)
  {
    digitalWrite(In1,LOW);
    digitalWrite(In2,HIGH);
    
  }
  else
  {
    digitalWrite (In2,LOW);
    digitalWrite (In1,HIGH);
  }
  int PWM = abs (u);
  analogWrite (Ena,PWM);

  lastinput = sensorValue;
  lastsensorValue = sensorValue;
  lastsensorValue2 = sensorValue2;
  }
}
