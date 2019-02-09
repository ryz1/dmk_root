#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

string problem_name,in,out,in1,out1,op;
bool input_only,output_only;
string std_name,dmk_name,input_suf,output_suf,data_prefix;

int l,n,tmp;
char s[100];
bool except[100100];

void make_input_file(int x)
{
	op = dmk_name;
  op = op + " ";
	sprintf(s,"%d",x);
	l = strlen(s);
	for (int i = 0;i < l;i++) op += s[i];
	system(op.c_str());
}

void get_input_file(int x) 
{
  in = problem_name + '.' + input_suf;
  sprintf(s,"%d",x);
  in1 = data_prefix + s + '.' + input_suf;
  op = "del " + in;
  system(op.c_str());
  op = "rename " + in1 + ' ' + in;
  system(op.c_str());
}

void make_output_file()
{
	op = std_name;
	system(op.c_str());
}

void rename(int x)
{
	in=problem_name;
	in+=".in";
	out=problem_name;
	out+=".out";
	sprintf(s,"%d",x);
	l=strlen(s);
	in1=data_prefix;
	out1=data_prefix;
	for (int i=0;i<l;i++)	in1+=s[i],out1+=s[i];
	in1+="."+input_suf;
	out1+="."+output_suf;
	
	op="del ";
	op+=in1;
	system(op.c_str());
	
	op="rename ";
	op+=in;
	op+=' ';
	op+=in1;
	system(op.c_str());
	
  if (input_only) return;
  
	op="del ";
	op+=out1;
	system(op.c_str());
	
	op="rename ";
	op+=out;
	op+=' ';
	op+=out1;
	system(op.c_str());
}

void help() {
  puts("Data maker root version 2.41");
  puts("Format: dmk_root [problem_name] [options]");
  puts("Some options:");
  puts("-io : Generate input file only.");
  puts("-number [number_of_data] : Set the number of data, default to be 10, maximum to be 100000.");
  puts("-dmk [data_maker_name] : Set the data maker name, default to be \"dmk.exe\".");
  puts("-std [standard_program_name] : Set the standard program name, default to be \"problem_name.exe\".");
  puts("-is [input_file_suffix] : Set the input file suffix, default to be .in");
  puts("-os [output_file_suffix] : Set the output file suffix, default to be .out.");
  puts("-oo : Generate output file only.");
  puts("-np : Set input and output prefix to be NONE.");
  puts("-auto : Compile the std and dmk before making data. You should name the std as \"problem_name.cpp\", and name the dmk as \"dmk.cpp\"");
  puts("-except [except_points] : Set the points that should NOT be generated (again). (default to be none, can be set multiple times) (except_points can be described as [a] (which means the point a) or [a-b] (which means the points a, a+1, ... b).");
}

int set_except(char *pattern) {
  char *pos = strchr(pattern,'-');
  char *errloc,*errloc2;
  int l = strlen(pattern);
  if (pos == pattern + l) {
    int a = strtol(pattern,&errloc,10);
    if (errloc != pattern + l || a < 0 || a > 100000)
      return -1;
    except[a] = true;
  }
  else {
    int a = strtol(pattern,&errloc,10);
    int b = strtol(pos + 1,&errloc2,10);
    if (errloc != pos || errloc2 != pattern + l) return -1;
    if (a > b || a < 0 || b > 100000) return -1;
    for (int i = a;i <= b;i++) except[i] = true;
  }
  return 0;
}

void compile() {
  op = "g++ " + problem_name + ".cpp -o " + problem_name + ".exe -O2 -std=c++11 -Wl,--stack=16777216";
  system(op.c_str());
  system("g++ dmk.cpp -o dmk -std=c++11 -O2 -Wl,--stack=16777216");
}

int main(int argc,char **argv)
{

	if (argc == 1)
	{
		help();
		return 0;
	}
	l=strlen(argv[1]);
	for (int i=0;i<l;i++)	problem_name += argv[1][i];
	n = 10;
  data_prefix = problem_name;
  std_name = problem_name;
  std_name = std_name + ".exe";
  dmk_name = "dmk.exe";
  input_suf = "in";
  output_suf = "out";
  input_only = false;
  for (int i = 2;i < argc;i++)
	{
		if (argv[i][0] != '-') {
      puts("Bad Format!");
      return 0;
    }
    switch (argv[i][1]) {
      case 'i':{
        switch (argv[i][2]) {
          case 'o': {
            input_only = true;
            break;
          }
          case 's': {
            i++;
            if (i == argc) {
              puts("Bad Format!");
              return 0;
            }
            input_suf = "";
            input_suf += argv[i];
            break;
          }
          default: {
            puts("Bad Format!");
            return 0;
          }
        }
        break;
      }
      case 'n' :{
        switch (argv[i][2]) {
          case 'u': {
            i++;
            if (i == argc) {
              puts("Bad Format!");
              return 0;
            }
            if (sscanf(argv[i],"%d",&n) < 1) {
              puts("Bad Format!");
              return 0;
            }
            break;
          }
          case 'p': {
            data_prefix = "";
            break;
          }
          default: {
            puts("Bad Format!");
            return 0;
          }
        }
        break;
      }
      case 'd' :{
        i++;
        if (i == argc) {
          puts("Bad Format!");
          return 0;
        }
        dmk_name = "";
        dmk_name.append(argv[i]);
        break;
      }
      case 's' :{
        i++;
        if (i == argc) {
          puts("Bad Format!");
          return 0;
        }
        std_name = "";
        std_name.append(argv[i]);
        break;
      }
      case 'o' :{
        switch (argv[i][2]) {
          case 's': {
            i++;
            if (i == argc) {
              puts("Bad Format!");
              return 0;
            }
            output_suf = "";
            output_suf += argv[i];
            break;
          }
          case 'o':{
            output_only = true;
            break;
          }
          default: {
            puts("Bad Format!");
            return 0;
          }
        }
        break;
      }
      case 'e' :{
        i++;
        if (i == argc) {
          puts("Bad Format!");
          return 0;
        }
        if (set_except(argv[i])) {
          puts("Bad Format!");
          return 0;
        }
        break;
      }
      case 'a' :{
        compile();
        break;
      }
      default :{
        puts("Bad Format!");
        return 0;
      }
    }
	}
	for (int i=0;i<n;i++) 
    if (!except[i]) {
      printf("Generating data #%d...\n",i);
      if (!output_only) make_input_file(i);else get_input_file(i);
      if (!input_only) make_output_file();
      rename(i);
    }
	return 0;
}
