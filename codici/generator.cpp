#include<bits/stdc++.h>
using namespace std;
vector<string> op={"star","seq","or","plus"};
int max_depth=5;
string expr="";
char get_atom(){
	return 'a'+rand()%26;
}
void get_expr(int depth=1){
	if(depth==max_depth){
		expr+=get_atom();
		return;
	}
	string new_op=op[rand()%(int)op.size()];
	expr+=new_op;
	expr+="(";
	int limit=1+rand()%3;
	if(new_op=="plus" || new_op=="star")
		limit=1;
	for(int i=0;i<limit;i++){
		get_expr(depth+1);
		if(i!=limit-1)
			expr+=",";
	}
	expr+=")";
}
int main(){
	srand(time(NULL));
	ofstream out("input/depth5/input0.txt");
	int n=100;
	while(n--){
		expr="";
		get_expr();
		out<<expr<<endl;
	}
}
