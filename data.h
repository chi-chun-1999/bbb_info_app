#ifndef __DATA_H__
#define __DATA_H__

#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<QString>
#include<QStringList>
#include<QDebug>
#include<QXmlStreamReader>
#include<QCryptographicHash>
#include<QByteArray>


using namespace std;

typedef struct AttendeeData
{
    QString name;
    QString role;
}AttendeeData;

typedef struct MeetingData
{
    QString meeting_name;
    QString meeting_id;
    QString create_date;
    QString attendee_pw;
    QString moderator_pw;
    QString attending_URL;
    vector<AttendeeData> attendees;
}MeetingData;

typedef struct FindString
{
    QString meeting="meeting";
    QString meeting_id="meetingID";
    QString meeting_name="meetingName";
    QString create_date="createDate";
    QString full_name="fullName";
    QString attendee_pw="attendeePW";
    QString moderator_pw="moderatorPW";
    QString role="role";
    QString attendee="attendee";
    QString attendees="attendees";

}FindString;

class XmlReader:public QXmlStreamReader
{
    public:

        XmlReader();
        void readData();
        vector<MeetingData> getMeetingData();
        ~XmlReader();

    private:
        vector<MeetingData> meeting_data;

};

class Attendee
{
    public:
        Attendee();
        QString getName();
        QString getRole();
        void setData(AttendeeData data);
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
        void setShareSecret(QString data);
        void setDomainName(QString domain_name);
        void setData(MeetingData meeting_data);
        void generateAttendingURL();
        QString getAttendingURL();

        ~Meeting();
    private:
        QString share_serect_;
        QString domain_name_;
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
        void setData(QString data);
        void setShareSecret(QString data);

        MeetingData getCurrentMeetingData(int index);
        vector<QString> getMeetingsName();
        int getMeetingNum();

        void setMeetings();
        string splitString(string src,string split_text);
        ~Server();
    private:
        QString share_serect_;
        FindString find_string;
        vector<Meeting> meetings_;
        vector<QString> meeting_names_;
        QString domain_name_;
        QString getMeetings_URL_;

        XmlReader *xml_reader_=new XmlReader;
};

#endif
