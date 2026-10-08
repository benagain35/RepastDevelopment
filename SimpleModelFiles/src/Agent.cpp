#include "repast_hpc/AgentId.h"

#include "Agent.h"

Agent::Agent(repast::AgentId id): id_(id) {}

Agent::~Agent() {}


double Agent::getNumber() { return myNumber; }


double Agent::getWinningPercentage() {
	if (totalPlay==0) //to avoid division by 0
		return 0;
	else
		return (double)totalWin / (double)totalPlay; //both are int so have to cast to double before division (so that it is not integer division)
}


void Agent::pickNumber() {
	myNumber = repast::Random::instance()->nextDouble();
}


void Agent::play(repast::SharedContext<Agent>* context) {
	std::vector<Agent*> agents;
	context->selectAgents(2, agents); //pick 2 random agents
	std::vector<Agent*>::iterator it = agents.begin();
	while(it != agents.end()){
		totalPlay++;
		if (myNumber > (*it)->getNumber()) { //compare numbers
			totalWin++;
			std::cout << "Agent " << id_ << "\t>\t" << "Agent " << (*it)->getId() << std::endl;
		} else {
			std::cout << "Agent " << id_ << "\t<\t" << "Agent " << (*it)->getId() << std::endl;
		}
		it++;
	}
}

