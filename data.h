#ifndef __DATA_H__
#define __DATA_H__

#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<QString>
#include<QStringList>
#include<QDebug>

using namespace std;

typedef struct AttendeeData
{
    QString name;
    QString role;
}AttendeeData;

typedef struct MeetingData
{
    QString meeting_name;
    QString date;
    QString attending_URL;
    vector<AttendeeData> attendees;
}MeetingData;

typedef struct FindString
{
    string meeting="meeting";
    string meeting_name="meetingName";
    string attendee_pw="attendeesPW";
}FindString;

class Attendee
{
    public:
        Attendee();
        QString getName();
        QString getRole();
        AttendeeData getData();

        ~Attendee();
    private:
        QString name;
        QString role;
        AttendeeData attendee_data_;
};

class Meeting
{
    public:
        Meeting();
        QString getName();
        MeetingData getData();

        void setMeetingName(QString name);
        void setAttendee(QString attendee_name,QString role);
        void setPW(QString attendeesPW,QString moderatorPW);
        ~Meeting();
    private:
        QString name_;
        QString date_;
        QString attendeePW_;
        QString moderatorPW_;
        QString attending_URL_;
        vector<Attendee> attendees_;
        MeetingData meeting_data_;
};

class Server
{
    public:
        Server();
        QString getMeetings();//used for get https request
        void setGetMeetingsURL(QString domain_name);
        void getData(QString data);
        MeetingData getCurrentMeetingData();
        vector<QString> getMeetingsName();
        void setMeetings();
        string splitString(string src,string split_text);
        ~Server();
    private:
        FindString find_string;
        vector<Meeting> meetings_;
        vector<QString> meeting_names_;
        QString domain_name_;
        QString getMeetings_URL_;
};

#endif
