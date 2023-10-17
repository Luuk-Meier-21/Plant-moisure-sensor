// Supresses vscode error squiggles:
#ifdef __INTELLISENSE__
#pragma diag_suppress
#endif;

#include <Arduino.h>

struct WiFiNetwork
{
  String ssid;
  String password;
}

template <size_t SIZE>
class DynamicWiFiNetwork
{
public:
  WiFiCredentials(WiFiCredentialsPair[SIZE] credentials);

  WiFiNetwork findCurrent(ESP8266WiFiClass wifi);
  size_t getLength();
}

// Class for scanning networks and joining based on given possible credentail pair.
class AutoConnectingWifiService
{

public:
  AutoConnectingWifiService(ESP8266WiFiClass wifi, WiFiCredentialsList network_options){};

  void beginConnection(){};

  void awaitConnection(void()() on_connection_tick){};
}

// Abstraction of httpClient, makes using http request easier by changing it to look more like Javascript's `fetch`.
class HTTPSRequestService
{
  typedef int (*RequestMethodFunction)();

public:
  HTTPService(String host_url) {}

  String getHost();

  String makeRequest(WiFiClient client, RequestMethodFunction request_method_func, String server_path){};
  String makeGETRequest(WiFiClient client, String server_path){};
}
