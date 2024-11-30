#include "queue.h"
#include <gtest.h>


TEST(TQueue, can_create_queue) {
	ASSERT_NO_THROW(TQueue<int> que);
}

TEST(TQueue, created_queue_is_empty) {
	TQueue<int> que;
	ASSERT_TRUE(que.IsEmpty());
}


TEST(TQueue, can_push_element_to_queue) {
	TQueue<int> que;
	ASSERT_NO_THROW(que.Push(10));
}

TEST(TQueue, push_increases_queue_size) {
	TQueue<int> que;
	que.Push(10);
	ASSERT_FALSE(que.IsEmpty());
}

TEST(TQueue, can_push_multiple_elements) {
	TQueue<int> que;
	ASSERT_NO_THROW({
	  que.Push(1);
	  que.Push(2);
	  que.Push(3);
		});
}


TEST(TQueue, can_pop_element_from_queue) {
	TQueue<int> que;
	que.Push(10);
	ASSERT_NO_THROW(que.Pop());
}

TEST(TQueue, pop_returns_correct_value) {
	TQueue<int> que;
	que.Push(10);
	int value = que.Pop();
	ASSERT_EQ(value, 10);
}

TEST(TQueue, pop_from_empty_queue_throws_exception) {
	TQueue<int> que;
	ASSERT_THROW(que.Pop(), std::underflow_error);
}


TEST(TQueue, can_view_first_element) {
	TQueue<int> que;
	que.Push(10);
	ASSERT_NO_THROW(que.ViewFirst());
}

TEST(TQueue, view_first_returns_correct_value) {
	TQueue<int> que;
	que.Push(20);
	int value = que.ViewFirst();
	ASSERT_EQ(value, 20);
}

TEST(TQueue, view_first_does_not_remove_element) {
	TQueue<int> que;
	que.Push(30);
	int value1 = que.ViewFirst();
	int value2 = que.Pop();
	ASSERT_EQ(value1, value2);
}

TEST(TQueue, view_first_on_empty_queue_throws_exception) {
	TQueue<int> que;
	ASSERT_THROW(que.ViewFirst(), std::underflow_error);
}


TEST(TQueue, queue_resizes_when_full) {
	TQueue<int> que;
	for (int i = 0; i < 100; i++) {
		ASSERT_NO_THROW(que.Push(i));
	}
}

TEST(TQueue, queue_resizes_down_when_not_utilized) {
	TQueue<int> que;
	for (int i = 0; i < 100; i++) {
		que.Push(i);
	}
	for (int i = 0; i < 75; i++) {
		que.Pop();
	}
	ASSERT_NO_THROW(que.Push(1));
}

TEST(TQueue, queue_handles_wrap_around_correctly) {
	TQueue<int> que;
	que.Push(1);
	que.Push(2);
	que.Pop();
	que.Push(3);
	ASSERT_EQ(que.Pop(), 2);
	ASSERT_EQ(que.Pop(), 3);
}


TEST(TQueue, works_correctly_with_custom_types) {
	struct CustomType {
		int a, b;
		bool operator==(const CustomType& other) const {
			return a == other.a && b == other.b;
		}
	};

	TQueue<CustomType> que;
	CustomType obj = { 1, 2 };
	que.Push(obj);
	CustomType result = que.Pop();
	ASSERT_EQ(obj, result);
}

TEST(TQueue, handles_large_number_of_operations) {
	TQueue<int> que;
	const int opsCount = 1e6;
	ASSERT_NO_THROW({
	  for (int i = 0; i < opsCount; i++) {
		que.Push(i);
	  }
	  for (int i = 0; i < opsCount; i++) {
		que.Pop();
	  }
		});
}