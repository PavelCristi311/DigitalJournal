//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef JSONREPO_H
#define JSONREPO_H
#include "Repository.h"


class JSONRepo final : public Repository {
public:
    void load() override;
    void save() const override;
    explicit JSONRepo(const QString &givenFilename):Repository(givenFilename) {}
    void add(const DataEntry &entry) override;
    void remove(const QString &date) override;
    void update(const QString &date, const DataEntry &newData) override;
    [[nodiscard]] std::vector<DataEntry> getAll() const override;
};



#endif //JSONREPO_H
