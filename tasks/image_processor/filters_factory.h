#include "image_processor.h"

std::shared_ptr<Filter> CreateFilter(const std::string &filter_name, const std::vector<std::string> &filter_params);

std::vector<std::shared_ptr<Filter>> CreateFilters(const std::vector<FilterDefinition>& filter_definitions);
