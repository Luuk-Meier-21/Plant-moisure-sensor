#ifndef DiscoveringWiFiCLient_test_h
#define DiscoveringWiFiCLient_test_h

#include <AUnitVerbose.h>

#include "../../src/WiFiNetwork/WiFiNetwork.h"
#include "../../src/DynamicWiFiNetwork/DynamicWiFiNetwork.h"
#include "../../src/DiscoveringWiFiClient/DiscoveringWiFiClient.h"

#define TEST

#include "../../src/MockESP8266Class/MockESP8266Class.h"

#include "stddef.h"
using namespace std;

test(DiscoveringWiFiClient_scan)
{
  const size_t network_count = 4;

  WiFiNetwork a("ssid-1", "pass-1");
  WiFiNetwork b("ssid-2", "pass-2");
  WiFiNetwork c("ssid-3", "pass-3");
  WiFiNetwork d("network-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b, c, d};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
  DiscoveringWiFiClient<network_count> discoveringNetworkClient(mockWiFi, &dynamic_network);

  bool foundNetwork = discoveringNetworkClient.scan();
  assertTrue(foundNetwork);
}

test(DiscoveringWiFiClient_begin)
{
  const size_t network_count = 2;

  WiFiNetwork a("network-2", "pass-3");
  WiFiNetwork b("network-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
  DiscoveringWiFiClient<network_count> discoveringNetworkClient(mockWiFi, &dynamic_network);

  bool foundNetwork = discoveringNetworkClient.scan();
  if (!foundNetwork)
    printf("No network found");
  bool triedConnection = discoveringNetworkClient.beginConnection();
  assertTrue(triedConnection);
}

test(DiscoveringWiFiClient_connection_found)
{
  auto onConnectionTick = []()
  {
    delay(200);
  };

  const size_t network_count = 2;

  WiFiNetwork a("network-2", "pass-3");
  WiFiNetwork b("network-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
  DiscoveringWiFiClient<network_count> discoveringNetworkClient(mockWiFi, &dynamic_network);

  bool foundNetwork = discoveringNetworkClient.scan();
  assertTrue(foundNetwork);

  discoveringNetworkClient.beginConnection();

  bool foundConnection = discoveringNetworkClient.awaitConnection(onConnectionTick, 300);
  assertTrue(foundConnection);
}

test(DiscoveringWiFiClient_connection_notFound)
{
  auto onConnectionTick = []() {

  };

  const size_t network_count = 2;

  WiFiNetwork a("unknown-network-2", "pass-3");
  WiFiNetwork b("unknown-network-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
  DiscoveringWiFiClient<network_count> discoveringNetworkClient(mockWiFi, &dynamic_network);

  bool foundNetwork = discoveringNetworkClient.scan();
  assertFalse(foundNetwork);

  discoveringNetworkClient.beginConnection();

  bool foundConnection = discoveringNetworkClient.awaitConnection(onConnectionTick, 100);
  assertFalse(foundConnection);
}
#endif