#include "FanPage.h"
#include "Status.h"
#include "Member.h"
#include "Exceptions.h"
using namespace std;

FanPage::FanPage(const string& name)
{
	this->name = name;
}

FanPage::FanPage(const FanPage& other)
{
	Vfans = other.Vfans;
	LallStatuses = other.LallStatuses;
	name = other.name;
}

FanPage::~FanPage()
{
	list<Status*>::iterator itr = LallStatuses.begin();
	list<Status*>::iterator itrEnd = LallStatuses.end();

	for (; itr != itrEnd; ++itr)
		delete* itr;
}

FanPage::FanPage(ifstream& in)
{
	in >> *this;
}

const vector<Member*>& FanPage::getVfans() const
{
	return Vfans;
}

const string FanPage::getName() const
{
	return name;
}

void FanPage::addStatus(const string& text, const int statusType)
{
	try
	{
		switch (statusType)
		{
		case 1: // text only
		{
			Status* newSt = new Status(text); // creates new status
			LallStatuses.push_back(newSt);  // adds new status to the end of VallStatuses list
			break;
		}
		case 2: // picture and text
		{
			Status* newSt = new Picture(text); // creates new status
			LallStatuses.push_back(newSt);  // adds new status to the end of VallStatuses list
			break;
		}
		case 3: // video and text
		{
			Status* newSt = new Video(text); // creates new status
			LallStatuses.push_back(newSt);  // adds new status to the end of VallStatuses list
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

void FanPage::addStatus(std::ifstream& in, int statusType)
{
	switch (statusType)
	{
	case 1: // text only
	{
		Status* newSt = new Status(in); // creates new status
		LallStatuses.push_back(newSt);  // adds new status to the end of VallStatuses list
		break;
	}
	case 2: // picture and text
	{
		Status* newSt = new Picture(in); // creates new status
		LallStatuses.push_back(newSt);  // adds new status to the end of VallStatuses list
		break;
	}
	case 3: // video and text
	{
		Status* newSt = new Video(in); // creates new status
		LallStatuses.push_back(newSt);  // adds new status to the end of VallStatuses list
		break;
	}
	default:
		break;
	}
}

void FanPage::printFans()
{
	vector<Member*>::iterator itr = Vfans.begin();
	vector<Member*>::iterator itrEnd = Vfans.end();
	int i = 0;
	try
	{
		areThereFans(Vfans.size()); // exception potential
		cout << name << "'s fans: ";

		for (; itr != itrEnd; ++itr)
		{
			cout << (*itr)->getName();
			if (i == Vfans.size() - 1)
				cout << "." << endl;
			else
				cout << ", ";
			i++;
		}
	}
	catch (noFansToPageException& ex)
	{
		cout << endl << "\n*** " << name << ex.what();
	}
	catch (...)
	{
		cout << endl << "\n*** Unknown Error ***\n" << endl;
	}
}

void FanPage::printStatuses()
{
	list<Status*>::iterator itr = LallStatuses.begin();
	list<Status*>::iterator itrEnd = LallStatuses.end();
	try
	{
		areThereStatuses(LallStatuses.size());
		cout << endl << name << "'s statuses:" << endl;
		for (; itr != itrEnd; ++itr)
		{
			(*itr)->printStatus();
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

// operators:

FanPage& FanPage::operator+=(Member& member)
{
	bool flag = false;
	vector<Member*>::iterator itr = Vfans.begin();
	vector<Member*>::iterator itrEnd = Vfans.end();

	for (; itr != itrEnd; ++itr)		// Checks if the current member is already a fan.
	{
		if ((*itr)->getName() == member.getName())
		{
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		Vfans.push_back(&member);
		member += *this;
	}
	return *this;
}

FanPage& FanPage::operator-=(Member& member)
{
	vector<Member*>::iterator itr = Vfans.begin();
	vector<Member*>::iterator itrEnd = Vfans.end();

	bool flag = false;
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == member.getName())
		{
			flag = true;
			break;
		}
	}
	if (flag == true)
	{
		Vfans.pop_back();	// removes the last fan in list
		member -= *this;	// mutual remove
	}
	return *this;
}

bool FanPage::operator>(FanPage& other)
{
	return (this->getVfans().size() > other.getVfans().size());
}

bool FanPage::operator>(Member& mem)
{
	return (this->getVfans().size() > mem.getVfriends().size());
}

ostream& operator<<(ostream& os, const FanPage& page)
{
	// writes to file: pages's name, statuses and fans
	os << page.name << endl;
	os << page.LallStatuses.size() << endl; // num of statuses

	list<Status*>::const_iterator status = page.LallStatuses.begin();
	list<Status*>::const_iterator statusEnd = page.LallStatuses.end();
	for (; status != statusEnd; ++status)
	{
		os << typeid(*status).name() + CLASS_LEN << endl; // type of status (Status, Picture, Video)
		os << (*status)->getText() << endl; // text
		os << (*status)->getDate() << endl; // date
	}
	return os;
}

ifstream& operator>>(ifstream& in, FanPage& page)
{
	getline(in, page.name);
	return in;
}


// exceptions:

void FanPage::areThereStatuses(int size)
{
	if (size == 0)
		throw noStatusException();
}

void FanPage::areThereFans(const int size)
{
	if (size == 0)
		throw noFansToPageException();
}