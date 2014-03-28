# include "Solver.h"

bool max(std::pair<int, int> a, std::pair<int, int> b)
{
	return a.first > b.first;
}

Solver::Solver(std::string filepath)
	: file (filepath)
{
}

void Solver::setDescentParameters(DescentParameters dp)
{
	descent = dp;
}

void Solver::setRecuitParameters(RecuitParameters rp)
{
	recuit = rp;
}

void Solver::setVerbose(bool v)
{
	verbose = v;
}

void Solver::parser(void)
{
	std::string line;
	std::ifstream infile(file);
	bool header = true;
	std::vector<int> tmp;
	std::string endline;

	while (std::getline(infile, line))
	{
		std::stringstream ss(line);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);

		if (header)
		{
			header = false;
			data.nbVars = atoi(vstrings[0].c_str());
			data.nbConstraints = atoi(vstrings[1].c_str());

			if (vstrings.size() == 3)
				data.bestObj = atoi(vstrings[2].c_str());
			else
				data.bestObj = -1;
		}
		else
		{
			for (unsigned int i = 0; i < vstrings.size(); i++)
			{
				if (tmp.size() >= data.nbVars)
				{
					data.values.push_back(tmp);
					tmp.clear();
				}
				tmp.push_back(atoi(vstrings[i].c_str()));
			}
		}
		if (!line.empty())
			endline = line;
	}

	std::stringstream ss(endline);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	for (unsigned int i = 0; i < vstrings.size(); i++)
		data.maxCapacity.push_back(atoi(vstrings[i].c_str()));

	std::cout << "> Problem informations: nb_vars=" << data.nbVars;
	std::cout << " nb_constraints=" << data.nbConstraints;
	std::cout << " best_result=" << data.bestObj << std::endl;
	std::cout << "> Data matrix:" << std::endl << std::endl;

	for (unsigned int i = 0; i < data.values.size(); i++)
	{
		if (i == 0)
			std::cout << "Profit: ";
		else
			std::cout << "Constraint " << i << ": ";
		
		for (unsigned int j = 0; j < data.values[i].size() - 1; j++)
			std::cout << data.values[i][j] << " ";
		std::cout << data.values[i][data.values[i].size() - 1] << std::endl;

		if (i == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Max capacity: ";
	for (unsigned int i = 0; i < data.maxCapacity.size(); i++)
		std::cout << data.maxCapacity[i] << " ";

	std::cout << std::endl << std::endl;
}

void Solver::evalSolution(Solution& solution)
{
	for (unsigned int i = 0; i < solution.values.size(); i++)
		solution.fctObj += solution.values[i].first;
}

int Solver::randomAlgorithm(void)
{
	int nbItem = data.nbVars / data.nbConstraints;
	std::vector<int> marks;
	std::vector<int> w;

	w.resize(data.nbConstraints);
	marks.resize(data.nbVars);

	for (int i = 0; i < data.nbConstraints; i++)
		w[i] = 0;

	for (int i = 0; i < data.nbVars; i++)
		marks[i] = -1;

	solution.fctObj = 0;

	bool stop = false;
	srand(time(NULL));
	while (!stop)
	{
		int pos = rand() % data.nbVars;

		if (marks[pos] == -1)
		{
			solution.values.push_back(std::make_pair(data.values[0][pos], pos));

			for (int i = 0; i < data.nbConstraints; i++)
			{
				if ((w[i] + data.values[i + 1][pos]) > data.maxCapacity[i])
					stop = true;
				else
					w[i] += data.values[i + 1][pos];
			}
		}
	}

	evalSolution(solution);

	std::cout << "Solution: ";
	for (unsigned int i = 0; i < solution.values.size(); i++)
		std::cout << solution.values[i].first << " ";
	std::cout << std::endl;

	for (unsigned int i = 0; i < w.size(); i++)
		std::cout << "Constraint " << (i + 1) << ": " << w[i] << " < " << data.maxCapacity[i] << std::endl;

	std::cout << "Optimal: " << solution.fctObj << std::endl;

	return solution.fctObj;
}

Solution Solver::getDescentNeighboorSolution()
{
	Solution sol;

	// A completer

	return sol;
}

int Solver::descentAlgorithm(void)
{
	int cpt = 0;
	Solution next;

	/*
	// Crée une solution aléatoire
	randomAlgorithm();


	do
	{
		next = getDescentNeighboorSolution();
		if (solution.fctObj < next.fctObj)
			solution = next;
	}
	while (cpt < descent.nbEvaluation);
	*/

	return solution.fctObj;
}

int Solver::recuitAlgorithm(void)
{

	return -1;
}

int Solver::solve(int type)
{
	if (type == 1)
		randomAlgorithm();
	else if (type == 2)
		descentAlgorithm();
	else if (type == 3)
		recuitAlgorithm();

	return solution.fctObj;
}