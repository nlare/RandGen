/*
 * RandGen.cpp
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: nlare
 */

#include "RNG.h"

using namespace std;

RNG::RNG(string _RNGFileName, string _RNGName) {
	N = 0;
	if(strcmp(_RNGName.c_str(), "std") == 0) {
		srand(time(NULL));
	}
	out_name = new char [strlen(_RNGFileName.c_str()+10)];
	strcpy(out_name,("output/"+_RNGFileName).c_str());
	cout << endl << "OUT_FILE = " << out_name << endl;
}

RNG::~RNG() {
	cout << endl <<  "End of generate" << endl;
}

int RNG::setSize(int _N) {
	N= _N;
	return 0;
}

int RNG::getSize() {
	return N;
}

void RNG::generateSTDLIB() {
	srand(time(NULL));
	ss.clear();
	if(N<=0)	{
		cerr << "N<=0, pls, set count of num to generate\nN = " << endl;
		cin >> N;
	}
	for (int num=0; num<=N; num++) {
		ss << (1 + rand() % 999)/1000.0 << endl;
	}
}

void RNG::generateMersenne() {
	int count = 0, num;
	CRandomMersenne Mersenne(time(NULL));
	seed = 1 + rand() % 100000;
	Mersenne.RandomInit(seed);
	ss.clear();
	ss_time.clear();
	if(N<=0)	{
		cerr << "N<=0, pls, set count of num to generate\nN = " << endl;
		cin >> N;
	}
//#ifndef _OPENMP
//	cout << "OMP is not defined" << endl;
//#else
//	omp_set_num_threads(4);
//	cout << "num threads is " << omp_get_num_threads() << endl;
//#pragma omp parallel for private(num)
//{
	for(num=0; num<=N; num++)    {

		ss << Mersenne.IRandomX(0,999)/1000.0 << endl;
		count++;
		t = clock();
		if((int(t))%1000000==0)	{
			cout << "i'am generate about " << count << " random nums for " << (float(t))/CLOCKS_PER_SEC << " sec" << endl;
		}
//}
	}
//#endif
	time_gen = (float(t))/CLOCKS_PER_SEC;
	ss_time << "Time of generate " << N << " numbers about " << time_gen << " sec" << endl;
}

int RNG::writeToFile(string _out_name)	{
	string buffer = ss.str();
	time_name = new char [strlen(_out_name.c_str())+10];
	strcpy(time_name, _out_name.c_str());
	strcat(time_name, ".time");
	out_file.open(_out_name.c_str(), ios::trunc);
	out_time.open(time_name, ios::out);
	buffer = ss.str();

	t = clock();
	if(out_file.good())	{
		cout << "writing to " << _out_name << "..." << endl;
		out_file << buffer;
	}
	t = clock() - t;
	time_write = float(t)/CLOCKS_PER_SEC;
	ss_time << "Time writing in to file " << time_write << " sec" << endl;
	ss_time << "All time run is " << time_gen+time_write << " sec" << endl;

	buffer.clear();
	buffer = ss_time.str();
	cout << buffer;

	if(out_file.good())	{
		out_time << buffer;
	}
	out_file.close();
	out_time.close();
	return 0;
}

int RNG::writeToFile()	{
	out_file.open(out_name, ios::trunc);
	string buffer = ss.str();

	t = clock();
	if(out_file.good())	{
		cout << "writing to " << out_name << "..." << endl;
		out_file << ss.str();
	}
	t = clock() - t;

	time_write = float(t)/CLOCKS_PER_SEC;
    ss_time << "Time writing in to file " << time_write << " sec" << endl;
    ss_time << "All time run is " << time_gen+time_write << " sec" << endl;

	buffer.clear();
	buffer = ss_time.str();
	cout << buffer;

	if(out_file.good())	{
		out_time << buffer;
	}

	out_file.close();
	out_time.close();
	return 0;
}
