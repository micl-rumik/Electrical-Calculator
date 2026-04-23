
//====DONE====
//add resistor calculator in row and parallel. {CHECK}
//add color code for resistors. {CHECK}
//add a tolerance function. {CHECK}
//reversed color code and tolerance for resistors. {CHECK}

//====CHECK LIST====
//AWG (american wire gauge)
//add voltage divider.
//E-series (cheking the closest real option for the requested resistor).    

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

float resistor_calc(bool is_parallel) {
    float current_R, sum = 0.0;
    int count;

    cout << "Enter the number of resistors: ";
    cin >> count;

    for (int i=1; i<=count; i++) {
        cout << "Enter the value of R"<<i<<": ";
        cin >> current_R;

        if (is_parallel) {
            sum += (1.0/current_R);
        }
        else {
            sum += current_R;
        }
    }
    if (is_parallel) {
        return (1.0/sum);
    }
    return sum;
}

float color_code(char c) {
    switch(toupper(c)) {
        case('B'): return 0;
        case('N'): return 1;
        case('R'): return 2;
        case('O'): return 3;
        case('Y'): return 4;
        case('G'): return 5;
        case('U'): return 6;
        case('V'): return 7;
        case('E'): return 8;
        case('W'): return 9;
        default: return -1;
    }
}

float tolerance(char t) {
    switch(toupper (t)) {
        case('N'): return 1;
        case('R'): return 2;
        case('O'): return 0.05;
        case('Y'): return 0.02;
        case('G'): return 0.5;
        case('U'): return 0.25;
        case('V'): return 0.1;
        case('E'): return 0.01;
        case('D'): return 5;
        case('S'): return 10;
        default: return -1;
    }
}

float color_to_value(int bands) {
    char c1,c2,c3,c4,c5;
    int v1,v2,v3,multiplier;
    float result,t;
    cout << "Enter color 1: "; cin >> c1;
    cout << "Enter color 2: "; cin >> c2;
    cout << "Enter color 3: "; cin >> c3;

    v1 = color_code(c1);
    v2 = color_code(c2);
    
    if (bands == 5) {
        v3 = color_code(c3);
        cout << "Enter color 4 (multiplier)"; cin >> c4;
        cout << "Enter color 5 (tolerance): "; cin >> c5;
        t = tolerance(c5);
        multiplier = color_code(c4);
        result = (v1 * 100 + v2 * 10 + v3) * pow(10,multiplier);

    }   
    else {
        multiplier = color_code(c3);
        cout << "Enter color 4 (tolerance): "; cin >> c4;
        t = tolerance(c4);
        result = (v1 * 10 + v2) * pow(10,multiplier);
    }
    cout << "Result: " << result << " +- " << t << "% [Ohms]";
    return result;
}

string second_color_code(int num) {
    switch(num) {
        case(0): return "Black";
        case(1): return "Brown";
        case(2): return "Red";
        case(3): return "Orange";
        case(4): return "Yellow";
        case(5): return "Green";
        case(6): return "Blue";
        case(7): return "Violet";
        case(8): return "Grey";
        case(9): return "White";
        default: return "Unknown";
    }
}

void digits (float num) {
    int multiplier = 0;
    while (num >= 100) {
        num = num / 10;
        multiplier++;
    }
    int digit1 = num / 10;
    int digit2 = (int)num % 10;
    cout << "The colors are: " << second_color_code(digit1) << ", " << second_color_code(digit2) << "\nThe Multiplier is: " << second_color_code(multiplier) << endl;
}

string tolerance_color(double num) {
    if (num == 1.0) return "Brown";
    else if (num == 2.0) return "Red";
    else if (num == 0.05) return "Orange";
    else if (num == 0.02) return "Yellow";
    else if (num == 0.5) return "Green";
    else if (num == 0.25) return "Blue";
    else if (num == 0.1) return "Violet";
    else if (num == 0.01) return "Grey";
    else if (num == 5.0) return "Gold";
    else if (num == 10.0) return "Silver";
    else return "unknown";
}

float awg_func(int num) {
    int awg_from_file;
    float res_from_file;
    ifstream file("AWG.txt");

    if (!file) {
        cout << "ERROR: FILE WAS NOT FOUND!" << endl;
    }

    while (file >> awg_from_file >> res_from_file) {
        if (awg_from_file == num) {
            return res_from_file;
        }
    }
}
int main () {
    int option;
    float R1, R2, I, V, R;
    do {
        system("cls");
        cout << "======ELECTRICAL CALCULATOR======\n";
        cout << "0 - exit\t 1 - Resistor calculator\t 2 - Resistor color code: \t 3 - Resistance to color: \t 4 - Voltage loss by cable AWG \nChoice: ";
        cin >> option;

        switch(option) {

            default:
                cout << "INVALID OPTION!\n";

            case 1:
                int connection;

                cout << "Choose the connection:\t 0 - row\t 1 - parallel\nChoice: ";
                cin >> connection;

                if (connection == 0) {
                    cout << resistor_calc(false)<<" [Ohms]\n";
                    break;
                }
            
                else {
                    cout << resistor_calc(true) << "[Ohms]\n";
                    break;
                }
            
            case 2:
                int num;
                cout << "The colors for you to choose are:\n B - black\n N - Brown\n R - red\n O - orange\n Y - yellow\n G - green\n U - blue\n V - violet\n E - grey\n W - white\n";
                cout << "Please enter the number of colors on the resistor(3, 4 or 5): "; cin >> num;
                if (num < 3 || num >5){
                    cout << "INVALID AMOUNT";
                }
                else {
                    color_to_value(num);
                    cout << " is the value of the resistor.\n";
                    break;
                }
            
            case 3:
                float number;
                double tolerance;
                cout << "Please enter the the resistance and then the tolerance: "; cin >> number >> tolerance; 
                digits(number);
                cout << "The tolerance color is: " << tolerance_color(tolerance) << endl;
                break;

            case 4: {

                int awg;
                float current;
                float length;


                cout << "Please enter the AWG of the cable and the length[m]: "; cin >> awg >> length;
                cout << "Enter the current: "; cin >> current;
                
                float res_per_km = awg_func(awg);
                float voltage_loss;
                float res_tot = (res_per_km/1000.0) * length;
                voltage_loss = res_tot * current;

                cout << "The resistance for " << awg << " is " << res_tot <<" [Ohm]"<< endl << "The Voltage loss is: " << voltage_loss <<" [V]"<< endl; 
                break;
            }
            
            case 0:
                cout << "Bye!";

        }
        if (option != 0) {
            cout << "PRESS ENTER TO RETURN TO MAIN MENU...";
            cin.ignore();
            cin.get();
        }
    }
    while (option != 0);
    
}