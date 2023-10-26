#ifndef HTTPRequestClient_h
#define HTTPRequestClient_h

#include <WiFiClient.h>

#include "../../src/MockHTTPClient/MockHTTPClient.h"

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
      // Prev response has not been consumed yet.
      Serial.println("Has prev response");
      return false;
    }

    currentResponseCode = httpService->sendRequest(getMethodChar(method));
    if (currentResponseCode > 0)
    {
      currentPayload = httpService->getString();
    }

    httpService->end();
    return currentResponseCode;
  };

  String consumePayload()
  {
    String payload = currentPayload;
    currentPayload = "";
    return payload;
  }

  const char *getMethodChar(HTTPMethod method)
  {
    switch (method)
    {
    case HTTP_GET:
      return "GET";
      break;
    case HTTP_DELETE:
      return "DELETE";
      break;
    case HTTP_PUT:
      return "PUT";
      break;
    case HTTP_PATCH:
      return "PATCH";
      break;
    }
  }
};

#endif