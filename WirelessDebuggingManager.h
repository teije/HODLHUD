#ifndef WIRELESSDEBUGGINGMANAGER_H
#define WIRELESSDEBUGGINGMANAGER_H

class WirelessDebuggingManager {
public:
  const uint port = 23;
  WiFiServer Server;
  WiFiClient RemoteClient;

  // Constructor
  WirelessDebuggingManager(WiFiManager wifiManager) : Server(23) { }

  void begin()
  {
    println("Starting Wireless Debugger...");
    Server.begin();
  }

  void CheckForConnections()
  {
    println("Wireless Debugger checking for remote connections... ");
    if (Server.hasClient())
    {
      print("Client found");
      // If we are already connected to another computer, 
      // then reject the new connection. Otherwise accept
      // the connection. 
      if (RemoteClient.connected())
      {
        println("Already connected to a client, rejected new connection");
        Server.available().stop();
      }
      else
      {
        println("Accepted new connection");
        Serial.println("Connection accepted");
        RemoteClient = Server.available();
      }
    }
  }

  void printToClient()
  {
    if (RemoteClient.connected())
    { 
      RemoteClient.println("Hello World!");
    } else {
      println("No client connected to send message to");
    }
    
  }

private:
  WiFiManager wifiManager;  // Instance of WiFiManager for Wi-Fi connection

  String Type() {
    return "WirelessDebuggingManager.h";
  }
};

#endif // WIRELESSDEBUGGINGMANAGER_H
