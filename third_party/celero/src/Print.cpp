///
/// \author	John Farrier
///
/// \copyright Copyright 2015, 2016, 2017, 2018. 2019 John Farrier
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
/// http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///

#include <celero/Benchmark.h>
#include <celero/Console.h>
#include <celero/PrintVector.h>
#include <celero/TestVector.h>
#include <celero/Timer.h>
#include <celero/UserDefinedMeasurementCollector.h>
#include <celero/Utilities.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace celero;

enum PrintVectorConstants : size_t
{
	ColumnSeperatorWidth = 3,
	DoubleDecimals = 5,
	NumberOfColumns = 8,
	ColumnWidth = 15
};

///
/// http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
/// Center-aligns string within a field of width w. Pads with blank spaces to enforce alignment.
///
std::string PrintVectorCenter(const std::string& s, const size_t w = PrintVectorConstants::ColumnWidth)
{
	std::stringstream ss;
	std::stringstream spaces;

	// count excess room to pad
	auto padding = w - s.size();

	for(size_t i = 0; i < padding / 2; ++i)
	{
		spaces << " ";
	}

	// format with padding
	ss << spaces.str() << s << spaces.str();

	// if odd #, add 1 space
	if((padding > 0) && (padding % 2 != 0))
	{
		ss << " ";
	}

	ss << " | ";
	return ss.str();
}

///
/// http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
/// Convert double to string with specified number of places after the decimal and left padding.
///
std::string PrintVectorColumn(const double x, const size_t decDigits = PrintVectorConstants::DoubleDecimals, const size_t width = PrintVectorConstants::ColumnWidth)
{
	std::stringstream ss;
	ss << std::fixed << std::right;

	// fill space around displayed #
	ss.fill(' ');

	// set  width around displayed #
	ss.width(width);

	// set # places after decimal
	ss.precision(decDigits);
	ss << x;

	return ss.str();
}

///
/// http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
/// Convert double to string with specified number of places after the decimal.
///
std::string PrintVectorColumn(const int64_t x, const size_t width = PrintVectorConstants::ColumnWidth)
{
	std::stringstream ss;
	ss << std::fixed;

	// fill space around displayed #
	ss.fill(' ');

	// set  width around displayed #
	ss.width(width);

	ss << x << " | ";
	return ss.str();
}

///
/// http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
/// Convert double to string with specified number of places after the decimal.
///
std::string PrintVectorColumn(const uint64_t x, const size_t width = PrintVectorConstants::ColumnWidth)
{
	std::stringstream ss;
	ss << std::fixed;

	// fill space around displayed #
	ss.fill(' ');

	// set  width around displayed #
	ss.width(width);

	ss << x << " | ";
	return ss.str();
}

///
/// http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
/// Convert double to string with specified number of places after the decimal.
///
std::string PrintVectorStrColumnAligned(const std::string& x, const size_t width = PrintVectorConstants::ColumnWidth, bool alignLeft = true)
{
	std::stringstream ss;
	ss << std::fixed << (alignLeft ? std::left : std::right);

	// fill space around displayed #
	ss.fill(' ');

	// set width around displayed #
	ss.width(width);

	if(x.length() > width)
	{
		// Truncate
		std::string xTrunc = x;
		xTrunc = xTrunc.substr(0, width);
		ss << xTrunc << " | ";
	}
	else
	{
		ss << x << " | ";
	}

	return ss.str();
}

std::string PrintVectorColumn(const std::string& x, const size_t width = PrintVectorConstants::ColumnWidth)
{
	return PrintVectorStrColumnAligned(x, width);
}

std::string PrintVectorColumnRight(const std::string& x, const size_t width = PrintVectorConstants::ColumnWidth)
{
	return PrintVectorStrColumnAligned(x, width, false);
}

std::string PrintVectorHRule(const size_t additionalColumns = 0)
{
	std::stringstream ss;
	std::string column{":"};

	while(column.length() < PrintVectorConstants::ColumnWidth)
	{
		column += "-";
	}

	std::string firstColumn = column + ":|";

	column += "-:|";

	ss << "|" << firstColumn;

	for(size_t i = 0; i < PrintVectorConstants::NumberOfColumns + additionalColumns - 1; ++i)
	{
		ss << column;
	}

	ss << std::endl;

	return ss.str();
}

namespace celero
{
	void PrintVectorer::Console(const std::string& x)
	{
		std::cout << "Celero: " << x << std::endl;
	}

	void PrintVectorer::TableBanner()
	{
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);

		std::cout << "|" << PrintVectorCenter("Group") << PrintVectorCenter("Experiment") << PrintVectorCenter("Prob. Space") << PrintVectorCenter("Samples")
				  << PrintVectorCenter("Iterations") << PrintVectorCenter("Baseline") << PrintVectorCenter("us/Iteration") << PrintVectorCenter("Iterations/sec");

		for(size_t i = PrintVectorConstants::NumberOfColumns; i < this->columnWidths.size(); ++i)
		{
			std::cout << PrintVectorCenter(this->userDefinedColumns[i - PrintVectorConstants::NumberOfColumns], this->columnWidths[i]);
		}

		std::cout << "\n";
		std::cout << PrintVectorHRule(this->userDefinedColumns.size());
	}

	void PrintVectorer::TableRowExperimentHeader(Experiment* x)
	{
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);
		std::cout << "|" << PrintVectorColumn(x->getBenchmark()->getName()) << PrintVectorColumn(x->getName());
	}

	void PrintVectorer::TableRowFailure(const std::string& msg)
	{
		std::cout << PrintVectorColumnRight("-") << PrintVectorColumnRight("-") << PrintVectorColumnRight("-");

		for(size_t i = PrintVectorConstants::NumberOfColumns; i < this->columnWidths.size(); ++i)
		{
			std::cout << PrintVectorColumnRight("-", this->columnWidths[i]);
		}

		celero::console::SetConsoleColor(celero::console::ConsoleColor::Red);
		std::cout << msg << std::endl;
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);
	}

	void PrintVectorer::TableRowProblemSpaceHeader(std::shared_ptr<celero::ExperimentResult> x)
	{
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);

		if(x->getProblemSpaceValue() == static_cast<int64_t>(TestFixture::Constants::NoProblemSpaceValue))
		{
			std::cout << PrintVectorColumnRight("Null");
		}
		else
		{
			std::cout << PrintVectorColumn(x->getProblemSpaceValue());
		}

		std::cout << PrintVectorColumn(x->getExperiment()->getSamples()) << PrintVectorColumn(x->getProblemSpaceIterations());
	}

	void PrintVectorer::TableRowHeader(std::shared_ptr<celero::ExperimentResult> x)
	{
		TableRowExperimentHeader(x->getExperiment());
		TableRowProblemSpaceHeader(x);
	}

	void PrintVectorer::TableResult(std::shared_ptr<celero::ExperimentResult> x)
	{
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);

		celero::console::ConsoleColor temp_color;

		// Slower than Baseline
		if(x->getBaselineMeasurement() > 1.0)
		{
			temp_color = celero::console::ConsoleColor::Yellow;
		}
		else if(x->getBaselineMeasurement() < 1.0)
		{
			temp_color = celero::console::ConsoleColor::Green;
		}
		else
		{
			temp_color = celero::console::ConsoleColor::Cyan;
		}

		celero::console::SetConsoleColor(temp_color);
		std::cout << PrintVectorColumn(x->getBaselineMeasurement());
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);	
		std::cout << " | ";

		celero::console::SetConsoleColor(temp_color);
		std::cout << PrintVectorColumn(x->getUsPerCall());
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);
		std::cout << " | ";

		celero::console::SetConsoleColor(temp_color);
		std::cout << PrintVectorColumn(x->getCallsPerSecond(), 2);
		celero::console::SetConsoleColor(celero::console::ConsoleColor::Default);
		std::cout << " | ";

		std::unordered_map<std::string, double> udmValues;

		auto udmCollector = x->getUserDefinedMeasurements();
		for(const auto& entry : udmCollector->getAggregateValues())
		{
			udmValues[entry.first] = entry.second;
		}

		for(size_t i = 0; i < this->userDefinedColumns.size(); ++i)
		{
			const auto& fieldName = this->userDefinedColumns[i];

			if(udmValues.find(fieldName) == udmValues.end())
			{
				std::cout << PrintVectorCenter("---", this->columnWidths[i + PrintVectorConstants::NumberOfColumns]);
			}
			else
			{
				std::cout << PrintVectorColumn(udmValues.at(fieldName), 2, this->columnWidths[i + PrintVectorConstants::NumberOfColumns]);
			}
		}

		std::cout << "\n";
	}

	void PrintVectorer::initialize(std::vector<std::string> userDefinedColumnsIn)
	{
		this->userDefinedColumns = userDefinedColumnsIn;

		this->columnWidths.clear();
		this->columnWidths.resize(PrintVectorConstants::NumberOfColumns, PrintVectorConstants::ColumnWidth);

		for(const auto& name : this->userDefinedColumns)
		{
			this->columnWidths.push_back(std::max(name.size() + 2, (size_t)PrintVectorConstants::ColumnWidth));
		}
	}

} // namespace celero
