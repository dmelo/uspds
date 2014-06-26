#include"history.h"

history::history() {
    n_scored_goals = 0;
    n_other_team_goals = 0;
    n_fouls = 0;
    n_goal_area = 0;
    n_enemy_goal_area = 0;

    state_scored_goals = false;
    state_other_team_goals = false;
    state_fouls = false;
    state_goal_area = false;
    state_enemy_goal_area = false;
}

void history::inc_n_scored_goals() {
    n_scored_goals++;
}

void history::inc_n_other_team_goals() {
    n_other_team_goals++;
}

void history::inc_n_fouls() {
    n_fouls++;
}

void history::inc_n_goal_area() {
    n_goal_area++;
}

void history::inc_n_enemy_goal_area() {
    n_enemy_goal_area++;
}



void history::in_n_scored_goals() {
    state_scored_goals = true;;
}

void history::in_n_other_team_goals() {
    state_other_team_goals = true;
}

void history::in_n_fouls() {
    state_fouls = true;
}

void history::in_n_goal_area() {
    state_goal_area = true;
}

void history::in_n_enemy_goal_area() {
    state_enemy_goal_area = true;
}




void history::out_n_scored_goals() {
    if(state_scored_goals) n_scored_goals++;
    state_scored_goals = false;
}

void history::out_n_other_team_goals() {
    if(state_other_team_goals) n_other_team_goals++;
    state_other_team_goals = false;
}

void history::out_n_fouls() {
    if(state_fouls) n_fouls++;
    state_fouls = false;
}

void history::out_n_goal_area() {
    if(state_goal_area) n_goal_area++;
    state_goal_area = false;
}

void history::out_n_enemy_goal_area() {
    if(state_enemy_goal_area) n_enemy_goal_area++;
    state_enemy_goal_area = false;
}

bool history::write_history() {
    return write_history("");
}

bool history::write_history(string filename) {
    string full_filename;
    FILE *fd;

    time_t raw_time;
    time(&raw_time);
    if(filename == "") {
	full_filename = "team_1_" + filename + asctime(localtime(&raw_time));
	for(int i = 0; i < full_filename.size(); i++)
	    if(full_filename[i] == ' ' || full_filename[i] == '\n')
		full_filename[i] = '_';
	full_filename += ".hty";
    } else
	full_filename = filename;
    cout << "recording in " << full_filename << endl;
    if((fd = fopen(full_filename.c_str(), "w")) == NULL) {
	cerr << "history: write_history: error: cannot open file " << full_filename << " for writing." << endl;
	return false;
    }


    fprintf(fd, "team_number 1\n");
    fprintf(fd, "n_scored_goals %d\n", n_scored_goals);
    fprintf(fd, "n_other_team_goals %d\n", n_other_team_goals);
    fprintf(fd, "n_fouls %d\n", n_fouls);
    fprintf(fd, "n_goal_area %d\n", n_goal_area);
    fprintf(fd, "n_enemy_goal_area %d\n", n_enemy_goal_area);
    fclose(fd);

    if(filename == "") {
	full_filename = "team_2_" + filename + asctime(localtime(&raw_time));
	for(int i = 0; i < full_filename.size(); i++)
	    if(full_filename[i] == ' ' || full_filename[i] == '\n')
		full_filename[i] = '_';
	full_filename += ".hty";
    } else 
	full_filename = filename;
    cout << "recording in " << full_filename << endl;
    if((fd = fopen(full_filename.c_str(), "w")) == NULL) {
	cerr << "history: write_history: error: cannot open file " << full_filename << " for writing." << endl;
	return false;
    }

    fprintf(fd, "team_number 2\n");
    fprintf(fd, "n_scored_goals %d\n", n_other_team_goals);
    fprintf(fd, "n_other_team_goals %d\n", n_scored_goals);
    fprintf(fd, "n_fouls %d\n", n_fouls);
    fprintf(fd, "n_goal_area %d\n", n_enemy_goal_area);
    fprintf(fd, "n_enemy_goal_area %d\n", n_goal_area);
    fclose(fd);
    
    return true;
}

void history::calc(simulator sim) {
    float x[4], y[4];

    x[0] = CAMPO_GOL_PROFUNDIDADE;
    y[0] = (CAMPO_ALTURA / 2) + (CAMPO_AREA_GOL_ALTURA / 2);

    x[1] = CAMPO_GOL_PROFUNDIDADE + CAMPO_AREA_GOL_LARGURA;
    y[1] = (CAMPO_ALTURA / 2) + (CAMPO_AREA_GOL_ALTURA / 2);

    x[2] = CAMPO_GOL_PROFUNDIDADE + CAMPO_AREA_GOL_LARGURA;
    y[2] = (CAMPO_ALTURA / 2) - (CAMPO_AREA_GOL_ALTURA / 2);

    x[3] = CAMPO_GOL_PROFUNDIDADE;
    y[3] = (CAMPO_ALTURA / 2) - (CAMPO_AREA_GOL_ALTURA / 2);


    if(objeto::point_inside_convex_polygon(sim.b->getX(), sim.b->getY(), x, y, 4)) in_n_goal_area();
    else out_n_goal_area();

    x[0] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LARGURA;
    y[0] = (CAMPO_ALTURA / 2) + (CAMPO_AREA_GOL_ALTURA / 2);

    x[1] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LARGURA - CAMPO_AREA_GOL_LARGURA;
    y[1] = (CAMPO_ALTURA / 2) + (CAMPO_AREA_GOL_ALTURA / 2);

    x[2] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LARGURA - CAMPO_AREA_GOL_LARGURA;
    y[2] = (CAMPO_ALTURA / 2) - (CAMPO_AREA_GOL_ALTURA / 2);

    x[3] = CAMPO_GOL_PROFUNDIDADE + CAMPO_LARGURA;
    y[3] = (CAMPO_ALTURA / 2) - (CAMPO_AREA_GOL_ALTURA / 2);

    if(objeto::point_inside_convex_polygon(sim.b->getX(), sim.b->getY(), x, y, 4)) in_n_enemy_goal_area();
    else out_n_enemy_goal_area();
}
