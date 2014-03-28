#ifndef SOLVER_H
# define SOLVER_H

# include <vector>
# include <utility>
# include <iostream>
# include <fstream>
# include <string>
# include <sstream>
# include <iterator>
# include <algorithm>

# include <time.h>

struct Data
{
	int bestObj;
	int nbVars;
	int nbConstraints;
	std::vector<std::vector<int>> values;
	std::vector<int> maxCapacity;
};

struct Solution
{
	int fctObj;
	std::vector<std::pair<int, int>> values;
};

struct DescentParameters
{
	int nbEvaluation;
};

struct RecuitParameters
{
	int temperature;
	int nbStep;
	int nbEvaluation;
};

class Solver
{
private:
	std::string file;
	bool verbose;

private:
	DescentParameters descent;
	RecuitParameters recuit;

private:
	Data data;
	Solution solution;

public:
	Solver(std::string filepath);

public:
	void setDescentParameters(DescentParameters dp);
	void setRecuitParameters(RecuitParameters rp);

public:
	void parser(void);

private:
	void evalSolution(Solution& sol);

public:
	void setVerbose(bool v);

private:
	int randomAlgorithm(void);

private:
	Solution getDescentNeighboorSolution();
	int descentAlgorithm(void);

private:
	int recuitAlgorithm(void);

public:
	int solve(int type);
};

#endif