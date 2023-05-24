#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <iostream>
#include <string>

#pragma warning(disable: 4996)

class FacebookException :public std::exception // general fail in system
{
public:
	const char* what() const override { return "\n*** Failed while running Facebook system ***\n"; }
};

class emptyTextException :public std::exception // user enters empty name/status ""
{
public:
	const char* what() const override { return " can't be empty ***\n"; }
};

class duplicateNamesException :public std::exception // user enters name that already exist in system
{
public:
	const char* what() const override { return "\n** Name is already taken ***\n"; }
};

class letterException :public std::exception // user enters number in name input
{
public:
	const char* what() const override { return "\n*** Invalid name ***\n"; }
};

class dateException :public std::exception // user enters wrong date
{
public:
	const char* what() const override { return "\n*** Invalid date***\n"; }
};

class letterInDateException :public std::exception // user enters letter in date input
{
public:
	const char* what() const override { return "\n*** Invalid date***\n"; }
};

class selfFriendshipException :public std::exception // Member adds himself to friends
{
public:
	const char* what() const override { return "\n*** Member can't be a friend with himself ***\n"; }
};

class multiFriendException :public std::exception
{
public:
	const char* what() const override { return " is a friend with all members in system already ***\n"; }
};

class alreadyFriendException :public std::exception
{
public:
	const char* what() const override { return " is already a friend of "; }
};

class noFriendsInSystemException :public std::exception
{
public:
	const char* what() const override { return "\n*** All members in system have no friends yet ***\n"; }
};

class noFriendsToMemberException :public std::exception
{
public:
	const char* what() const override { return " has no friends yet ***\n"; }
};

class noFansToPageException :public std::exception
{
public:
	const char* what() const override { return " has no fans yet ***\n"; }
};

class alreadyFanException :public std::exception
{
public:
	const char* what() const override { return " is already a fan of "; }
};

class noFansException :public std::exception
{
public:
	const char* what() const override { return "\n*** All members in system are not fans of any page yet ***\n"; }
};

class noMembersException :public std::exception
{
public:
	const char* what() const override { return "\n*** There are no members in the system yet ***\n"; }
};

class noFanPagesException :public std::exception
{
public:
	const char* what() const override { return "\n*** There are no fan pages in the system yet ***\n"; }
};

class noStatusException :public std::exception
{
public:
	const char* what() const override { return " has no statuses ***\n"; }
};
#endif // __EXCEPTIONS_H