#ifndef __FACEBOOK_H
#define __FACEBOOK_H

#define MAX_NAME_LEN 51
#define MAX_STATUS_LEN 201
#define FIRST 1
#define ONE 1
#define THREE 3
#define LAST_MONTH 12
#define LAST_DAY 31
#define PRE_HISTORIC 1900
#define AFTER_LIFE 120
#define REGRET 0

#pragma warning(disable: 4996)

#include <ctime>
#include <list>
#include <vector>
#include <string>

#include "Member.h"
#include "FanPage.h"
#include "Exceptions.h"
#include <fstream>

class Status;

class Facebook
{
private:
	std::list<Member> Lmembers; // holds all members in system
	std::list<FanPage> Lpages;  // holds all fan pages in system

public:
	Facebook() = default;
	Facebook(const Facebook& facebook) = delete;
	~Facebook() = default;
	std::list<Member>& getMembersArr();
	std::list<FanPage>& getPagesArr();

	void addMember();									  		
	void addMember(const std::string& name, Date date);         // case 1
	void addMember(std::ifstream& inFile);
	void addFanPage();											
	void addFanPage(const std::string& name);			 		// case 2
	void addFanPage(std::ifstream& inFile);			 			
	void addStatus(int choice);									// case 3
	void addStatus(Member& member, const std::string& text);    // case 3
	void addStatus(FanPage& page, const std::string& text);     // case 3
	void showStatuses(int choice);								// case 4
	void latest10Statuses();									// case 5
	void addFriendToMember();									// case 6
	void cancelFriendship();									// case 7
	void addMemberToPage();										// case 8
	void addMemberToPage(Member& member, FanPage& page);		// case 8
	void removeFan();											// case 9
	void printAllEntities();									// case 10
	void showAll(int choice);									// case 11

	// operators:
	friend std::ostream& operator<<(std::ostream& os, Facebook& f);
	friend std::ifstream& operator>>(std::ifstream& in, Facebook& f);

	// Validations:
	const std::string getStatus();
	const std::string getName(int nameType, int size);			// size of members/fan pages (according to nameType value)
	const Date& getDate();
	void printAllMembersInSystem();
	void printAllPagesInSystem();
	void chooseStatusType(int& choice);
	
	// exceptions:
	void isValidChoice(int num, int min, int max);
	void isEmpty(const std::string& name);
	void dupCheck(const std::string& name1, const std::string& name2);
	void noFriendsInSystem(const int i);
	void noFriendsToMember(const int i);
	void noFans(const int i);
	void dateCheck(const int day, const int month, const int year);
	void isAlreadyFan(const std::string& name1, const std::string& name2);
	void isAlreadyFriend(const std::string& name1, const std::string& name2);
	void selfie(const int choice1, const int choice2);
	void friendWithAllMembers(const int size1, const int size2);
	void noUsersInSystem(const int size);
	void noPagessInSystem(const int size);
	void lettersCheck(const std::string& name);
};

#endif //__FACEBOOK_H
