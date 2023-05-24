#ifndef __MEMBER_H
#define __MEMBER_H

#define TO_ARRANGE 10
#define CLASS_LEN 6
#define MAX_NAME_LEN 51

#include "Date.h"
#include <typeinfo>
#include <string>
#include <fstream>
#include <vector>
#include <list>

class FanPage;
class Status;

class Member
{
private:
    std::vector<Member*> Vfriends;   // vector of friends of this member
    std::vector<FanPage*> VfanPages; // vector of fan pages that this member is a fan of
    std::list<Status*> LbillBoard;    // list of all member's statuses
    std::string name;                // member's name
    Date birthDay;                   // member's name

public:
    Member(const Date& birthDay, const std::string& name);
    Member(const Member& other);
    Member(Member&& other);
    Member(std::ifstream& in);
    Member() = delete;
    ~Member();

    std::vector<Member*>& getVfriends();
    const std::vector<FanPage*>& getVfanPages() const;
    const std::string getName() const;
    const std::list<Status*> getBillBoard() const;
    const Date& getBirthDay()    const;
    FanPage& getFanPage(int i);
    Member& getFriend(int i);

    void addStatus(const std::string& text, const int statusType);
    void addStatus(std::ifstream& in, int statusType);

    void arrange10FriendsStatuses();
    void print10FriendsStatuses(std::list<Status*> friendsStatuses, int len, std::list<std::string> users);

    void printFriends();
    void printFanPages();
    void printStatuses();

    // operators
    Member& operator+=(Member& member);
    Member& operator+=(FanPage& page);
    Member& operator-=(Member& member);
    Member& operator-=(FanPage& page);
    bool operator>(Member& other);
    bool operator>(FanPage& page);
    void operator=(const Member& other);
    const Member& operator=(Member&& other);

    friend std::ostream& operator<<(std::ostream& os, const Member& mem);
    friend std::ifstream& operator>>(std::ifstream& in, Member& mem);

    // exceptions:
    void areThereStatuses(const int size);
    void areThereFriends(const int size);
};
#endif // __MEMBER_H