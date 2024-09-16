#ifdef TEST
#ifndef MockESP8266Class_h
#define MockESP8266Class_h

struct MockESP8266WiFiData
{
  String ssid;

  MockESP8266WiFiData(String _ssid) : ssid(_ssid){};
};

typedef enum
{
  WL_NO_SHIELD = 255, // for compatibility with WiFi Shield library
  WL_IDLE_STATUS = 0,
  WL_NO_SSID_AVAIL = 1,
  WL_SCAN_COMPLETED = 2,
  WL_CONNECTED = 3,
  WL_CONNECT_FAILED = 4,
  WL_CONNECTION_LOST = 5,
  WL_WRONG_PASSWORD = 6,
  WL_DISCONNECTED = 7
} wl_status_t;

typedef enum WiFiMode
{
  WIFI_OFF = 0,
  WIFI_STA = 1,
  WIFI_AP = 2,
  WIFI_AP_STA = 3
} WiFiMode_t;

class ESP8266WiFiClass
{
  bool isConnected = false;
  WiFiMode sta_mode;

  static const int size = 4;
  MockESP8266WiFiData mock_networks[size] = {
      MockESP8266WiFiData("network-1"),
      MockESP8266WiFiData("network-2"),
      MockESP8266WiFiData("network-3"),
      MockESP8266WiFiData("network-4"),
  };

public:
  int scanNetworks(bool async, bool hidden)
  {
    (void)async;
    (void)hidden;
    return size;
  };

  bool begin(String ssid, String password)
  {
    (void)ssid;
    (void)password;
    delay(300);
    isConnected = true;
    return true;
  }

  bool mode(WiFiMode _mode)
  {
    sta_mode = _mode;
    return true;
  }

  wl_status_t status()
  {
    if (isConnected)
    {
      return WL_CONNECTED;
    }
    return WL_IDLE_STATUS;
  }

  bool getNetworkInfo(uint8_t i, String &ssid, uint8_t &encType, int32_t &rssi, uint8_t *&bssid, int32_t &channel, bool &isHidden)
  {
    MockESP8266WiFiData n = mock_networks[i];
    ssid = n.ssid;
    (void)encType;
    (void)rssi;
    (void)bssid;
    (void)channel;
    (void)isHidden;

    return true;
  };
} mockWiFi;

#endif

#endif