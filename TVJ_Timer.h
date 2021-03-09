/*
 * File: TVJ_Timer.h
 * --------------------
 *
 * @author: Teddy van Jerry
 * @licence: The MIT Licence
 * @compiler: At least C++/11
 *
 * @version 1.1 2021/03/09
 * - bug fix
 * 
 * @version 1.0 2021/03/01
 * - initial version
 *
 */

#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std::chrono;

class TVJ_Timer
{
	// friendship declaration
	friend std::ostream& operator<<(std::ostream& out, const TVJ_Timer& timer);

public:
	/**
	 * Constructor that can take two arguments.
	 * Argument 1: time unit of TVJ_Timer (default as millisecond)
	 * Argument 2: output with unit or not
	 */
	TVJ_Timer(std::string time_unit = "m", bool output_with_unit = false) : time_beg(system_clock::now())
	{
		setUnit(time_unit, output_with_unit);
	}

	/**
	 * setUnit is used to set the time unit of TVJ_Timer
	 * and set whether there is unit in the output.
	 * return void
	 */
	void setUnit(std::string time_unit, bool output_with_unit = false)
	{
		o_with_unit = output_with_unit;
		if (time_unit == "") time_unit = "m";
		t_unit = time_unit[0];
		if (time_unit.length() == 3 && time_unit[1] == '.' && '0' < time_unit[2] && time_unit[2] <= '9')
		{
			precision = time_unit[2] - '0';
		}
		else
		{
			precision = 0;
		}
	}

	/**
	 * restart is used to restart the timer.
	 * return void
	 */
	void restart()
	{
		time_beg = system_clock::now();
	}

	/**
	 * durationTime is used to return the 'long long' version of time duration.
	 * return long long
	 */
	auto durationTime() const
	{
		int x = 1000;
		time_t t = duration_cast<microseconds>(system_clock::now() - time_beg).count();
		switch (t_unit)
		{
		case 'u': x = 1;     break; // microsecond
		case 'm': x = 1000;  break; // millisecond
		case 's': x = 1E6;   break; // second
		case 'M': x = 6E7;   break; // minute
		case 'h': x = 3.6E9; break; // hour
		default:            break;
		}
		return t / x;
	}

	/**
	 * durationTimeDouble is used to return the 'double' version of time duration.
	 * return double
	 */
	auto durationTimeDouble() const
	{
		double x = 1000;
		time_t t = duration_cast<microseconds>(system_clock::now() - time_beg).count();
		switch (t_unit)
		{
		case 'u': x = 1;     break; // microsecond
		case 'm': x = 1000;  break; // millisecond
		case 's': x = 1E6;   break; // second
		case 'M': x = 6E7;   break; // minute
		case 'h': x = 3.6E9; break; // hour
		default:            break;
		}
		return t / x;
	}

protected:
	/**
	 * Print with no unit.
	 * return void
	 */
	void print(std::ostream& out = std::cout) const
	{
		if (precision) // double
		{
			out << std::setprecision(precision) << durationTimeDouble();
		}
		else // long long
		{
			out << durationTime();
		}
	}

private:
	system_clock::time_point time_beg; // the starting time
	char t_unit = 'm';                 // the time unit (default as millisecond)
	int precision = 0;                 // the precision of output if it is double
	bool o_with_unit = false;          // whether output with the unit
};

/**
 * Overloaded << function to output the time
 * return ostream&
 */
std::ostream& operator<<(std::ostream& out, const TVJ_Timer& timer)
{
	timer.print(out);
	if (timer.o_with_unit)
	{
		std::string unit;
		switch (timer.t_unit)
		{
		case 'u': unit = "us"; break; // microsecond
		case 'm': unit = "ms"; break; // millisecond
		case 's': unit = "s";  break; // second
		case 'M': unit = "m";  break; // minute
		case 'h': unit = "h";  break; // hour
		default:            break;
		}
		out << unit;
	}
	return out;
}