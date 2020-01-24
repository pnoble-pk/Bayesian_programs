// Designed by Peter A Noble December 2020 panoble2017@gmail.com or pnoble@prokarma.com
// Purpose is to extract the probabilities from ESRD using multiple priors
#include <chrono>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<cstring>
#include <thread>
using namespace std;

// g++ randomize_records.cpp -o randomize_records
// ./randomize_records nr_report.txt 
//
//
// purpose is to randomize records

int main(int argc, char* argv[]) {
string sentence;

double RAND;
srand (time(NULL));
//RAND = rand();  

string str= "sed 's/^[^\t]*[\t]//' out2.txt >temp.txt";
const char *command = str.c_str(); 

ifstream in(argv[1]); 		
ofstream out("out.txt"); 	

int x=0;
while(!in.eof())  // read in the matrix
    {
    RAND = rand() % 1000000 + 1;  
	getline(in,sentence); 
	out << double(RAND) << "\t" << sentence << "\n" << flush; //exit(1);
	}	

system("sort -h -k1 out.txt -o out2.txt");
system("sleep 1");
system(command); 
system("sleep 1");
system("rm out.txt"); 
system("rm out2.txt"); 
system("cp temp.txt r_nr_report.txt"); 
system("sleep 1");
system("rm temp.txt"); 
system("wait");

return 0;
}
