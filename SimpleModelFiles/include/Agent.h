#ifndef AGENT_H_
#define AGENT_H_

#include "repast_hpc/SharedContext.h"

class Agent {

private:
	repast::AgentId id_;
	double myNumber;
	int totalWin = 0;
	int totalPlay = 0;

public:
	Agent(repast::AgentId id);

	~Agent();

	/* Required Getters */
	virtual repast::AgentId& getId() {                return id_;    }
	virtual const repast::AgentId& getId() const {    return id_;    }

	/* Getters specific to this kind of Agent */
	double getNumber();
	double getWinningPercentage();
	
	void pickNumber();
	void play(repast::SharedContext<Agent>* context);

};

#endif