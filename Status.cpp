#include "Status.h"
#include "Date.h"
#include "Exceptions.h"
using namespace std;

Status::Status(const string& text) noexcept(false)
{
    isEmpty(text);
    setText(text);
}

Status::Status(ifstream& in)
{
	getline(in, text);
    Date d(in);
    date = d;
}

Picture::Picture(ifstream& in)
{
    getline(in, text);
    Date d(in);
    date = d;
}

Video::Video(ifstream& in)
{
    getline(in, text);
    Date d(in);
    date = d;
}

Status::Status(const Status& other)
{
    date = other.date;
    text = other.text;
}

Status::Status(Status&& other)
{
    date = other.date;
    text = other.text;
}

void Status::setDate(Date date)
{
    this->date = date;
}

void Status::setText(const string& text)
{
    this->text = text;
}

const string& Status::getText() const
{
    return text;
}

void Status::printStatus() const
{
    cout << "Published at: ";
    date.dayShow();
    cout << ", ";
    date.timeShow();
    cout << text << endl;
}

const Date Status::getDate() const
{
    return date;
}

// operators:

bool Status::operator==(const Status& other) const
{
    return (this->getText() == other.getText());
}

bool Status::operator!=(const Status& other) const
{
    return (this->getText() != other.getText());
}

void Status::operator=(const Status& other)
{
    date = other.date;
    text = other.text;
}

const Status& Status::operator=(Status&& other)
{
    if (this != &other)
	{
        date = other.date;
        text = other.text;
	}
    return *this;
}

// exceptions:

void Status::isEmpty(const string& text)
{
    if (text[0] == '\0')
        throw emptyTextException();
}
