#ifndef SERIALREADER_HPP
#define SERIALREADER_HPP

#include "./../serial/serialdevbase.hpp"


class SerialReader
{
public:
    SerialReader(SerialDevBase   *port);
    bool    readByte(char *chBytes, int iCnt);
private:
    SerialDevBase   *m_port;
};

#endif // SERIALREADER_HPP
