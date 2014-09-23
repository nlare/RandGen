#include "RNG.cpp"

int main(int argc, char **argv) {
	char *filename;

	if(argc<3)	{
		cerr << "Set the command line arguments" << endl;
	}	else	{
		cout << "Execute: ";
		for(int i=0;i<argc;i++)	{
			if(strcmp(argv[i], "-o") == 0)	{
				if((i+1) < argc)	{
					cout << argv[i] << " " << argv[i+1];
					filename = new char [strlen(argv[i])];
					strcpy(filename, argv[i+1]);
				}
				else cerr << "try to use --help" << endl;
			}
		}
	}
	RNG Generator(filename, "mt19937");
	Generator.setSize(1000000000);
	//Generator.setGenerator("mt19937");
	Generator.generateMersenne();
	Generator.writeToFile("1e9.dat");
	delete filename;
	return 0;
}
