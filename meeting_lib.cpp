#include"./data.h"
Meeting::Meeting()
{

}

void Meeting::setData(MeetingData meeting_data)
{
    meeting_data_=meeting_data;
}

QString Meeting::getName()
{
    return meeting_data_.meeting_name;
}

MeetingData Meeting::getData()
{
    return meeting_data_;
}



Meeting::~Meeting()
{

}



