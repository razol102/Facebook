#ifndef __DATE_H
#define __DATE_H

#include <iostream>
#include <fstream>

#pragma warning(disable: 4996)
#define PRE_HISTORIC 1900
#define TWO_DIGITS 10

class Date
{
private:
	int day, month, year, hours, minutes;
public:
	Date();
	Date(int day, int month, int year);
	Date(std::ifstream& in);
	Date(const Date& other);
	~Date() = default;
	void dayShow()			const;
	const int getYear()		const;
	const int getMonth()	const;
	const int getDay()		const;
	const int getHour()		const;
	const int getMinute()	const;
	void timeShow()			const;

	//operators:

	void operator=(const Date& other);
	friend std::ostream& operator<<(std::ostream& os, const Date& d);
	friend std::istream& operator>>(std::istream& in, Date& d);
};
#endif // __DATE_H