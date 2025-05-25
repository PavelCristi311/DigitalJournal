
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
    Controller controller(&repo2);
    MainWindow window(&controller);
    window.show();
    return QApplication::exec();
}