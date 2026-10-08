#include <boost/mpi.hpp>
#include "repast_hpc/RepastProcess.h"


#include "Model.h"


int main(int argc, char** argv){
	
	boost::mpi::environment env(argc, argv);
	boost::mpi::communicator world;


	if (argc < 3) {
		std::cerr << "There aren't enough arguments. Number of provided arguments: " << argc << std::endl;
		return -1;
	}
	
	std::string configFile = argv[1];
	std::string propsFile  = argv[2];


	repast::RepastProcess::init(configFile);
	Model* model = new Model(propsFile, argc, argv, &world);


	repast::ScheduleRunner& runner = repast::RepastProcess::instance()->getScheduleRunner();
	model->initAgents();
	model->initSchedule(runner);
	runner.run();	


	delete model;
	
	repast::RepastProcess::instance()->done();
	return 0;
}