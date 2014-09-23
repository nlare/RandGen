/*
 * RandGen.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: nlare
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <omp.h>
#include "mersenne.cpp"

#ifndef RNG_H_
#define RNG_H_

class RNG {
public:
	RNG(std::string, std::string);
	~RNG(void);
	int setGenerator(char*);
	int setSize(int);
	int setRNGFile(char*);
	int setTimeFile(char*);
	int setSeedMersenne(int);

	int getGenerator();
	int getSize();
	int getRNGFile();
	int getTimeFile();
	int getSeedMersenne();

	void generateMersenne();
	void generateSTDLIB();
	int writeToFile(std::string);
	int writeToFile();
private:
	std::ofstream out_file, out_time;
	char *out_name, *time_name;
	std::stringstream ss, ss_time;
	clock_t t;
	float time_gen, time_write;
	int seed;
	int N;
};

#endif /* RANDGEN_H_ */
