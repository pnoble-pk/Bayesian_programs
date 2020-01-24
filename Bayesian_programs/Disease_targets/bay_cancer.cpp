// Designed by Peter A Noble December 2019 panoble2017@gmail.com or pnoble@prokarma.com
// Purpose is to extract the probabilities from matrix using multiple priors

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<cstring>
using namespace std;

// g++ bay_cancer.cpp -o bay_cancer
// ./bay_cancer nr_report.txt ICD10_Cancer MSDRG_917 ICD10_A41 
// ./bay_cancer nr_test.txt IICD10_Cancer ICD10_F11 ICD10_B96

// purpose is to determine the prob of multiple targets on massive scale 
// Prob_ICD10_Stroke|MSDRG_917
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

while(argv[i]!=NULL)
	{
    strcpy(temp_word,argv[i]); 
    length=strlen(temp_word);
    if ((i==2) && (length>9)) 
    	{
		for (int q = 0; q < 9; q++)
			{
			new_word[q]=temp_word[q];
			}
		new_word[9]='\0';
     	strcpy(temp_word,new_word);      
   		}
    strcpy(word[i],temp_word);      
    i++;
    }

/*
for (int t = 2; t < i; t++)
	{
	cout << t << "\t" << word[t] << "\n";
	}
//cout << "\n";
*/

for (int t = 0; t < columns; t++)
	{
	for (int s = 0; s < rows; s++)
		{
		strcpy(icd[s][t],"0");
		}
	}

/*
char** patient_id = new char*[rows];
for (int s = 0; s < rows; s++)
	{
	patient_id[s] = new char[standard];
	strcpy(patient_id[s],"0");
	}
*/
ifstream in(argv[1]); 		
ofstream out(argv[2]); 	

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
	for (int s=1; s<(h);s++)  // new_word=stroke
		{
   		if (strcmp(word2[s],"ICD10_C00")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C01")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C02")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C03")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C04")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C05")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C06")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C07")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C08")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C09")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C10")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C11")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C12")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C13")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C14")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C15")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C16")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C17")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C18")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C19")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C20")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C21")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C22")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C22")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C23")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C24")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C25")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C26")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C27")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C28")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C29")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C30")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C31")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C32")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C33")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C34")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C35")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C36")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C37")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C38")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C39")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C40")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C41")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C42")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C43")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C44")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C45")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C46")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C47")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C48")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C49")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C50")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C51")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C52")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C53")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C54")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C55")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C56")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C57")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C58")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C59")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C60")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C61")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C62")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C63")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C64")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C65")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C66")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C67")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C68")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C69")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C70")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C71")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C72")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C73")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C74")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C75")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C76")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C77")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C78")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C79")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C80")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C7A")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
    	if (strcmp(word2[s],"ICD10_c81")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C82")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C83")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C84")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
   		if (strcmp(word2[s],"ICD10_C85")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
  		if (strcmp(word2[s],"ICD10_C86")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
  		if (strcmp(word2[s],"ICD10_C87")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
  		if (strcmp(word2[s],"ICD10_C88")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
  		if (strcmp(word2[s],"ICD10_C89")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
  		if (strcmp(word2[s],"ICD10_C90")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C91")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C92")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C93")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C94")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C95")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C96")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
 		if (strcmp(word2[s],"ICD10_C97")==0)  { strcpy (word2[s],new_word);flag=flag+1;}

 		if (strcmp(word2[s],"ICD9_172")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_174")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_239")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_153")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_154")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_235")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_180")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_182")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_183")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_184")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_236")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_185")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_186")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_187")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_140")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_141")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_142")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_143")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_144")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_145")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_146")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_147")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_148")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_149")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_160")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_161")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_162")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_195")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_173")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_238")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_150")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_151")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_152")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_152")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_155")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_156")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_157")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_158")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_159")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_235")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_162")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_162")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_239")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_163")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_164")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_195")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_199")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_238")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_239")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_196")==0)  { strcpy (word2[s],new_word);flag=flag+1;}
		if (strcmp(word2[s],"ICD9_197")==0)  { strcpy (word2[s],new_word);flag=flag+1;}  // from Weiner 2009
   	//if (s==0)   { strcpy(patient_id[x],word2[s]);}
		if (flag==1) {strcpy(icd[x][s-1],word2[s]);} 
 		if (strcmp (word2[s],new_word)!=0) {strcpy(icd[x][s-1],word2[s]);}		 
		}
	num_cols[x]=h-1; // because excludes patient id
	x=x+1; 
    }
//    cout << x << "\n";  // number of patients
//exit(1);

/*
for (int s = 0; s < x; s++)  // print out matrix to see if correct
	{
//	cout << patient_id[s] << "\t";
	for (int t = 0; t < num_cols[s]; t++)  
		{
		cout << icd[s][t] << "\t";
		}
	cout << "\n";
}
exit(1);
*/

// matrix has been read in....  now for the stats 

// matrix has been read in....  now for the stats 

// determine the num patients with target (i.e., obesity aka new_word)
for (int r = 3; r < i; r++) // 3 -> ICD10_F11 the prior
	{
	p_A=0;p_B_A=0;p_B=0;d_p_A=0.0;d_p_B=0.0;d_p_B_A=0.0;p_A_B=0.0;
	for (int s = 0; s < x; s++)  
		{
	//	cout << patient_id[s] << "\t";
		for (int t = 0; t < num_cols[s]; t++)  
			{
			if (strcmp(icd[s][t],word[2])==0) 
				{
				p_A=p_A+1;
				}
			if (strcmp(icd[s][t],word[r])==0) 
				{
				p_B=p_B+1;
				for (int q = 0; q < num_cols[s]; q++)  
					{
					if (strcmp(icd[s][q],word[2])==0) 
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
	if (p_A_B!=0.0)
	{
	cout << "Prob_" << word[2] << "|" << word[r] <<  "\t";
//	cout << p_A << "\t" << p_B << "\t" <<  p_B_A << "\n";  // count1 is number of stroke patients  P(A)
//	cout << d_p_A << "\t" << d_p_B << "\t" <<  d_p_B_A << "\t" <<  p_A_B << "\n";  // count1 is number of stroke patients  P(A)
	cout <<  p_A_B << "\t" << p_B << "\n";  // count1 is number of stroke patients  P(A)
	}
}
//exit(1);
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
return 0;
}
