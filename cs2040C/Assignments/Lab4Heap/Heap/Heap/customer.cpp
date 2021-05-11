#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 0; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? processing_time < c.processing_time : arrival_time < c.arrival_time; // a customer is "greater" if his time is shorter
};

bool Customer::operator<(const Customer& c) {
	return comparisonWay ? processing_time > c.processing_time : arrival_time > c.arrival_time; // a customer is "worser" if his time is longer
};

bool Customer::operator==(const Customer& c) {
	return comparisonWay ? processing_time == c.processing_time : arrival_time == c.arrival_time; // comparing customer times
};

void Customer::operator=(int a) {
	processing_time = a;
	arrival_time = a;
};

void customerQueueTest(int n_cust) {
	int i;

	Heap<Customer> queue;

	Customer* custList = new Customer[n_cust];
	cout << endl << endl << "Setup" << endl;
	cout << "List of customers and their arrival and processing times" << endl;
	for (i = 0; i<n_cust; i++)
	{
		custList[i].setAT(i);
		custList[i].setPT((n_cust - i) % (n_cust / 2) + 1 + (i % 2)*(n_cust / 2));
		cout << "Customer " << i << " will arrive at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
	}
	cout << endl;

	for (int round = 0; round<2; round++) {
		int WT = 0; // waiting time for each customer
		int current_time = 0;
		int totalWaitingTime = 0;
		bool serving = false;
		int timeServed = 0;
		int timeFinish = 0;
		// you may need a big modification within this for-loop
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = round;
		for (i = 0; i < n_cust; i++) {
			queue.insert(custList[i]);

			cout << "Customer arrives at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
			current_time = custList[i].AT();
			if (current_time - timeFinish >= 0) serving = false;

			if (!serving) {
				Customer c = queue.extractMax();
				serving = true;
				timeServed = current_time;
				timeFinish = timeServed + c.PT();
				WT = timeServed - c.AT();
				if (WT == 0) cout << "Customer arrives when no one is waiting" << endl;
				cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() << " after waiting for "
					<< WT << " min." << endl;
				totalWaitingTime += WT;
			}
		}

		while (!queue.empty()) {

			current_time += 1;
			if (current_time - timeFinish >= 0) serving = false;

			if (!serving) {
				Customer c = queue.extractMax();
				serving = true;
				timeServed = current_time;
				timeFinish = timeServed + c.PT();
				WT = timeServed - c.AT();
				if (WT == 0) cout << "Customer arrives when no one is waiting" << endl;
				cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() << " after waiting for "
					<< WT << " min." << endl;
				totalWaitingTime += WT;
			}
			// you should change all of the code here inside
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;

	}

	delete[] custList;
}
