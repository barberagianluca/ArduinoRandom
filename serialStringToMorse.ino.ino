
// Variables
byte const MESSAGE_MAX_SIZE = 25;
byte messageRealSize = 0;
char message[MESSAGE_MAX_SIZE];
char rx_byte = 0;

short const DOT_TIME = 500;
short const DASH_TIME = DOT_TIME*3;
short const SAME_LETTER_SPACE = DOT_TIME;
short const DIFFERENT_LETTER_SPACE = DOT_TIME*3;
short const DIFFERENT_WORDS_SPACE = DOT_TIME*5; // == ' '

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize Serial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Send initialization end message
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for 3 second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  Serial.print("Ready to get the message - max chars: "); Serial.println((MESSAGE_MAX_SIZE-1));
  Serial.println("Add . to end the message");
  
  byte count = 0;
  while((count < MESSAGE_MAX_SIZE) && (rx_byte != 3)) { // 3 == EOM
    if (Serial.available() > 0) {    // is a character available?
      rx_byte = Serial.read();       // get the character
      if((rx_byte == '.'))
        break;
      
      // check if a number was received
      if ( ((rx_byte >= 'a') && (rx_byte <= 'z')) || ((rx_byte >= 'A') && (rx_byte <= 'Z') || (rx_byte == ' ')) ) {
        //Serial.print("Character received: ");
        //Serial.println(rx_byte);
        message[count] = rx_byte;
        count++;
      }
      else {        
        Serial.print("'");
        Serial.print(rx_byte);
        Serial.println("' is not a valid character!");
      }
    }
  }

  messageRealSize = count;
}

void dot() {
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(DOT_TIME);
  digitalWrite(LED_BUILTIN, LOW);
  delay(SAME_LETTER_SPACE); 
}

void dash() {
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(DASH_TIME);
  digitalWrite(LED_BUILTIN, LOW);
  delay(SAME_LETTER_SPACE); 
}

void letterBreak() {
  delay(DIFFERENT_LETTER_SPACE); 
}

void wordBreak() {
  delay(DIFFERENT_WORDS_SPACE);   
}

void convertCharToMorse(char x) {
  switch(x) {
    case 'a': case 'A': Serial.print("A"); dot(); dash(); break;
    case 'b': case 'B': Serial.print("B"); dash(); dot(); dot(); dot(); break;
    case 'c': case 'C': Serial.print("C"); dash(); dot(); dash(); dot(); break;
    case 'd': case 'D': Serial.print("D"); dash(); dot(); dot(); break;
    case 'e': case 'E': Serial.print("E"); dot(); break;
    case 'f': case 'F': Serial.print("F"); dot(); dot(); dash(); dot(); break;
    case 'g': case 'G': Serial.print("G"); dash(); dash(); dot(); break;
    case 'h': case 'H': Serial.print("H"); dot(); dot(); dot(); dot(); break;
    case 'i': case 'I': Serial.print("I"); dot(); dot(); break;
    case 'j': case 'J': Serial.print("J"); dot(); dash(); dash(); dash(); break;
    case 'k': case 'K': Serial.print("K"); dash(); dot(); dash(); break;
    case 'l': case 'L': Serial.print("L"); dot(); dash(); dot(); dot(); break;
    case 'm': case 'M': Serial.print("M"); dash(); dash(); break;
    case 'n': case 'N': Serial.print("N"); dash(); dot(); break;
    case 'o': case 'O': Serial.print("O"); dash(); dash(); dash(); break;
    case 'p': case 'P': Serial.print("P"); dot(); dash(); dash(); dot(); break;
    case 'q': case 'Q': Serial.print("Q"); dash(); dash(); dot(); dash(); break;
    case 'r': case 'R': Serial.print("R"); dot(); dash(); dot(); break;
    case 's': case 'S': Serial.print("S"); dot(); dot(); dot(); break;
    case 't': case 'T': Serial.print("T"); dash(); break;
    case 'u': case 'U': Serial.print("U"); dot(); dot(); dash(); break;
    case 'v': case 'V': Serial.print("V"); dot(); dot(); dot(); dash(); break;
    case 'w': case 'W': Serial.print("W"); dot(); dash(); dash(); break;
    case 'x': case 'X': Serial.print("X"); dash(); dot(); dot(); dash(); break;
    case 'y': case 'Y': Serial.print("Y"); dash(); dot(); dash(); dash(); break;
    case 'z': case 'Z': Serial.print("Z"); dash(); dash(); dot(); dot(); break;
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Message ready (");
  Serial.print(message);
  Serial.println(")");

  delay(3000);
  Serial.println("Starting morse trasmission...");
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  
  for(byte i=0; i<messageRealSize; i++) {
    if(message[i] == ' ')
    {
      wordBreak();
      Serial.print(" ");
    }
    else
      letterBreak();
    convertCharToMorse(message[i]);
  }

  Serial.println("");
  Serial.println("------- End Trasmission ------");
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000);  
}



