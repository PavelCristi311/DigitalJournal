
#include <QApplication>
#include "RepositoryLayer/JSONRepo.h"
#include "RepositoryLayer/CSVRepo.h"
#include "ControllerLayer/Controller.h"
#include "UILayer/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":images/UILayer/logo.png"));
    JSONRepo repo("journal.json");
    repo.load();
    CSVRepo repo2("journal.csv");
    repo2.load();
    CSVRepo repo3("1000_entries.csv");
    repo3.load();
    Controller controller(&repo3);
    MainWindow window(&controller);
    window.show();
    repo3.save();
    repo2.save();
    repo.save();
    return QApplication::exec();
}