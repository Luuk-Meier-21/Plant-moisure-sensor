#ifndef HTTPRequestClient_test_h
#define HTTPRequestClient_test_h

#include "../../src/MockHTTPClient/MockHTTPClient.h"
#include "../../src/HTTPRequestClient/HTTPRequestClient.h"

#include "stddef.h"
using namespace std;

test(HTTPRequestClient_makeRequest)
{
  String url = "test";

  WiFiClient client;
  HTTPClient http;
  HTTPRequestClient requestClient(&client, &http);

  int responseCode = requestClient.makeRequest(HTTP_GET, url);
  assertEqual(responseCode, 200);
}

test(HTTPRequestClient_consumePayload)
{

  String url = "test";
  String p = "long-test-payload";

  WiFiClient client;
  HTTPClient http;
  http.setMockPayload(p);
  HTTPRequestClient requestClient(&client, &http);

  int responseCode = requestClient.makeRequest(HTTP_GET, url);
  assertTrue(responseCode > 0);
  String payload = requestClient.consumePayload();
  assertEqual(payload, p);
}

test(HTTPRequestClient_flush)
{

  String url = "test";

  WiFiClient client;
  HTTPClient http;
  HTTPRequestClient requestClient(&client, &http);

  int responseCode = requestClient.makeRequest(HTTP_GET, url);
  assertTrue(responseCode > 0);

  requestClient.flush();

  String payload = requestClient.consumePayload();
  assertEqual(payload, "");
}

#endif
