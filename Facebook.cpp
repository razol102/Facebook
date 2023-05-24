	#include "Facebook.h"
#include "Member.h"
#include "FanPage.h"
#include "Exceptions.h"
#include "Date.h"
using namespace std;

list<Member>& Facebook::getMembersArr()
{
	return Lmembers;
}

list<FanPage>& Facebook::getPagesArr()
{
	return Lpages;
}

void Facebook::addMember() // case 1
{
	try
	{
		const string name = getName(0, Lmembers.size()); // exception potential
		Member newMem(getDate(), name);					 // exception potential
		Lmembers.push_back(newMem);						 // adds new member to the end of Vmembers list
		cout << endl << "The member: " << newMem.getName() << " has been successfuly added to Facebook!" << endl;
	}
	catch (emptyTextException& ex)
	{
		cout << endl << "\n*** Member name" << ex.what();
	}
	catch (letterException& ex)
	{
		cout << endl << ex.what();
	}
	catch (duplicateNamesException& ex)
	{
		cout << endl << ex.what();
	}
	catch (dateException& ex)
	{
		cout << endl << ex.what();
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::addMember(const string& name, Date date) // case 1
{
	Member newMem(date, name);  // creates new member
	Lmembers.push_back(newMem); // adds new member to the end of Vmembers list
}

void Facebook::addMember(ifstream& inFile)
{
	Member newMem(inFile);  // creates new member
	Lmembers.push_back(newMem);
}

void Facebook::addFanPage() // case 2
{
	try
	{
		const string name = getName(1, Lpages.size()); // exception potential
		FanPage newPage(name);						   // creates new fan page
		Lpages.push_back(newPage);					   // adds new fan page to the end of Vpages list
		cout << endl << "The page: " << newPage.getName() << " has been successfuly added to Facebook!" << endl;
	}
	catch (emptyTextException& ex)
	{
		cout << endl << "\n*** Fan page name" << ex.what();
	}
	catch (duplicateNamesException& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::addFanPage(const string& name) // case 2
{
	FanPage newPage(name);
	Lpages.push_back(newPage);  // adds new fan page to the end of Vpages list
}

void Facebook::addFanPage(ifstream& inFile)
{
	FanPage newPage(inFile);  // creates new page
	Lpages.push_back(newPage);
}

void Facebook::addStatus(int choice) noexcept (false) // case 3
{
	int i = 1, memberChoice, statusType;
	list<Member>::iterator itr = Lmembers.begin();

	try
	{
		if (choice == 1) //  1 - Member, 2 - Fan page
		{
			cout << "In which member's feed do you want to post? choose 1 - " << Lmembers.size() << ":" << endl;
			cout << "0 - Back to menu" << endl;
			printAllMembersInSystem();
			cin >> memberChoice;
			isValidChoice(memberChoice, REGRET, Lmembers.size()); // exception potential
			if (memberChoice == REGRET)
				return;
			advance(itr, (memberChoice - 1));
			chooseStatusType(statusType);
			isValidChoice(statusType, ONE, THREE); // exception potential
			cout << "Enter status in " << itr->getName() << "'s feed (Maximum 200 characters): " << endl;
			itr->addStatus(getStatus(), statusType);  // exception potential
		}
		else
		{
			list<FanPage>::iterator itr = Lpages.begin();
			cout << "In which page feed do you want to post? choose 0-" << Lpages.size() << ": " << endl;
			cout << "0 - Back to menu" << endl;
			printAllPagesInSystem();
			cin >> memberChoice;
			isValidChoice(memberChoice, REGRET, Lpages.size()); // exception potential
			if (memberChoice == REGRET)
				return;
			advance(itr, (memberChoice - 1));

			chooseStatusType(statusType);
			isValidChoice(statusType, ONE, THREE); // exception potential
			cout << "Enter status in " << itr->getName() << "'s feed (Maximum 200 characters): " << endl;
			itr->addStatus(getStatus(), statusType);  // exception potential
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
}

void Facebook::addStatus(Member& member, const string& text)  // case 3
{
	member.addStatus(text, 1);
}

void Facebook::addStatus(FanPage& page, const string& text) // case 3
{
	page.addStatus(text, 1);
}

void Facebook::showStatuses(int choice) // case 4
{
	try
	{
		int i = 1, memberChoice;
		if (choice == 1) //  1 - Member, 2 - Fan page
		{
			list<Member>::iterator itr = Lmembers.begin();
			cout << "Choose a member to show statuses: choose 0 - " << Lmembers.size() << ":" << endl;
			cout << "0 - Back to menu" << endl;
			printAllMembersInSystem();
			cin >> memberChoice;
			if (memberChoice == REGRET)
				return;
			advance(itr, (memberChoice - 1));
			itr->printStatuses();  // exception potential
		}
		else
		{
			list<FanPage>::iterator itr = Lpages.begin();
			cout << "Choose a fan page to show statuses: choose 0 - " << Lpages.size() << ":" << endl;
			cout << "0 - Back to menu" << endl;
			printAllPagesInSystem();
			cin >> memberChoice;
			isValidChoice(memberChoice, REGRET, Lpages.size()); // exception potential
			if (memberChoice == REGRET)
				return;
			advance(itr, (memberChoice - 1));
			itr->printStatuses();  // exception potential
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
}

void Facebook::latest10Statuses() // case 5
{
	list<Member>::iterator itr = Lmembers.begin();
	try
	{
		int i = 1, memberChoice;
		cout << "Choose a member: 0-" << Lmembers.size() << ":" << endl;
		cout << "0 - Back to menu" << endl;
		printAllMembersInSystem();
		cin >> memberChoice;
		isValidChoice(memberChoice, REGRET, Lmembers.size()); // exception potential
		if (memberChoice == REGRET)
			return;
		advance(itr, (memberChoice - 1));
		noFriendsToMember(itr->getVfriends().size()); // member has no friends to show statuses
		itr->arrange10FriendsStatuses();
	}
	catch (noFriendsToMemberException& ex)
	{
		cout << endl << "\n*** " << itr->getName() << ex.what();
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::addFriendToMember() // case 6
{
	list<Member>::iterator itr = Lmembers.begin();
	list<Member>::iterator mem1 = Lmembers.begin();
	list<Member>::iterator mem2 = Lmembers.begin();
	try
	{

		int i = 1, choice1, choice2;
		cout << "Choose a member: 1-" << Lmembers.size() << ":" << endl;
		printAllMembersInSystem();
		cin >> choice1;
		isValidChoice(choice1, 1, Lmembers.size()); // exception potential
		advance(itr, (choice1 - 1));
		friendWithAllMembers(itr->getVfriends().size(), Lmembers.size() - 1); // exception potential
		cout << "Choose another member to make friendship with " << itr->getName() << ":" << endl;
		printAllMembersInSystem();

		cin >> choice2;
		isValidChoice(choice2, 1, Lmembers.size()); // exception potential
		selfie(choice1, choice2);  // exception potential
		advance(mem1, (choice1 - 1));
		advance(mem2, (choice2 - 1));
		vector<Member*>::const_iterator itr3 = mem1->getVfriends().begin();
		vector<Member*>::const_iterator itrEnd3 = mem1->getVfriends().end();
		for (; itr3 != itrEnd3; ++itr3)
			isAlreadyFriend((*itr3)->getName(), mem2->getName()); // exception potential
		*mem1 += *mem2;
		cout << mem1->getName() << " and " << mem2->getName() << " are friends now!" << endl;
	}
	catch (alreadyFriendException& ex)
	{
		cout << endl << "\n*** " << mem1->getName() << ex.what() << mem2->getName() << " ***\n" << endl;
	}
	catch (selfFriendshipException& ex)
	{
		cout << ex.what() << endl;
	}
	catch (multiFriendException& ex)
	{
		cout << endl << "\n*** " << itr->getName() << ex.what() << endl;
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}

	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::cancelFriendship() // case 7
{
	int choice1, choice2, count1 = 0, count2 = 0;
	list<Member>::iterator itr = Lmembers.begin();
	list<Member>::iterator itrEnd = Lmembers.end();
	try
	{
		for (; itr != itrEnd; ++itr)								// counts members that have friends.
		{
			if (itr->getVfriends().size() != 0)
				count1++;
		}
		noFriendsInSystem(count1);									// exception potential
		cout << "Choose a member: (showing all members that have friends already)" << endl;
		itr = Lmembers.begin();
		count1 = 0;

		for (; itr != itrEnd; ++itr)								// prints members that have friends.
		{
			if (itr->getVfriends().size() != 0)
			{
				cout << count1 + 1 << " - " << itr->getName() << endl;
				count1++;
			}
		}

		cin >> choice1;
		isValidChoice(choice1, 1, count1);							 // exception potential
		itr = Lmembers.begin();

		cout << "Choose a friend to cancel friendship with:" << endl;
		for (; itr != itrEnd; ++itr)								  // To find the member that the user chose.
		{
			if (itr->getVfriends().size() != 0)
				count2++;
			if (choice1 == count2)
			{
				itr->printFriends();								  // exception potential
				break;
			}
		}

		cin >> choice2;
		isValidChoice(choice2, 1, itr->getVfriends().size()); // exception potential
		vector<Member*>::const_iterator itr2 = itr->getVfriends().begin() + (choice2 - 1);
		cout << itr->getName() << " and " << (*itr2)->getName() << " are not friends now :(" << endl;
		*itr -= **itr2;
	}
	catch (noFriendsInSystemException& ex)
	{
		cout << endl << ex.what();
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::addMemberToPage() // case 8
{
	list<Member>::iterator itr = Lmembers.begin();
	list<FanPage>::iterator itrChoice = Lpages.begin();
	int i = 1, choiceMem, choicePage;
	try
	{
		cout << "Choose a member: 0-" << Lmembers.size() << ":" << endl;
		cout << "0 - Back to menu" << endl;
		printAllMembersInSystem();
		cin >> choiceMem;
		isValidChoice(choiceMem, REGRET, Lmembers.size()); // exception potential
		if (choiceMem == REGRET)
			return;
		else
		{
			itr = Lmembers.begin();
			advance(itr, (choiceMem - 1));
			cout << "Choose a page to add to " << itr->getName() << "'s pages list:" << endl;
			cout << "0 - Back to menu" << endl;
			printAllPagesInSystem();
			cin >> choicePage;
			isValidChoice(choicePage, REGRET, Lpages.size()); // exception potential
			if (choicePage == REGRET)
				return;
			vector<FanPage*>::const_iterator itr2 = itr->getVfanPages().begin();
			vector<FanPage*>::const_iterator itrEnd2 = itr->getVfanPages().end();
			advance(itrChoice, (choicePage - 1));

			for (; itr2 != itrEnd2; ++itr2)								// Runs on pages that the members is a fan of. 
				isAlreadyFan((*itr2)->getName(), itrChoice->getName()); // exception potential
			*itr += *itrChoice;
			cout << itr->getName() << " is a new fan of the page " << itrChoice->getName() << endl;
		}
	}
	catch (alreadyFanException& ex)
	{
		cout << endl << "\n*** " << itr->getName() << ex.what() << itrChoice->getName() << " ***\n" << endl;
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::addMemberToPage(Member& member, FanPage& page) // case 8
{
	member += page;
}

void Facebook::removeFan() // case 9
{
	int choice1, choice2, count1 = 0, count2 = 0;
	list<Member>::iterator itr = Lmembers.begin();
	list<Member>::iterator itrEnd = Lmembers.end();
	try
	{
		for (; itr != itrEnd; ++itr)				// counts members that have at least 1 fan page
		{
			if (itr->getVfanPages().size() != 0)
				count1++;
		}
		noFans(count1); // exception potential
		count1 = 0;
		cout << "Choose a member: " << endl;
		itr = Lmembers.begin();
		for (; itr != itrEnd; ++itr)				// prints members that have at least 1 fan page
		{
			if (itr->getVfanPages().size() != 0)
			{
				cout << count1 + 1 << " - " << itr->getName() << endl;
				count1++;
			}
		}

		itr = Lmembers.begin();
		cin >> choice1;
		isValidChoice(choice1, 1, count1);			 // exception potential
		cout << "Choose a fan page: " << endl;
		for (; itr != itrEnd; ++itr)				 // finds the fan that the user chose.
		{
			if (itr->getVfanPages().size() != 0)	 // counts all members that are fans of any page
				count2++;
			if (choice1 == count2)
			{
				itr->printFanPages();				 // exception potential
				break;
			}
		}
		cin >> choice2;
		isValidChoice(choice2, 1, itr->getVfanPages().size()); // exception potential
		vector<FanPage*>::const_iterator itr2 = itr->getVfanPages().begin();
		vector<FanPage*>::const_iterator itrEnd2 = itr->getVfanPages().end();
		vector<FanPage*>::const_iterator itrChoice = itr->getVfanPages().begin() + (choice2 - 1);
		for (; itr2 != itrEnd2; ++itr2)				// runs over all pages that this member is a fan of
		{
			if (itr2 == itrChoice)
			{
				cout << itr->getName() << " is no longer a fan of the page: " << (*itrChoice)->getName() << endl;
				*itr -= **itrChoice;
				break;
			}
		}
	}
	catch (noFansException& ex)
	{
		cout << endl << ex.what();
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::printAllEntities() // case 10
{
	list<Member>::iterator itr = Lmembers.begin();
	list<Member>::iterator itrEnd = Lmembers.end();
	list<FanPage>::iterator itr2 = Lpages.begin();
	list<FanPage>::iterator itrEnd2 = Lpages.end();

	try
	{
		noUsersInSystem(Lmembers.size());  // exception potential
		cout << "Members in system: " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << "Name: " << itr->getName() << ", date of birth: ";
			cout << itr->getBirthDay().getDay() << "/" << itr->getBirthDay().getMonth() << "/" << itr->getBirthDay().getYear() << endl;
		}
	}
	catch (noMembersException& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}

	try
	{
		noPagessInSystem(Lpages.size());  // exception potential
		cout << endl;
		cout << "Fan pages in system: " << endl;
		for (; itr2 != itrEnd2; ++itr2)
			cout << "Page: " << itr2->getName() << endl;
	}

	catch (noFanPagesException& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Facebook::showAll(int choice) // case 11
{
	list<Member>::iterator itr = Lmembers.begin();
	list<FanPage>::iterator itr2 = Lpages.begin();
	int i = 1, memberChoice;
	try
	{
		if (choice == 1)
		{
			noUsersInSystem(Lmembers.size());					 // exception potential
			cout << "Choose a member: 0-" << Lmembers.size() << ":" << endl;
			cout << "0 - Back to menu" << endl;
			printAllMembersInSystem();
			cin >> memberChoice;
			isValidChoice(memberChoice, REGRET, Lmembers.size()); // exception potential
			if (memberChoice == REGRET)
				return;
			itr = Lmembers.begin();
			advance(itr, (memberChoice - 1));
			itr->printFriends();								 // exception potential
		}
		else
		{
			noPagessInSystem(Lpages.size());					 // exception potential
			cout << "Choose a fan page: 0-" << Lpages.size() << ":" << endl;
			cout << "0 - Back to menu" << endl;
			printAllPagesInSystem();
			cin >> memberChoice;
			isValidChoice(memberChoice, REGRET, Lpages.size()); // exception potential
			if (memberChoice == REGRET)
				return;
			itr2 = Lpages.begin();
			advance(itr2, (memberChoice - 1));
			itr2->printFans();
		}
	}
	catch (noMembersException& ex)
	{
		cout << endl << ex.what();
	}
	catch (noFanPagesException& ex)
	{
		cout << endl << ex.what();
	}
	catch (std::out_of_range& ex)
	{
		cout << endl << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

// Validations:

const string Facebook::getStatus()
{
	int i;
	char c;
	char text[MAX_STATUS_LEN];
	c = getchar();
	for (i = 0; i < MAX_STATUS_LEN - 1; i++)
	{
		c = getchar();
		if (c == '\n')
			break;
		else
			text[i] = c;
	}
	text[i] = '\0';

	if (text[0] != '\0') // makes sure names have capital letter in first letter
	{
		if (text[0] >= 'a' && text[0] <= 'z')
			text[0] -= 'a' - 'A';
	}
	return text;
}

const string Facebook::getName(int nameType, int size) noexcept(false)		// nameType = 0 for members. 1 for fan pages.
{
	int i;
	char c;
	string name;
	c = getchar();

	for (i = 0; i < MAX_NAME_LEN - 1; i++)		// input from user for name
	{
		c = getchar();
		if (c == '\n')
			break;
		else
			name.push_back(c);
	}
	isEmpty(name);

	if (nameType == 0) // checks if member name has only letters	
		lettersCheck(name);

	string::iterator itr = name.begin();

	if (*itr != '\0')
	{
		if (*itr >= 'a' && *itr <= 'z')
			*itr -= 'a' - 'A';

		for (i = 0; i < size; i++)
		{
			if (nameType == 0)
			{
				list<Member>::iterator itr2 = Lmembers.begin();
				advance(itr2, i);
				dupCheck(name, itr2->getName());
			}
			else
			{
				list<FanPage>::iterator itr2 = Lpages.begin();
				advance(itr2, i);
				dupCheck(name, itr2->getName());
			}
		}
	}
	return name;
}

const Date& Facebook::getDate() noexcept (false)
{
	int  day, month, year;

	cout << "Please enter your date of birth: ";
	cin >> day >> month >> year;
	dateCheck(day, month, year); //

	return (Date(day, month, year));
}

void Facebook::printAllMembersInSystem()
{
	list<Member>::iterator itr = Lmembers.begin();
	list<Member>::iterator itrEnd = Lmembers.end();
	int i = 1;
	for (; itr != itrEnd; ++itr)
	{
		cout << i << " - " << itr->getName() << endl;
		i++;
	}
}

void Facebook::printAllPagesInSystem()
{
	list<FanPage>::iterator itr = Lpages.begin();
	list<FanPage>::iterator itrEnd = Lpages.end();
	int i = 1;
	for (; itr != itrEnd; ++itr)
	{
		cout << i << " - " << itr->getName() << endl;
		i++;
	}
}

void Facebook::chooseStatusType(int& choice)
{
	cout << "Choose type of status (1-3):" << endl;
	cout << "1 - Text only" << endl;
	cout << "2 - Text and picture" << endl;
	cout << "3 - Text and video" << endl;
	cin >> choice;
}


// exceptions:

void Facebook::isValidChoice(int num, int min, int max)
{
	if (num < min || num > max)
		throw std::out_of_range("--------------------\nInvalid choice index\n--------------------\n");
}

void Facebook::isEmpty(const string& name)
{
	if (name[0] == '\0')
		throw emptyTextException();
}

void Facebook::dupCheck(const string& name1, const string& name2)
{
	if (name1 == name2)
		throw duplicateNamesException();
}

void Facebook::noFriendsInSystem(const int i)
{
	if (i == 0)
		throw noFriendsInSystemException();
}

void Facebook::noFriendsToMember(const int i)
{
	if (i == 0)
		throw noFriendsToMemberException();
}

void Facebook::noFans(const int i)
{
	if (i == 0)
		throw noFansException();
}

void Facebook::dateCheck(const int day, const int month, const int year)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	bool flag = true;

	if (day < FIRST || day > LAST_DAY)																	// day check
		flag = false;
	else if (month < FIRST || month > LAST_MONTH)														// month check
		flag = false;
	else if (year < PRE_HISTORIC + ltm->tm_year - AFTER_LIFE || year > PRE_HISTORIC + ltm->tm_year)		// year check
		flag = false;

	if (!flag)
		throw dateException();
}

void Facebook::isAlreadyFan(const string& name1, const string& name2)
{
	if (name1 == name2)
		throw alreadyFanException();
}

void Facebook::isAlreadyFriend(const string& name1, const string& name2)
{
	if (name1 == name2)
		throw alreadyFriendException();
}

void Facebook::selfie(const int choice1, const int choice2)
{
	if (choice1 == choice2)
		throw selfFriendshipException();
}

void Facebook::friendWithAllMembers(const int size1, const int size2)
{
	if (size1 == size2)
		throw multiFriendException();
}

void Facebook::noUsersInSystem(const int size)
{
	if (size == 0)
		throw noMembersException();
}

void Facebook::noPagessInSystem(const int size)
{
	if (size == 0)
		throw noFanPagesException();
}

void Facebook::lettersCheck(const string& name)
{
	int i = 0;
	while (name[i] != '\0')
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a') && name[i] <= 'z' || name[i] <= ' '))
			throw letterException();
		i++;
	}
}

// operators:

ostream& operator<<(ostream& os, Facebook& f)
{	
	// writes to file members number and pages number
	os << f.Lmembers.size() << endl << f.Lpages.size() << endl;

	// writes to file: member name, birthday, statuses and friends
	list<Member>::iterator member = f.Lmembers.begin();
	list<Member>::iterator memberEnd = f.Lmembers.end();
	for (; member != memberEnd; ++member)
		os << *member; // member

	member = f.Lmembers.begin();
	for (; member != memberEnd; ++member)
	{
		os << member->getVfriends().size() << endl; // number of friends of member

		vector<Member*>::iterator friends = member->getVfriends().begin();
		vector<Member*>::iterator friendsEnd2 = member->getVfriends().end();
		// Writes all friends of each member.
		for (; friends != friendsEnd2; ++friends)
		{
			os << (*friends)->getName() << endl; // friends of member (names)
		}
	}

	// Fan pages:
	list<FanPage>::const_iterator page = f.Lpages.begin();
	list<FanPage>::const_iterator pageEnd = f.Lpages.end();
	for (; page != pageEnd; ++page)
		os << *page; // page

	page = f.Lpages.begin();
	for (; page != pageEnd; ++page)
	{
		os << page->getVfans().size() << endl; // number of fans of page

		vector<Member*>::const_iterator fan = page->getVfans().begin();
		vector<Member*>::const_iterator fanEnd2 = page->getVfans().end();

		// Writes all fans of each fan page.
		for (; fan != fanEnd2; ++fan)
		{
			os << (*fan)->getName() << endl; // friends of member (names)
		}
	}
	return os;
}

ifstream& operator>>(ifstream& in, Facebook& f)
{
	int i, j, memNum, pagesNum, friendsNum, fansNum, numOfStatuses;
	string statusType;

	// reads from file members number and pages number
	in >> memNum >> pagesNum;

	// reads all members from file.
	for (i = 0; i < memNum; i++)
	{
		in.get(); // '\n'
		f.addMember(in);

		// add statuses to each member in system
		list<Member>::iterator mem = f.getMembersArr().begin();
		advance(mem, i);
		in >> numOfStatuses;

		for (j = 0; j < numOfStatuses; j++)
		{
			in.get(); // '\n'
			getline(in, statusType);
			if (statusType == "Status *")
				mem->addStatus(in, 1);
			else if (statusType == "Picture *")
				mem->addStatus(in, 2);
			else if (statusType == "Video *")
				mem->addStatus(in, 3);
		}
	}

	in.get(); // '\n'
	string friendName;

	// makes friendships between members
	for (i = 0; i < memNum; i++) // runs over all members in system
	{
		list<Member>::iterator mem = f.Lmembers.begin();
		advance(mem, i);
		in >> friendsNum;
		in.get(); // '\n'

		for (j = 0; j < friendsNum; j++) // runs over all friends of each member
		{ 
			getline(in, friendName);
			list<Member>::iterator mem2 = f.Lmembers.begin();
			list<Member>::iterator mem2End = f.Lmembers.end();

			for (; mem2 != mem2End; ++mem2)
			{
				if (mem2->getName() == friendName)
				{
					*mem += *mem2;
					break;
				}
			}
		}
	}

	// reads all pages from file.
	for(i = 0; i < pagesNum; i++)
	{
		f.addFanPage(in);

		// add statuses to each member in system
		list<FanPage>::iterator page = f.getPagesArr().begin();
		advance(page, i);
		in >> numOfStatuses;
		for (j = 0; j < numOfStatuses; j++)
		{
			in.get(); // '\n'
			getline(in, statusType);
			if (statusType == "Status *")
				page->addStatus(in, 1);
			else if (statusType == "Picture *")
				page->addStatus(in, 2);
			else if (statusType == "Video *")
				page->addStatus(in, 3);
		}
		in.get(); // '\n'
	}

	string fanName;

	// adds fans to pages
	for (i = 0; i < pagesNum; i++) // runs over all pages in system
	{
		list<FanPage>::iterator page = f.Lpages.begin();
		advance(page, i);
		in >> fansNum;
		in.get(); // '\n'

		for (j = 0; j < fansNum; j++) // runs over all fans of each member
		{ 
			getline(in, fanName);
			list<Member>::iterator mem2 = f.Lmembers.begin();
			list<Member>::iterator mem2End = f.Lmembers.end();

			for (; mem2 != mem2End; ++mem2)
			{
				if (mem2->getName() == fanName)
				{
					*mem2 += *page;
					break;
				}
			}
		}
	}
	return in;
}
