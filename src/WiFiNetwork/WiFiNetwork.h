#ifndef WiFiNetwork_h
#define WiFiNetwork_h
class WiFiNetwork
{
  boolean valid;
  String ssid;
  String password;

private:
  WiFiNetwork()
  {
    valid = false;
  };

public:
  WiFiNetwork(String ssid, String password) : ssid(ssid), password(password)
  {
    valid = true;
  };

  String getSsid()
  {
    return ssid;
  }

  String getPassword()
  {
    return password;
  }

  bool isValid()
  {
    return valid;
  };

  static WiFiNetwork empty()
  {
    WiFiNetwork network;
    return network;
  }
};

#endif