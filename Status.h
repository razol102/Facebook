#ifndef __STATUS_H
#define __STATUS_H

#include "Date.h"
#include <fstream>
#define MAX_STATUS_LEN 201

class Status
{
protected:
	Date date;
	std::string text;

public:
	Status() = default;
	Status(const std::string& text) noexcept(false);
	Status(std::ifstream& in);
	Status(const Status& other);
	Status(Status&& other);
	virtual ~Status() = default;

	void setDate(Date date);
	void setText(const std::string& text);
	const std::string& getText()	const;
	const Date getDate()			const;
	virtual void printStatus()		const;

	// operators:
	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;
	void operator=(const Status& other);
	const Status& operator=(Status&& other);

	// exceptions:
	void isEmpty(const std::string& text);
};

class Picture : public Status
{

public:
	Picture() = default;
	Picture(const std::string& text) : Status(text) {};
	Picture(std::ifstream& in);
	virtual void printStatus() const override
	{
		Status::printStatus();
		system("start mypicture.jpg");
		std::cout << std::endl;
	}
};

class Video : public Status
{
public:
	Video() = default;
	Video(const std::string& text) : Status(text) {};
	Video(std::ifstream& in);
	virtual void printStatus() const override
	{
		Status::printStatus();
		system("start myvideo.mov");
		std::cout << std::endl;
	}
};
#endif // __STATUS_H