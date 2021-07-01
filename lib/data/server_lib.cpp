#include"./data.h"

Server::Server()
{

}

void Server::setGetMeetingsURL(QString domain_name)
{
    domain_name_=domain_name;
    //domain_name_="bbb2.ical.tw";
    QString https="https://";
    QString bbb="/bigbluebutton/api/getMeetings?checksum=";
    QString query_string;

    query_string="getMeetings"+share_serect_;
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(query_string.toUtf8().data());
    QByteArray checksum;
    checksum=hash.result().toHex();

    getMeetings_URL_=https+domain_name_+bbb+checksum;
    qDebug()<<getMeetings_URL_;
}

QString Server::getMeetings()
{
    return getMeetings_URL_;
}
void Server::setData(QString data)
{
    xml_reader_=new XmlReader();
    xml_reader_->addData(data);

    xml_reader_->readData();

    if(xml_reader_->errorReadXml()==0)
    {
        vector<MeetingData> meeting_data=xml_reader_->getMeetingData();

        meetings_.resize(meeting_data.size());
        for(int i=0;i<meeting_data.size();i++)
        {
            meetings_[i].setDomainName(domain_name_);
            meetings_[i].setShareSecret(share_serect_);
            meetings_[i].setData(meeting_data[i]);
        }

    }

}

ServerError Server::errorReadXml()
{
    return xml_reader_->errorReadXml();
}

void Server::setShareSecret(QString data)
{
    share_serect_=data;
}

MeetingData Server::getCurrentMeetingData(int index)
{
    return meetings_[index].getData();
}

vector<QString> Server::getMeetingsName()
{
    for(auto& iter:meetings_)
    {
        meeting_names_.push_back(iter.getName());
    }

    return meeting_names_;
}

int Server::getMeetingNum()
{
    return meetings_.size();
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
