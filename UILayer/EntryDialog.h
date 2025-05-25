// UILayer/EntryDialog.h
#pragma once
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class EntryDialog final : public QDialog {
public:
    EntryDialog(const QString& title, const QString& date, const QString& content, QWidget* parent = nullptr)
        : QDialog(parent) {
        setWindowTitle(title+"  ("+date+")");

        auto* mainLayout = new QVBoxLayout(this);

        auto* titleDateWidget = new QWidget(this);
        auto* titleDateLayout = new QVBoxLayout(titleDateWidget);
        titleDateLayout->setSpacing(8);
        titleDateLayout->setContentsMargins(0, 0, 0, 0);

        auto* titleLabel = new QLabel("<b>" + title + "</b>", this);
        auto* dateLabel = new QLabel("<i>" + date + "</i>", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        dateLabel->setAlignment(Qt::AlignCenter);

        titleDateLayout->addWidget(titleLabel);
        titleDateLayout->addWidget(dateLabel);

        titleDateWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        mainLayout->addWidget(titleDateWidget, 0, Qt::AlignHCenter);
        mainLayout->addSpacing(20);

        auto* contentLabel = new QLabel(content, this);
        contentLabel->setWordWrap(true);
        contentLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        mainLayout->addWidget(contentLabel);

        setLayout(mainLayout);
        setMinimumSize(500, 500);
        setStyleSheet(
            "QDialog { background: #EAEAEA;} "
            "QLabel { color: #2B3232; font-size: 16px; }"
        );
    }
};