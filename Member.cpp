#include "Member.h"
#include "FanPage.h"
#include "Status.h"
#include "Date.h"
#include "Exceptions.h"

using namespace std;

Member::Member(const Date& birthDay, const string& name) : birthDay(birthDay)
{
	this->name = name;
}

Member::Member(const Member& other)
{
	this->name = other.name;
	Vfriends = other.Vfriends;
	VfanPages = other.VfanPages;
	LbillBoard = other.LbillBoard;
	birthDay = other.birthDay;
}

Member::Member(Member&& other)
{
	this->name = other.name;
	Vfriends = other.Vfriends;
	VfanPages = other.VfanPages;
	LbillBoard = other.LbillBoard;
	birthDay = other.birthDay;
}

Member::~Member()
{
	list<Status*>::iterator itr = LbillBoard.begin();
	list<Status*>::iterator itrEnd = LbillBoard.end();

	for (; itr != itrEnd; ++itr)
		delete* itr;
}

Member::Member(ifstream& in)
{
	in >> *this;
}

const list<Status*> Member::getBillBoard() const
{
	return LbillBoard;
}

vector<Member*>& Member::getVfriends()
{
	return Vfriends;
}

const vector<FanPage*>& Member::getVfanPages() const
{
	return VfanPages;
}

FanPage& Member::getFanPage(int i)
{
	vector<FanPage*>::iterator itr = VfanPages.begin() + i;
	return **itr;
}

Member& Member::getFriend(int i)
{
	vector<Member*>::iterator itr = Vfriends.begin() + i;
	return **itr;
}

void Member::addStatus(const string& text, const int statusType)
{
	try
	{
		switch (statusType)
		{
		case 1: // text only
		{
			Status* newSt = new Status(text); // creates new status
			LbillBoard.push_back(newSt);  // adds new status to the end of VallStatuses list
			break;
		}
		case 2: // picture and text
		{
			Status* newSt = new Picture(text); // creates new status
			LbillBoard.push_back(newSt);  // adds new status to the end of VallStatuses list
			break;
		}
		case 3: // video and text
		{
			Status* newSt = new Video(text); // creates new status
			LbillBoard.push_back(newSt);  // adds new status to the end of VallStatuses list
			break;
		}
		default:
			break;
		}
	}
	catch (emptyTextException& ex)
	{
		cout << endl << "\n*** Status" << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Member::addStatus(ifstream& in, int statusType)
{
	switch (statusType)
	{
	case 1: // text only
	{
		Status* newSt = new Status(in); // creates new status
		LbillBoard.push_back(newSt);  // adds new status to the end of VallStatuses list
		break;
	}
	case 2: // picture and text
	{
		Status* newSt = new Picture(in); // creates new status
		LbillBoard.push_back(newSt);  // adds new status to the end of VallStatuses list
		break;
	}
	case 3: // video and text
	{
		Status* newSt = new Video(in); // creates new status
		LbillBoard.push_back(newSt);  // adds new status to the end of VallStatuses list
		break;
	}
	default:
		break;
	}
}

void Member::arrange10FriendsStatuses()
{
	int counter = 0;
	list<Status*> friendsStatuses;									 // Holds Statuses of all friends.
	list<string> users;												 // Holds names of a member for each status that we insert in friendsStatuses arr
	vector<Member*>::iterator itr = Vfriends.begin();				 // Holds all statuses of member's friends
	vector<Member*>::iterator itrEnd = Vfriends.end();
	itr = Vfriends.begin();

	for (; itr != itrEnd; ++itr)									 // runs over all the member's friends
	{
		list<Status*>::iterator itrStatus = (*itr)->LbillBoard.begin();
		list<Status*>::iterator itrStatusEnd = (*itr)->LbillBoard.end();
		for (; itrStatus != itrStatusEnd; ++itrStatus)				 // runs over all the statuses of each friend of the member.
		{
			friendsStatuses.push_back(*itrStatus);
			users.push_back((*itr)->getName());
			counter++;
		}
	}
	print10FriendsStatuses(friendsStatuses, counter, users);
}

void Member::print10FriendsStatuses(list<Status*> friendsStatuses, int len, list<string> users)
{
	int count = 0, i;

	while (count < TO_ARRANGE && len > 0)
	{
		i = 0;
		list<Status*>::iterator itr = friendsStatuses.begin();
		list<Status*>::iterator itrEnd = friendsStatuses.end();
		list<string>::iterator itrUser = users.begin();

		int yearMax = (*itr)->getDate().getYear();
		int monthMax = (*itr)->getDate().getMonth();
		int dayMax = (*itr)->getDate().getDay();
		int hourMax = (*itr)->getDate().getHour();
		int minuteMax = (*itr)->getDate().getMinute();

		for (; itr != itrEnd; ++itr)							// Runs on statuses					 
		{
			if ((*itr)->getDate().getYear() > yearMax)
			{
				yearMax = (*itr)->getDate().getYear();
				monthMax = (*itr)->getDate().getMonth();
				dayMax = (*itr)->getDate().getDay();
				hourMax = (*itr)->getDate().getHour();
				minuteMax = (*itr)->getDate().getMinute();
				i++;
			}

			else if ((*itr)->getDate().getYear() == yearMax)
			{
				if ((*itr)->getDate().getMonth() > monthMax)
				{
					yearMax = (*itr)->getDate().getYear();
					monthMax = (*itr)->getDate().getMonth();
					dayMax = (*itr)->getDate().getDay();
					hourMax = (*itr)->getDate().getHour();
					minuteMax = (*itr)->getDate().getMinute();
					i++;
				}
				else if ((*itr)->getDate().getMonth() == monthMax)
				{
					if ((*itr)->getDate().getDay() > dayMax)
					{
						yearMax = (*itr)->getDate().getYear();
						monthMax = (*itr)->getDate().getMonth();
						dayMax = (*itr)->getDate().getDay();
						hourMax = (*itr)->getDate().getHour();
						minuteMax = (*itr)->getDate().getMinute();
						i++;
					}
					else if ((*itr)->getDate().getDay() == dayMax)
					{
						if ((*itr)->getDate().getHour() > hourMax)
						{
							yearMax = (*itr)->getDate().getYear();
							monthMax = (*itr)->getDate().getMonth();
							dayMax = (*itr)->getDate().getDay();
							hourMax = (*itr)->getDate().getHour();
							minuteMax = (*itr)->getDate().getMinute();
							i++;
						}
						else if ((*itr)->getDate().getHour() == hourMax)
						{
							if ((*itr)->getDate().getMinute() > minuteMax)
							{
								yearMax = (*itr)->getDate().getYear();
								monthMax = (*itr)->getDate().getMonth();
								dayMax = (*itr)->getDate().getDay();
								hourMax = (*itr)->getDate().getHour();
								minuteMax = (*itr)->getDate().getMinute();
								i++;
							}
						}
					}
				}
			}

		}
		// Advances to the max.

		itr = friendsStatuses.begin();
		itrUser = users.begin();
		advance(itr, i);
		advance(itrUser, i);

		//Prints
		cout << *itrUser << "'s status: ";
		(*itr)->printStatus();

		// Erases from lists after using.
		friendsStatuses.erase(itr);
		users.erase(itrUser);

		count++;
		len--;
	}
}

const string Member::getName() const
{
	return name;
}

void Member::printFanPages()
{
	vector<FanPage*>::iterator itr = VfanPages.begin();
	vector<FanPage*>::iterator itrEnd = VfanPages.end();
	int i = 1;

	if (VfanPages.size() == 0)
		cout << this->name << " has no fan pages!" << endl;
	else
		cout << this->name << "'s fan pages: " << endl;

	for (; itr != itrEnd; ++itr) // runs over all fan pages to print its name
	{
		cout << i << " - " << (*itr)->getName() << endl;
		i++;
	}
}

void Member::printFriends()
{
	vector<Member*>::iterator itr = Vfriends.begin();
	vector<Member*>::iterator itrEnd = Vfriends.end();
	int i = 1;
	try
	{
		areThereFriends(Vfriends.size()); // exception potential
		cout << endl << name << "'s friends:" << endl;

		for (; itr != itrEnd; ++itr) // runs over all friends to print
		{
			cout << i << " - " << (*itr)->getName() << endl;
			i++;
		}
	}
	catch (noFriendsToMemberException& ex)
	{
		cout << endl << "\n*** " << name << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void Member::printStatuses()
{
	list<Status*>::iterator itr = LbillBoard.begin();
	list<Status*>::iterator itrEnd = LbillBoard.end();
	try
	{
		areThereStatuses(LbillBoard.size());  // exception potential
		cout << endl << name << "'s statuses:" << endl;
		for (; itr != itrEnd; ++itr)
		{
			(*itr)->printStatus(); // exception potential
			cout << endl;
		}
	}
	catch (noStatusException& ex)
	{
		cout << endl << "\n*** " << name << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

const Date& Member::getBirthDay() const
{
	return birthDay;
}

// operators:

Member& Member::operator+=(Member& member)
{
	bool flag = false;
	vector<Member*>::iterator itr = Vfriends.begin();
	vector<Member*>::iterator itrEnd = Vfriends.end();

	for (; itr != itrEnd; ++itr)		// Checks if the current member is already in the friends' array.
	{
		if ((*itr)->getName() == member.getName())
		{
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		Vfriends.push_back(&member); // adds the last member in list
		member += *this;		     // mutual add
	}
	return *this;
}

Member& Member::operator+=(FanPage& page)
{
	bool flag = false;
	vector<FanPage*>::iterator itr = VfanPages.begin();
	vector<FanPage*>::iterator itrEnd = VfanPages.end();

	for (; itr != itrEnd; ++itr)		// Checking if the current member is already a fan.
	{
		if ((*itr)->getName() == page.getName())
		{
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		VfanPages.push_back(&page); // adds the last fan page in list
		page += *this;				// mutual add
	}
	return *this;
}

Member& Member::operator-=(Member& member)
{
	vector<Member*>::iterator itr = Vfriends.begin();
	vector<Member*>::iterator itrEnd = Vfriends.end();
	bool flag = false;

	for (; itr != itrEnd; ++itr)         // Checking if the current member is already in the friends' array.
	{
		if ((*itr)->getName() == member.getName()) // checks if member is in list (by unique name)
		{
			flag = true;
			break;
		}
	}
	if (flag == true)
	{
		Vfriends.pop_back();		// removes the last member in list
		member -= *this; // mutual remove
	}
	return *this;
}

Member& Member::operator-=(FanPage& page)
{
	vector<FanPage*>::iterator itr = VfanPages.begin();
	vector<FanPage*>::iterator itrEnd = VfanPages.end();
	bool flag = false;
	for (; itr != itrEnd; ++itr)				// runs over VfanPages list
	{
		if ((*itr)->getName() == page.getName()) // checks if page is in list (by unique name)
		{
			flag = true;
			break;
		}
	}
	if (flag == true)
	{
		VfanPages.pop_back();	 // removes the last fan page in list
		page -= *this;	 // mutual remove
	}
	return *this;
}

bool Member::operator>(Member& other)
{
	return (this->getVfriends().size() > other.getVfriends().size());
}

bool Member::operator>(FanPage& page)
{
	return (this->getVfriends().size() > page.getVfans().size());
}

ostream& operator<<(ostream& os, const Member& mem)
{
	// writes to file: member's name, birthday, statuses and friends
	os << mem.name << endl;
	os << mem.getBirthDay() << endl;
	os << mem.LbillBoard.size() << endl; // num of statuses

	list<Status*>::const_iterator itr = mem.LbillBoard.begin();
	list<Status*>::const_iterator itrEnd = mem.LbillBoard.end();
	for (; itr != itrEnd; ++itr)
	{
		os << typeid(*itr).name() + CLASS_LEN << endl; // type of status (Status, Picture, Video)
		os << (*itr)->getText() << endl; // text
		os << (*itr)->getDate() << endl; // date
	}
	return os;
}

ifstream& operator>>(ifstream& in, Member& mem)
{
	getline(in, mem.name);
	in >> mem.birthDay;
	return in;
}

void Member::operator=(const Member& other)
{
	this->name = other.name;
	Vfriends = other.Vfriends;
	VfanPages = other.VfanPages;
	LbillBoard = other.LbillBoard;
	birthDay = other.birthDay;
}

const Member& Member::operator=(Member&& other)
{
	if (this != &other)
	{
		this->name = other.name;
		Vfriends = other.Vfriends;
		VfanPages = other.VfanPages;
		LbillBoard = other.LbillBoard;
		birthDay = other.birthDay;
	}
	return *this;
}

// exceptions:
void Member::areThereStatuses(const int size)
{
	if (size == 0)
		throw noStatusException();
}

void Member::areThereFriends(const int size)
{
	if (size == 0)
		throw noFriendsToMemberException();
}

