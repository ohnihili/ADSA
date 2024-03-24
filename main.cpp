#include <iostream>
#include <string>

using namespace std;

string addStrings(string no1, string no2, int base) 
{
    int carry = 0;
    int sum;
    string result;

    while (no1.size() < no2.size())
    {
        no1.insert(0, "0");
    }
    
    while (no2.size() < no1.length())
    {
        no2.insert(0, "0");
    }
    
    for (int i = no1.length() - 1; i >= 0; i--) 
    {
        sum = (no1[i] - '0') + (no2[i] - '0') + carry;
        carry = sum / base;
        result.insert(0, to_string(sum % base));
    }

    if (carry==1)
    {
        result.insert(0, to_string(carry));
    }

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string subStrings(string no1, string no2, int base) 
{
    int diff;
    string result;

    while (no1.size() < no2.length())
    {
        no1.insert(0, "0");
    }
    
    while (no2.size() < no1.length())
    {
        no2.insert(0, "0");
    }

    for (int i = no1.size() - 1; i >= 0; i--)
    {
        diff = (no1[i] - '0') - (no2[i] - '0');
        if (diff >= 0){
            result.insert(0, to_string(diff));
        }
        else 
        {
            int j = i - 1;
            while (j >= 0) 
            {
                no1[j] = ((no1[j] - '0') - 1) % base + '0';
                char maxincol = base-1 +'0';
                
                if (no1[j] != maxincol)
                {
                    break;
                }
                else{
                    j--;
                }
            }
            result.insert(0, to_string(diff + base));
        }
    }

    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string multStrings(string no1, string no2, int base) 
{
    while (no1.size() < no2.size())
        no1.insert(0, "0");

    while (no2.size() < no1.size())
        no2.insert(0, "0");

    if (no1.size() == 1)
    {
        int product= (no1[0] - '0') * (no2[0] - '0');
        string stringproduct="";
        while(product>0)
        {
            stringproduct = to_string(product%base) + stringproduct;
            product/=base;
        }
        return stringproduct;
    }

    string no1L = no1.substr(0, no1.size() / 2);
    string no1R = no1.substr(no1.size() / 2, no1.size() - no1.size() / 2);
    string no2L = no2.substr(0, no2.size() / 2);
    string no2R = no2.substr(no2.size() / 2, no1.size() - no1.size() / 2);

    string p0 = multStrings(no1L, no2L, base);
    string p1 = multStrings(no1R, no2R, base);
    string p2 = multStrings(addStrings(no1L, no1R, base), addStrings(no2L, no2R, base), base);
    string p3 = subStrings(p2, addStrings(p0, p1, base), base);

    for (int i = 0; i < 2 * (no1.size() - no1.size() / 2); i++)
        p0.append("0");
    for (int i = 0; i < no1.size() - no1.size() / 2; i++)
        p3.append("0");

    return addStrings(addStrings(p0, p1, base), p3, base);
}

int main() 
{
    string I1, I2;
    int B;

    cin >> I1 >> I2 >> B;
    cout << addStrings(I1, I2, B) <<" ";
    cout << multStrings(I1, I2, B) <<" 0";
    cout << endl;

    return 0;
}
