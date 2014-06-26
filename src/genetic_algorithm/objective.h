#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include<vector>

using namespace std;

class objective {
    private:
	vector<double> objs;

    public:
	objective();
	objective(int n_obj);
	vector<double> get_objective();
	double get_objective(int index);
	void set_objective(vector<double> objective);
	bool set_objective(int  index, double value);
	int size();
	void clear();
	bool operator<(const objective &a);
	bool operator>(const objective &a);
	bool operator==(const objective &a);
	// Colocar o cmp
};

#endif
