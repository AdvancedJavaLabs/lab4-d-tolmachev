#include "mapper.hpp"

#include "StringUtils.hh"

#include <cctype>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace analytics {

AggregateMapper::AggregateMapper(HadoopPipes::TaskContext& context) {
}

void AggregateMapper::map(HadoopPipes::MapContext& context) {
    if (std::isalpha(context.getInputValue().front())) {
        return;
    }
    std::vector<std::string> columns(HadoopUtils::splitString(context.getInputValue(), ","));
    std::ostringstream os;
    os << columns.at(3) << "," << columns.at(4);
    context.emit(columns.at(2), os.str());
}

SortMapper::SortMapper(HadoopPipes::TaskContext& context)
    : is_first_(true) {
}

void SortMapper::map(HadoopPipes::MapContext& context) {
    if (is_first_) {
        is_first_ = false;
        context.emit(std::to_string(std::numeric_limits<size_t>::max()), "Quantity,Category,Revenue");
    }
    std::vector<std::string> columns(HadoopUtils::splitString(context.getInputValue(), ","));
    std::ostringstream os;
    os << columns.at(2) << "," << columns.at(0);
    context.emit(columns.at(1), os.str());
}

}
