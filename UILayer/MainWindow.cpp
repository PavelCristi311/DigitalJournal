//
// Created by Cristian Pavel on 24.05.2025.
//

#include "MainWindow.h"
#include "../ControllerLayer/FilterStrategy/AndFilterStrategy.h"
#include "../ControllerLayer/FilterStrategy/OrFilterStrategy.h"
#include <QMessageBox>
#include <QSoundEffect>
#include "EntryWidget.h"
#include "EntryDialog.h"
#include "../ControllerLayer/AIHelper.h"


MainWindow::MainWindow(Controller* ctrl, QWidget* parent)
    : QMainWindow(parent), controller(ctrl) {
    controller->sortAll();
    aiHelper = new AIHelper(this);
    setupUI();
    aiHelper->setJournalEntries(controller->getAll());
    connect(aiHelper, &AIHelper::replyReceived, this, [this](const QString& reply) {
        auto* aiItem = new QListWidgetItem(chatHistory);

        auto* containerWidget = new QWidget();
        auto* containerLayout = new QHBoxLayout(containerWidget);
        containerLayout->setContentsMargins(0, 0, 0, 0);

        auto* aiLabel = new QLabel("<b>Little Friend:</b> " + reply);
        aiLabel->setWordWrap(true);
        aiLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        aiLabel->setStyleSheet(
            "background-color: #e8dab2;"
            "border-radius: 10px;"
            "padding: 8px 12px;"
            "margin: 2px;"
            "color: #000000;"
            "font-size: 18px;"
        );
        const int availableWidth = chatHistory->width() - 30;
        aiLabel->setMaximumWidth(static_cast<int>(availableWidth * 0.8));
        aiLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

        containerLayout->addWidget(aiLabel);
        containerLayout->addStretch();

        chatHistory->setItemWidget(aiItem, containerWidget);

        const QFontMetrics metrics(aiLabel->font());
        const int textWidth = metrics.horizontalAdvance(reply);
        const int lineHeight = metrics.height();
        const int lineCount = (textWidth / static_cast<int>(availableWidth * 0.8)) + 1;
        const int estimatedHeight = lineHeight * lineCount + 40;

        aiItem->setSizeHint(QSize(containerWidget->width(),
                                 qMax(containerWidget->sizeHint().height(), estimatedHeight)));

        chatHistory->scrollToBottom();
    });
}

void MainWindow::setupUI() {
    setWindowTitle("DigitalJournal");
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* mainLayout = new QHBoxLayout(central);

    auto* journalLayout = new QVBoxLayout();
    entryList = new QListWidget(this);
    setupListWidgetProperties();
    entryList->setFlow(QListView::LeftToRight);
    journalLayout->setAlignment(entryList, Qt::AlignHCenter);
    journalLayout->addWidget(entryList, 1);

    auto* formLayout = new QHBoxLayout();
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Title (maximum 50 characters)");
    titleEdit->setMaxLength(50);
    contentEdit = new QLineEdit(this);
    contentEdit->setPlaceholderText("Content");
    formLayout->addWidget(titleEdit);
    formLayout->addWidget(contentEdit);
    journalLayout->addLayout(formLayout);


    auto* filterLayout = new QHBoxLayout();
    filterEdit1 = new QLineEdit(this);
    filterEdit1->setPlaceholderText("Filter Title");
    filterEdit1->setMaxLength(50);
    filterEdit2 = new QLineEdit(this);
    filterEdit2->setPlaceholderText("Filter Content");
    filterAndButton = new QPushButton("Filter AND", this);
    filterOrButton = new QPushButton("Filter OR", this);
    showAllButton = new QPushButton("Show All", this);
    filterLayout->addWidget(filterEdit1);
    filterLayout->addWidget(filterEdit2);
    filterLayout->addWidget(filterAndButton);
    filterLayout->addWidget(filterOrButton);
    filterLayout->addWidget(showAllButton);
    journalLayout->addLayout(filterLayout);

    auto* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add", this);
    updateButton = new QPushButton("Update", this);
    removeButton = new QPushButton("Remove", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);
    journalLayout->addLayout(buttonLayout);

    mainLayout->addLayout(journalLayout, 2);


    auto* chatLayout = new QVBoxLayout();
    auto* chatTitleLabel = new QLabel("Little Friend AI", this);
    chatTitleLabel->setAlignment(Qt::AlignCenter);

    QFont titleFont("Courier New", 22);
    titleFont.setBold(true);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, 2);
    titleFont.setCapitalization(QFont::AllUppercase);
    chatTitleLabel->setFont(titleFont);


    chatTitleLabel->setStyleSheet(
        "color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #EAEAEA, stop:1 #e8dab2); "
        "background-color: #333333; "
        "border-radius: 10px; "
        "padding: 8px; "
    );
    chatLayout->addWidget(chatTitleLabel);
    chatHistory = new QListWidget(this);
    chatInput = new QLineEdit(this);
    chatInput->setPlaceholderText("Type a message...");
    auto* sendButton = new QPushButton("Send", this);
    chatHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chatHistory->setTextElideMode(Qt::ElideNone);
    chatHistory->setResizeMode(QListView::Adjust);
    chatLayout->addWidget(chatHistory, 1);
    chatLayout->addWidget(chatInput);
    chatLayout->addWidget(sendButton);

    mainLayout->addLayout(chatLayout, 1);

    setCentralWidget(central);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdate);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemove);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::onRedo);
    connect(filterAndButton, &QPushButton::clicked, this, &MainWindow::onFilterAnd);
    connect(filterOrButton, &QPushButton::clicked, this, &MainWindow::onFilterOr);
    connect(showAllButton, &QPushButton::clicked, this, &MainWindow::onShowAll);
    connect(chatInput, &QLineEdit::returnPressed, this, &MainWindow::onChatbot);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onChatbot);
    connect(entryList, &QListWidget::itemSelectionChanged, this, &MainWindow::onListSelectionChanged);
    connect(entryList, &QListWidget::itemDoubleClicked, this, &MainWindow::onEntryDoubleClicked);
    connect(titleEdit,   &QLineEdit::textChanged, this, [this]{ updateButtonStates(); });
    connect(contentEdit, &QLineEdit::textChanged, this, [this]{ updateButtonStates(); });
    updateButtonStates = [this]() {
        undoButton->setEnabled(controller->canUndo());
        redoButton->setEnabled(controller->canRedo());

        const bool hasSelection = entryList->currentRow() >= 0;
        updateButton->setEnabled(hasSelection);
        removeButton->setEnabled(hasSelection);
        addButton->setEnabled(!titleEdit->text().isEmpty() and !contentEdit->text().isEmpty());
    };

    refreshList(controller->getAll());
    setFixedSize(1305, 800);
}

void MainWindow::refreshList(const std::vector<DataEntry>& entries) const {
    entryList->clear();
    entryList->clearSelection();
    entryList->setCurrentRow(-1);
    setupListWidgetProperties();
    for (const auto& entry : entries) {
        auto* item = new QListWidgetItem();
        item->setSizeHint(QSize(200,200));
        entryList->addItem(item);
        entryList->setItemWidget(item, new EntryWidget(entry.getTitle(), entry.getDate()));
    }
    entryList->clearSelection();
    entryList->setCurrentRow(-1);
    if (updateButtonStates) updateButtonStates();
    const auto data_entries = controller->getAll();
    aiHelper->setJournalEntries(data_entries);
}

void MainWindow::onAdd() const {
    const DataEntry entry(titleEdit->text(), contentEdit->text(), QDateTime::currentDateTime().toString("hh:mm:ss / dd.MM.yyyy"));
    controller->add(entry);
    refreshList(controller->getAll());
    titleEdit->clear();
    contentEdit->clear();
}

void MainWindow::onUpdate() const {
    const int row = entryList->currentRow();
    if (row < 0) return;
    const auto entries = controller->getAll();
    if (row >= static_cast<int>(entries.size())) return;
    const QString date = entries[row].getDate();
    const DataEntry newEntry(titleEdit->text(), contentEdit->text(), QDateTime::currentDateTime().toString("hh:mm:ss / dd.MM.yyyy"));
    controller->update(date, newEntry);
    controller->sortAll();
    refreshList(controller->getAll());
    titleEdit->clear();
    contentEdit->clear();

}

void MainWindow::onRemove() const {
    const int row = entryList->currentRow();
    if (row < 0) return;
    const auto entries = controller->getAll();
    if (row >= static_cast<int>(entries.size())) return;
    controller->remove(entries[row].getDate());
    controller->sortAll();
    refreshList(controller->getAll());
    titleEdit->clear();
    contentEdit->clear();
}

void MainWindow::onUndo() const {
    controller->undo();
    controller->sortAll();
    refreshList(controller->getAll());
}

void MainWindow::onRedo() const {
    controller->redo();
    controller->sortAll();
    refreshList(controller->getAll());
}

void MainWindow::onFilterAnd() const {
    auto c1 = [text = filterEdit1->text()](const DataEntry& e) { return e.getTitle().contains(text, Qt::CaseInsensitive); };
    auto c2 = [text = filterEdit2->text()](const DataEntry& e) { return e.getContent().contains(text, Qt::CaseInsensitive); };
    const AndFilterStrategy strategy(c1, c2);
    refreshList(controller->filter(strategy));
    filterEdit1->clear();
    filterEdit2->clear();
    titleEdit->clear();
    contentEdit->clear();
}

void MainWindow::onFilterOr() const {
    auto c1 = [text = filterEdit1->text()](const DataEntry& e) { return e.getTitle().contains(text, Qt::CaseInsensitive); };
    auto c2 = [text = filterEdit2->text()](const DataEntry& e) { return e.getContent().contains(text, Qt::CaseInsensitive); };
    const OrFilterStrategy strategy(c1, c2);
    refreshList(controller->filter(strategy));
    filterEdit1->clear();
    filterEdit2->clear();
    titleEdit->clear();
    contentEdit->clear();
}

void MainWindow::onListSelectionChanged() const {
    const int row = entryList->currentRow();
    if (row < 0) {
        titleEdit->clear();
        contentEdit->clear();
        if (updateButtonStates) updateButtonStates();
        return;
    }
    const auto entries = controller->getAll();
    if (row >= static_cast<int>(entries.size())) return;
    titleEdit->setText(entries[row].getTitle());
    contentEdit->setText(entries[row].getContent());
    if (updateButtonStates) updateButtonStates();
}

void MainWindow::onEntryDoubleClicked(const QListWidgetItem* item) {
    const int row = entryList->row(item);
    if (const auto entries = controller->getAll(); row >= 0 && row < static_cast<int>(entries.size())) {
        const auto& e = entries[row];
        EntryDialog dlg(e.getTitle(), e.getDate(), e.getContent(), this);
        dlg.exec();
    }
}

void MainWindow::onShowAll() const {
    refreshList(controller->getAll());
    filterEdit1->clear();
    filterEdit2->clear();
    titleEdit->clear();
    contentEdit->clear();
}

QString MainWindow::getUserInput() {
    return QInputDialog::getText(this, "Input", "Enter text:");
}

void MainWindow::onChatbot() const {
    const QString text = chatInput->text();
    if (text.isEmpty()) return;
    auto* userItem = new QListWidgetItem(chatHistory);

    auto* containerWidget = new QWidget();
    auto* containerLayout = new QHBoxLayout(containerWidget);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    auto* userLabel = new QLabel("<b>You:</b> " + text);
    userLabel->setWordWrap(true);
    userLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    userLabel->setStyleSheet(
        "background-color: #EAEAEA;"
        "border-radius: 10px;"
        "padding: 8px 12px;"
        "margin: 2px;"
        "color: #000000;"
        "font-size: 18px;"
    );

    const int availableWidth = chatHistory->width() - 30;
    userLabel->setMaximumWidth(static_cast<int>(availableWidth * 0.8));

    userLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

    containerLayout->addStretch();
    containerLayout->addWidget(userLabel);

    chatHistory->setItemWidget(userItem, containerWidget);

    const QFontMetrics metrics(userLabel->font());
    const int textWidth = metrics.horizontalAdvance(text);
    const int lineHeight = metrics.height();
    const int lineCount = (textWidth / static_cast<int>(availableWidth * 0.8)) + 1;
    const int estimatedHeight = lineHeight * lineCount + 40; // Add padding

    userItem->setSizeHint(QSize(containerWidget->width(),
                               qMax(containerWidget->sizeHint().height(), estimatedHeight)));

    chatInput->clear();
    aiHelper->setJournalEntries(controller->getAll());
    aiHelper->sendMessage(text);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    updateChatMessagesWidth();
}

void MainWindow::updateChatMessagesWidth() const {

    const int availableWidth = chatHistory->width() - 30;

    for (int i = 0; i < chatHistory->count(); ++i) {
        QListWidgetItem* item = chatHistory->item(i);
        const QWidget* containerWidget = chatHistory->itemWidget(item);
        if (!containerWidget) continue;

        const auto* layout = qobject_cast<QHBoxLayout*>(containerWidget->layout());
        if (!layout) continue;

        QLabel* label = nullptr;
        for (int j = 0; j < layout->count(); j++) {
            if (const QLayoutItem* layoutItem = layout->itemAt(j); layoutItem->widget()) {
                label = qobject_cast<QLabel*>(layoutItem->widget());
                if (label) break;
            }
        }

        if (label) {

            label->setMaximumWidth(static_cast<int>(availableWidth * 0.8));

            QString text = label->text();
            if (text.startsWith("<b>You:</b> ")) text = text.mid(5);
            else if (text.startsWith("<b>Little Friend:</b> ")) text = text.mid(4);

            QFontMetrics metrics(label->font());
            const int textWidth = metrics.horizontalAdvance(text);
            const int lineHeight = metrics.height();
            const int lineCount = (textWidth / static_cast<int>(availableWidth * 0.8)) + 1;
            int estimatedHeight = lineHeight * lineCount + 40;

            item->setSizeHint(QSize(containerWidget->width(),
                                   qMax(containerWidget->sizeHint().height(), estimatedHeight)));
        }
    }
}

void MainWindow::setupListWidgetProperties() const {
    entryList->setViewMode(QListView::IconMode);
    entryList->setResizeMode(QListView::Fixed);
    entryList->setSpacing(10);
    entryList->setMovement(QListView::Static);
    entryList->setSelectionMode(QAbstractItemView::SingleSelection);
    entryList->setIconSize(QSize(200, 200));
    entryList->setGridSize(QSize(210, 210));
    entryList->setUniformItemSizes(true);
    entryList->setWrapping(true);
    entryList->setFlow(QListView::LeftToRight);
    entryList->setStyleSheet(
        "QListWidget::item:selected { "
        "    background: transparent; "
        "    border: 2px solid #d0d0d0; "
        "    border-radius: 30px; "
        "}"
        R"(QListView::item {margin-top: 5px;})"
    );


    constexpr int itemWidth = 210;
    constexpr int totalItems = 4;
    constexpr int horizontalPadding = 20;
    constexpr int paddingLeftAdjustment = 10;
    constexpr int width = (itemWidth * totalItems) - 10 + horizontalPadding + paddingLeftAdjustment;
    entryList->setFixedWidth(width);
}
