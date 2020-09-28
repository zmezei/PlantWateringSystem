const int switchPin = 8;
const int switchPin_restart = 12;
unsigned long previousTime = 0;
#include <Servo.h>
Servo myServo;

int switchState_restart = 0;
int switchState = 0;
int basicSwitchState = 0;
long interval = 30000;
int cycle_num = 0;
int warning_num = 7;
int max_cycle_num = 10;
void setup() {
  myServo.attach(9);
  myServo.write(90);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  if(cycle_num <= warning_num){
    Serial.print("A 10 öntözési ciklusból eddig lement:\t");
    Serial.println(cycle_num);
  }
  else if(warning_num < cycle_num && cycle_num < max_cycle_num){
    Serial.print("A 10 öntözési ciklusból eddig lement: ");
    Serial.print(cycle_num);
    Serial.print("\t Figyelem! Már csak ");
    Serial.print(max_cycle_num-cycle_num);
    Serial.println(" öntözésre elegendő víz van a tartályban!");
  }

  switchState_restart = digitalRead(switchPin_restart);
  if (switchState_restart != basicSwitchState){
    cycle_num = 0;
  }

  if(cycle_num == max_cycle_num){
    previousTime = currentTime;
    tone(11, 2000, 20);
    delay(10);
    Serial.println("Hoppá! Nincs víz a tartályban!");
  }
    
  if(currentTime - previousTime > interval){
    previousTime = currentTime;
    myServo.write(45);
    delay(5000);
    myServo.write(90);
    cycle_num = cycle_num + 1;
    if (warning_num < cycle_num && cycle_num < max_cycle_num){
      tone(11, 2000, 1000);
      delay(10);
    }
  }
  
  switchState = digitalRead(switchPin);
  if (switchState != basicSwitchState){
    previousTime = currentTime;
    myServo.write(45);
    delay(5000);
    myServo.write(90);
    cycle_num = cycle_num + 1;
    if (warning_num < cycle_num && cycle_num < max_cycle_num){
      tone(11, 2000, 1000);
      delay(10);
    }
  }
}
