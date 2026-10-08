#ifndef MODEL_H_
#define MODEL_H_

#include "repast_hpc/Properties.h"

#include "repast_hpc/SharedContext.h"

#include "Agent.h"



class Model {

private:

	repast::Properties* props;
	repast::SharedContext<Agent> context;
	int stopAt;
	int countOfAgents;

	void printToScreen();


public:
	Model(const std::string& propsFile, int argc, char** argv, boost::mpi::communicator* comm);
	~Model();
	void initAgents();
	void initSchedule(repast::ScheduleRunner& runner);
	void doSomething();
};

#endif