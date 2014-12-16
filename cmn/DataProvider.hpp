#ifndef DATAPROVIDER_HPP
#define DATAPROVIDER_HPP
class DataProvider{
public:
    virtual         bool          writeData(const char * chBuf, int iLng)=0;
    virtual         bool          readData(char *chBytes, int iCnt)=0;
};

#endif // DATAPROVIDER_HPP
