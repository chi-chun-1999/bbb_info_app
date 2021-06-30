#include"data.h"

XmlReader::XmlReader()
{

}
void XmlReader::readData()
{
    qDebug()<<"Strart to read data...";
    MeetingData tmp;
    AttendeeData tmp_attendee_data;

    FindString find_str;

    while(!atEnd())
    {

        this->readNext();
        if(this->isStartElement())
        {
            if(this->name()==find_str.meeting_name)
            {
                tmp.meeting_name=readElementText();
            }
            if(this->name()==find_str.meeting_id)
            {
                tmp.meeting_id=readElementText();
            }
            if(this->name()==find_str.create_date)
            {
                tmp.create_date=readElementText();
            }
            if(this->name()==find_str.attendee_pw)
            {
                tmp.attendee_pw=readElementText();
            }
            if(this->name()==find_str.moderator_pw)
            {
                tmp.moderator_pw=readElementText();
            }
            if(this->name()==find_str.full_name)
            {
                tmp_attendee_data.name=this->readElementText();
            }
            if(this->name()==find_str.role)
            {
                tmp_attendee_data.role=this->readElementText();
            }
        }
        if(this->isEndElement())
        {

            if(this->name()==find_str.attendee)
            {
                //qDebug()<<"";
                tmp.attendees.push_back(tmp_attendee_data);
                tmp_attendee_data.name="";
                tmp_attendee_data.role="";
            }

            if(this->name()==find_str.meeting)
            {
                meeting_data.push_back(tmp);
                tmp.meeting_name="";
                tmp.create_date="";
                tmp.attendee_pw="";
                tmp.moderator_pw="";
                tmp.attending_URL="";
                tmp.attendees.clear();
            }

        }
    }
}
vector<MeetingData> XmlReader::getMeetingData()
{
    return meeting_data;
}
XmlReader::~XmlReader()
{
}
