#include <bits/stdc++.h>

using namespace std;

string prologToLisp(string curr_exp){
	while((curr_exp.find('(') < curr_exp.length() && curr_exp.find('(') >= 0) ||(curr_exp.find(',') < curr_exp.length() && curr_exp.find(',') >= 0)){
		if(curr_exp.find(',') == curr_exp.length() || curr_exp.find('(') < curr_exp.find(','))
			return "("+curr_exp.substr(0,curr_exp.find('(')) + " " + prologToLisp(curr_exp.substr(curr_exp.find('(') + 1));
		else if (curr_exp.find(',') == curr_exp.find(", "))
			return curr_exp.substr(0, curr_exp.find(", ")) + prologToLisp(curr_exp.substr(curr_exp.find(", ") + 1));
		else
			return curr_exp.substr(0,curr_exp.find(',')) + " " + prologToLisp(curr_exp.substr(curr_exp.find(',') + 1));
	}
	return curr_exp;
}

int main(){
	for(char j = '3'; j < '6'; j += 2)
		for(char i = '0'; i < '5'; i++){
			string result = "(and ";
			string inputFile = "input/depth";
			inputFile += j;
			inputFile += "/input";
			inputFile +=  i;
			inputFile += ".txt";
			
			string outputFile = "output/lisp/depth";
			outputFile += j;
			outputFile += "/output";
			outputFile += i;
			outputFile += ".txt";
			ifstream in (inputFile);
			ofstream out (outputFile);
			while(!in.eof()){
				string plString;
				in>>plString;
				if(plString.length() > 4)
					result += "(is-regexp '"+ prologToLisp(plString) + ")";
			}
			out<<result<<")";	
		}
}
