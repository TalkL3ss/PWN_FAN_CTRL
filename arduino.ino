/*
Connection Schema:
12DCV Power Supply to the fan
GND to BradBoard 0 line (all the GND should be togetter also the GND of the arduino)
PIN9 -> PWM Control -> Control on the load of the fan
Arduino 5DCV -> ESP8266 VIN pin
RX + TX -> TX + RX = (RX To Tx and TX to RX)
Remember that the Serial port can handle only one connection
*/
const byte OC1A_PIN = 9;
const byte OC1B_PIN = 10;

const word  PWM_FREQ_HZ = 25000; //Adjust this value to adjust the frequency (Frequency in HZ!)  (Set currently to 25kHZ)
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);
const unsigned int MAX_MESSAGE_LENGTH = 4;

void  setup() {
  Serial.begin(115200);
  pinMode(OC1A_PIN, OUTPUT);
  //pinMode(ctrlPin,INPUT);
  // Clear Timer1 control  and count registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  //  Set Timer1 configuration
  // COM1A(1:0) = 0b10   (Output A clear rising/set  falling)
  // COM1B(1:0) = 0b00   (Output B normal operation)
  // WGM(13:10)  = 0b1010 (Phase correct PWM)
  // ICNC1      = 0b0    (Input capture noise canceler  disabled)
  // ICES1      = 0b0    (Input capture edge select disabled)
  //  CS(12:10)  = 0b001  (Input clock select = clock/1)
  
  TCCR1A |= (1 << COM1A1)  | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << CS10);
  ICR1 = TCNT1_TOP;
}

void  loop() {
while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';

     //Print the message (or do other things)
     if (isValidNumber(message)) {
      int Val = String(message).toInt();
      if (Val >=0 && Val <= 100) {
        Serial.println(message);
        setPwmDuty(Val);
      }
     }
     //Reset for the next message
     message_pos = 0;
   }
 }

    /*setPwmDuty(0);
    Serial.println("0");
    delay(50000);
    setPwmDuty(25); //Change  this value 0-100 to adjust duty cycle
    Serial.println("25");
    delay(50000);
    setPwmDuty(50);
    Serial.println("50");
    delay(200000);
    setPwmDuty(75);
    Serial.println("75");
    delay(200000);
    setPwmDuty(100);
    Serial.println("100");
    delay(200000);*/

}

void setPwmDuty(byte duty) {
  OCR1A = (word) (duty*TCNT1_TOP)/100;
}

boolean isValidNumber(String str) {
  for (byte i = 0; i < str.length(); i++) {
    if (isDigit(str.charAt(i))) return true;
  }
  return false;
}
