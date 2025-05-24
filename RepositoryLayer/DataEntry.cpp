//
// Created by Cristian Pavel on 24.05.2025.
//

#include "DataEntry.h"

QString DataEntry::getContent() const{
    return content;
}
QString DataEntry::getDate() const{
    return date;
}
QString DataEntry::getTitle() const {
    return title;
}
void DataEntry::setContent(const QString &givenContent) {
    content=givenContent;
}
void DataEntry::setDate(const QString &givenDate) {
    date=givenDate;
}
void DataEntry::setTitle(const QString &givenTitle) {
    title=givenTitle;
}
