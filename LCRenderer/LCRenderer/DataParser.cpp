#include "DataParser.hpp"


DataParser::DataParser(double convert)
	: m_pFile(NULL),
	m_Convert(convert)
{
}

DataParser::~DataParser()
{
	if(m_pFile)
	{
		fclose(m_pFile);
	}
}

int DataParser::OpenFile(std::string fileName)
{
	m_pFile = fopen(fileName.c_str(), "r");

	if(m_pFile)
	{
		return 0;
	}

	return 1;
}

int DataParser::CloseFile()
{
	return fclose(m_pFile);
}

int DataParser::GetNextDataPoint(DataPoint& data)
{
	int readStatus = 0;
	long float temp;
	readStatus = fscanf_s(m_pFile, "%d", &data.number);
	data.number -= 1;
	readStatus = fscanf(m_pFile, "%d", &data.type);
	readStatus = fscanf(m_pFile, "%lf", &data.x);
	readStatus = fscanf(m_pFile, "%lf", &data.y);
	readStatus = fscanf(m_pFile, "%lf", &data.z);
	readStatus = fscanf(m_pFile, "%lf", &data.ux);
	readStatus = fscanf(m_pFile, "%lf", &data.uy);
	readStatus = fscanf(m_pFile, "%lf", &data.uz);
	readStatus = fscanf(m_pFile, "%lf", &temp);

	data.rz = atan2(data.uy, data.ux) * m_Convert;
	data.ry = atan2(data.uz, sqrt(data.ux*data.ux+data.uy*data.uy)) * m_Convert;

	return readStatus;
	
}