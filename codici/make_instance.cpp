#include<bits/stdc++.h>
using namespace std;
bool notSpecialFunctor(string a){
	return !(a == "plus" || a == "or" || a == "star" || a == "seq");
}
string instance(string &s, int begin, int end){
	if(begin >= end)
		return "";
	vector<pair<int, int>> exps;
	int i = begin;
	int tempBegin;
	deque<int> parenthesis;
	while(s[i]!='(' && i<end)
		i++;
	if(i==end || notSpecialFunctor(s.substr(begin, i - begin))){  //Riconosce i simboli dell'alfabeto
		string final = "";
		for(i = begin; i < end; i++)
			final += s[i];
		return final;
	}
	tempBegin = i + 1;
	while(i<end-1){
		i++;
		if(s[i]=='(')
			parenthesis.push_back(i);
		if(s[i]==')'){
			if(parenthesis.empty())
				exps.push_back({tempBegin, i});
			else
				parenthesis.pop_back();
		}
		if(s[i]==',' && parenthesis.empty())
			exps.push_back({tempBegin, i}), tempBegin = i + 1;
	}
	vector<string> result;
	
	for(auto a : exps){
		result.push_back(instance(s, a.first, a.second));
	}
	int N = result.size();
	if(s[begin]=='o' && s[begin + 1]=='r'){
		int choice=rand()%result.size();
		
		return result[choice];
	}
	else if(s[begin]=='s' && s[begin + 1]=='e' && s[begin + 2]=='q'){
		string final="";
		for(int res = 0; res < N; res++)
			final+=result[res] + (res != N - 1 ? ", " : "");	
		return final;
	}
	else if(s[begin]=='p' && s[begin + 1]=='l' && s[begin + 2]=='u' && s[begin + 3]=='s'){
		string final="";
		for(int res = 0; res < N; res++)
			final += result[res] + (res != N - 1 ? ", " : "");
		int times=rand()%3;
		times++;
		string really_final="";
		while(times--)
			really_final+=final + (times != 0 ? ", " : "");

		return really_final;
	}
	else{
		string final="";
		for(int res = 0; res < N; res++)
			final+=result[res] + (res != N - 1 ? ", " : "");
		int times=rand()%3;
		string really_final="";
		while(times--)
			really_final+=final + (times != 0 ? ", " : "");

		return really_final != "" ? really_final : "epsilon";
	}
}

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

string rmEpsilon (string exp){
	string result = "";
	while(exp.find("epsilon, ") >= 0 && exp.find("epsilon, ") < exp.length()){
		result += exp.substr(0, exp.find("epsilon, "));
		exp = exp.substr(min(exp.length()-1,exp.find("epsilon, ") + 9));
	}
	if(exp.length() >= 9 && exp.substr(exp.length() - 9) == ", epsilon")
		result += exp.substr(0, exp.length() - 9);
	else if (exp.length() >= 8 && exp.substr(exp.length() - 8) == " epsilon")
		result += exp.substr(0, exp.length() - 8);
	else if (exp != "epsilon")
		result += exp;
	return result;
}

int main(){
	srand(time(NULL));
	string FA_Id, expr, outputFile;
	int times, mode;
	cout<<"Inserisci file di output: ";
	cin>>outputFile;
	cout<<"Inserisci FA_Id: ";
	cin>>FA_Id;
	cout<<"Inserisci regexp (nello standard Prolog): ";
	string buffer;
	getline(cin,buffer);
	getline(cin,expr);
	cout<<"Inserisci quante istanze vuoi generare: ";
	cin>>times;
	cout<<"Quale modalita' (0 = Prolog, 1 = Lisp)? ";
	cin>>mode;
	ofstream out(outputFile);
	if(mode){
		string exprL = prologToLisp(expr);
		out<<"(and ";		
		for(int i=0;i<times;i++){		
			string curr_exp = rmEpsilon(instance(expr, 0, expr.length()));
			curr_exp = prologToLisp(curr_exp);
			out<<"(nfa-test (nfa-regexp-comp  '"<<exprL<<") '("<<curr_exp<<"))";			
		}	
		out<<")";
	}
	else{
		out<<"nfa_regexp_comp("<<FA_Id<<", "<<expr<<"),";
		for(int i=0;i<times;i++)
		 	out<<"nfa_test("<<FA_Id<<", ["<<rmEpsilon(instance(expr, 0, expr.length()))<<"])"<<(i == times - 1 ? "." : ",");
	}	
}
