
#include "../../playerbot.h"
#include "GrindingStrategy.h"

using namespace ai;


NextAction** GrindingStrategy::getDefaultActions()
{
    return NULL;
}

void GrindingStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no target",
        NextAction::array( { new NextAction("attack anything", 5.0f) })));
}

