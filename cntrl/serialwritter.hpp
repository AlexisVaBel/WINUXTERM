#ifndef SERIALWRITTER_HPP
#define SERIALWRITTER_HPP

#include "../serial/serialdevbase.hpp"

class SerialWritter
{
public:
    SerialWritter(SerialDevBase   *port);
private:
    SerialDevBase   *m_port;
};

#endif // SERIALWRITTER_HPP
