#pragma once
#include <vector>
#include <algorithm>

template <typename T>
struct array2d
{
	array2d() {}
	array2d(size_t x, size_t y) : count_of_row(x), size_of_row(y), data(count_of_row)
	{
		std::for_each(data.begin(), data.end(), [=](auto& row) {
			row.resize(size_of_row);
		});
	}

	auto get_element(int32_t x_index, int32_t y_index) -> T&
	{
		return this->data[x_index][y_index];
	}
	auto get_row(int32_t x_index) -> std::vector<T>&
	{
		return this->data[x_index];
	}

	auto get_row_count() -> size_t
	{
		return this->count_of_row;
	}
	auto get_row_size() -> size_t
	{
		return this->size_of_row;
	}

private:
	size_t count_of_row;
	size_t size_of_row;
	std::vector<std::vector<T>> data;
};