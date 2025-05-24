//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef DATAENTRY_H
#define DATAENTRY_H
#pragma once
#include <QString>
#include <utility>


class DataEntry {
private:
    QString title;
    QString content;
    QString date;
public:
    DataEntry(QString  givenTitle, QString  givenContent, QString  givenDate): title(std::move(givenTitle)),content(std::move(givenContent)),date(std::move(givenDate)){}

    [[nodiscard]] QString getTitle() const;
    [[nodiscard]] QString getContent() const;
    [[nodiscard]] QString getDate() const;
    void setTitle(const QString& givenTitle);
    void setContent(const QString& givenContent);
    void setDate(const QString& givenDate);

};
#endif //DATAENTRY_H
