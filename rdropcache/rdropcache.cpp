#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	cout<<"before:"<<endl;
	system("free -m");
	system("sudo echo 1 > /proc/sys/vm/drop_caches");
	system("sudo echo 2 > /proc/sys/vm/drop_caches");
	system("sudo echo 3 > /proc/sys/vm/drop_caches");
	cout<<"=========================================================================================";
	cout<<endl<<"after:"<<endl;
	system("free -m");
	return 0;
}
