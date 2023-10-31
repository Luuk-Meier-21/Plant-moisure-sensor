#ifndef DynamicWiFiNetwork_h
#define DynamicWiFiNetwork_h

#include "../../src/DiscoveringWiFiClient/DiscoveringWiFiClient.h"
#include "../../src/WiFiNetwork/WiFiNetwork.h"

template <size_t SIZE>
class DynamicWiFiNetwork : public WiFiDiscoverable
{
  WiFiNetwork (&networks)[SIZE];

public:
  DynamicWiFiNetwork(WiFiNetwork (&target_networks)[SIZE]) : networks(target_networks){};

  WiFiNetwork find(String ssid)
  {
    for (size_t i = 0; i < SIZE; i++)
    {
      Serial.print("Found: ");
      Serial.println(networks[i].getSsid());
      if (ssid == networks[i].getSsid())
      {
        return networks[i];
        break;
      }
    }

    return WiFiNetwork::empty();
  };

  bool has(String ssid)
  {
    for (size_t i = 0; i < SIZE; i++)
    {
      if (ssid == networks[i].getSsid())
      {
        return true;
        break;
      }
    }

    return false;
  }

  size_t count()
  {
    return SIZE;
  };
};

#endif