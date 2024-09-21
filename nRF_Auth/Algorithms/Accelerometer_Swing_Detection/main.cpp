#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>	
#include <vector>
#include <deque>

using namespace std;

int res_positive_swing = 0;
int res_negative_swing = 0;
int timestamp = 0;

void positive_pulse(void)
{
	res_positive_swing++;
}

void negative_pulse(void)
{
	res_negative_swing++;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("input.txt", "r", stdin);
	deque<int> dq;

	int sensor_val;

	// 30[ms] sampling interval
	const int resting_time = 90;  // 3000[ms] -> 3[s] 
	const int sign_time = 200;  // 6000[ms] -> 6[s] 
	const int avg_deviation_range = 50;

	// Resting Stage - Get avg current 
	int stationary_avg = 0;
	for (int i = 0; i < resting_time; i++)
	{
		cin >> sensor_val;
		timestamp++;
		stationary_avg += sensor_val;
	}
	stationary_avg = stationary_avg / resting_time;
	cout << "average:" << stationary_avg << '\n';

	// Sign Stage
	bool state_avg_range = true;
	for (int i = 0; i < sign_time; i++)
	{
		cin >> sensor_val;
		timestamp++;
		// hits acceptable average range
		if (sensor_val <= (stationary_avg + avg_deviation_range) &&
			sensor_val >= (stationary_avg - avg_deviation_range))
		{
			if (state_avg_range == false)
			{
				state_avg_range = true;
			}
		}
		// got out of the acceptable average range
		else
		{
			if (state_avg_range == true)
			{
				state_avg_range = false;
				int derivative = sensor_val - stationary_avg;
				if (derivative < 0)
				{
					cout << "pulse : timestamp : negative:::" << timestamp << '\n';
					negative_pulse();
				}
				if (derivative > 0)
				{
					cout << "pulse : timestamp : positive:::" << timestamp << '\n';
					positive_pulse();
				}
			}
		}
	}

	// Resting Stage
	for (int i = 0; i < resting_time; i++)
	{
		cin >> sensor_val;
	}

	cout << "positive swing count:::" << res_positive_swing << '\n';
	cout << "negative swing count:::" << res_positive_swing << '\n';

	return 0;
}
