#ifndef __FANPAGE_H
#define __FANPAGE_H

#define MAX_NAME_LEN 51
#define MAX_STATUS_LEN 201

#include <string>
#include <list>
#include <vector>
#include "Member.h"
class Status;
#pragma warning(disable: 4996)

class FanPage
{
private:
	std::vector<Member*> Vfans;			// vector of all members that are fans of this page
	std::list<Status*> LallStatuses;	// vector of all statuses of this page
	std::string name;					// page name

public:
	FanPage() = default;
	FanPage(const std::string& name); // avoids cloning members fan page
	FanPage(const FanPage& other);
	FanPage(std::ifstream& in);
	~FanPage();

	const std::vector<Member*>& getVfans() const;
	const std::string getName() const;

	void addStatus(const std::string& text, const int statusType);
    void addStatus(std::ifstream& in, int statusType);

	void printFans();
	void printStatuses();

	// operators:
	FanPage& operator+=(Member& member);
	FanPage& operator-=(Member& member);
	bool operator>(FanPage& other);
	bool operator>(Member& mem);
	
	friend std::ostream& operator<<(std::ostream& os, const FanPage& page);
    friend std::ifstream& operator>>(std::ifstream& in, FanPage& page);

	// exceptions:
	void areThereStatuses(int size);
	void areThereFans(const int size);
};
#endif // __FANPAGE_H