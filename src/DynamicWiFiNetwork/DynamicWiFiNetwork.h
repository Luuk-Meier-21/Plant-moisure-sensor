#include "../../src/WiFiNetwork/WiFiNetwork.h"

#ifndef DynamicWiFiNetwork_h
#define DynamicWiFiNetwork_h

template <size_t SIZE>
class DynamicWiFiNetwork
{
  WiFiNetwork networks[SIZE];

public:
  DynamicWiFiNetwork(WiFiNetwork networks[SIZE]) : networks(networks)
  {
  }

  WiFiNetwork find(String ssid)
  {
    for (size_t i = 0; i < SIZE; i++)
    {
      if (ssid == networks[i].ssid)
      {
        return networks[i];
        break;
      }
    }

    return WiFiNetwork::empty();
  }

  size_t length()
  {
    return SIZE;
  }
};

#endif