#include <stdio.h>
#include <string>
#include <math.h>

typedef struct DataPoint
{
	unsigned short number;
	unsigned short type;
	double x;
	double y;
	double z;
	double ux;
	double uy;
	double uz;
	double rz;
	double ry;
} DataPoint;


class DataParser
{
private:
	FILE* m_pFile;

	double m_Convert;
public:
	DataParser(double convert);
	~DataParser();

	int OpenFile(std::string fileName);
	int CloseFile();
	int GetNextDataPoint(DataPoint& data);
};
