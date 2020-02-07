#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string F(string n);
string n_minus_1(string n);
string n_minus_2(string n);
void find_F_greater_than(string n);
bool is_divisible(string dividend, string divisor);
bool is_prime(string n);

string add(string top, string bottom);
string subtract(string top, string bottom);
string format_commas(string number);
string remove_excess_0s(string n);

int main(int argc, char** argv)
{
    cout << "Will generate as many prime Fibonaccis as possible." << endl;
    string total = "0", n_minus_1 = "1", n_minus_2 = "0";
    cout << "F(0) = 0 is NOT prime." << endl;
    cout << "F(1) = 1 is NOT prime." << endl;
    int prime_number_counter = 0;
    
    //change prime number counter here:
    for(int i = 2; prime_number_counter < 100; i++)
    {
        total = add(n_minus_1, n_minus_2);
        n_minus_2 = n_minus_1;
        n_minus_1 = total;
        if(is_prime(total))
        {
            prime_number_counter++;
            cout << endl << "****************F(" + to_string(i) + ") = " + format_commas(total) << " is prime." << endl;
        }
        else
            cout << "F(" + to_string(i) + ") = " + format_commas(total) << " is NOT prime." << endl;
    }
}

//recursive Fibonacci function;
//takes a number as a string input;
string F(string n)
{
    if(n == "0")
        return "0";
    else if(n == "1")
        return "1";
    else
        return add(F(n_minus_1(n)), F(n_minus_2(n)));
}

string n_minus_1(string n)
{
    return to_string((stoi(n) - 1));
}

string n_minus_2(string n)
{
    return to_string((stoi(n) - 2));
}

void find_F_greater_than(string n)
{
    n = remove_excess_0s(n);
    string total, n_minus_1 = "1", n_minus_2 = "0";
    for(int i = 2; ; i++)
    {
        if(total.length() > n.length())
        {
            cout << "The smallest fibonacci number greater than " + format_commas(n) + " is: " << endl;
            cout << "F(" + to_string(i - 1) + ") = " + format_commas(total) << endl;
            return;
        }
        else if(total.length() == n.length())
        {
            for(int j = 0; j < total.length(); j++)
            {
                //if the digit of total > digit of n, total > n;
                //else if the digit of total < digit of n, total < n;
                //else, move to next digit;
                if(total[j] > n[j])
                {
                    cout << "The smallest fibonacci number greater than " + format_commas(n) + " is: " << endl;
                    cout << "F(" + to_string(i - 1) + ") = " + format_commas(total) << endl;
                    return;
                }
                else if(total[j] < n[j])
                    break;
            }
        }
        total = add(n_minus_1, n_minus_2);
        n_minus_2 = n_minus_1;
        n_minus_1 = total;
    }
}

//returns true if dividend % divisor == 0; otherwise false;
bool is_divisible(string dividend, string divisor)
{
    dividend = remove_excess_0s(dividend);
    divisor = remove_excess_0s(divisor);
    string remainder = dividend, quick_divisor = divisor;
    //creates division through repeated subtraction;
    for(; quick_divisor.length() < (remainder.length() - 1);)
    {
        //greatly speed up the process by "multiplying" the divisor by multiples of 10; store in quick_divisor;
        for(int i = divisor.length(); i < remainder.length() - 1; i++)
        {
            quick_divisor = quick_divisor + "0";
        }
        for(;;)
        {
            if(remainder[0] == '-')
            {
                //revert last subtraction, because the original divisor is smaller;
                remainder[0] = '0';
                remainder = subtract(quick_divisor, remainder);
                remainder = remove_excess_0s(remainder);
                quick_divisor = divisor;
                break;
            }
            else if(remainder[0] == '0')
                return true;
            remainder = subtract(remainder, quick_divisor);
        }
    }
    //checks to see if the smallest divisor is capable of dividing into the dividend;
    //the dividend has already been reduced from the repeated subtraction of the quick_divisor;
    for(;;)
    {
        if(remainder[0] == '-')
            return false;
        else if(remainder[0] == '0')
            return true;
            remainder = subtract(remainder, divisor);
    }
}

bool is_prime(string n)
{
    n = remove_excess_0s(n);
    int max_length_sqrt_n = 0;
    //digits of sqrt(n) is n/2 if n has even length of digits; (n/2) + 1 if odd length of digits;
    if(n.length() % 2 == 0)
        max_length_sqrt_n = (n.length() / 2) + 1;
    else
        max_length_sqrt_n = (n.length() / 2) + 2;
    if(n == "0" || n == "1")
        return false;
    if(is_divisible(n, "2") && n != "2")
        return false;
    //since primes are never even with the exception of 2;
    for(string i = "3"; i.length() < max_length_sqrt_n; i = add(i, "2"))
    {
        if(is_divisible(n, i) && n != i)
            return false;
    }
}

string add(string top, string bottom)
{
    //******Preparation for addition**********;
    top = remove_excess_0s(top);
    bottom = remove_excess_0s(bottom);
    int length = 0;
    if(top.length() < bottom.length())
        length = bottom.length();
    else
        length = top.length();
    //adds 0 in front of the number to adjust them to the same size;
    for(int i = 0; i < length; i++)
    {
        //equivalent to if(left[i] == NULL);
        if(top[i] == '\0')
            top = "0" + top;
        if(bottom[i] == '\0')
            bottom = "0" + bottom;
    }
    //reverse the orders of the digits to perform addition from left to right;
    reverse(top.begin(), top.end());
    reverse(bottom.begin(), bottom.end());
    //*************Part to perform the addition*************;
    //carry_over signifies the one that gets carried over when adding;
    bool carry_over = false;
    string total;
    for(int i = 0; i < length; i ++)
    {
        //get the digits as single digit integers to perform addition;
        int top_digit = (top[i] - '0');
        int bottom_digit = (bottom[i] - '0');
        if(carry_over == true)
        {
            top_digit++;
            carry_over = false;
        }
        if((top_digit + bottom_digit) / 10 > 0)
            carry_over = true;
            
        //concatenates a digit between 0 and 9;
        int result = (top_digit + bottom_digit) % 10;
        total = total + to_string(result);
        
        //in case the last addition carries over;
        if(carry_over == true && i == (length - 1))
            total = total + "1";
    }
    //undo the initial reverse for proper ordering;
    reverse(total.begin(), total.end());
    total = remove_excess_0s(total);
    return total;
}

string subtract(string top, string bottom)
{
    //************Preparation for subtraction***********
    top = remove_excess_0s(top);
    bottom = remove_excess_0s(bottom);
    bool top_smaller_than_bottom = false;
    int length = 0;
    //get the bigger number on top;
    if(top.length() < bottom.length())
    {
        length = bottom.length();
        top_smaller_than_bottom = true;
        swap(top, bottom);
    }
    else if(top.length() == bottom.length())
    {
        length = top.length();
        for(int i = 0; i < length; i++)
        {
            if(top[i] < bottom[i])
            {
                top_smaller_than_bottom = true;
                swap(top, bottom);
                break;
            }
            else if(top[i] > bottom[i])
                break;
        }
    }
    else
        length = top.length();
    //adds 0 in front of the number to adjust them to the same size;
    for(int i = 0; i < length; i++)
    {
        if(top[i] == '\0')
            top = "0" + top;
        if(bottom[i] == '\0')
            bottom = "0" + bottom;
    }
    //reverse the orders of the digits to perform subtraction from left to right;
    reverse(top.begin(), top.end());
    reverse(bottom.begin(), bottom.end());
    
    //**************Parts to perform the subtraction*************
    //carry_over siginifies the one that gets borrowed when subtracting with smaller digits;
    bool carry_over = false;
    string total;
    for(int i = 0; i < length; i++)
    {
        //get the digits as single digit integers to perform subtraction;
        int top_digit = (top[i] - '0');
        int bottom_digit = (bottom[i] - '0');
        if(carry_over == true)
        {
            top_digit--;
            carry_over = false;
        }
        if((top_digit - bottom_digit) < 0)
        {
            top_digit = top_digit + 10;
            carry_over = true;
        }
        
        int result = top_digit - bottom_digit;
        total = total + to_string(result);
    }
    reverse(total.begin(), total.end());
    total = remove_excess_0s(total);
    if(top_smaller_than_bottom == true)
        total = "-" + total;
    return total;
}

//create substrings from groups of 3, inserts a comma in between, and concatenates;
string format_commas(string number)
{
    number = remove_excess_0s(number);
    reverse(number.begin(), number.end());
    for(int i = 3; i < number.length(); i = i + 3)
    {
        string first_part = number.substr(0, i);
        string second_part = number.substr(i);
        number = first_part + "," + second_part;
        i++;
    }
    reverse(number.begin(), number.end());
    return number;
}

//removes the 0s that appear before a string number (e.g. "0045" -> "45");
string remove_excess_0s(string n)
{
    for(int i = 0; i < n.length(); i++)
    {
        if(n[i] == '0')
            continue;
        else
        {
            n = n.substr(i);
            break;
        }
    }
    return n;
}