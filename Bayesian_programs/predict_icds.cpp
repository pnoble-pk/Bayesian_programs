#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<cstring>

using namespace std;


// g++ predict_icds.cpp -o predict_icds
// ./predict_icds p_data.txt ICD10_E78 ICD10_I10 ICD10_I11 ICD10_I21 ICD10_I25 ICD10_I27 ICD10_I31 ICD10_I34 ICD10_I48 ICD10_I50 ICD10_J96 ICD10_K21 ICD10_M19 ICD10_R06 ICD10_R07 ICD10_Z79 ICD10_Z86 ICD10_Z95 MSDRG_280 MSDRG_291 

//./predict_icds p_data.txt ICD10_E46 ICD10_E83 ICD10_E86 ICD10_E87 ICD10_F11 ICD10_F17 ICD10_F41 ICD10_G89 ICD10_G93 ICD10_I10 ICD10_I13 ICD10_I42 ICD10_I50 ICD10_I87 ICD10_I95 ICD10_J01 ICD10_J32 ICD10_J44 ICD10_J69 ICD10_K04 ICD10_K56 ICD10_L03 ICD10_L30 ICD10_L97 ICD10_M40 ICD10_M41 ICD10_M47 ICD10_M54 ICD10_M62 ICD10_M79 ICD10_N17 ICD10_N18 ICD10_R19 ICD10_R29 ICD10_R53 ICD10_R68 ICD10_R91 ICD10_S91 ICD10_W19 ICD10_Z68 ICD10_Z80 ICD10_Z91 MSDRG_683 

//./predict_icds p_data.txt ICD10_H18 ICD10_H25 ICD10_H40 ICD10_I10 ICD10_Z96  
//./predict_icds p_data.txt ICD10_H40 ICD10_I10 ICD10_M47 ICD10_M60 ICD10_M79 ICD10_N30 ICD10_R10 ICD10_Z87 ICD10_Z96 ICD10_Z99 

//a//./predict_icds p_data.txt ICD10_E03 ICD10_E11 ICD10_E78 ICD10_F31 ICD10_F41 ICD10_K21 ICD10_K42 ICD10_K57 ICD10_K80 ICD10_M25 ICD10_R03 ICD10_Z87 ICD10_Z88 ICD10_Z96 ICD10_Z98 
//a//./predict_icds p_data.txt ICD10_B20 ICD10_E21 ICD10_E78 ICD10_F17 ICD10_G89 ICD10_I10 ICD10_I25 ICD10_I42 ICD10_J44 ICD10_K08 ICD10_M25 ICD10_M79 ICD10_R41 ICD10_Z21 ICD10_Z79 ICD10_Z95 

// purpose is to calculate predictions using probability 

int main(int argc, char*argv[]) {

ifstream in(argv[1]); 		
ifstream in2("sort.txt"); 		
ofstream out("edges.csv"); 	
ofstream out2("unsorted.txt"); 	
ofstream out3("nodes.csv"); 	

int num=300000;
int standard=20;
double p_threshold=0.5;  //0.4 is great
int c_threshold=2;
double prob[num];
int count[num];
int number[num];
char** icd = new char*[num];
for (int s = 0; s < num; s++)
	{
	icd[s] = new char[standard];
	//strcpy(word[s],"test");
	}

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
	//strcpy(word[s],"test");
	}

char** word3 = new char*[num];
for (int s = 0; s < num; s++)
	{
	word3[s] = new char[standard];
	//strcpy(word[s],"test");
	}
char word4[standard];
char temp_word[standard];
strcpy(temp_word,"test");
int x=0;
int i=0;
int d=0;

while(argv[i]!=NULL)
	{
    strcpy(icd[i],argv[i]);      
    i++;
    }

for (int t = 2; t < i; t++)
	{
	cout << t-1 << "\t" << icd[t] << "\n";
	}
cout << "\n"; //exit(1);

while(!in.eof())  
	{
	in >> prob[x];      //target
	in >> count[x];      //target
	in >> word[x];      //target
	in >> word2[x];		//prior
	x=x+1;	
	}	
cout << "data read in\n\n";

// ICD10_F03	ICD10_R10	ICD10_R41	ICD10_R45
// ICD10_E46	ICD10_E83	ICD10_E86	ICD10_E87	ICD10_F11	ICD10_F17	ICD10_F41	ICD10_G89	ICD10_G93	ICD10_I10	ICD10_I13	ICD10_I42	ICD10_I50	ICD10_I87	ICD10_I95	ICD10_J01	ICD10_J32	ICD10_J44	ICD10_J69	ICD10_K04	ICD10_K56	ICD10_L03	ICD10_L30	ICD10_L97	ICD10_M40	ICD10_M41	ICD10_M47	ICD10_M54	ICD10_M62	ICD10_M79	ICD10_N17	ICD10_N18	ICD10_R19	ICD10_R29	ICD10_R53	ICD10_R68	ICD10_R91	ICD10_S91	ICD10_W19	ICD10_Z68	ICD10_Z80	ICD10_Z91	MSDRG_683	
out << "from,to,weight,count,c,\n";
out3 << "ids,c,type\n";
int y=0;
int c=0;
for (int s = 2; s < i; s++)
	{
	for (int t = 0; t < x; t++)
		{
		if (strcmp(word2[t],icd[s])==0)
			{
			c=0;
			if ((prob[t]> p_threshold) && (count[t]> c_threshold))
				{
				for (int s1 = 2; s1 < i; s1++)
					{
					if (strcmp(icd[s1],word[t])==0)
						{
						//cout << icd[s1]; 
						//cout << "confirmed!"; 
						c=1;
						}
					}
				//cout << icd[s] << " with " << prob[t] << " predicts" << count[t] << "\t" << word[t] << "\t";
				cout << icd[s] << " with " << prob[t] << " predicts " << word[t] << " ";
				if (c==1) { cout << "confirmed!"; }
				 out << icd[s] << ","  << word[t] << "," << prob[t]*100 <<  "," << count[t] << "," << "\n";
				strcpy(word3[y],icd[s]); y=y+1;
				strcpy(word3[y],word[t]); number[y]=c; y=y+1;
				cout << "\n";
				}
			}	
		}
	}

for (int s = 0; s < y; s++)
	{
	if (number[s]==1) 
		{
		for (int t = 0; t < y; t++)
			{
			if (strcmp(word3[s],word3[t])==0)
				{
				number[t]=1;
				}
			}
	//word3[s] << " " << number[s] << "\n";
		}
	}


for (int s = 0; s < y; s++)
	{
	out2 << word3[s] << " " << number[s] << "\n";
	}
	out2 << flush;
	system("sort unsorted.txt > sort.txt");

for (int s = 0; s < y; s++)
	{
	in2 >> word4;
	in2 >> c; 
	d=0;
	for (int t = 0; t < i; t++)
		{
		if (strcmp(word4,argv[t])==0)
			{
			d=1;
			}
		}
	if (strcmp(temp_word,word4)!=0)
		{
		out3 << word4 << "," << c << "," << d << "\n" << flush;
		}
	//if (s==0) {cout << word4 << "\n" << flush;}
	strcpy(temp_word,word4);
	}
//system("rm sort.txt");
//system("rm unsorted.txt");
//system("rm out.txt");
	

return 0;
}
