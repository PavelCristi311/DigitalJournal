
#include <QApplication>
#include "RepositoryLayer/JSONRepo.h"
#include "RepositoryLayer/CSVRepo.h"
#include "ControllerLayer/Controller.h"
#include "UILayer/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":images/UILayer/logo.png"));
    JSONRepo repo1("1000JSON.json");
    repo1.load();
    CSVRepo repo2("1000CSV.csv");
    repo2.load();
    Controller controller(&repo1);
    MainWindow window(&controller);
    window.show();
    repo1.save();
    repo2.save();
    return QApplication::exec();
}