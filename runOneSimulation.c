#include "runOneSimulation.h"

/* Runs the actual simulation of the program*/
extern float* runOneSimulation(float leftTraffic ,float rightTraffic ,int rightTrafficLight,int leftTrafficLight)
{
    const gsl_rng_type *T;
    gsl_rng *r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    gsl_rng_set(r,time(0));
    int time_iteration = 1; /*inital start time*/
    node_t *right = NULL; /*initial node*/
    node_t *left = NULL;  /*intial left node*/

    int left_time = gsl_rng_uniform_int(r,1); /*randomly checks if 0 or 1 gets chosen to determine if left starts first*/
    int right_time = left_time == 0 ? 1 : 0;/* checks if left is True ,if not*/
    int left_time_count = 0;
    int right_time_count = 0;
    int rightMax = 0;
    int leftMax = 0;
    int total_left_waiting = 0;
    int total_right_waiting = 0;
    int left_vehicle_count = 0;
    int right_vehicle_count = 0;
    int total_left_clearance = 0;
    int total_right_clearance = 0;
    float* traffic_data;
    /* check if there is adequate memory*/
    if ( !(traffic_data = malloc(sizeof(int)*9)))
    {
        fprintf(stderr,"Out of memory\n");
        exit(1);
    }else{
        traffic_data = malloc(sizeof(float)*9);
    }

    while (time_iteration != 0) {    
 
        if ((leftTraffic >= gsl_ran_flat(r,0,1)) && (time_iteration < 501)){
            enqueue(&left, time_iteration);
        }
        if((rightTraffic >= gsl_ran_flat(r,0,1)) && (time_iteration < 501)){
            enqueue(&right, time_iteration);

        }
        
        if(left_time == 1){

            if (left_time_count!=leftTrafficLight) /* check time left for traffic counter*/
            {   left_time_count += 1; /*increments time counter*/
                if(isEmpty(&left)==0) /* checks if queue is empty*/
                {   
                    int queue_time;
                    int val = dequeue(&left);
                    /*vehicle count*/
                    left_vehicle_count += 1;
                    queue_time = time_iteration - val;
                    /*for calculating average total*/
                    total_left_waiting  += queue_time;
                    
                    /*Max waiting time*/
                    if(queue_time>leftMax){
                        leftMax = queue_time;
                    }
                    /* total clearance time*/
                    if(time_iteration>500){
                        total_left_clearance = time_iteration-500;
                    } else {
                        total_left_clearance = 0;
                    }

                }
            }
            else
            {   /*swaps the traffic light signs */
                right_time = 1;
                left_time = 0;
                left_time_count = 0;
            }
        } 
        
        if (right_time == 1) {
            
            if(right_time_count != rightTrafficLight) {
                right_time_count = right_time_count + 1;
                if(isEmpty(&right)==0) /* checks if queue is empty*/
                {
                    int queue_time;
                    int val = dequeue(&right); 
                    /*vehicle count*/
                    right_vehicle_count = right_vehicle_count + 1;
                    queue_time = time_iteration - val;
                    /*for calculating average total*/
                    total_right_waiting = total_right_waiting + queue_time;
                    /*Max waiting time*/
                    
                    if(queue_time>rightMax){
                        rightMax = queue_time;
                    }
                    /* total clearance time*/
                    if(time_iteration>500){
                        total_right_clearance = time_iteration - 500;
                    } else{
                        total_right_clearance = 0;
                    }
                    } 
            }
            else
            {   /*swaps the traffic light signs */
                left_time = 1;
                right_time = 0;
                right_time_count=0;
            }
            
        }
         /*checks if the queues are empty and the vehicles have stopped coming and then gathers all the data*/
        if(isEmpty(&right) == 1 && isEmpty(&left) == 1 && time_iteration>500){
            float average_left_lane  = (float)total_left_waiting/(float)left_vehicle_count;
            float average_right_lane = (float)total_right_waiting/(float)right_vehicle_count;
            traffic_data[0] = (float)left_vehicle_count;
            traffic_data[1] = average_left_lane;
            traffic_data[2] = (float)leftMax;
            traffic_data[3] = (float)total_left_clearance;
            traffic_data[4] = (float)right_vehicle_count;
            traffic_data[5] = average_right_lane;
            traffic_data[6] = (float)rightMax;
            traffic_data[7] = (float)total_right_clearance;
            gsl_rng_free(r);

            break;
        }
        time_iteration +=1;
        
    }
    return traffic_data ;
};

