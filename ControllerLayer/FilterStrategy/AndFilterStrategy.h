//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef ANDFILTERSTRATEGY_H
#define ANDFILTERSTRATEGY_H
#include "FilterStrategy.h"

class AndFilterStrategy final : public FilterStrategy {
    std::function<bool(const DataEntry&)> c1, c2;
public:
    AndFilterStrategy(std::function<bool(const DataEntry&)> f1, std::function<bool(const DataEntry&)> f2): c1(std::move(f1)), c2(std::move(f2)) {}
    std::vector<DataEntry> filter(const std::vector<DataEntry>& entries) const override {
        std::vector<DataEntry> result;
        for (const auto& e : entries)
            if (c1(e) && c2(e))
                result.push_back(e);
        return result;
    }
};

#endif //ANDFILTERSTRATEGY_H
