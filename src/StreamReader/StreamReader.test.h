#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

#include "../../src/StreamReader/StreamReader.h"

#include "stddef.h"
using namespace std;

String getStringOfLength(int count)
{
  char data[count];
  for (size_t i = 0; i < (size_t)count; i++)
  {
    data[i] = 'a';
  }
  return data;
}

class MockSerial : public Stream
{
  int index;

public:
  MockSerial(int availableCount) : index(availableCount){};
  MockSerial() : index(5){};
  ~MockSerial(){};
  virtual int available()
  {
    return index;
  }
  virtual int read()
  {
    index = index > 0 ? index - 1 : 0;
    return 'a';
  }

  virtual int peek()
  {
    return 0;
  };

  virtual size_t write(uint8_t a)
  {
    (void)a;
    return 0;
  }
};

test(SensorService_flushData)
{
  MockSerial mock_serial;
  StreamReader serial_reader(&mock_serial);

  serial_reader.readAvailable();
  serial_reader.flushData();
  String data = serial_reader.getData();

  assertEqual(data, "");
}

test(SensorService_getData_5)
{
  int count = 5;
  MockSerial mock_serial(count);
  StreamReader serial_reader(&mock_serial);

  serial_reader.readAvailable();
  String data = serial_reader.getData();

  assertEqual(data, getStringOfLength(count));
}

test(SensorService_getData_10)
{
  int count = 5;
  MockSerial mock_serial(count);
  StreamReader serial_reader(&mock_serial);

  serial_reader.readAvailable();
  String data = serial_reader.getData();

  assertEqual(data, getStringOfLength(count));
}

test(SensorService_getData_15)
{
  int count = 5;
  MockSerial mock_serial(count);
  StreamReader serial_reader(&mock_serial);

  serial_reader.readAvailable();
  String data = serial_reader.getData();

  assertEqual(data, getStringOfLength(count));
}

test(SensorService_extractData)
{
  int count = 5;
  MockSerial mock_serial(count);
  StreamReader serial_reader(&mock_serial);

  serial_reader.readAvailable();
  String data = serial_reader.extractData();

  assertEqual(data, getStringOfLength(count));

  String empty_data = serial_reader.getData();

  assertEqual(empty_data, "");
}
