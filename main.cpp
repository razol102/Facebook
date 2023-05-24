#include "Header.h"
#include "Facebook.h"
using namespace std;

int main()
{
	Facebook f;
	ifstream inFile("Facebook.txt");
	if (inFile.good())
	{
		loadFromFile(inFile, f);
		inFile.close();
	}
	else
		setFacebookData(f);

	cout << "Hello!" << endl << "Welcome to MTA Facebook!" << endl;
	menu(f);
	ofstream outFile("Facebook.txt", ios::trunc);
	saveToFile(f, outFile);
	outFile.close();
	return 0;
}