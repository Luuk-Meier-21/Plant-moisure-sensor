#ifdef TEST
#ifndef MockHTTPClient_h
#define MockHTTPClient_h

class WiFiClient
{
};

class HTTPClient
{
  bool isOpen = false;
  String payload = "default";

public:
  HTTPClient() = default;
  ~HTTPClient() = default;

  int sendRequest(const char *type, const uint8_t *payload = NULL, size_t size = 0)
  {
    (void)type;
    (void)payload;
    (void)size;

    if (!isOpen)
    {
      return 0;
    }
    return 200;
  }

  bool begin(WiFiClient &client, const String &url)
  {
    (void)client;
    (void)url;
    isOpen = true;
    return true;
  }

  void end()
  {
    isOpen = false;
  }

  void setMockPayload(String _payload)
  {
    payload = _payload;
  }

  const String getString()
  {
    return payload;
  }
};

#endif
#endif