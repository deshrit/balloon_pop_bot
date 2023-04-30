#define right1 2                
#define rightEnb 3            // right motor driving pins 
#define right2 4

#define left1 5                 
#define leftEnb 6             // left motor driving pin
#define left2 7             

#define weapon1 8             
#define weapon2 9              // weapon motor driving pin
#define weaponEnb 10        

#define input1 11          
#define input2 12                // output from the receiver of the transmitter
#define input3 13

#define deadzone 20


int dur1, dur2, dur3, var1, var2; 


void setup()
{
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(rightEnb, OUTPUT);
  
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(leftEnb, OUTPUT);

  pinMode(weapon1, OUTPUT);
  pinMode(weapon2, OUTPUT);
  pinMode(weaponEnb, OUTPUT);

  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
  
}

void loop()
{
  dur3 = pulseIn(input3, HIGH, 25000);
  dur2 = pulseIn(input2, HIGH, 25000);        
  dur1 = pulseIn(input1, HIGH, 25000);

  dur3 = weaponPWM(dur3);
  dur2 = pulseToPWM(dur2);
  dur1 = pulseToPWM(dur1);

  

  var1 = dur2 + dur1;
  var2 = dur2 - dur1;

  
  drive(var1, var2);

  weaponDrive(dur3);
}


// PPM LAI PWM MA LANE FUNCTION

int pulseToPWM(int pulse)
{
  if(pulse > 1000) {
    pulse = map(pulse, 1000, 2000, -300, 300);
    pulse = constrain(pulse, -255, 255);
    if(abs(pulse) <= 20) {
      pulse = 0;
    }
  }
  else {
    pulse = 0;
  }


  return pulse;
  
}


// WEAPON KO PPM LAI PWM MA LANE FUNCTION

int weaponPWM(int weaponPulse)
{
  if(weaponPulse > 1000) {
    weaponPulse = map(weaponPulse, 1000, 2000, 0, 255);
  }
  else {
    weaponPulse = 0;
  }

  return weaponPulse;
}


// MAIN DRIVING FUNCTION

void drive(int speedLeft, int speedRight)
{
  speedRight = constrain(speedRight, -255, 255);
  speedLeft = constrain(speedLeft, -255, 255);
  
   // LEFT MOTOR KO DRIVING SETUP
    
   if(speedRight == 0) {
    digitalWrite(right1, LOW);
    digitalWrite(right2, LOW);
   }
   else if(speedRight > 0) {
    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);
   }
   else{
    digitalWrite(right1, HIGH);
    digitalWrite(right2, LOW);
   }

   // RIGHT MOTOR KO SETUP
  
   if(speedLeft == 0) {
    digitalWrite(left1, LOW);
    digitalWrite(left2, LOW);
   } else if(speedLeft > 0) {
    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);
   } else {
    digitalWrite(left1, HIGH);
    digitalWrite(left2, LOW);
   }

   // MOTOR KO SPEED

   analogWrite(rightEnb, abs(speedRight));
   analogWrite(leftEnb, abs(speedLeft));
}



// WEAPON DRIVING FUNTION

void weaponDrive(int weaponSpeed)
{ 
  digitalWrite(weapon1, HIGH);
  digitalWrite(weapon2, LOW);
  analogWrite(weaponEnb, weaponSpeed);
}
