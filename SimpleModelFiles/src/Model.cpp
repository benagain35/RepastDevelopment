#include <boost/mpi.hpp>
#include "repast_hpc/RepastProcess.h"

#include "Model.h"

#include "repast_hpc/initialize_random.h"


Model::Model(const std::string& propsFile, int argc, char** argv, boost::mpi::communicator* comm) : context(comm) {


	props = new repast::Properties(propsFile, argc, argv, comm);
	stopAt = repast::strToInt(props->getProperty("stop.at"));

	countOfAgents = repast::strToInt(props->getProperty("count.of.agents"));

	initializeRandom(*props, comm);

}

void Model::initAgents() {
	int rank = repast::RepastProcess::instance()->rank();
	for(int i = 0; i < countOfAgents; i++) {
		repast::AgentId id(i, rank, 0);
		id.currentRank(rank);
		Agent* agent = new Agent(id);
		context.addAgent(agent);
	}
}


Model::~Model() {

		delete props;
}

void Model::doSomething() {
	std::vector<Agent*> agents;
	context.selectAgents(countOfAgents, agents); //select all agents


	//each agent picks a random number
	std::vector<Agent*>::iterator it = agents.begin();
	while(it != agents.end()){
		(*it)->pickNumber();
		it++;
	}


	//each agent plays
	it = agents.begin();
	while(it != agents.end()){
		(*it)->play(&context);
		it++;
	}


	//print winning percentages
	it = agents.begin();
	while(it != agents.end()){
		std::cout << "Agent " << (*it)->getId() << ": " << (*it)->getWinningPercentage() << std:: endl;
		it++;
	}
}


void Model::initSchedule(repast::ScheduleRunner& runner) {
	runner.scheduleEvent(1, 1, repast::Schedule::FunctorPtr(new repast::MethodFunctor<Model> (this, &Model::doSomething)));
	runner.scheduleStop(stopAt);
}
