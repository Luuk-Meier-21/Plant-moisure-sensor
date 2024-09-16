#ifndef HTTPRequestClient_h
#define HTTPRequestClient_h

#ifdef CORE // Core entry point
#include <ESP8266HTTPClient.h>
#endif
#ifdef TEST // Test entry point
#include "../../src/MockHTTPClient/MockHTTPClient.h"
#endif

enum HTTPMethod
{
  HTTP_GET = 0,
  HTTP_DELETE = 1,
  HTTP_PUT = 2,
  HTTP_PATCH = 3,
};

class HTTPRequestClient
{
  WiFiClient *wifiService;
  HTTPClient *httpService;

  int currentResponseCode = 0;
  String currentPayload = "";

public:
  // HTTPRequestClient(String url) : host_url(url){};
  HTTPRequestClient(WiFiClient *wifi, HTTPClient *http)
      : wifiService(wifi), httpService(http){};

  int makeRequest(HTTPMethod method, String url)
  {
    httpService->begin(*wifiService, url);

    if (currentResponseCode > 0)
    {
      flush();
    }

    currentResponseCode = httpService->sendRequest(getMethodChar(method));
    if (currentResponseCode > 0)
    {
      currentPayload = httpService->getString();
    }

    httpService->end();
    return currentResponseCode;
  };

  void flush()
  {
    currentResponseCode = 0;
    currentPayload = "";
  }

  String consumePayload()
  {
    String payload = currentPayload;
    flush();
    return payload;
  }

  const char *getMethodChar(HTTPMethod method)
  {
    switch (method)
    {
    case HTTP_GET:
      return "GET";
    case HTTP_DELETE:
      return "DELETE";
    case HTTP_PUT:
      return "PUT";
    case HTTP_PATCH:
      return "PATCH";
    default:
      return "GET";
    }
  }
};

#endif