#include"./data.h"
Meeting::Meeting()
{

}
void Meeting::setShareSecret(QString data)
{
    share_serect_=data;
}
void Meeting::setDomainName(QString domain_name)
{
    domain_name_=domain_name;
}
void Meeting::setData(MeetingData meeting_data)
{
    vector<AttendeeData> sort;
    meeting_data_=meeting_data;
    attendees_.resize(meeting_data_.attendees.size());
        for(int j=0;j<meeting_data_.attendees.size();j++)
        {
            QString role=meeting_data_.attendees[j].role;

            if(role!="MODERATOR")
            {
                AttendeeData insert_front;
                insert_front.role=meeting_data_.attendees[j].role;
                insert_front.name=meeting_data_.attendees[j].name;
                sort.push_back(insert_front);

            }
            else
            {
               sort.insert(sort.begin(),meeting_data.attendees[j]);
            }

    }

    meeting_data_.attendees.swap(sort);

    for(int i=0;i<meeting_data_.attendees.size();i++)
    {
        attendees_[i].setData(meeting_data_.attendees[i]);
    }
    //qDebug()<<meeting_data_.meeting_name;
    generateAttendingURL();
}

QString Meeting::getName()
{
    //qDebug()<<meeting_data_.meeting_name;
    return meeting_data_.meeting_name;
}

MeetingData Meeting::getData()
{
    return meeting_data_;
}
void Meeting::generateAttendingURL()
{
    //QString share_serect="OxzJf6PFXpvo9ovT3oOAzlIAZHUlKXI8SPPnay4";
    FindString find_str;
    QString user_name="serverManager";
    QString str_and="&";
    QString str_equ="=";
    QString query_string;
    //QString query_string="createname=Test+Meeting&meetingID=abc123&attendeePW=111222&moderatorPW=333444639259d4-9dd8-4b25-bf01-95f9567eaf4b";
    query_string="join"+find_str.full_name+"="+user_name+"&"+find_str.meeting_id+"="+meeting_data_.meeting_id+"&password="+meeting_data_.moderator_pw+"&redirect=true"+share_serect_;
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(query_string.toUtf8().data());
    QByteArray checksum;
    checksum=hash.result().toHex();
    //qDebug()<<checksum;
    meeting_data_.attending_URL="https://"+domain_name_+"/bigbluebutton/api/join?"+find_str.full_name+"="+user_name+"&"+find_str.meeting_id+"="+meeting_data_.meeting_id+"&password="+meeting_data_.moderator_pw+"&redirect=true&checksum="+checksum;

    //qDebug()<<meeting_data_.attending_URL;
}

Meeting::~Meeting()
{

}



