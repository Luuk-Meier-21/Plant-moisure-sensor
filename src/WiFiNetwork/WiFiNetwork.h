#ifndef WiFiNetwork_h
#define WiFiNetwork_h

struct WiFiNetwork
{
  String ssid;
  String password;

  static WiFiNetwork create(String ssid, String password)
  {
    WiFiNetwork network;
    network.ssid = ssid;
    network.password = password;

    return network;
  }
};

// template <size_t SIZE>
// class DynamicWiFiNetwork
// {
//   WiFiNetwork[SIZE] networks;

// public:
//   WiFiNetwork(WiFiNetwork[SIZE] networks) : networks(networks){};

//   size_t length()
//   {
//     return SIZE;
//   }
// };

#endif