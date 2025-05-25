//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef FILTERSTRATEGY_H
#define FILTERSTRATEGY_H
#include"../../RepositoryLayer/DataEntry.h"
#include <vector>
#include <functional>

class FilterStrategy {
public:
    virtual ~FilterStrategy() = default;
    [[nodiscard]] virtual std::vector<DataEntry> filter(const std::vector<DataEntry>& entries) const = 0;
};

#endif //FILTERSTRATEGY_H
