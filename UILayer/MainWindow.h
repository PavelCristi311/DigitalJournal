//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QHBoxLayout>
#include "../ControllerLayer/Controller.h"
#include "../ControllerLayer/AIHelper.h"
#include <QEvent>
#include <QMouseEvent>

class MainWindow final : public QMainWindow {
    Q_OBJECT
    Controller* controller;
    QListWidget* entryList{};
    QLineEdit* titleEdit{};
    QLineEdit* contentEdit{};
    QLineEdit* filterEdit1{};
    QLineEdit* filterEdit2{};
    QPushButton* addButton{};
    QPushButton* updateButton{};
    QPushButton* removeButton{};
    QPushButton* undoButton{};
    QPushButton* redoButton{};
    QPushButton* filterAndButton{};
    QPushButton* filterOrButton{};
    QPushButton* showAllButton{};
    QPushButton* sentimentButton{};
    QPushButton* grammarButton{};
    QPushButton* chatbotButton{};

    void setupUI();
    void refreshList(const std::vector<DataEntry>& entries) const;
    std::function<void()> updateButtonStates;
private slots:
    void onAdd() const;
    void onUpdate() const;
    void onRemove() const;
    void onUndo() const;
    void onRedo() const;
    void onFilterAnd() const;
    void onFilterOr() const;
    void onListSelectionChanged() const;
    void onEntryDoubleClicked(const QListWidgetItem* item);
    void onShowAll() const;
public slots:
    void onChatbot() const;
private:
    QString getUserInput();
    AIHelper* aiHelper;
    QListWidget* chatHistory{};
    QLineEdit* chatInput{};
    mutable std::vector<DataEntry> currentlyDisplayedEntries;
protected:
    void resizeEvent(QResizeEvent* event) override;
    void updateChatMessagesWidth() const;
    void setupListWidgetProperties() const;
public:
    explicit MainWindow(Controller* ctrl, QWidget* parent = nullptr);
};

#endif //MAINWINDOW_H
