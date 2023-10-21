#include <AUnitVerbose.h>

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
