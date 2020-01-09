#include<bits/stdc++.h>
using namespace std;
int main(){
	string final_query="is_regexp(";
	ifstream in("input/depth5/input0.txt");
	ofstream out("output/depth5/output0.txt");
	string s;
	in>>s;
	final_query+=s;
	final_query+=")";
	while(!in.eof()){
		final_query+=", is_regexp(";
		in>>s;
		final_query+=s;
		final_query+=")";
	}
	final_query+=".";
	out<<final_query;
}
