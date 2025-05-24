//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef CSVREPO_H
#define CSVREPO_H
#include "Repository.h"


class CSVRepo final :public Repository {
protected:
    void load() override;
    void save() const override;
public:
    explicit CSVRepo(const QString &givenFilename): Repository(givenFilename){}
    void add(const DataEntry &entry) override;
    void remove(const QString &date) override;
    void update(const QString &date, const DataEntry &newData) override;
    [[nodiscard]] std::vector<DataEntry> getAll() const override;
};




#endif //CSVREPO_H
