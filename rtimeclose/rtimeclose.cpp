#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout<<"No arguments. Print rtimeclose h to take help"<<endl;
		return 0;
	}

	if (argc > 1)
	{
		if (argv[1][0] == 'h')
		{
			cout<<"Print rtimeclose to close some process by timeout"<<endl;
			cout<<"by name of this process"<<endl<<endl;
			cout<<"Example : rtimeclose [seconds] [process]"<<endl;
			cout<<"or"<<endl;
			cout<<"rtimeclose u [seconds] [shell commands] - to run command by timer"<<endl;
			return 0;
		}

		if (argv[1][0] == 'u')
		{
			if ((argv[2][0] > '0') && (argv[2][0] <= '9'))
			{
				string a;
				a.append("xte 'sleep ");
				a.append((const char*)argv[2]);
				a.append("';");
				system(a.c_str());

				a.clear();
				for(int i = 3; i < argc; i++)
				{
					a.append(argv[i]);
					a.append(" ");
				}

				system(a.c_str());
			}
		}

		if ((argv[1][0] > '0') && (argv[1][0] <= '9'))
		{
			string a;
			a.append("xte 'sleep ");
			a.append((const char*)argv[1]);
			a.append("';");
			system(a.c_str());

			a.clear();
			a.append("killall -q ");
			a.append((const char*)argv[2]);
			system(a.c_str());
		}
	}

	return 0;
}
