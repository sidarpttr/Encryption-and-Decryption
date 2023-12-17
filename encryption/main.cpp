#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>

using namespace std;
using namespace chrono;

class encryption
{
public:
    int matrix[26][26];
    encryption()
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                matrix[i][j] = (65 + (i + j) % 26);
            }
        }
    }
    string encrypt(string data, string key)
    {
        int size = data.length();
        int pre_key[size];
        int _key[size];
        int _pas[size];
        string password;

        for (char &k : key)
            k = (char)toupper(k);
        for (char &d : data)
            d = (char)toupper(d);

        for (int i = 0; i < size; i++)
        {
            pre_key[i] = key[i % key.length()];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (pre_key[i] == matrix[0][j])
                {
                    _key[i] = j;
                }
                if ((int)data[i] == matrix[j][0])
                {
                    _pas[i] = j;
                }
            }
        }

        for (int i = 0; i < size; i++)
            password += matrix[_key[i]][_pas[i]];

        return password;
    }

    string decrypt(string password, string _key)
    {
        string text;
        string pre_text;
        int size = password.length();
        string key;
        int c[size];

        if (size > _key.length())
        {
            for (int i = 0; i < size; i++)
            {
                key += _key[i % _key.length()];
            }
        }

        for (char &k : key)
            k = toupper(k);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (key[i] == matrix[0][j])
                {
                    c[i] = j;
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (password[i] == matrix[j][c[i]])
                {
                    text += matrix[j][0];
                }
            }
        }

        return text;
    }

    bool hasvowel(string a)
    {
        string consonants = "BCDFGHJKLMNPQRSTVWXYZ";
        int size = a.length();
        int counter = 0;
        for (int i = 0; i < size; i++)
        {
            for (char c : consonants)
            {
                if (a[i] == c)
                {
                    counter++;
                }
            }
        }
        if (counter == size)
            return 0;
        return 1;
    }

    double similar(string guess, string pw)
    {
        for (char &g : guess)
            g = toupper(g);

        for (char &p : pw)
            p = toupper(p);

        int control = 0;
        int size = pw.length();

        for (char &p : pw)
        {
            for (char &g : guess)
            {
                if (g == p)
                {
                    p = '0';
                    control++;
                }
            }
        }

        return (double)control / size;
    }

    void find(string password, string guess = "", float r = 1)
    {
        string key = "AAA";
        bool isguess = (guess == "") ? 0 : 1;
        auto start = high_resolution_clock::now();
        float max_ratio = 0;
        int max_count = 0;
        string word[50];
        string pw;

        cout << "-----START-----" << endl;
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                for (int k = 0; k < 26; k++)
                {
                    key[0] = matrix[i][0];
                    key[1] = matrix[j][0];
                    key[2] = matrix[k][0];

                    pw = decrypt(password, key);
                    
                    if (hasvowel(pw))
                    {
                        if (guess != "")
                        {
                            float ratio = similar(guess, pw);

                            if (ratio > max_ratio)
                            {
                                max_count = 0;
                                max_ratio = ratio;
                            }
                            else if (ratio == max_ratio)
                            {
                                word[max_count] = pw;
                                max_count++;
                            }
                            if (ratio >= r)
                            {
                                if (ratio >= 0.8 && ratio < 1)
                                    cout << " [" << pw << " <" << ratio << ">]";
                                else if (ratio == 1)
                                    cout << endl
                                         << "!!! [" << pw << " <" << ratio << ">] !!!" << endl;
                                else
                                    cout << " (" << pw << " " << ratio << ") ";
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else
                        {
                            cout << " " <<key<<" " << pw << " ";
                        }
                    }
                }
            }
            cout << endl;
            for (int g = 0; g < 200; g++)
                cout << "-";
            cout << endl;
        }
        cout << endl
             << "-----FINISH-----";

        if (guess != "")
        {
            for (int i = 0; i < max_count; i++)
                cout << "\n'" << word[i] << "'";
            cout << "\nmax ratio:\t" << max_ratio << " (" << ++max_count << ")";
        }

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);

        float seconds = duration.count() / 1000.0f;
        ;

        cout << "\nprocess time:    " << seconds << " second" << endl;
    }
};

int main()
{

    encryption d;
    string choice;
    string prompt;
    string key;
    while (1)
    {

        cout << "\nwhat do you want to do?\n1.\tencryption\n2.\tdecryption\n3.\tdecryption without key (length of key must 3)\t\n0.\tquit\n>>";
        cin >> choice;
        if (choice == "1")
        {
            system("cls");
            cout << "enter a text to encrypt:\t";
            cin >> prompt;
            cout << "enter a key:\t";
            cin >> key;
            cout << "-----------------------------\nencrypted text:\t" << d.encrypt(prompt, key) << endl;
        }
        else if (choice == "2")
        {
            system("cls");
            cout << "enter a encrypted text to decrypt:\t";
            cin >> prompt;
            cout << "enter a key:\t";
            cin >> key;
            cout << "-----------------------------\ntext:\t" << d.decrypt(prompt, key) << endl;
        }
        else if (choice == "3")
        {
            system("cls");
            cout << "enter a encrypted text to decrypt:\t";
            cin >> prompt;
            cout << "if you have a guess type guess or type 0:\t";
            cin >> key;
            if (key != "0")
            {
                float ratio;
                cout << "min ratio (0-1) :\t";
                cin >> ratio;
                d.find(prompt, key, ratio);
            }
            else
            {
                cout << "-----------------------------\n";
                d.find(prompt);
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}