//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef ENTRYWIDGET_H
#define ENTRYWIDGET_H
#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class EntryWidget final : public QWidget {
public:
    EntryWidget(const QString& title, const QString& date, QWidget* parent = nullptr)
        : QWidget(parent) {
        auto* layout = new QVBoxLayout(this);
        auto* titleLabel = new QLabel(title, this);
        auto* dateLabel = new QLabel(date, this);
        titleLabel->setStyleSheet("font-weight: bold; color: #2B3232;");
        dateLabel->setStyleSheet("color:#2B3232");
        titleLabel->setAlignment(Qt::AlignCenter);
        dateLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(titleLabel);
        layout->addWidget(dateLabel);
        setLayout(layout);
        setFixedSize(200, 200); // Square-like
        setStyleSheet("background: #EAEAEA; border: 1px solid black; border-radius: 30px;");
    }
};
#endif //ENTRYWIDGET_H
