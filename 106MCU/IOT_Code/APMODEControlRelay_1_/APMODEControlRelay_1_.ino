#include <WiFi.h>
#define RelayPin 8
#define Turnon HIGH
#define Turnoff LOW

char ssid[] = "Ameba";  //Set the AP's SSID
char pass[] = "12345678";     //Set the AP's password
char channel[] = "1";         //Set the AP's channel
int status = WL_IDLE_STATUS;     // the Wifi radio's status

int keyIndex = 0;                 // your network key Index number (needed only for WEP)

WiFiServer server(80);
boolean  RelayMode[4]= { false,false,false,false} ;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
pinMode(RelayPin, OUTPUT);      // set the LED pin mode
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to start AP:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to start AP with SSID: ");
    Serial.println(ssid);
    status = WiFi.apbegin(ssid, pass, channel);
    delay(10000);
  }

  //AP MODE already started:
  Serial.println("AP mode already started");
  Serial.println();
    server.begin();    
  printWifiData();
  printCurrentNet();
}

void loop() {
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");

            client.println("Content-type:text/html");
            client.println();

           client.print("<title>Ameba AP Mode Control Relay</title>");
            client.println();
                          client.print("<html>");
                          client.println();
                          client.print("<body>");
                          client.println();
 //----------control code start--------------------
                          // the content of the HTTP response follows the header:
                          client.print("<p>Relay 1") ; 
                          if (RelayMode[0])
                              {
                                  client.print("(ON)") ; 
                              }
                                else
                              {
                                  client.print("(OFF)") ; 
                              }
                                
                          client.print(":") ; 
                          client.print("<a href='/H1' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/L1' target='_self'>Close</a>") ;
                          client.print("</p>");
                          client.print("<p>Relay 2") ; 
                          if (RelayMode[1])
                              {
                                  client.print("(ON)") ; 
                              }
                                else
                              {
                                  client.print("(OFF)") ; 
                              }
                                
                          client.print(":") ; 
                          client.print("<a href='/H2' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/L2' target='_self'>Close</a>") ;
                          client.print("</p>");
                          client.print("<p>Relay 3") ; 
                          if (RelayMode[2])
                              {
                                  client.print("(ON)") ; 
                              }
                                else
                              {
                                  client.print("(OFF)") ; 
                              }
                                
                          client.print(":") ; 
                          client.print("<a href='/H3' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/L3' target='_self'>Close</a>") ;
                          client.print("</p>");
                          client.print("<p>Relay 1") ; 
                          if (RelayMode[3])
                              {
                                  client.print("(ON)") ; 
                              }
                                else
                              {
                                  client.print("(OFF)") ; 
                              }
                                
                          client.print(":") ; 
                          client.print("<a href='/H4' target='_self'>Open</a>") ;
                          client.print("/") ; 
                          client.print("<a href='/L4' target='_self'>Close</a>") ;
                          client.print("</p>");
                          /*
                          client.print("<p>繼電器二") ; 
                          if (RelayMode[1])
                              {
                                  client.print("目前開啟") ; 
                              }
                                else
                              {
                                  client.print("目前關閉") ; 
                              }
                          client.print(":") ;                           
                          client.print("<a href='/H2' target='_self'>開啟</a>") ;
                          client.print("<a href='/L2' target='_self'>關閉</a>") ;
                          client.print("</p>");
                          client.print("<p>繼電器三") ; 
                          if (RelayMode[2])
                              {
                                  client.print("目前開啟") ; 
                              }
                                else
                              {
                                  client.print("目前關閉") ; 
                              }
                          client.print(":") ;                           
                          client.print("<a href='/H3' target='_self'>開啟</a>") ;
                          client.print("<a href='/L3' target='_self'>關閉</a>") ;
                          client.print("</p>");
                          client.print("<p>繼電器四") ; 
                          if (RelayMode[3])
                              {
                                  client.print("目前開啟") ; 
                              }
                                else
                              {
                                  client.print("目前關閉") ; 
                              }
                          client.print(":") ;                           
                          client.print("<a href='/H4' target='_self'>開啟</a>") ;
                          client.print("<a href='/L5' target='_self'>關閉</a>") ;
                          client.print("</p>");
          */
//----------control code end                               
                          client.print("</body>");
                          client.println();
                          client.print("</html>");
                          client.println();

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(RelayPin, Turnon);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(RelayPin, Turnoff);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your subnet mask:
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
  Serial.println();
}

void printCurrentNet() {
  // print the SSID of the AP:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of AP:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[0], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.println(bssid[5], HEX);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

