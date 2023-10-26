#ifdef TEST
#ifndef MockHTTPClient_h
#define MockHTTPClient_h

class HTTPClient
{
  HTTPClient() = default;
  ~HTTPClient() = default;

  int sendRequest(const char *type, const uint8_t *payload = NULL, size_t size = 0);
  bool begin(WiFiClient &client, const String &url);

  const String &HTTPClient::getString();
  void HTTPClient::end()
}

#endif

#endif