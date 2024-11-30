#pragma once
#ifndef _Cluster_
#define _Cluster_

#include "queue.h"
#include <iostream>
#include <vector>

using namespace std;

struct Task {
	int nodesRequired;
	int executionTime;
	int initialNodesRequired;
};

struct Statistics {
	int totalTacts = 0;
	int totalTasksCreated = 0;
	int completedTasks = 0;
	int unfinishedTasks = 0;
	int idleTacts = 0;
	double averageLoad = 0.0;
	vector<int> usedNodes;

	friend ostream& operator<<(ostream& out, const Statistics& stats) {
		out << "Обработка завершена за: " << stats.totalTacts << " тактов" << endl;
		out << "Всего задач создано: " << stats.totalTasksCreated << endl;
		out << "Задач выполнено: " << stats.completedTasks << endl;
		out << "Количество задач, завершенных с ошибкой: " << stats.unfinishedTasks << endl;
		out << "Кластер простаивал: " << stats.idleTacts << " тактов" << endl;
		out << "Средний процент загрузки кластера: " << stats.averageLoad << "%" << endl;

		return out;
	}
};

class Cluster {
private:
	int nodes = 0;
	int tasksPerStep = 0;
	int tacts = 0;
	double taskSpawnChance = 0.0;
public:
	Cluster(int maxTacts, int totalNodes, int tasksPerTact, double spawnProbability);
	Task generateTask(int maxNodes);
	Statistics simulate();
};

#endif
