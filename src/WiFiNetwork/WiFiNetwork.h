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

  String getSsid() const
  {
    return ssid;
  }

  String getPassword() const
  {
    return password;
  }

  bool isValid() const
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