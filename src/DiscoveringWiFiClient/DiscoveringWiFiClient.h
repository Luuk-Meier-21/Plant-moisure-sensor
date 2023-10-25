#ifndef DiscoveringWiFiClient_h
#define DiscoveringWiFiClient_h

#include "../../src/WiFiNetwork/WiFiNetwork.h"

// Only for test usage, contents only available if the TEST env is present:
#include "../../src/MockESP8266Class/MockESP8266Class.h"

class WiFiDiscoverable
{
public:
  virtual WiFiNetwork find(String ssid) = 0;
  virtual bool has(String ssid) = 0;
};

/**
 * Client for manipulating passed DynamicWiFiNetwork
 */
template <size_t SIZE>
class DiscoveringWiFiClient
{
  ESP8266WiFiClass wifi;
  WiFiDiscoverable *networks;
  String current_ssid = "";

public:
  DiscoveringWiFiClient(ESP8266WiFiClass wifi_class, WiFiDiscoverable *network_options)
      : wifi(wifi_class), networks(network_options){};

  bool beginConnection()
  {
    if (current_ssid.length() > 0)
    {
      WiFiNetwork target_network = networks->find(current_ssid);
      wifi.begin(target_network.getSsid(), target_network.getPassword());
      return true;
    }
    return false;
  };

  bool awaitConnection(void (*on_connection_tick)(), unsigned long timer)
  {
    static unsigned long startTime = millis();
    while (wifi.status() != WL_CONNECTED)
    {
      on_connection_tick();
      // Return false after n seconds:
      if ((millis() - startTime) > timer)
      {
        return false;
      }
    }
    return true;
  };

  bool scan()
  {
    String ssid;
    int32_t rssi;
    uint8_t encryption_type;
    uint8_t *bssid;
    int32_t channel;
    bool hidden;

    int scan_results = wifi.scanNetworks(false, true);

    if (scan_results == 0)
    {
      return false;
    }
    else if (scan_results > 0)
    {
      for (int8_t i = 0; i < scan_results; i++)
      {
        wifi.getNetworkInfo(i, ssid, encryption_type, rssi, bssid, channel, hidden);
        if (networks->has(ssid))
        {
          // Found a network we can connect to:
          current_ssid = ssid;
          return true;
        }
      }
    }
    else
    {
      // Error
    }

    return false;
  };
};

#endif