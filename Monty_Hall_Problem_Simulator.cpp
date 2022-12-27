// Automated Monty Hall Simulator
// By: Benjamin Yee
// Email: yeebenja@umich.edu
// LinkedIn: https://www.linkedin.com/in/bay02

#include <iostream>
#include <random>
#include <string>
#include <map>

using namespace std;

int random_1_to_3(void){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,2); // distribution in range [0, 2]

    // std::cout << dist6(rng) << std::endl;
    return dist6(rng);
}

// Monty Hall Problem Simulator
class Monty_Hall_Module{
    
  private:
  map<int, string> door;
  int car_pos;
  int first_choice;
  int door_reveal;
  int new_choice;

  
  public:
  // Default Constructor
  Monty_Hall_Module() {}


  // Top level Module
  void run(void){
      init_doors();
      step_1();
      step_2();
  }
  
  // Initialize doors module
  void init_doors(void){
    // First, figure out where to put the car
    // Then, put goats in the rest of the doors
    car_pos = random_1_to_3();
    if(car_pos == 0){ door[0] = "car"; door[1] = "goat"; door[2] = "goat";}
    else if(car_pos == 1){ door[1] = "car"; door[0] = "goat"; door[2] = "goat";}
    else{ door[2] = "car"; door[0] = "goat"; door[1] = "goat";}
  }
  
  // Step 1 Module: Choose a door and reveal a goat
  void step_1(void){
    first_choice = random_1_to_3();
    
    // We need a way to figure out what door we need to reveal
    // -------
    // We need a function to reveal a goat door that is not
    // the same door as our first choice
    reveal_goat();
  }
  
  
  // Step 2 Module: Switch choice to other door when goat
  // is revealed
  void step_2(void){
    if(first_choice == 0){
        if(door_reveal == 1) new_choice = 2;
        else if(door_reveal == 2) new_choice = 1;
    }
    else if(first_choice == 1){
        if(door_reveal == 0) new_choice = 2;
        else if(door_reveal == 2) new_choice = 0;
    }
    else if(first_choice == 2){
        if(door_reveal == 0) new_choice = 1;
        else if(door_reveal == 1) new_choice = 0;
    }
  }
  
  // Result Module: Reveal results
  int won_car(void){
      // Output result into ostringstream
      if(door[new_choice] == "car") return 1;
      else return 0;
  }
  
  
  void reveal_goat(void){
    if(first_choice == 0){
        if(door[1] == "goat") door_reveal = 1;
        else door_reveal = 2;
    }
    else if(first_choice == 1){
        if(door[0] == "goat") door_reveal = 0;
        else door_reveal = 2;
    }
    else if(first_choice == 2){
        if(door[0] == "goat") door_reveal = 0;
        else door_reveal = 1;
    }
  }
  
};



int main(){
    
    vector<int> win_loss;
    int number_of_samples = 1000; // Number of Simulation Trials
                                  // Change as needed!
    double win_car_percentage;
    int number_of_wins = 0;

    for(int i = 0; i < number_of_samples; ++i){
        Monty_Hall_Module inst1;
        inst1.run();
        win_loss.push_back(inst1.won_car());
    }
    for(int i = 0; i < number_of_samples; ++i){
        if(win_loss[i] == 1) number_of_wins++;
    }
    win_car_percentage = (double) number_of_wins / (double) number_of_samples;
    
    cout << "You won a car " << win_car_percentage * (double) 100 << "% of the time!" << endl;

    return 0;
}
