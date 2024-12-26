#include "Pipes.hh"
#include "TemplateFactory.hh"

#include "mapper.hpp"
#include "reducer.hpp"

int main() {
    return HadoopPipes::runTask(HadoopPipes::TemplateFactory<analytics::AggregateMapper, analytics::AggregateReducer>());
}
