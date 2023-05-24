#include "Header.h"
#include "FanPage.h"
#include "Member.h"
#include "Date.h"
#include "Exceptions.h"
using namespace std;

enum CASES { CASE1 = 1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10, CASE11, CASE12 };

void loadFromFile(ifstream& inFile, Facebook& f)
{
	inFile >> f;
}

void saveToFile(Facebook& f, ofstream& outFile)
{
	outFile << f;
}

void setFacebookData(Facebook& f)
{
	f.addMember("Raz Olewsky", Date(20, 8, 1996));
	f.addMember("Nizan Naor", Date(11, 4, 1995));
	f.addMember("Matan Tsts", Date(27, 2, 1996));

	list<Member>::iterator mem1 = f.getMembersArr().begin();
	list<Member>::iterator mem2 = f.getMembersArr().begin();
	advance(mem2, 1);
	list<Member>::iterator mem3 = f.getMembersArr().begin();
	advance(mem3, 2);

	*mem1 += *mem2;
	*mem1 += *mem3;
	*mem2 += *mem3;

	f.addFanPage("BasketBall");
	f.addFanPage("Romina");
	f.addFanPage("Qatar world cup");

	list<FanPage>::iterator fp1 = f.getPagesArr().begin();
	list<FanPage>::iterator fp2 = f.getPagesArr().begin();
	advance(fp2, 1);
	list<FanPage>::iterator fp3 = f.getPagesArr().begin();
	advance(fp3, 2);

	*mem1 += *fp1;
	*mem1 += *fp2;
	*mem1 += *fp3;
	*mem2 += *fp2;
	*mem3 += *fp1;
	*mem3 += *fp2;

	f.addStatus(*mem1, "Did USA reach to the moon??");
	f.addStatus(*mem1, "Let's go Boston!!!!");
	f.addStatus(*mem2, "Any good party around?");
	f.addStatus(*mem2, "Who comes with me to Sinai?");
	f.addStatus(*mem3, "Africa/Toto");
	f.addStatus(*mem3, "Hello World!");

	f.addStatus(*fp1, "Lebron James is not the best yet..");
	f.addStatus(*fp1, "Did you see Jason Tatum's dunk on Giannis Antetokounmpo?!?!!?!? INSAINE!");
	f.addStatus(*fp2, "What's 2 plus 2?");
	f.addStatus(*fp2, "Shayachut and Hachala are not the same!!");
	f.addStatus(*fp3, "Don't mix sports and politics!");
	f.addStatus(*fp3, "Here Messi, put this shirt on before you celebrate");
}

void menuOptions()
{
	cout << endl << "Menu:" << endl;
	cout << "1 - " << "Add a member" << endl;
	cout << "2 - " << "Add a fan page" << endl;
	cout << "3 - " << "Add a status to member/fan page" << endl;
	cout << "4 - " << "Show statuses of member/fan page" << endl;
	cout << "5 - " << "Show 10 latest statuses of a member's friend" << endl;
	cout << "6 - " << "Friendship between 2 members" << endl;
	cout << "7 - " << "Cancel friendship between 2 members" << endl;
	cout << "8 - " << "Add a member to a fan page" << endl;
	cout << "9 - " << "Remove a member from a fan page" << endl;
	cout << "10 - " << "Show all details in system" << endl;
	cout << "11 - " << "Show all friends of a member/fan page" << endl;
	cout << "12 - " << "Exit" << endl << endl;
}

void menu(Facebook& f)
{
	int choice, caseChoice;
	do
	{
		try
		{
			menuOptions();
			cout << "Please choose one of the following (1-12): ";
			cin >> choice;
			switch (choice)
			{
			case (CASE1): // add a member
			{
				cout << "-------------" << endl;
				cout << "Add a member:" << endl;
				cout << "-------------" << endl;
				cout << "Please enter your name (up to 50 chars): ";
				f.addMember();
				break;
			}
			case (CASE2): // add a fan page 
			{
				cout << "---------------" << endl;
				cout << "Add a fan page:" << endl;
				cout << "---------------" << endl;
				cout << "Please enter fan page name (up to 50 chars): ";
				f.addFanPage();
				break;
			}
			case (CASE3): // add a status to member/fan page
			{
				cout << "--------------------------------" << endl;
				cout << "Add a status to member/fan page:" << endl;
				cout << "--------------------------------" << endl;
				cout << "Choose - 1: Member, 2: Fan page: " << endl;
				cin >> caseChoice;
				isValidChoice(caseChoice, 1, 2); // exception potential
				f.addStatus(caseChoice);
				break;
			}
			case (CASE4): // show statuses of member/fan page
			{
				cout << "-----------------------------------" << endl;
				cout << "Show a statuses of member/fan page:" << endl;
				cout << "-----------------------------------" << endl;
				cout << "Choose - 1: Member, 2: Fan page: " << endl;
				cin >> caseChoice;
				isValidChoice(caseChoice, 1, 2); // exception potential
				f.showStatuses(caseChoice);
				break;
			}
			case (CASE5): // show 10 latest statuses of a member's friend
			{
				cout << "----------------------------------------" << endl;
				cout << "10 latest statuses of a member's friend:" << endl;
				cout << "----------------------------------------" << endl;
				f.latest10Statuses();
				break;
			}
			case (CASE6): // friendship between 2 members
			{
				cout << "-----------------------------" << endl;
				cout << "friendship between 2 members:" << endl;
				cout << "-----------------------------" << endl;
				f.addFriendToMember();
				break;
			}
			case (CASE7): // cancel friendship between 2 members
			{
				cout << "------------------------------------" << endl;
				cout << "Cancel friendship between 2 members:" << endl;
				cout << "------------------------------------" << endl;
				f.cancelFriendship();
				break;
			}
			case (CASE8): // add a member to a fan page
			{
				cout << "---------------------------" << endl;
				cout << "Add a member to a fan page:" << endl;
				cout << "---------------------------" << endl;
				f.addMemberToPage();
				break;
			}
			case (CASE9): // remove a member from a fan page
			{
				cout << "--------------------------------" << endl;
				cout << "Remove a member from a fan page:" << endl;
				cout << "--------------------------------" << endl;
				f.removeFan();
				break;
			}
			case (CASE10): // show all details in system
			{
				cout << "---------------------------" << endl;
				cout << "Show all details in system:" << endl;
				cout << "---------------------------" << endl;
				f.printAllEntities();
				break;
			}
			case (CASE11): // show all friends of a member / fan page
			{
				cout << "----------------------------------------" << endl;
				cout << "Show all friends of a member / fan page:" << endl;
				cout << "----------------------------------------" << endl;
				cout << "Choose - 1: Member, 2: Fan page: ";
				cin >> caseChoice;
				isValidChoice(caseChoice, 1, 2); // exception potential
				f.showAll(caseChoice);
				break;
			}
			case (CASE12): // exit
			{
				cout << "-----" << endl;
				cout << "Exit:" << endl;
				cout << "-----" << endl;
				cout << "Bye!" << endl;
				break;
			}
			default:
			{
				cout << endl << "--------------------\nInvalid choice index\n--------------------" << endl;
				break;
			}
			}
		}
		catch (std::out_of_range& ex)
		{
			cout << endl << ex.what();
		}
		catch (...)
		{
			cout << endl << "\n*** Unknown Error ***\n" << endl;
		}
	} while (choice != CASE12);
}

// exceptions:

void isValidChoice(const int num, const int min, const int max)
{
	if (num < min || num > max)
		throw std::out_of_range("--------------------\nInvalid choice index\n--------------------\n");
}

