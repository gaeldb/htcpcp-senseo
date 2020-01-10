#include <SPI.h>
#include <Ethernet.h>

/*
 * Global variables
 */

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

// Fix IP address if DHCP is unreachable
IPAddress ip(192, 168, 1, 127);
IPAddress dns(192,168,1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// HTTP server struct
EthernetServer httpServer(80);

/*
 * Setup sequence
 */

void setup()
{
  configureSerialPort(9600);
  configureIPAddress();
  printIPAddress();
  httpServer.begin();
  Serial.println("HTCPCP server initialized normally");
}

/*
 * HTCPCP server loop
 */
 
void          loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("new client");
    char      c;
    boolean   currentLineIsBlank = true;
    String    httpReq = "";
    
    while (client.connected())
    {
      if (client.available())
      {
        c = client.read();
        httpReq += c;
        if (c == '\n' && currentLineIsBlank && req_str.startsWith("GET"))
        {
          // Waiting for implementation
          response(client, "406 Not acceptable here");
        }
        else if (c == '\n' && currentLineIsBlank && (req_str.startsWith("POST") || req_str.startsWith("BREW")))
        {
          // Waiting for implementation
          response(client, "406 Not acceptable here");
        }
        else if (c == '\n' && currentLineIsBlank && (req_str.startsWith("PROFIND") || req_str.startsWith("WHEN")))
        {
          // Will ne be implemented due to hardware limitation. See README.md.
          response(client, "501 Not Implemented");
        }
        
        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }

}

void response(EthernetClient client, String httpCode)
{
    client.print("HTTP/1.1 ");
    client.println(httpCode);
    client.println("Content-Type: text/html");
    client.println("Connection: close");
}

void printIPAddress()
{
  ip = Ethernet.localIP();
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}

void configureIPAddress()
{
  // start the Ethernet connection:
  Serial.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the Ethernet device not using DHCP:
    Ethernet.begin(mac, ip, dns, gateway, subnet);
  }
}

void configureSerialPort(int baudrate)
{
  // Initialize debug serial interface
  Serial.begin(baudrate);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
