#ifndef HISTORY_H
#define HISTORY_H

#include<iostream>
#include<stdio.h>
#include<time.h>
#include<string>
#include"simulator.h"
#include"../lib/parametros.h"
#include"../lib/objeto.h"

using namespace std;

class history {
    private:
	string team_name;
	int team_number;

	int n_scored_goals;
	int n_other_team_goals;
	int n_fouls;
	int n_goal_area;
	int n_enemy_goal_area;

	bool state_scored_goals;
	bool state_other_team_goals;
	bool state_fouls;
	bool state_goal_area;
	bool state_enemy_goal_area;

	void in_n_scored_goals();
	void in_n_other_team_goals();
	void in_n_fouls();
	void in_n_goal_area();
	void in_n_enemy_goal_area();

	void out_n_scored_goals();
	void out_n_other_team_goals();
	void out_n_fouls();
	void out_n_goal_area();
	void out_n_enemy_goal_area();

    public:
	history();

	void inc_n_scored_goals();
	void inc_n_other_team_goals();
	void inc_n_fouls();
	void inc_n_goal_area();
	void inc_n_enemy_goal_area();

	void calc(simulator sim);


	bool write_history();
	bool write_history(string filename);
};

#endif
