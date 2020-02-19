#include <bits/stdc++.h>

using namespace std;
const int MAXN = 5;

string scelteLISP[MAXN]={"seq","or","star","plus", "nfa-test"};
string cambiaLISP[MAXN]={"[]", "/", "*", "+", "nfa-rec"};

string sceltePL[MAXN]={"seq(","or","star","plus","nfa_test"};
string cambiaPL[MAXN]={"[", "/", "*", "+", "nfa_rec"};

void translateLisp(string input, string output);
void translateProlog(string input, string output);

int main(){
	string input, output;
	for(int i = 0; i < 5; i++)
		input = "output/lisp/depth3/output"+to_string(i)+".txt",output = "output/E2P/lisp/depth3/output"+to_string(i)+".txt",
		translateLisp(input, output);
	for(int i = 0; i < 5; i++)
		input = "output/lisp/depth5/output"+to_string(i)+".txt",output = "output/E2P/lisp/depth5/output"+to_string(i)+".txt",
		translateLisp(input, output);
	for(int i = 0; i < 5; i++)
	{
		input = "output/Inst-Ex/Lisp/InstLISP"+to_string(i)+".txt",output = "output/E2P/Inst-Ex/Lisp/InstLISP"+to_string(i)+".txt";
		translateLisp(input, output);
	}
	for(int i = 0; i < 5; i++)
		input = "output/prolog/depth3/output"+to_string(i)+".txt",output = "output/E2P/prolog/depth3/output"+to_string(i)+".txt",
		translateProlog(input, output);
	for(int i = 0; i < 5; i++)
		input = "output/prolog/depth5/output"+to_string(i)+".txt",output = "output/E2P/prolog/depth5/output"+to_string(i)+".txt",
		translateProlog(input, output);
	for(int i = 0; i < 5; i++)
	{
		input = "output/Inst-Ex/Prolog/InstPL"+to_string(i)+".txt",output = "output/E2P/Inst-Ex/Prolog/InstPL"+to_string(i)+".txt";
		translateProlog(input, output);
	}
}

void translateLisp(string input, string output)
{
	ifstream in (input);
	ofstream out (output);
	string s;
	getline(in, s);
	for(int j = 0; j < s.length(); j++)
	{
		bool ok = false;
		for(int k = 0;!ok && k < MAXN; k++){
			if(j+scelteLISP[k].length() < s.length() && s.substr(j, scelteLISP[k].length()) == scelteLISP[k])
			{
				j += scelteLISP[k].length();
				ok = true;
				out<<cambiaLISP[k];
			}
		}
		if (ok)
			j--;
		else
			out<<s[j];
	}
	out.close();
}

void translateProlog(string input, string output)
{
	ifstream in (input);
	ofstream out (output);
	string s;
	getline(in, s);
	bool fase_seq = false;
	deque<string> stack;
	for(int j = 0; j < s.length(); j++)
	{
		if(stack.empty())
		{
			bool ok = false;
			for(int k = 0;!ok && k < MAXN; k++){
				if(j+sceltePL[k].length() < s.length() && s.substr(j, sceltePL[k].length()) == sceltePL[k])
				{
					j += sceltePL[k].length();
					ok = true;
					out<<cambiaPL[k];
					if(sceltePL[k] == "seq(")
						stack.push_front(sceltePL[k]);
				}
			}
			if (ok)
				j--;
			else
				out<<s[j];	
		}
		else
		{
			bool ok = false;
			if(s[j] == ')')
			{
				if (stack.front() == "seq(")
					out<<']';
				else
					out<<s[j];
				stack.pop_front();
				ok = true;
				j++;
			}
			for(int k = 0;!ok && k < MAXN; k++){
				if(j+sceltePL[k].length() < s.length() && s.substr(j, sceltePL[k].length()) == sceltePL[k])
				{
					j += sceltePL[k].length();
					ok = true;
					out<<cambiaPL[k];
					stack.push_front(sceltePL[k]);
				}
			}
			if (ok)
				j--;
			else
				out<<s[j];		
		}
	}
	out.close();
}
