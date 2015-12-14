unsigned short int punto = 70; // Duracion del punto
unsigned short int raya = punto * 4; // Duracion de la raya
unsigned short int negro = punto * 3; // Duracion del apagado entre rayas y puntos
unsigned short int letrayletra = punto * 5; // Duracion del apagado entre letras
 
void playTone(int tone, int duration, int speakerPin) {
  // Sends the signal to the speakerPin
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
 
void playToneLed(int tone, int duration, int speakerPin, int ledPin) {
  // Sends the signal to speakerPin and ledPin
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    digitalWrite(ledPin, LOW);
    delayMicroseconds(tone);
  }
}
 
// ########## CLASE LETRA #########
class letra {
  private:
    char caracter;
    char* codigo;
    int ledPin;
  public:
    letra (char car, char* cad, unsigned short int pin);
    void set (char car, char* cad, unsigned short int pin);
    void mostrar ();
    void sonar ();
    void mostrarYsonar ();
};
 
letra::letra (char car, char* cad, unsigned short int pin) {
  // Constructor
  caracter = car;
  codigo = cad;
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
}
 
void letra::set (char car, char* cad, unsigned short int pin) {
  // Setter
  caracter = car;
  codigo = cad;
  ledPin = pin;
}
 
void letra::mostrar () {
  // Shows the code in in the ledPin
  unsigned short int j = 0;
  while (codigo[j] != 0) {
    if (codigo[j] == '.') {
      digitalWrite (ledPin, HIGH);
      delay (punto);
      digitalWrite (ledPin, LOW);
      delay (negro);
    } else if (codigo[j] == '-') {
      digitalWrite (ledPin, HIGH);
      delay (raya);
      digitalWrite (ledPin, LOW);
      delay (negro);
    }
    j++;
  }
  delay (letrayletra);
}
 
void letra::sonar () {
  // Sounds the code on the speakerPin
  unsigned short int j = 0;
  while (codigo[j] != 0) {
    if (codigo[j] == '.') {
      playTone (440, 100, 9);
      delay (negro/3);
    } else if (codigo[j] == '-') {
      playTone (440, 100 * 4, 9);
      delay (negro/3);
    }
    j++;
  }
  delay (letrayletra);
}
 
void letra::mostrarYsonar () {
  // Sounds and shows the code (ledPin + speakerPin)
  unsigned short int j = 0;
  while (codigo[j] != 0) {
    if (codigo[j] == '.') {
      playToneLed (440, 100, 9, ledPin);
      delay (negro/4);
    } else if (codigo[j] == '-') {
      playToneLed (440, 100 * 4, 9, ledPin);
      delay (negro/4);
    }
    j++;
  }
  delay (letrayletra/2);
}
// ##############################
 
void setup() {
  Serial.begin(9600);
  
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}
 
int letraIN = 0;
unsigned short int ledPin = 13;
void loop() {
  digitalWrite(ledPin, LOW);
  letraIN = 0;
  letraIN = Serial.read();
  letra let (0, "", ledPin);
  switch (letraIN) {
    case 'a': let.set ('a', ".-", ledPin);
              break;
    case 'b': let.set ('b', "-...", ledPin);
              break;
    case 'c': let.set ('c', "-.-.", ledPin);
              break;
    case 'd': let.set ('d', "-..", ledPin);
              break;
    case 'e': let.set ('e', ".", ledPin);
              break;
    case 'f': let.set ('f', "..-.", ledPin);
              break;
    case 'g': let.set ('g', "--.", ledPin);
              break;
    case 'h': let.set ('h', "....", ledPin);
              break;
    case 'i': let.set ('i', "..", ledPin);
              break;
    case 'j': let.set ('j', ".---", ledPin);
              break;
    case 'k': let.set ('k', "-.-", ledPin);
              break;
    case 'l': let.set ('l', ".-..", ledPin);
              break;
    case 'm': let.set ('m', "--", ledPin);
              break;
    case 'n': let.set ('n', "-.", ledPin);
              break;
    case 'o': let.set ('o', "---", ledPin);
              break;
    case 'p': let.set ('p', ".--.", ledPin);
              break;
    case 'q': let.set ('q', "--.-", ledPin);
              break;
    case 'r': let.set ('r', ".-.", ledPin);
              break;
    case 's': let.set ('s', "...", ledPin);
              break;
    case 't': let.set ('t', "-", ledPin);
              break;
    case 'u': let.set ('u', "..-", ledPin);
              break;
    case 'v': let.set ('v', "...-", ledPin);
              break;
    case 'w': let.set ('w', ".--", ledPin);
              break;
    case 'x': let.set ('x', "-..-", ledPin);
              break;
    case 'y': let.set ('y', "-.--", ledPin);
              break;
    case 'z': let.set ('z', "--..", ledPin);
              break;
    case '0': let.set ('0', "-----", ledPin);
             break;
    case '1': let.set ('1', ".----", ledPin);
             break;
    case '2': let.set ('2', "..---", ledPin);
             break;
    case '3': let.set ('3', "...--", ledPin);
             break;
    case '4': let.set ('4', "....-", ledPin);
             break;
    case '5': let.set ('5', ".....", ledPin);
             break;
    case '6': let.set ('6', "-....", ledPin);
             break;
    case '7': let.set ('7', "--...", ledPin);
             break;
    case '8': let.set ('8', "---..", ledPin);
             break;
    case '9': let.set ('9', "----.", ledPin);
             break;
    case '.': let.set ('.', ".-.-.-", ledPin);
             break;
    case ',': let.set (',', "--..--", ledPin);
             break;
    case '?': let.set ('?', "..--..", ledPin);
             break;
    case '"': let.set ('"', ".-..-.", ledPin);
             break;
  }
  //let.mostrar();
  //let.sonar();
  let.mostrarYsonar();
}
