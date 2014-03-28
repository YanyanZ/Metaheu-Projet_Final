// Knapsack.cpp : définit le point d'entrée pour l'application console.

# include <iostream>

# include "Solver.h"

int main(int argc, char* argv[])
{
	std::cout << "################### Knapsack Solver ###################" << std::endl;
	if (argc >= 4)
	{
		Solver* solver = new Solver(argv[1]);

		std::cout << "> File load: " << argv[1] << std::endl;

		int type = atoi(argv[2]);
		if (type == 1)
			std::cout << "> Solver algorithm: Random" << std::endl;
		else if (type == 2)
		{
			DescentParameters dp;

			dp.nbEvaluation = atoi(argv[4]);
			solver->setDescentParameters(dp);

			std::cout << "> Solver algorithm: Descent" << std::endl;
		}
		else if (type == 3)
		{
			RecuitParameters rp;

			rp.nbEvaluation = atoi(argv[4]);
			rp.nbStep = atoi(argv[5]);
			rp.temperature = atoi(argv[6]);
			solver->setRecuitParameters(rp);

			std::cout << "> Solver algorithm: Recuit" << std::endl;
		}
		else if (type == 4)
			std::cout << "> Solver algorithm: Taboo" << std::endl;
		else
		{
			std::cerr << "ERROR - Unknow algorithm" << std::endl;
			return -1;
		}

		solver->parser();
		solver->solve(type);

		if (solver)
			delete solver;

		std::cout << "#######################################################" << std::endl;

		std::string useless;
		std::cin >> useless;

		return 0;
	}

	std::cerr << "> Error - Bas useage - ./exec file type verbose" << std::endl;
	std::cout << "#######################################################" << std::endl;

	std::string useless;
	std::cin >> useless;

	return -1;
}

