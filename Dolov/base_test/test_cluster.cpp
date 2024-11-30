#include "cluster.h"
#include "cluster.cpp"
#include <gtest.h>


TEST(Cluster, can_create_cluster) {
	ASSERT_NO_THROW(Cluster cl(10, 32, 3, 0.5));
}

TEST(Cluster, cant_create_with_negative_tacts) {
	ASSERT_ANY_THROW(Cluster cl(-1, 32, 3, 0.5));
}

TEST(Cluster, cant_create_with_tacts_less_than_one) {
	ASSERT_ANY_THROW(Cluster cl(0, 32, 3, 0.5));
}

TEST(Cluster, cant_create_with_too_few_nodes) {
	ASSERT_ANY_THROW(Cluster cl(10, 15, 3, 0.5));
}

TEST(Cluster, cant_create_with_too_many_nodes) {
	ASSERT_ANY_THROW(Cluster cl(10, 65, 3, 0.5));
}

TEST(Cluster, cant_create_with_negative_tasks_per_tact) {
	ASSERT_ANY_THROW(Cluster cl(10, 32, -1, 0.5));
}

TEST(Cluster, cant_create_with_zero_tasks_per_tact) {
	ASSERT_ANY_THROW(Cluster cl(10, 32, 0, 0.5));
}

TEST(Cluster, cant_create_with_invalid_spawn_probability) {
	ASSERT_ANY_THROW(Cluster cl(10, 32, 3, -0.1));
	ASSERT_ANY_THROW(Cluster cl(10, 32, 3, 1.1));
}

TEST(Cluster, can_create_with_border_values) {
	ASSERT_NO_THROW(Cluster cl(1, 16, 1, 0.0));
	ASSERT_NO_THROW(Cluster cl(1000, 64, 10, 1.0));
}


TEST(Cluster, generateTask_returns_valid_task) {
	Cluster cl(10, 32, 3, 0.5);
	Task task = cl.generateTask(32);
	ASSERT_GT(task.nodesRequired, 0);
	ASSERT_LE(task.nodesRequired, 32);
	ASSERT_GT(task.executionTime, 0);
}


TEST(Cluster, simulate_runs_successfully) {
	Cluster cl(10, 32, 3, 0.5);
	ASSERT_NO_THROW(cl.simulate());
}

TEST(Cluster, simulate_results_are_correct) {
	Cluster cl(10, 16, 2, 1.0);
	Statistics stats = cl.simulate();
	ASSERT_EQ(stats.totalTasksCreated, 10 * 2);
	ASSERT_GE(stats.averageLoad, 0.0);
	ASSERT_LE(stats.averageLoad, 100.0);
	for (int used : stats.usedNodes) {
		ASSERT_GE(used, 0);
		ASSERT_LE(used, 16);
	}
}

TEST(Cluster, simulate_handles_no_tasks_spawned) {
	Cluster cl(10, 32, 3, 0.0);
	Statistics stats = cl.simulate();
	ASSERT_EQ(stats.totalTasksCreated, 0);
	ASSERT_EQ(stats.idleTacts, 10);
	ASSERT_EQ(stats.averageLoad, 0.0);
}

TEST(Cluster, simulate_handles_max_tasks_spawned) {
	Cluster cl(10, 32, 3, 1.0);
	Statistics stats = cl.simulate();
	ASSERT_EQ(stats.totalTasksCreated, 10 * 3);
	ASSERT_GE(stats.completedTasks, 1);
	for (int used : stats.usedNodes) {
		ASSERT_LE(used, 32);
	}
}
TEST(Cluster, simulate_handles_task_execution) {
	Cluster cl(10, 16, 2, 1.0);
	Statistics stats = cl.simulate();
	ASSERT_LE(stats.completedTasks, stats.totalTasksCreated);
	ASSERT_EQ(stats.unfinishedTasks, stats.totalTasksCreated - stats.completedTasks);
}
