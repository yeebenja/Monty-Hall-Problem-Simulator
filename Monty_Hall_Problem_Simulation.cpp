// Automated Monty Hall Simulator
// By: Benjamin Yee
// Email: yeebenja@umich.edu
// LinkedIn: https://www.linkedin.com/in/bay02

#include <iostream>
#include <random>
#include <string>
#include <map>

using namespace std;

// ------------------------------
// Got this idea off of Stack Overflow. I
// modified it to return a random integer from 0 to 2.
// 
// EFFECTS: Function returns random integer from 0
// to 2. 
int random_0_to_2(void) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution_obj(0, 2); // distribution in range [0, 2]
                                                     // ^^^ Change as needed ^^^
    return distribution_obj(rng);
}
// ------------------------------

// Monty Hall Problem Simulator
class Monty_Hall_Module_Switch {

private:
    map<int, string> door;
    int car_pos;
    int first_choice;
    int door_reveal;
    int new_choice;


public:
    // Default Constructor
    Monty_Hall_Module_Switch() {}


    // Top level Module
    // EFFECTS: Runs all helper functions in three steps
    void run(void) {
        init_doors();
        step_1();
        step_2();
    }

    // Initialize doors module
    // EFFECTS: Initializes all three doors. Car and goats are
    // randomly placed
    void init_doors(void) {
        // First, figure out where to put the car
        // Then, put goats in the rest of the doors
        car_pos = random_0_to_2();
        if (car_pos == 0) { door[0] = "car"; door[1] = "goat"; door[2] = "goat"; }
        else if (car_pos == 1) { door[1] = "car"; door[0] = "goat"; door[2] = "goat"; }
        else { door[2] = "car"; door[0] = "goat"; door[1] = "goat"; }
    }

    // Step 1 Module: Choose a door and reveal a goat
    void step_1(void) {
        first_choice = random_0_to_2();

        // We need a way to figure out what door we need to reveal
        // -------
        // We need a function to reveal a goat door that is not
        // the same door as our first choice
        reveal_goat();
    }


    // Step 2 Module: Switch choice to other door when goat
    // is revealed
    void step_2(void) {
        if (first_choice == 0) {
            if (door_reveal == 1) new_choice = 2;
            else if (door_reveal == 2) new_choice = 1;
        }
        else if (first_choice == 1) {
            if (door_reveal == 0) new_choice = 2;
            else if (door_reveal == 2) new_choice = 0;
        }
        else if (first_choice == 2) {
            if (door_reveal == 0) new_choice = 1;
            else if (door_reveal == 1) new_choice = 0;
        }
    }

    // Result Module
    // EFFECTS: Returns 1 if Candidate won a car
    // else returns 0
    int won_car(void) {
        // Output result into ostringstream
        if (door[new_choice] == "car") return 1;
        else return 0;
    }

    // EFFECTS: Reveals goat after Step 1
    void reveal_goat(void) {
        if (first_choice == 0) {
            if (door[1] == "goat") door_reveal = 1;
            else door_reveal = 2;
        }
        else if (first_choice == 1) {
            if (door[0] == "goat") door_reveal = 0;
            else door_reveal = 2;
        }
        else if (first_choice == 2) {
            if (door[0] == "goat") door_reveal = 0;
            else door_reveal = 1;
        }
    }

};

class Monty_Hall_Module_Keep {
private:
    map<int, string> door;
    int car_pos;
    int choice;
    int door_reveal;

public:
    // Top Level Module
    // EFFECTS: Runs all helper functions
    void run(void) {
        init_doors();
        pick_door();
        reveal_goat();
    }

    // Initialize-doors Module
    // EFFECTS: Initializes all three doors. Car and goats are
    // randomly placed
    void init_doors(void) {
        // First, figure out where to put the car
        // Then, put goats in the rest of the doors
        car_pos = random_0_to_2();
        if (car_pos == 0) { door[0] = "car"; door[1] = "goat"; door[2] = "goat"; }
        else if (car_pos == 1) { door[1] = "car"; door[0] = "goat"; door[2] = "goat"; }
        else { door[2] = "car"; door[0] = "goat"; door[1] = "goat"; }
    }
    
    // Pick-Door Module
    // EFFECTS: Candidate randomly picks a door
    void pick_door(void) {
        choice = random_0_to_2();
    }

    // EFFECTS: Reveals goat after Step 1
    void reveal_goat(void) {
        if (choice == 0) {
            if (door[1] == "goat") door_reveal = 1;
            else door_reveal = 2;
        }
        else if (choice == 1) {
            if (door[0] == "goat") door_reveal = 0;
            else door_reveal = 2;
        }
        else if (choice == 2) {
            if (door[0] == "goat") door_reveal = 0;
            else door_reveal = 1;
        }
    }

    // Result Module
    // EFFECTS: Returns 1 if Candidate won a car
    // else returns 0
    int won_car(void) {
        // Output result into ostringstream
        if (door[choice] == "car") return 1;
        else return 0;
    }
    
};

// Main function
int main() {

    vector<int> win_loss;
    size_t number_of_samples = 200000; // Number of Simulation Trials
    // Change value of "number_of_samples" as needed!
    double win_car_percentage;
    int number_of_wins = 0;
   
    cout << "Monty Hall Simulation: Switching Choices" << endl;
    cout << "Running..." << endl;

    for (size_t i = 0; i < number_of_samples; ++i) {
        Monty_Hall_Module_Switch inst1;
        inst1.run();
        win_loss.push_back(inst1.won_car());
    }
    for (int i = 0; i < number_of_samples; ++i) {
        if (win_loss[i] == 1) number_of_wins++;
    }
    win_car_percentage = (double) number_of_wins / (double) number_of_samples;
    cout << "You won a car " << win_car_percentage * (double)100 << "% of the time!" << endl;
    

    vector<int> win_loss_keep;
    // Change variable "number_of_samples" as needed!
    double win_car_percentage_keep;
    int number_of_wins_keep = 0;

    cout << "Monty Hall Simulation: Keeping Original Choice" << endl;
    cout << "Running..." << endl;

    for (size_t i = 0; i < number_of_samples; ++i) {
        Monty_Hall_Module_Keep inst2;
        inst2.run();
        win_loss_keep.push_back(inst2.won_car());
    }
    for (int i = 0; i < number_of_samples; ++i) {
        if (win_loss_keep[i] == 1) number_of_wins_keep++;
    }
    win_car_percentage_keep = (double)number_of_wins_keep / (double)number_of_samples;
    cout << "You won a car " << win_car_percentage_keep * (double)100 << "% of the time!" << endl;

    return 0;
}
