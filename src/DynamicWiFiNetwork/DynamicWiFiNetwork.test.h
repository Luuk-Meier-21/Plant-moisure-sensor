#ifndef DynamicWiFiNetwork_test_h
#define DynamicWiFiNetwork_test_h

#include <AUnitVerbose.h>

#include "../../src/WiFiNetwork/WiFiNetwork.h"
#include "../../src/DynamicWiFiNetwork/DynamicWiFiNetwork.h"

#include "stddef.h"
using namespace std;

test(DynamicWiFiNetwork_count)
{
  const size_t network_count = 3;

  WiFiNetwork a("ssid-1", "pass-1");
  WiFiNetwork b("ssid-2", "pass-2");
  WiFiNetwork c("ssid-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b, c};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);

  assertEqual(dynamic_network.count(), network_count);
}

test(DynamicWiFiNetwork_find_found)
{
  const size_t network_count = 3;

  WiFiNetwork a("ssid-1", "pass-1");
  WiFiNetwork b("ssid-2", "pass-2");
  WiFiNetwork c("ssid-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b, c};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);

  for (size_t i = 0; i < network_count; i++)
  {
    auto target_network = private_networks[i];
    WiFiNetwork n = dynamic_network.find(target_network.getSsid());
    assertEqual(n.getSsid(), target_network.getSsid());
    assertEqual(n.getPassword(), target_network.getPassword());
  }
}

test(DynamicWiFiNetwork_find_notFound)
{
  const size_t network_count = 3;

  WiFiNetwork a("ssid-1", "pass-1");
  WiFiNetwork b("ssid-2", "pass-2");
  WiFiNetwork c("ssid-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b, c};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);

  WiFiNetwork n = dynamic_network.find("unknown-ssid");

  assertFalse(n.isValid());
}

test(DynamicWiFiNetwork_has_found)
{
  const size_t network_count = 3;

  WiFiNetwork a("ssid-1", "pass-1");
  WiFiNetwork b("ssid-2", "pass-2");
  WiFiNetwork c("ssid-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b, c};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);

  for (size_t i = 0; i < network_count; i++)
  {
    auto target_network = private_networks[i];
    bool found = dynamic_network.has(target_network.getSsid());
    assertTrue(found);
  }
}

test(DynamicWiFiNetwork_has_notFound)
{
  const size_t network_count = 3;

  WiFiNetwork a("ssid-1", "pass-1");
  WiFiNetwork b("ssid-2", "pass-2");
  WiFiNetwork c("ssid-3", "pass-3");
  WiFiNetwork private_networks[network_count] = {a, b, c};
  DynamicWiFiNetwork<network_count> dynamic_network(private_networks);

  bool found = dynamic_network.has("ssid-4");
  assertFalse(found);
}
#endif