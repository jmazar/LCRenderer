#include <iostream>
#include "DataParser.hpp"
int main()
{

	DataParser parser(57.2957795);

	DataPoint point;

	int i = 0;
	parser.OpenFile("traj.inp");
	while(parser.GetNextDataPoint(point) > 0)
	{
		i++;
		printf("%d\n", i);
	}
	
	parser.CloseFile();
	return 0;
}