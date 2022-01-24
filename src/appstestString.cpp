#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;


int main(void)
{
		char myStr[10];
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				myStr[j] = rand()%(90-65)+65;
			}
			string s = myStr;
            cout<<s<<endl;
        }
    return 0;
}