#include <iostream>
#include <vector>

struct RM
{
	unsigned int r;
	unsigned int m;
};

std::vector<std::vector<int>> ReedMuellerAlgorithm(RM rm);
void PrintMatrix(int rowCount, int columnCount, std::vector<std::vector<int>> matrix);

std::vector<std::vector<int>> ReedMuellerAlgorithm(RM rm)
{
	std::vector<std::vector<int>> result;

	RM work = rm;

	if (work.r > work.m)
	{
		work.r = work.m;
	}

	if (work.r == 0)
	{
		std::vector<int> value;
		for (int i = 0; i < std::pow(2, work.m); i++)
		{
			value.push_back(1);
		}
		result.push_back(value);
	}
	else
	{
		std::vector<std::vector<int>> matrix00 = ReedMuellerAlgorithm({ work.r, work.m - 1});
		std::vector<std::vector<int>> matrix11 = ReedMuellerAlgorithm({ work.r - 1, work.m - 1});

		for (int i = 0; i < matrix00.size(); i++)
		{
			std::vector<int> value;
			for (int j = 0; j < matrix00[i].size(); j++)
			{
				value.push_back(matrix00[i][j]);
			}
			for (int j = 0; j < matrix00[i].size(); j++)
			{
				value.push_back(matrix00[i][j]);
			}
			result.push_back(value);
		}

		for (int i = 0; i < matrix11.size(); i++)
		{
			std::vector<int> value;
			for (int j = 0; j < matrix11[i].size(); j++)
			{
				value.push_back(0);
			}
			for (int j = 0; j < matrix11[i].size(); j++)
			{
				value.push_back(matrix11[i][j]);
			}
			result.push_back(value);
		}
	}

	 return result;
}

void PrintMatrix(int rowCount, int columnCount, std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

int main()
{
	//unsigned int r = 1, m = 3;
	//unsigned int r = 1, m = 5;
	unsigned int r = 2, m = 3;
	std::cout << "Reed-Muller Code with Parameters: r = " << r << " and m = " << m << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::vector<std::vector<int>> matrix = ReedMuellerAlgorithm({r, m});
	
	PrintMatrix(matrix.size(), matrix[0].size(), matrix);

	int test = 0;
    std::cout << "Hello World!\n";
}
