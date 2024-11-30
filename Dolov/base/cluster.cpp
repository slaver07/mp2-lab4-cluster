#include "cluster.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <stdexcept>

using namespace std;

Task Cluster::generateTask(int maxNodes) {
	Task newTask;
	newTask.nodesRequired = 1 + rand() % maxNodes;
	newTask.initialNodesRequired = newTask.nodesRequired;
	newTask.executionTime = 1 + rand() % 15;
	return newTask;
}

Cluster::Cluster(int maxTacts, int totalNodes, int tasksPerTact, double spawnProbability) {
	if (maxTacts < 1)
		throw invalid_argument("Ошибка: количество тактов должно быть не менее 1.");
	if (totalNodes < 16 || totalNodes > 64)
		throw invalid_argument("Ошибка: количество узлов должно быть в диапазоне от 16 до 64.");
	if (tasksPerTact < 1)
		throw invalid_argument("Ошибка: количество задач в такт должно быть хотя бы 1.");
	if (spawnProbability < 0.0 || spawnProbability > 1.0)
		throw invalid_argument("Ошибка: вероятность появления задачи должна быть в диапазоне [0, 1].");

	tacts = maxTacts;
	nodes = totalNodes;
	tasksPerStep = tasksPerTact;
	taskSpawnChance = spawnProbability;
}

Statistics Cluster::simulate() {
	setlocale(LC_ALL, "Russian");
	Statistics results{};
	results.totalTacts = tacts;
	results.averageLoad = 0.0;

	int availableNodes = nodes;
	int taskQueueSize = 0;
	TQueue<Task> taskQueue;
	vector<Task> currentTasks;

	vector<char> nodeVisualization(nodes, '.');

	for (int tact = 0; tact < results.totalTacts; tact++) {
		cout << "Такт " << tact + 1 << ":" << endl;

		for (int i = 0; i < tasksPerStep; i++) {
			if ((double(rand()) / RAND_MAX) <= taskSpawnChance) {
				Task newTask = generateTask(nodes);
				taskQueue.Push(newTask);
				taskQueueSize++;
				results.totalTasksCreated++;
			}
		}

		while (!taskQueue.IsEmpty() && availableNodes >= taskQueue.ViewFirst().nodesRequired) {
			Task taskToProcess = taskQueue.Pop();
			taskQueueSize--;
			currentTasks.push_back(taskToProcess);
			availableNodes -= taskToProcess.nodesRequired;

			for (int i = 0; i < nodes; i++) {
				if (nodeVisualization[i] == '.' && taskToProcess.nodesRequired > 0) {
					nodeVisualization[i] = '#';
					taskToProcess.nodesRequired--;
				}
			}
		}

		for (auto it = currentTasks.begin(); it != currentTasks.end();) {
			it->executionTime--;
			if (it->executionTime == 0) {
				availableNodes += it->initialNodesRequired;

				int nodesToFree = it->initialNodesRequired;
				for (int i = 0; i < nodes; i++) {
					if (nodeVisualization[i] == '#' && nodesToFree > 0) {
						nodeVisualization[i] = '.';
						nodesToFree--;
					}
				}

				it = currentTasks.erase(it);
				results.completedTasks++;
			}
			else {
				++it;
			}
		}

		if (currentTasks.empty()) {
			results.idleTacts++;
		}

		results.averageLoad += ((static_cast<double>(nodes) - availableNodes) / nodes);
		results.usedNodes.push_back(nodes - availableNodes);

		cout << "Состояние узлов: ";
		for (char c : nodeVisualization) {
			cout << c;
		}
		cout << endl;

		cout << "Узлов занято: " << nodes - availableNodes << " из " << nodes << endl;
		cout << "Текущих задач в очереди: " << taskQueueSize << endl;
		cout << "Завершенные задачи: " << results.completedTasks << endl;
		cout << "Обрабатываемые задачи: " << currentTasks.size() << endl << endl;
	}
	results.unfinishedTasks = results.totalTasksCreated - results.completedTasks;
	results.averageLoad = (results.averageLoad / results.totalTacts) * 100;

	return results;
}
