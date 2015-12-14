const int led = 9;
const int potenciometro = 4;

void setup(){
  
  pinMode(led,OUTPUT);

}

void loop(){
  
  
  int intensidad = (analogRead(potenciometro) / 4); // entre 0 y 1023
  analogWrite(led, intensidad); // entre  0 y 255 por eso dividimos xd
  
}
