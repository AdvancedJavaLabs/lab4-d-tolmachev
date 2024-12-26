#include "reducer.hpp"

#include "StringUtils.hh"

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace analytics {

AggregateReducer::AggregateReducer(HadoopPipes::TaskContext& context) {
}


void AggregateReducer::reduce(HadoopPipes::ReduceContext& context) {
    double revenue = 0;
    size_t quantity = 0;
    while (context.nextValue()) {
        std::vector<std::string> columns(HadoopUtils::splitString(context.getInputValue(), ","));
        revenue += std::stod(columns.at(0)) * std::stoull(columns.at(1));
        quantity += std::stoull(columns.at(1));
    }
    std::ostringstream os;
    os << revenue << "," << quantity;
    context.emit(context.getInputKey(), os.str());
}

SortReducer::SortReducer(HadoopPipes::TaskContext& context)
    : is_first_(true) {
}

void SortReducer::reduce(HadoopPipes::ReduceContext& context) {
    while (context.nextValue()) {
        std::vector<std::string> columns(HadoopUtils::splitString(context.getInputValue(), ","));
        std::ostringstream os;
        if (columns.size() == 2) {
            os << context.getInputKey() << "," << columns.at(0);
        } else if (is_first_) {
            is_first_ = false;
            os << columns.at(2) << "," << columns.at(0);
        }
        context.emit(columns.at(1), os.str());
    }
}

}
