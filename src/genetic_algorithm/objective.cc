#include"objective.h"

objective::objective() {
    objs.clear();
}

objective::objective(int n_obj) {
    for(int i = 0; i < n_obj; i++) objs.push_back(0);
}

vector<double> objective::get_objective() {
    return objs;
}

double objective::get_objective(int index) {
    if(index < objs.size())
	return objs[index];
    return 0;
}

void objective::set_objective(vector<double> objective) {
    objs = objective;
}

bool objective::set_objective(int  index, double value) {
    if(index >= objs.size())
	return false;

    objs[index] = value;
    return true;
}

int objective::size() {
    return objs.size();
}

void objective::clear() {
    objs.clear();
}

bool objective::operator<(const objective &a) {
    int counter = 0;

    if(a.objs.size() != objs.size()) return false;

    for(int i = 0; i < objs.size(); i++) {
	if(objs[i] > a.objs[i])
	    return false;
	if(objs[i] < a.objs[i])
	    counter++;
    }
    if(counter) return true;
    return false;
}

bool objective::operator>(const objective &a) {
    int counter = 0;

    if(a.objs.size() != objs.size()) return false;

    for(int i = 0; i < objs.size(); i++) {
	if(objs[i] < a.objs[i])
	    return false;
	if(objs[i] > a.objs[i])
	    counter++;
    }
    if(counter) return true;
    return false;
}

bool objective::operator==(const objective &a) {
    if((*this > a == false) && (*this < a == false))
	return true;
    return false;
}
