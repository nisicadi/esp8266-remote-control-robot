#include <ESP8266WiFi.h>

const char* ssid = "--------";      // Your Wi-Fi Name
const char* password = "--------";   // Wi-Fi Password

bool upaljenaSvjetla = false;

#define IN1   D5   //IN1, plava 
#define IN2   D6   //IN2, zelena
#define IN3   D7   //IN3, zuta
#define IN4   D8   //IN4, narandzasta
#define LED   D3   

void naprijed()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void nazad()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void lijevo()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void desno()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stani()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
}

void svjetlaOn()
{
  digitalWrite(LED, HIGH);
}

void svjetlaOff()
{
  digitalWrite(LED, LOW);
}

WiFiServer server(80);

void setup()

{

  Serial.begin(115200); //Default Baudrate

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(LED, LOW);

 

  Serial.print("Connecting to the Newtork");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("WiFi connected"); 

  server.begin();  // Starts the Server

  Serial.println("Server started");

 

  Serial.print("IP Address of network: "); // Prints IP address on Serial Monitor

  Serial.println(WiFi.localIP());

  Serial.print("Copy and paste the following URL: https://"); // Prints IP address in URL format

  Serial.print(WiFi.localIP());

  Serial.println("/");

}

 

void loop()

{

  WiFiClient client = server.available();

  if (!client)

  {

    return;

  }

  Serial.println("Waiting for new client");

  while(!client.available())

  {

    delay(1);

  }

 

  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();

 

  if (request.indexOf("GET /naprijed") >= 0) {
    Serial.println("naprijed()");
    naprijed();
  } else if (request.indexOf("GET /nazad") >= 0) {
    Serial.println("nazad()");
    nazad();
  } else if (request.indexOf("GET /lijevo") >= 0) {
    Serial.println("lijevo()");
    lijevo();
  } else if (request.indexOf("GET /desno") >= 0) {
    Serial.println("desno()");
    desno();
  } else if (request.indexOf("GET /stop") >= 0) {
    Serial.println("stop()");
    stani();
  } else if (request.indexOf("GET /svjetlaOn") >= 0) {
    Serial.println("svjetlaOn()");
    svjetlaOn();
    upaljenaSvjetla = true;
  } else if (request.indexOf("GET /svjetlaOff") >= 0) {
    Serial.println("svjetlaOff()");
    svjetlaOff();
    upaljenaSvjetla = false;
   }

 

//*------------------HTML Page Code---------------------*//

 

  client.println("HTTP/1.1 200 OK"); //

  client.println("Content-Type: text/html");

  client.println("");

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 5px 5px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println("div{text-align: center;}</style></head>");
            
            client.println("<body><h1>----------<br>-----------</h1>");
            
            client.println("<div><p><a href=\"/naprijed\"><button class=\"button button2\">Naprijed</button></a></p></div>");      
            client.println("<div><a href=\"/lijevo\"><button class=\"button button2\">Lijevo</button></a>");      
            client.println("<a href=\"/stop\"><button class=\"button button2\">Stop</button></a>");      
            client.println("<a href=\"/desno\"><button class=\"button button2\">Desno</button></a></div>");      
            client.println("<div><p><a href=\"/nazad\"><button class=\"button button2\">Nazad</button></a></p></div>");
            if(upaljenaSvjetla)
            {
              client.println("<div><br><br><a href=\"/svjetlaOff\"><button class=\"button button2\">Svjetla</button></a></div>");
            } else
            {
              client.println("<div><br><br><a href=\"/svjetlaOn\"><button class=\"button button2\">Svjetla</button></a></div>");
            }
                  
            client.println("</body></html>");

 

  delay(1);
  
  client.stop();

  Serial.println("Client disonnected");

  Serial.println("");

}
