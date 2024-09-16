#ifndef WiFiNetwork_test_h
#define WiFiNetwork_test_h

#include "../../src/WiFiNetwork/WiFiNetwork.h"

#include "stddef.h"
using namespace std;

test(WiFiNetwork_constructor)
{
  WiFiNetwork network("name", "pass");

  assertTrue(network.isValid());
}

test(WiFiNetwork_empty_constructor)
{
  WiFiNetwork network = WiFiNetwork::empty();

  assertFalse(network.isValid());
}

test(WiFiNetwork_getSsid)
{
  String ssid = "12345-ssid";
  WiFiNetwork network(ssid, "pass");

  assertEqual(network.getSsid(), ssid);
}

test(WiFiNetwork_getPassword)
{
  String pass = "12345-pass";
  WiFiNetwork network("ssid", pass);

  assertEqual(network.getPassword(), pass);
}

#endif