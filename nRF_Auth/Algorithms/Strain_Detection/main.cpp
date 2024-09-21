#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>

using namespace std; 
int timestamp = 0;
int bent_result = 0;
int straight_result = 0; 


void pulse_bent(void)
{
	cout << "timestamp :: " << timestamp << ":: bent state" << '\n';
	bent_result++;
}

void pulse_straight(void)
{
	cout << "timestamp :: " << timestamp << ":: straight state" << '\n';
	straight_result++; 
}

int main()
{
	ios_base::sync_with_stdio(0); 
	freopen("input.txt", "r", stdin);

	int sensor_val = 0;
	int stationary_avg = 0;
	const int resting_time = 50; 
	const int sign_time = 200; 
	const int avg_deviation_range = 100; 

	// resting state - get average value 
	for (int i = 0; i < resting_time; i++)
	{
		timestamp++;
		cin >> sensor_val;
		stationary_avg += sensor_val; 
	}
	stationary_avg = stationary_avg / timestamp;
	cout << "stationary average ADC value: " << stationary_avg << '\n';

	bool state_straight = true;
	// sign state - detection 
	for (int i = 0; i < sign_time; i++) 
	{
		timestamp++; 
		cin >> sensor_val; 
		// hits acceptable base range 
		if (sensor_val <= (stationary_avg + avg_deviation_range))
		{
			if (state_straight == false)
			{				
				state_straight = true; 
				pulse_straight();
			}
		}

		// got out of the acceptable average range
		else
		{
			if (state_straight == true)
			{
				state_straight = false; 
				pulse_bent();
			}
		}
	}
	
	cout << "\n";
	
	cout << "straight -> bent result:::" << bent_result << '\n';
	cout << "bent -> straight result:::" << straight_result << '\n'; 
}