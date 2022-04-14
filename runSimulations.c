#include "runSimulations.h"

/* Main progam that loops through 100 single simulations*/
void runSimulations(float leftTraffic ,float rightTraffic ,int rightTrafficLight,int leftTrafficLight){
    int i;
    float f_avg_left_vehicles = 0;
    float f_avg_left = 0;
    float f_max_avg_left = 0;
    float f_avg_left_clear = 0;
    float f_avg_right_vehicles = 0;
    float f_avg_right = 0;
    float f_max_avg_right = 0;
    float f_avg_right_clear = 0;

    for(i = 0 ; i<100 ; i++) {
        float* result = runOneSimulation(leftTraffic, rightTraffic,rightTrafficLight,leftTrafficLight);
        f_avg_left_vehicles += result[0];
        f_avg_left += result[1];
        f_max_avg_left += result[2];
        f_avg_left_clear += result[3];
        f_avg_right_vehicles += result[4];
        f_avg_right += result[5];
        f_max_avg_right += result[6];
        f_avg_right_clear += result[7];
        free(result);
    }

    fprintf(stdout,"Paramater values:\n");
    fprintf(stdout,"    from left:\n");
    fprintf(stdout,"                traffic arrival rate: %f\n",leftTraffic);
    fprintf(stdout,"                traffic light period: %i\n", leftTrafficLight);
    fprintf(stdout,"    from right:\n");
    fprintf(stdout,"                traffic arrival rate: %f\n",rightTraffic);
    fprintf(stdout,"                traffic light period: %i\n",rightTrafficLight);
    fprintf(stdout,"Results (averaged over 100 runs):\n");
    fprintf(stdout,"    from left:\n");
    fprintf(stdout,"                number of vehicles: %i\n",(int)f_avg_left_vehicles/100);
    fprintf(stdout,"                average waiting time: %f\n",f_avg_left/100);
    fprintf(stdout,"                maximum waiting time: %f\n",f_max_avg_left/100);
    fprintf(stdout,"                clearance time: %f\n",f_avg_left_clear/100);
    fprintf(stdout,"    from right:\n");
    fprintf(stdout,"                number of vehicles: %i\n",(int)f_avg_right_vehicles/100);
    fprintf(stdout,"                average waiting time: %f\n",f_avg_right/100);
    fprintf(stdout,"                maximum waiting time: %f\n",f_max_avg_right/100);
    fprintf(stdout,"                clearance time: %f\n",f_avg_right_clear/100);



}

/* validate float from argument*/
int checkFloat(char* input){
    if(atof(input)==0){
        return 0;
    }else{
        return 1;
    }
    return 0;
}

/* validate int from argument*/
int checkInt(char* input){
    if(atoi(input)==0){
        return 0;
    } else {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    int a1;
    int a2;
    float a3;
    float a5;
    /* validates the arguments before input to the simulation */
    if(argc == 5 && checkFloat(argv[1]) && checkFloat(argv[2]) && checkInt(argv[3]) && checkInt(argv[4])){
    } 
    else {
        fprintf(stderr,"Arguments passed through are in incorrect order or count\n");
        return 0;
    }

    float rt = atof(argv[1]);
    float lt = atof(argv[2]);
    int rtl = atoi(argv[3]);
    int ltl = atoi(argv[4]);


    runSimulations(lt,rt,rtl,ltl);
    return 0;

}
