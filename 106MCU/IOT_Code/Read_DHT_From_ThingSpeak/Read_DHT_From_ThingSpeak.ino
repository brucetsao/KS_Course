#include <String.h>
//-------------- dht use
#include <WiFi.h>
#include "ThingSpeak.h"

char ssid[] = "BruceiPhone";      // your network SSID (name)
char pass[] = "12345678";     // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiClient client;

//IPAddress server(64,233,189,94);  // numeric IP for Google (no DNS)
char server[] = "184.106.153.149";    // name address for Google (using DNS)
String readAPIKey = "76YGI60KQ9880WI4";    // Write API Key for a ThingSpeak Channel
const int updateInterval = 30000;        // Time interval in milliseconds to update ThingSpeak   
// Variable Setup
long lastConnectionTime = 0; 
boolean lastConnected = false;
int resetCounter = 0;



void setup()   /*----( SETUP: RUNS ONCE )----*/
{
    Serial.begin(9600);
  Serial.println("DHTxx test!");
    dht.begin();
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
//   end of init wifi

}// END Setup


void loop()   
{
 
}

void resetEthernetShield()
{
  Serial.println("Resetting Ethernet Shield.");   
  Serial.println();
  
  client.stop();
  delay(1000);
 }


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

