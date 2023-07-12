#include "filters_factory.h"
#include "Crop.h"
#include "EdgeDetection.h"
#include "GrayScale.h"
#include "Jitter.h"
#include "Negative.h"
#include "Sharpening.h"


std::shared_ptr<Filter> CreateFilter(const std::string &filter_name, const std::vector<std::string> &filter_params) {
    if (filter_name == "-crop") {
        return std::make_shared<Crop>(std::stoi(filter_params[0]), std::stoi(filter_params[1]));
    }
    if (filter_name == "-gs") {
        return std::make_shared<GrayScale>();
    }
    if (filter_name == "-neg") {
        return std::make_shared<Negative>();
    }
    if (filter_name == "-sharp") {
        return std::make_shared<Sharpening>();
    }
    if (filter_name == "-edge") {
        return std::make_shared<EdgeDetection>(std::stof(filter_params[0]));
    }
    if (filter_name == "-jit") {
        return std::make_shared<Jitter>();
    }
    return 0;
}

std::vector<std::shared_ptr<Filter>> CreateFilters(const std::vector<FilterDefinition>& filter_definitions) {
    std::vector<std::shared_ptr<Filter>> filters1;
    filters1.reserve(filter_definitions.size());
    for (const auto& definition: filter_definitions) {
        filters1.push_back(CreateFilter(definition.name, definition.params));
    }
    return filters1;
}