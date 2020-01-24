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

// g++ bay_all.cpp -o bay_all
// ./bay_all r_nr_report.txt 1.txt
//
// purpose is to determine the prob of multiple targets on massive scale 
// e.g., ICD10_I60 to I69 -> ICD10_Stroke
// https://apps.who.int/classifications/apps/icd/icd10online2003/fr-icd.htm?gi60.htm+

char icd[500000][100][20];
int num_cols[500000];

int main(int argc, char* argv[]) {
string sentence;
int num=100;
int h=0;
int standard=20;
char * pos2;
int count[100];
int p_A=0;
int p_B=0;
int p_B_A=0;
double p_A_B=0.0;
int flag=0;
int rows=500000;
int columns=100;
int s=0;
int r=0;
double d_p_A=0.0;
double d_p_B=0.0;
double d_p_B_A=0.0;

system("./randomize_records nr_report.txt");

char** word = new char*[num];
for (int s = 0; s < num; s++)
	{
	word[s] = new char[standard];
	//strcpy(word[s],"test");
	}

char** word2 = new char*[num];
for (int s = 0; s < num; s++)
	{
	word2[s] = new char[standard];
	//strcpy(word2[s],"test");
	}

int i=0; int length=0;
char temp_word[standard];
char new_word[standard];

for (int t = 0; t < columns; t++)
	{
	for (int s = 0; s < rows; s++)
		{
		strcpy(icd[s][t],"0");
		}
	}

ifstream in(argv[1]); 		
ofstream out(argv[2]); 	
//std::ofstream out;
//out.open("final.txt", std::ios_base::app);

int x=0;
while(!in.eof())  // read in the matrix
    {
	getline(in,sentence); 
	//cout << sentence << "\n"; //exit(1); 
	h=0;
	char * char_array = new char [sentence.length()+ 1];	
	strcpy (char_array, sentence.c_str());
	char delimiters[2];
	strcpy(delimiters,"\t");
    pos2 = strtok (char_array, delimiters);
	
  	while (pos2 != NULL)
   		{
   		word2[h]=(pos2);
   		pos2 = strtok (NULL, delimiters);
		h=h+1;
  		}

	flag=0;
	for (int s=0; s<(h);s++)  // new_word=stroke
		{
 //  	if (strcmp(word2[s],"ICD10_I21")==0) { strcpy (word2[s],new_word); flag=flag+1;}
 //  	if (strcmp(word2[s],"ICD9_410")==0) { strcpy (word2[s],new_word); flag=flag+1;}
		if (flag==1) {strcpy(icd[x][s],word2[s]);} 
 		if (strcmp (word2[s],new_word)!=0) {strcpy(icd[x][s],word2[s]);}		 
		}
 		
	num_cols[x]=h; // 
	x=x+1; 
    }
/*  
for (int s = 0; s < x-2; s++)  // print out matrix to see if correct
	{
	for (int t = 0; t < num_cols[s]; t++)  
		{
		cout << icd[s][t] << "\t";
		}
	cout << "\n";
}
cout << "\n" <<flush;
*/

// extract one record
	for (int t = 1; t < num_cols[x-2]+1; t++)  
		{
//		cout << icd[x-2][t-1] << "\t";
		strcpy (word[t-1],icd[x-2][t]);
		} 
//	cout << "\n";
/*	
	for (int t = 0; t < num_cols[x-2]-1; t++)  
		{
		cout << word[t] << "\t";
		} 
	cout << "\n";
*/	
//exit(1);
// matrix has been read in....  now for the stats 
// matrix has been read in....  now for the stats 

// determine the num patients with target (i.e., obesity aka new_word)
for (int q = 0; q < (num_cols[x-2]-1); q++) 
	{
	for (int r = 0; r < (num_cols[x-2]-1); r++) 
		{
		p_A=0;p_B_A=0;p_B=0;d_p_A=0.0;d_p_B=0.0;d_p_B_A=0.0;p_A_B=0.0;
		for (int s = 0; s < (x-2); s++)  
			{
			for (int t = 0; t < num_cols[s]; t++)  
				{
				if (strcmp(icd[s][t],word[q])==0) 
					{
					p_A=p_A+1;
					}
				if (strcmp(icd[s][t],word[r])==0) 
					{
					p_B=p_B+1;
					for (int q1 = 0; q1 < num_cols[s]; q1++)  
						{
						if (strcmp(icd[s][q1],word[q])==0) 
							{
							p_B_A=p_B_A+1;
							}
						}
					}
				}
			}

		d_p_A=double(double(p_A)/x);  // 3/10
		d_p_B=double(double(p_B)/x);; // 2/10
		d_p_B_A=double(double(p_B_A)/p_A);  //2/3

		if (d_p_B!=0.0)
			{
			p_A_B=double(double(d_p_B_A*d_p_A)/d_p_B);
			}
		if ((p_A_B!=0.0) && strcmp(word[q],word[r])!=0)
		//if (strcmp(word[q],word[r])!=0)
			{
			cout << "Prob_" << word[q] << "|" << word[r] <<  "\t";
			out << "Prob_" << word[q] << "|" << word[r] <<  "\t";
		//	cout << p_A << "\t" << p_B << "\t" <<  p_B_A << "\n";  // count1 is number of stroke patients  P(A)
		//	cout << d_p_A << "\t" << d_p_B << "\t" <<  d_p_B_A << "\t" <<  p_A_B << "\n";  // count1 is number of stroke patients  P(A)
		cout <<  p_A_B << "\t" << p_B << "\n";  // count1 is number of stroke patients  P(A)
		out <<  p_A_B << "\t" << p_B << "\n";  // count1 is number of stroke patients  P(A)
			}
		}
	}
//exit(1);
/*
//cout << "i=\t" << i << "\n";
if (i>3)  // now the combinations
	{
	p_B_A=0;p_B=0;d_p_B=0.0;d_p_B_A=0.0;p_A_B=0.0;
	for (int s = 0; s < x; s++)  
		{
		for (int t = 0; t < num_cols[s]; t++)  
			{
			if (strcmp(icd[s][t],word[2])==0) 
				{
				for (int q = 0; q < num_cols[s]; q++)  
					{
					if (strcmp(icd[s][q],word[3])==0) 
						{
						for (int w = 0; w < num_cols[s]; w++)  
							{
							if (strcmp(icd[s][w],word[4])==0) 
								{
								p_B_A=p_B_A+1;
								}
							}
						}
					}
				}
			}
	
		for (int t = 0; t < num_cols[s]; t++)  
			{
			if (strcmp(icd[s][t],word[3])==0) 
				{
				for (int w = 0; w < num_cols[s]; w++)  
					{
					if (strcmp(icd[s][w],word[4])==0) 
						{
						p_B=p_B+1;
						}
					}
				}
			}
		}

	d_p_B=double(double(p_B)/x);;
	d_p_B_A=double(double(p_B_A)/p_A);;
	if (d_p_B!=0.0)
		{
		p_A_B=double(double(d_p_B_A*d_p_A)/d_p_B);
		}
	if (p_A_B!=0.0)
		{
		cout << "Prob_" << word[2] << "|" << word[3] <<  "_"<< word[4]<<  "\t";
 //   	cout << p_A << "\t" << p_B << "\t" <<  p_B_A << "\n";  // count1 is number of stroke patients  P(A)
//		cout << d_p_A << "\t" << d_p_B << "\t" <<  d_p_B_A << "\t" <<  p_A_B << "\n";  // count1 is number of stroke patients  P(A)
	    cout <<  p_A_B << "\t" << p_B << "\n";  // count1 is number of stroke patients  P(A)
		}
	}
*/
return 0;
}
