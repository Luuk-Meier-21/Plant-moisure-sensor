#ifndef StreamReader_h
#define StreamReader_h

class StreamReader
{
    Stream *serial_stream;
    String data;

public:
    StreamReader(Stream *stream) : serial_stream(stream) {}

    void readAvailable()
    {
        while (serial_stream->available())
        {
            delay(3); // delay to allow buffer to fill
            if (serial_stream->available() > 0)
            {
                char c = serial_stream->read(); // gets one byte from serial buffer
                data += c;                      // makes the string readString
            }
        }
    }

    boolean hasData()
    {
        return data.length() > 0;
    }

    void flushData()
    {
        data = "";
    }

    String getData()
    {
        return data;
    }

    String extractData()
    {
        String current_data = getData();
        flushData();

        return current_data;
    }
};

#endif
