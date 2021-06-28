#include"./data.h"

Server::Server()
{

}

void Server::setGetMeetingsURL(QString domain_name)
{
    domain_name_=domain_name;
    domain_name_="bbb2.ical.tw";
    QString https="https://";
    QString bbb="/bigbluebutton/api/getMeetings?checksum=";
    QString checksum="b2f3e005ff665505815084b10070d557289d0f13";

    getMeetings_URL_=https+domain_name_+bbb+checksum;

}

QString Server::getMeetings()
{
    return getMeetings_URL_;
}
void Server::getData(QString data)
{
    int meeting_str_times=0;
    bool save=0;
    vector<MeetingData> meeting_data;
    MeetingData tmp;
    //string data_str=data.toUtf8().constData();
    //cout<<data_str<<endl;
    QStringList lines=data.split("\n",QString::SkipEmptyParts);
    foreach(QString line,lines)
    {
        string::size_type found;
        string line_str=line.toUtf8().constData();
        if(line_str.find("meeting>")!=string::npos)
        {
            meeting_str_times++;
        }
        if(meeting_str_times%2==1)
        {
            save=1;
            found=line_str.find(find_string.meeting_name);
           if(found!=string::npos)
           {
              string str=splitString(line_str,find_string.meeting_name);
                tmp.meeting_name=QString::fromStdString(str);

           }
        }
        else if(meeting_str_times%2==0&&save==1)
        {
           meeting_data.push_back(tmp);
           tmp.meeting_name="";
           save=0;
        }

    }

    for(auto &iter:meeting_data)
    {
        qDebug()<<iter.meeting_name;
    }
}
string Server::splitString(string src,string split_text)
{
   cout<<src<<endl;
    string::size_type first_position,last_position;
    string split_first="<"+split_text+">";
    string split_second="</"+split_text+">";

    string outcome="";

    first_position=src.find_first_not_of(split_first);
    last_position=src.find_last_of(split_second);
    cout<<last_position<<endl;
    outcome.append(src.begin()+first_position,src.begin()+last_position-2-split_text.length());
    return outcome;
}
Server::~Server()
{}
