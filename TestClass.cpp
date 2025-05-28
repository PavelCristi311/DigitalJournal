#include <cassert>
#include <iostream>
#include <fstream>
#include "RepositoryLayer/JSONRepo.h"
#include "RepositoryLayer/CSVRepo.h"
#include "ControllerLayer/Controller.h"
#include "ControllerLayer/FilterStrategy/AndFilterStrategy.h"
#include "ControllerLayer/FilterStrategy/OrFilterStrategy.h"

class TestClass {
private:
    static void createTestFiles() {
        std::ofstream jsonFile("test.json");
        jsonFile << "[]";
        jsonFile.close();

        std::ofstream csvFile("test.csv");
        csvFile.close();
    }

    static void cleanupTestFiles() {
        std::remove("test.json");
        std::remove("test.csv");
    }

    static void testJSONRepo() {
        std::cout << "Testing JSONRepo..." << std::endl;

        JSONRepo repo("test.json");

        DataEntry entry1("Title1", "Content1", "12:30:00 / 01.05.2024");
        DataEntry entry2("Title2", "Content2", "13:45:00 / 02.05.2024");
        DataEntry entry3("Title3", "Content3", "14:15:00 / 03.05.2024");

        repo.add(entry1);
        repo.add(entry2);
        repo.add(entry3);

        auto entries = repo.getAll();
        assert(entries.size() == 3);
        assert(entries[0].getTitle() == "Title1");
        assert(entries[1].getTitle() == "Title2");
        assert(entries[2].getTitle() == "Title3");

        repo.remove("13:45:00 / 02.05.2024");
        entries = repo.getAll();
        assert(entries.size() == 2);
        assert(entries[0].getTitle() == "Title1");
        assert(entries[1].getTitle() == "Title3");

        DataEntry updatedEntry("UpdatedTitle", "UpdatedContent", "12:30:00 / 01.05.2024");
        repo.update("12:30:00 / 01.05.2024", updatedEntry);
        entries = repo.getAll();
        assert(entries[0].getTitle() == "UpdatedTitle");
        assert(entries[0].getContent() == "UpdatedContent");

        DataEntry newerEntry("Newer", "Content", "15:00:00 / 04.05.2024");
        repo.add(newerEntry);
        repo.sortByDate();
        entries = repo.getAll();
        assert(entries[0].getTitle() == "Newer");

        std::cout << "JSONRepo tests passed!" << std::endl;
    }

    static void testCSVRepo() {
        std::cout << "Testing CSVRepo..." << std::endl;

        CSVRepo repo("test.csv");

        DataEntry entry1("Title1", "Content1", "12:30:00 / 01.05.2024");
        DataEntry entry2("Title2", "Content2", "13:45:00 / 02.05.2024");
        DataEntry entry3("Title3", "Content3", "14:15:00 / 03.05.2024");

        repo.add(entry1);
        repo.add(entry2);
        repo.add(entry3);

        auto entries = repo.getAll();
        assert(entries.size() == 3);
        assert(entries[0].getTitle() == "Title1");
        assert(entries[1].getTitle() == "Title2");
        assert(entries[2].getTitle() == "Title3");

        repo.remove("13:45:00 / 02.05.2024");
        entries = repo.getAll();
        assert(entries.size() == 2);
        assert(entries[0].getTitle() == "Title1");
        assert(entries[1].getTitle() == "Title3");

        DataEntry updatedEntry("UpdatedTitle", "UpdatedContent", "12:30:00 / 01.05.2024");
        repo.update("12:30:00 / 01.05.2024", updatedEntry);
        entries = repo.getAll();
        assert(entries[0].getTitle() == "UpdatedTitle");
        assert(entries[0].getContent() == "UpdatedContent");

        DataEntry newerEntry("Newer", "Content", "15:00:00 / 04.05.2024");
        repo.add(newerEntry);
        repo.sortByDate();
        entries = repo.getAll();
        assert(entries[0].getTitle() == "Newer");

        std::cout << "CSVRepo tests passed!" << std::endl;
    }

    static void testController() {
        std::cout << "Testing Controller..." << std::endl;

        JSONRepo repo("test.json");
        Controller controller(&repo);

        const DataEntry entry1("Title1", "Content1", "12:30:00 / 01.05.2024");
        const DataEntry entry2("Title2", "Content2", "13:45:00 / 02.05.2024");

        controller.add(entry1);
        controller.add(entry2);

        auto entries = controller.getAll();
        assert(entries.size() == 2);
        assert(entries[0].getTitle() == "Title1");
        assert(entries[1].getTitle() == "Title2");

        controller.undo();
        entries = controller.getAll();
        assert(entries.size() == 1);
        assert(entries[0].getTitle() == "Title1");

        controller.redo();
        entries = controller.getAll();
        assert(entries.size() == 2);
        assert(entries[1].getTitle() == "Title2");

        controller.remove("12:30:00 / 01.05.2024");
        entries = controller.getAll();
        assert(entries.size() == 1);
        assert(entries[0].getTitle() == "Title2");

        controller.undo();
        entries = controller.getAll();
        assert(entries.size() == 2);
        assert(entries[0].getTitle() == "Title2");

        const DataEntry updatedEntry("UpdatedTitle", "UpdatedContent", "12:30:00 / 01.05.2024");
        controller.update("12:30:00 / 01.05.2024", updatedEntry);
        entries = controller.getAll();
        assert(entries[0].getTitle() == "Title2");

        controller.undo();
        entries = controller.getAll();
        assert(entries[0].getTitle() == "Title2");

        assert(controller.canUndo() == true);
        controller.undo();
        assert(controller.canUndo() == true);
        assert(controller.canRedo() == true);

        std::cout << "Controller basic tests passed!" << std::endl;
    }

    static void testFilterStrategies() {
        std::cout << "Testing Filter Strategies..." << std::endl;

        JSONRepo repo("test.json");
        Controller controller(&repo);

        DataEntry entry1("Meeting", "Important business meeting", "12:30:00 / 01.05.2024");
        DataEntry entry2("Lunch", "Lunch with friends", "13:45:00 / 02.05.2024");
        DataEntry entry3("Work", "Finish important project", "14:15:00 / 03.05.2024");

        controller.add(entry1);
        controller.add(entry2);
        controller.add(entry3);

        auto titleFilter = [](const DataEntry& e) { return e.getTitle().contains("Meeting", Qt::CaseInsensitive); };
        auto contentFilter = [](const DataEntry& e) { return e.getContent().contains("Important", Qt::CaseInsensitive); };

        AndFilterStrategy andStrategy(titleFilter, contentFilter);
        auto filteredEntries = controller.filter(andStrategy);
        assert(filteredEntries.size() == 1);
        assert(filteredEntries[0].getTitle() == "Meeting");

        auto titleFilter2 = [](const DataEntry& e) { return e.getTitle().contains("Meeting", Qt::CaseInsensitive); };
        auto contentFilter2 = [](const DataEntry& e) { return e.getContent().contains("friends", Qt::CaseInsensitive); };

        OrFilterStrategy orStrategy(titleFilter2, contentFilter2);
        filteredEntries = controller.filter(orStrategy);
        assert(filteredEntries.size() == 2);

        controller.sortAll();
        auto sortedEntries = controller.getAll();
        assert(sortedEntries[0].getTitle() == "Work");

        std::cout << "Filter strategy tests passed!" << std::endl;
    }

public:
    static void runAll() {
        createTestFiles();

        try {
            testJSONRepo();
            testCSVRepo();
            testController();
            testFilterStrategies();

            std::cout << "All tests passed successfully!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Test failed: " << e.what() << std::endl;
        }

        cleanupTestFiles();
    }
};