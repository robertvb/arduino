#include <LiquidCrystal.h>
#include <SPI.h> // needed in Arduino 0019 or later
#include <Ethernet.h>
#include <Twitter.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192,168,1,10);
  EthernetServer server(80);
Twitter twitter("2444352816-CE6IX6DFCYVaXJ5vfLeo0suJN1laaajJzSHR4RC");
char buf[100];
LiquidCrystal lcd(19, 18, 14, 15, 16, 17);
String estado="OFF"; //Estado del Led inicialmente "OFF"
int retardo = 0;


void setup() {
  
  delay(1000);
  Ethernet.begin(mac);
  server.begin();
  lcd.begin(16, 2);
  //irrecv.enableIRIn();
  lcd.print("Iniciando alarma");
  delay(1000);
  sprintf(buf, "Set up de la alarma OK: %d", millis()); 
  tweet(buf);
  delay(3000);
  lcd.clear();
  lcd.print("Bienvenido Robert!");
 
  
  
  
  
  delay(2000);
  lcd.clear();
  lcd.print("estado:");
  lcd.setCursor(0, 1);
  lcd.print("deasctivada");
  pinMode(7,OUTPUT);
  Ethernet.begin(mac , ip);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(8, OUTPUT);
}

void tweet(char msg[]) {
  if (twitter.post(msg)) {
    
    int status = twitter.wait(&Serial);
    if (status == 200) {
            lcd.clear();
      lcd.print("tweet enviado!");
    } 
    else {
      lcd.clear();
      lcd.print("error en tweet!");
      lcd.setCursor(0 , 1);
      lcd.print("error: ");
      lcd.print(status);
    }
  } 
  else {
    lcd.print("error en conexion.");
  }
  delay(500);
}

void loop()
{
 EthernetClient client = server.available(); //Creamos un cliente Web
  //Cuando detecte un cliente a través de una petición HTTP
  if (client) {
    boolean currentLineIsBlank = true; //Una petición HTTP acaba con una línea en blanco
    String cadena=""; //Creamos una cadena de caracteres vacía
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();//Leemos la petición HTTP carácter por carácter
        cadena.concat(c);//Unimos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String
         int posicion=cadena.indexOf("ALARM="); //Guardamos la posición de la instancia "LED=" a la variable 'posicion'
 
          if(cadena.substring(posicion)=="ALARM=ON")//Si a la posición 'posicion' hay "LED=ON"
          {
            estado="ON";
            lcd.clear();
            lcd.print("tiempo de act: ");
            for(int i = 9; i >= 0; i --)
            {
              lcd.setCursor(0,1);
              lcd.print(i);
              lcd.print(" segundos");
              delay(1000);
            }
            digitalWrite(7,HIGH);
            lcd.clear();
            lcd.print("Estado:");
            lcd.setCursor(0,1);
            lcd.print("activada");
            
            
          }
          if(cadena.substring(posicion)=="ALARM=OFF")//Si a la posición 'posicion' hay "LED=OFF"
          {
            digitalWrite(7,LOW);
            estado="OFF";
            lcd.clear();
            lcd.write("Estado:");
            lcd.setCursor(0,1);
            lcd.print("desactivada");
          }
 
        //Cuando reciba una línea en blanco, quiere decir que la petición HTTP ha acabado y el servidor Web está listo para enviar una respuesta
        if (c == '\n' && currentLineIsBlank) {
 
            // Enviamos al cliente una respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();
             
             
            //Página web en formato HTML
            client.println("<html>");
            client.println("<head>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1 align='center'>ALARMA:</h1><h3 align='center'>Bienvenido Robert</h3>");
            //Creamos los botones. Para enviar parametres a través de HTML se utiliza el metodo URL encode. Los parámetros se envian a través del símbolo '?'
            client.println("<div style='text-align:center;'>");
            client.println("<button onClick=location.href='./?ALARM=ON\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
            client.println("ON");
            client.println("</button>");
            client.println("<button onClick=location.href='./?ALARM=OFF\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
            client.println("OFF");
            client.println("</button>");
            client.println("<br /><br />");
            client.println("<b>ALARMA = ");
            client.print(estado);
            client.println("</b><br />");
            client.println("</b></body>");
            client.println("</html>");
            break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
      if(estado=="ON")
            {
              do{
            digitalWrite (3, HIGH);
            delay (1);
            digitalWrite (3, LOW);
            retardo = pulseIn (4, HIGH);
            delay(150);
              }while(!retardo || retardo/58  > 120);
            lcd.clear();
            lcd.print("intrusismo detectado!");
            lcd.setCursor(0,1);
            digitalWrite(8,HIGH);
           sprintf(buf, "Intrusismo detectado!: %d", millis());
            Ethernet.begin(mac);
            tweet(buf);
            delay(10000);
            digitalWrite(8,LOW);
            Ethernet.begin(mac, ip);
            }
            
    //Dar tiempo al navegador para recibir los datos
    }
    delay(1);
    client.stop();// Cierra la conexión
          
  }
}

