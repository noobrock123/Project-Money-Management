#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
int main()
{
	cout << "Initializing file..." << endl;
    std::fstream inFile;
    inFile.open("DATA.file", std::ios::in);
    if (!inFile.is_open()) {
        std::cerr << "Error: File is either missing or corrupted." << endl;
        return 1;
    }
    cout << "Loading data..." << endl;
    string line;
    string list; double mChange; double balance; int index;
    //----------------------------------------------------------
    std::vector <string> lists;
    std::vector <double> change;
    std::vector <double> balances;
    std::getline(inFile, line);
    std::stringstream ss;
    while (std::getline(inFile, line)) {
        ss << line;
        ss >> list;
        ss >> mChange;
        ss >> balance;
        lists.push_back(list); change.push_back(mChange);
        balances.push_back(balance);
        ss.clear();
    }
    inFile.close();
    cout <<"Completed..." << endl;
    cout << endl;
    cout << std::setw(30) << "Welcome to my program" << endl;
    cout << "===========================================" << endl;
    cout << endl;
    short n;
    while (n != 4) {
        n = 0;
        cout << "Please select below" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Check my data" << endl;
        cout << "2. Check balance" << endl;
        cout << "3. Including my list" << endl;
        cout << "4. Change my list" << endl;
        cout << "5. Save and close program" << endl;
        cout << "6. Discard and close program" << endl;
        cout << ">>> ";
        cin >> n;
        switch (n) {
            case 1:
                if (static_cast<int>(lists.size()) == 0) {
                    cout << "You don't have anything in the list yet..." << endl;
                    break;
                }
                cout << "            List            |           Change           |       Balance" << endl;
                cout << std::left;
                for (size_t i = 0; i < lists.size(); i++) {
                    cout << (i+1) << std::setw(4) << ".";
                    cout << std::setw(23) << lists[i];
                    cout << std::setw(3) << "|";
                    cout << std::showpos << std::setw(26) << change[i];
                    cout << std::setw(3) << "|";
                    cout << std::noshowpos << balances[i] << endl;
                }
                break;
            case 2:
                cout << "Your balance is " << balances[static_cast<int>(balances.size()) - 1] << endl;
                break;
            case 3:
                cout << "Enter a list\n" << ">>> ";
                cin >> list;
                cout << "Enter money change\n" << ">>> ";
                cin >> mChange;
                cout << "Processing..." << endl;
                lists.push_back(list);
                change.push_back(mChange);
                if (static_cast<int>(balances.size()) - 1 < 0) {
                    balances.push_back(mChange);
                    cout << "Completed..." << endl;
                    break;
                }
                balances.push_back(balances[static_cast<int>(balances.size()) - 1] + mChange);
                list = ""; mChange = 0;
                cout << "Completed..." << endl;
                break;
            case 4:
                cout << "            List            |           Change           |       Balance" << endl;
                cout << std::left;
                for (size_t i = 0; i < lists.size(); i++) {
                    cout << (i+1) << std::setw(4) << ".";
                    cout << std::setw(23) << lists[i];
                    cout << std::setw(3) << "|";
                    cout << std::showpos << std::setw(26) << change[i];
                    cout << std::setw(3) << "|";
                    cout << std::noshowpos << balances[i] << endl;
                }
                cout << "Select a list\n" << ">>> ";
                cin >> index;
                if (index - 1 < 0 || index - 1 > static_cast<int>(lists.size())) {
                    std::cerr << "Error: Either invalid input or exceed the current list." << endl;
                    break;
                }
                cout << "Change a list name?\nYes: 1 No: 0\n" << ">>>";
                cin >> n;
                if (n == 1) {
                    cout << "Enter a list name\n" << ">>> ";
                    cin >> list;
                    lists[index - 1] = list;
                }
                cout << "Enter a change in balance\n" << ">>> ";
                cin >> mChange;
                change[index - 1] = mChange;
                cout << "Processing..." << endl;
                change[0] = balances[0] = mChange;
                if (lists.size() > 1) {
                    for (size_t i = 1; i < lists.size(); i++) {
                        balances[i] = change[i] + balances[i - 1];
                    }
                }
                cout << "Completed..." << endl;
                cout << endl;
                break;
            case 5:
                cout << "Saving..." << endl;
                inFile.open("DATA.file", std::ios::out);
                inFile << std::left;
                inFile << "List                        Change                      Balance" << endl;
                for (size_t i = 0; i < lists.size(); i++) {
                    inFile << std::setw(28) << lists[i];
                    inFile << std::setw(28) << change[i];
                    inFile << balances[i];
                    
                    inFile << endl;
                    }
                inFile.close();
                cout << "Saving completed. Thank you for using our program!" << endl;
                return 0;
            case 6:
                cout << "Do you want to discard any progress?\nYes: 1 No: 0\n" << ">>> ";
                cin >> n;
                if (n == 1) {
                    cout << "Exiting program... Thank you for using our program!" << endl;
                    return 0;
                }
                else {
                    break;
                }
            default: {
                break;
            }
        }
        
        
    }
	return 0;
    
}
