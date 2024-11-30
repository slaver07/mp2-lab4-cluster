#include "cluster.h"
#include <ctime>
#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int totalTacts, nodeCount, tasksPerTact;
	double taskFrequency;

	srand(time(NULL));

	cout << "Введите количество тактов программы (от 1):" << endl;
	cin >> totalTacts;
	while (totalTacts < 1) {
		cout << "Некорректное значение! Попробуйте еще раз (от 1):" << endl;
		cin >> totalTacts;
	}

	cout << "Введите количество узлов (от 16 до 64):" << endl;
	cin >> nodeCount;
	while (nodeCount < 16 || nodeCount > 64) {
		cout << "Некорректное значение! Попробуйте еще раз (от 16 до 64):" << endl;
		cin >> nodeCount;
	}

	cout << "Введите количество задач, которые могут появляться за один такт (от 1):" << endl;
	cin >> tasksPerTact;
	while (tasksPerTact < 1) {
		cout << "Некорректное значение! Попробуйте еще раз (от 1):" << endl;
		cin >> tasksPerTact;
	}

	cout << "Введите вероятность появления задачи (от 0 до 1):" << endl;
	cin >> taskFrequency;
	while (taskFrequency < 0.0 || taskFrequency > 1.0) {
		cout << "Некорректное значение! Попробуйте еще раз (от 0 до 1):" << endl;
		cin >> taskFrequency;
	}

	try {
		Cluster cluster(totalTacts, nodeCount, tasksPerTact, taskFrequency);
		cout << "Запуск симуляции кластерной системы..." << endl;
		Statistics simulationResults = cluster.simulate();
		cout << "Симуляция завершена!" << endl;
		cout << simulationResults << endl;
	}
	catch (const invalid_argument & error) {
		cerr << "Ошибка создания кластера: " << error.what() << endl;
	}

	return 0;
}