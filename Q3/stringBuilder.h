#include<iostream>
#include<string.h>
using namespace std;

class stringBuilder
{
public:
	char *word;
	stringBuilder *left;
	stringBuilder *right;
	bool leaf;

	stringBuilder(char *ptr, bool l)
	{
		word = ptr;
		left = NULL;
		right = NULL;
		leaf = l;
	}
};

void postorder(stringBuilder& obj, char *ts, int& ind)
{
	//cout<<"postorder called "<<ind<<endl;
	if(obj.leaf == true)
	{
		//cout<<"leaf node\n";
		for(int lv=0; lv < strlen(obj.word); lv++, ind++)
		{
			ts[ind] = obj.word[lv];
			//cout<<"looping \n";
		}
		//cout<<"returning\n";
		return;
	}
	//cout<<"non leaf node\n";
	if(obj.left && obj.right)
	{
		postorder(*(obj.left), ts, ind);
		postorder(*(obj.right), ts, ind);
	}
	//cout<<"end postorder\n";
	return;
}



char *buildup(stringBuilder& s, char *ts)
{
	int i =0;
	//cout<<"buildup called\n";
	//cout<<"params "<<s.leaf<<' '<<ts<<' '<<i;
	postorder(s, ts, i);

}

stringBuilder stringInitialize(char *ptr)
{
	//cout<<"got in init "<<ptr<<endl;
	stringBuilder *temp = new stringBuilder(ptr, true);
	return *temp;
}

stringBuilder stringAppend(stringBuilder& a, stringBuilder& b)
{
	//cout<<"got addresses "<<&a<<' '<<&b<<endl;
	stringBuilder *temp = new stringBuilder(NULL, false);
	temp->left = &a;
	temp->right = &b;
	return *temp;
}

int findSubstring(stringBuilder& s, char *str)
{
	char *tempstring = new char[500];
	memset(tempstring, '\0', sizeof(char)*500);

	char *text = buildup(s, tempstring);
	cout<<"got text :"<<tempstring<<endl;
	delete tempstring;
	return 1;
}