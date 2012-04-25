// Arduino Components
const int WIN_LED = 13;
const int LED1 = 12;
const int LED2 = 11;
const int LED3 = 10;
const int BUTTON1 = 7;
const int BUTTON2 = 6;
const int BUTTON3 = 5;
const int PIEZO = A0;
const int MOTOR = 4;

// extra information
const int MOLE_UP = 1;
const int MOLE_DOWN = -1;

int count = 0;
int blinker = 0;
long ran = 100;
long ran_seed;

// Mole class
class Mole{
  public:
    int state;
    int lifespan;
    int ledPin;
    int buttonPin;
    
    Mole(int state, int ledPin, int buttonPin){
      this->state = state;
      this->lifespan = 0;
      this->ledPin = ledPin;
      this->buttonPin = buttonPin;
    }
    void showInfo(){
      Serial.println(this->state);
      Serial.println(this->ledPin);
      Serial.println(this->buttonPin);
    }
    void check(){
      //this->showInfo();
      if(this->state == MOLE_DOWN){
        ran = random(100000);
        if(ran < 5){
          this->state = MOLE_UP;
          this->lifespan = 10000;
          digitalWrite(this->ledPin, HIGH);
        }
      }else{
        if(digitalRead(this->buttonPin) == HIGH){
          count++;
          this->showInfo();
          this->state = MOLE_DOWN;
          digitalWrite(MOTOR, HIGH);
          delay(100);
          digitalWrite(this->ledPin, LOW);
          ran_seed = analogRead(PIEZO);
          randomSeed(ran_seed);
          delay(10);
          digitalWrite(MOTOR, LOW);
        }else{
          lifespan--;
          if(lifespan <= 0){
            this->state = MOLE_DOWN;
            digitalWrite(this->ledPin, LOW);
          }
        }
      }  
    }
};// end Mole class

// set up moles
Mole mole1(MOLE_DOWN, LED1, BUTTON1);
Mole mole2(MOLE_DOWN, LED2, BUTTON2);
Mole mole3(MOLE_DOWN, LED3, BUTTON3);

void setup(){
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
  pinMode(PIEZO, INPUT);
  pinMode(WIN_LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT); 
  pinMode(BUTTON3, INPUT);
}

void loop(){
  mole1.check();
  mole2.check(); 
  mole3.check();
  // Player has finished
  while(count >= 20){
    digitalWrite(WIN_LED, HIGH);
  }
}
