#include "StringObject.h"

int main(){
	String firstString, secondString, thirdString;
	cout << "Enter first string A: ";
	cin >> firstString;
	cout << "Enter second string B: ";
	cin >> secondString;
	cout << "Enter third string C: ";
	cin >> thirdString;


	cout << endl << "A + B + word + C : ";
	String result = firstString + secondString + "word" + thirdString;
	cout << result << "   COPPIED:   ";
	cout << firstString + secondString + "word" + thirdString << endl;

	firstString = secondString = "word";
	cout <<  endl << "A = B = word" << endl << "A: " << firstString << endl;



	firstString += thirdString += 'W';
	cout << endl << "A += C += 'W' : " << endl << "A: " << firstString << endl << "C: " << thirdString << endl;


	cout << endl << "A == C?: ";
	if (firstString == thirdString) cout << "true" << endl;
	else cout << "false" << endl;


	cout << endl << "hello < B?: ";
	if ("hello" < secondString) cout << "true" << endl;
	else cout << "false" << endl;

	
	cout << endl << "The first symbol of string A is " << firstString[0] << endl;
	cout << endl << "The substring of string B: " << secondString(1, 3) << endl;

	String NewObj;
	cin >> NewObj;
	rewind(stdin);
	cin.clear();
	cout << endl << "Char + StringObject: " << 'a' + NewObj;

	return 0;
}