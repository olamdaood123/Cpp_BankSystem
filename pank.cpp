
#include<iostream>

#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;
const string ClientFileName = "PANk.txt";
void ShowMinueScreen();
void ShowTransactionMinue();
struct sClient
{
    string AccountNumber;
    string pinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelet = false;
};

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    (void)FileName;
    vector<sClient> vClient;
    fstream MyFile;
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        if (Client.AccountNumber == AccountNumber)
        {
            MyFile.close();
            return true;
        }
        MyFile.close();
    }
    return false;
}
sClient ReadNewClient()
{
    sClient Client;
    cout << "ENTER ACCOUNT NUMBER ";
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName))
    {
        cout << "\n\n CLIENT WITH ACCOUNT NUMBER ( " << Client.AccountNumber << " )ALREADY EXISTS,\n ENTER ANOTHER ACCOUNT NUMBER?";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "ENTER PIN COUD ";
    getline(cin, Client.pinCode);
    cout << "ENTER NAME ";
    getline(cin, Client.Name);
    cout << "ENTER PHONE ";
    getline(cin, Client.Phone);
    cout << "ENTER ACCOUNT PALANCE ";
    cin >> Client.AccountBalance;
    return Client;
}
void PrintClientRecordLine(sClient Client)
{
    cout << "|  " << left << setw(12) << Client.AccountNumber;
    cout << "|  " << left << setw(12) << Client.pinCode;
    cout << "|  " << left << setw(30) << Client.Name;
    cout << "|  " << left << setw(12) << Client.Phone;
    cout << "|  " << left << setw(12) << Client.AccountBalance;
}
void printClientRecordBalanceLine(sClient Client)
{
    cout << "|  " << left << setw(12) << Client.AccountNumber;
    cout << "|  " << left << setw(30) << Client.Name;
    cout << "|  " << left << setw(12) << Client.AccountBalance;
}
string ConvertRecordToLine(sClient Client, string Seperetor)
{
    string S1 = "";
    S1 += Client.AccountNumber + Seperetor;
    S1 += Client.pinCode + Seperetor;
    S1 += Client.Name + Seperetor;
    S1 += Client.Phone + Seperetor;
    S1 += to_string(Client.AccountBalance);
    return S1;
}
void AddDataLineToFILE(string ClientFileName, string REcordToLine)
{
    fstream MyFile;
    MyFile.open(ClientFileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << REcordToLine << endl;
        MyFile.close();
    }
}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFILE(ClientFileName, ConvertRecordToLine(Client, "#//#"));
}
void AddClients()
{
    char AddMore = 'y';

    do
    {
        system("cls");
        cout << "\n\t***ADD NEW CLIENT***\n";
        AddNewClient();
        cout << "***CLIENT ADDED SUCCESSFULY***\ndoyou want to add more client (y/n)? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

enum enMainMenueOption
{
    eListClient = 1,
    eAddNewClient = 2,
    eDeletClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTRANSACTION = 6,
    eExite = 7,
};
enum enTransactionMenueOption
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMinue = 4
};
void CoBackToMainMinue()
{
    cout << "\n press any key to go back to main minue ";
    system("pause>0");
    ShowMinueScreen();
}
void CoBackToTransactionMenue()
{
    cout << "\n press any key to go back to TRANSACTION minue ";
    system("pause>0");
    ShowTransactionMinue();
}

short ReadMainMinueOption()
{
    cout << "\nchoose what da you want to do ?(1,6)\n";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
short ReadTransactionMenueOption()
{
    short Choise = 0;
    cout << "please enter your choose (1 to 4)?";
    cin >> Choise;
    return Choise;
}



vector<string> SplitString(string Line, string Delim)
{
    std::string::size_type Pos = 0;
    vector<string> vString;
    string sWord;
    while ((Pos = Line.find(Delim)) != std::string::npos)
    {
        sWord = Line.substr(0, Pos);
        if (!sWord.empty())
        {
            vString.push_back(sWord);
        }
        Line.erase(0, Pos + Delim.length());
    }
    if (!Line.empty())
    {
        vString.push_back(Line);
    }
    return vString;
}
sClient ConvertLineToRecord(string Line, string Seperetor)
{
    vector<string> vClientData = SplitString(Line, Seperetor);
    sClient Client;
    Client.AccountNumber = vClientData[0];
    Client.pinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);
    return Client;
}
vector<sClient> LoadClientDataFromFile(string ClientFileName)
{
    vector<sClient> vClient;
    fstream MyFile;
    MyFile.open(ClientFileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line, "#//#");
            vClient.push_back(Client);
        }
        MyFile.close();
    }
    return vClient;
}
void ShowAllClientData()
{
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    cout << "\n\t\t\t\t\tclient list (" << vClient.size() << ")";
    cout << "\n------------------------------------------------------------";
    cout << "-----------------------------------------------------\n"
        << endl;
    cout << "|  " << left << setw(12) << "accpunt number";
    cout << "|  " << left << setw(12) << "pin code";
    cout << "|  " << left << setw(30) << "name";
    cout << "|  " << left << setw(12) << "phone";
    cout << "|  " << left << setw(12) << "account balance";
    cout << "\n------------------------------------------------------------";
    cout << "-----------------------------------------------------\n"
        << endl;
    if (vClient.size() == 0)
    {
        cout << "\n\t\t\t***NO CLIENT ADVILABLE IN THE SYSTEM!!!!***\n";
    }
    else
    {
        for (sClient Client : vClient)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    }

    cout << "\n------------------------------------------------------------";
    cout << "-----------------------------------------------------\n"
        << endl;
}






bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClient, sClient& Client)
{
    vClient = LoadClientDataFromFile(ClientFileName);
    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
sClient ChangeClientRecord(string AccountNumber)
{

    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "enter pin code ";
    getline(cin >> ws, Client.pinCode);
    cout << "enter name ";
    getline(cin, Client.Name);
    cout << "enter phone ";
    getline(cin, Client.Phone);
    cout << "enter account balance ";
    cin >> Client.AccountBalance;
    return Client;
}
bool MarkClientForDeletByAccountNumber(string AccountNumber, vector<sClient>& Vclient)
{
    for (sClient& C : Vclient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelet = true;
            return true;
        }
    }
    return false;
}
vector<sClient> SaveClientDataToFile(string FileName, vector<sClient> vClient)
{
    fstream myFile;
    myFile.open(FileName, ios::out);
    string DalaLine;
    if (myFile.is_open())
    {
        for (sClient C : vClient)
        {
            if (!C.MarkForDelet)
            {
                DalaLine = ConvertRecordToLine(C, "#//#");
                myFile << DalaLine << endl;
            }
        }
        myFile.close();
    }
    return vClient;
}
bool DeletClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
    sClient Client;    // „ €Ì— ·Õ›Ÿ »Ì«‰«  «·⁄„Ì· «·„ƒﬁ …
    char Answer = 'n'; // · Œ“Ì‰ ≈Ã«»… «·„” Œœ„ ⁄·Ï ”ƒ«· «· √ﬂÌœ

    // «·»ÕÀ ⁄‰ «·⁄„Ì· ›Ì «·ﬁ«∆„…
    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientRecordLine(Client); // ⁄—÷ »Ì«‰«  «·⁄„Ì· ﬁ»· «·Õ–›
        cout << "\nARE YOU SURE YOU WANT TO DELETE THIS CLIENT? (y/n) ";
        cin >> Answer; // ﬁ—«¡… ≈Ã«»… «·„” Œœ„

        if (toupper(Answer) == 'Y')
        { // ≈–« Ê«›ﬁ «·„” Œœ„ ⁄·Ï «·Õ–›
            //  ⁄·Ì„ «·⁄„Ì· ··Õ–› „‰ «·‹ vector
            if (MarkClientForDeletByAccountNumber(AccountNumber, vClient))
            {
                // Õ›Ÿ «·‹ vector »⁄œ Õ–› «·⁄„Ì· ›Ì «·„·›
                vClient = SaveClientDataToFile(ClientFileName, vClient);
                // ≈⁄«œ…  Õ„Ì· «·‹ vector „‰ «·„·› · ÕœÌÀ «·‰”Œ… «·Õ«·Ì…
                vClient = LoadClientDataFromFile(ClientFileName);
                cout << "\n* CLIENT DELETED SUCCESSFULLY *\n";
                return true; // ‰Ã«Õ «·Õ–›
            }
            else
            {
                // ≈–« «·⁄„Ì· ·„ ÌıÊÃœ ›Ì «·ﬁ«∆„… („Õ „· Ãœ« ‰«œ—)
                cout << "\nClient not found in the list.\n";
                return false;
            }
        }
        else
        {
            // ≈–« —›÷ «·„” Œœ„ «·Õ–›
            cout << "\nDelete cancelled.\n";
            return false;
        }
    }
    // ≈–« «·⁄„Ì· €Ì— „ÊÃÊœ „‰– «·»œ«Ì…
    else
    {
        cout << "\nClient with account number (" << AccountNumber << ") not found.\n";
        return false;
    }
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
    sClient client;    // „ €Ì— · Œ“Ì‰ »Ì«‰«  «·⁄„Ì· «·„ƒﬁ …
    char Answer = 'n'; // · Œ“Ì‰ ≈Ã«»… «·„” Œœ„ ⁄·Ï «· √ﬂÌœ

    // √Ê·«°  Õﬁﬁ „‰ ÊÃÊœ «·⁄„Ì· ›Ì «·ﬁ«∆„…
    if (FindClientByAccountNumber(AccountNumber, vClient, client))
    {
        PrintClientRecordLine(client); // ⁄—÷ »Ì«‰«  «·⁄„Ì· «·Õ«·Ì
        cout << "\nARE YOU SURE YOU WANT TO UPDATE THIS CLIENT? (y/n) ";
        cin >> Answer; // ﬁ—«¡… ≈Ã«»… «·„” Œœ„

        if (toupper(Answer) == 'Y')
        { // ≈–« Ê«›ﬁ «·„” Œœ„ ⁄·Ï «· ÕœÌÀ
            for (sClient& C : vClient)
            { // «·»ÕÀ œ«Œ· «·‹ vector
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber); //  ÕœÌÀ »Ì«‰«  «·⁄„Ì·
                    break;                                 // «·«‰ Â«¡ »⁄œ «·⁄ÀÊ— ⁄·Ï «·⁄„Ì·
                }
            }
            SaveClientDataToFile(ClientFileName, vClient); // Õ›Ÿ «·‰”Œ… «·ÃœÌœ… ›Ì «·„·›
            cout << "\n\n*Client Updated Successfully*\n";
            return true;
        }
        else
        {
            cout << "\nUpdate cancelled.\n";
            return false;
        }
    }
    else
    {
        // ≈–« «·⁄„Ì· €Ì— „ÊÃÊœ
        cout << "\nClient with account number (" << AccountNumber << ") not found.\n";
        return false;
    }
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClient)
{
    char Answer = 'n';
    cout << "\n\n ARE YOU SURE YOU WANT PERFORM THIS TRANSACTION (y/n)?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        for (sClient& c : vClient)
        {
            if (c.AccountNumber == AccountNumber)
            {
                c.AccountBalance += Amount;
                SaveClientDataToFile(ClientFileName, vClient);
                cout << "\n\n DONE SECCESSFULY .\n\t\t NEW BALANCE IS : " << c.AccountBalance;
                return true;
            }

        }
        return false;
    }


}
void  ShowTotalBalance()
{
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    cout << "\n\t\t\tBALANCE LIST (" << vClient.size() << ")Client(s)";
    cout << "\n====================================================================================================\n";
    cout << "| " << left << setw(12) << "ACCOUNT NUMBER ";
    cout << "| " << left << setw(30) << "Client Name ";
    cout << "| " << left << setw(12) << "BALANCE ";
    double TotalBalance = 0;
    if (vClient.size() == 0)
    {
        cout << "\n\t\t NO CLIENT AVAILABLE IN THE SYSTEM ";
    }
    else
    {
        for (sClient Client : vClient)
        {
            printClientRecordBalanceLine(Client);
            TotalBalance += Client.AccountBalance;
            cout << endl;
        }
        cout << "\n===========================================================================================================\n";
        cout << "\n\t\t\t \tTOTAL BALANCE = " << TotalBalance;
    }


}

string ReadClientAccountNumber()
{
    string AccountNumber;
    cout << "\nPLEASE ENTER ACCOUNT NUMBER ? ";
    cin >> AccountNumber;
    return AccountNumber;
}


void ShowDeletClientScreen()
{
    cout << "\n-----------------------------------------\n";
    cout << "\tDelet Client Screen";
    cout << "\n----------------------------------------\n";
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeletClientByAccountNumber(AccountNumber, vClient);
}
void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n----------------------------------------\n";
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClient);
}
void ShowAddNewClientScreen()
{
    cout << "\n-----------------------------------------\n";
    cout << "\tAdd Client Screen";
    cout << "\n----------------------------------------\n";
    AddClients();
}
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n----------------------------------------\n";
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientRecordLine(Client);
    }
    else
    {
        cout << "\n Client with account number [" << AccountNumber << "]is not found!!";
    }
}
void ShowEndScreen()
{
    cout << "\n--------------------------------";
    cout << "\n\t\tProgram End ";
    cout << "\n--------------------------------";
}


void ShowDepositScreen()
{
    cout << "\n==========================================\n";
    cout << "\t Deposit Screen\n";
    cout << "\n==========================================\n";
    sClient Client;
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\n client with account number (" << AccountNumber << ") doesn't exist .\n please enter anuther account number ";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientRecordLine(Client);
    double Amount = 0;
    cout << "\nplease enter Deposit Amount ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClient);
}
void ShowWithDrawScreen()
{
    cout << "\n==========================================\n";
    cout << "\t With Drow Screen\n";
    cout << "\n==========================================\n";
    sClient Clien;
    vector<sClient> vClient = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClient, Clien));
    {
        cout << "\n client with account number (" << AccountNumber << ") doesn't exist .\n please enter anuther account number ";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientRecordLine(Clien);
    double Amount = 0;
    cout << "\n PLEASE ENTER WITHDRAW AMOUNT ";
    cin >> Amount;
    while (Amount > Clien.AccountBalance)
    {
        cout << "\n Amount Exceeds the balance you can withdraw uo to : " << Clien.AccountBalance;
        cout << "\n PLEASE ENTER ANOTHER AMOUNT ";
        cin >> Amount;
    }
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClient);

}
void ShowTotalBalanceScreen()
{
    ShowTotalBalance();
}


void PerfromMainMenueOption(enMainMenueOption MainMinueOption)
{
    switch (MainMinueOption)
    {
    case enMainMenueOption::eListClient:
    {
        system("cls");
        ShowAllClientData();
        CoBackToMainMinue();
        break;
    }

    case enMainMenueOption::eAddNewClient:
    {
        system("cls");
        ShowAddNewClientScreen();
        CoBackToMainMinue();
        break;
    }

    case enMainMenueOption::eDeletClient:
    {
        system("cls");
        ShowDeletClientScreen();
        CoBackToMainMinue();
        break;
    }

    case enMainMenueOption::eUpdateClient:
    {
        system("cls");
        ShowUpdateClientScreen();
        CoBackToMainMinue();
        break;
    }

    case enMainMenueOption::eFindClient:
    {
        system("cls");
        ShowFindClientScreen();
        CoBackToMainMinue();
        break;
    }
    case enMainMenueOption::eTRANSACTION:
    {
        system("cls");
        ShowTransactionMinue();
        break;
    }

    case enMainMenueOption::eExite:
    {
        system("cls");
        ShowEndScreen();
        break;
    }
    }
}
void PerformTransactionMenueOption(enTransactionMenueOption TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionMenueOption::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        CoBackToTransactionMenue();
        break;
    }
    case enTransactionMenueOption::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        CoBackToTransactionMenue();
        break;
    }
    case enTransactionMenueOption::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalanceScreen();
        CoBackToTransactionMenue();
        break;
    }
    case enTransactionMenueOption::eShowMainMinue:
    {
        system("cls");
        ShowMinueScreen();
    }

    }

}
void ShowTransactionMinue()
{
    system("cls");
    cout << "\n================================================\n";
    cout << "\t\tTRANSACTION MENUE SCREEN\n";
    cout << "\n================================================\n";
    cout << "\t[1] DEPOSIT .\n";
    cout << "\t[2] WITHDRAW .\n";
    cout << "\t[3] TOTAL BALANCE .\n";
    cout << "\t[4] MAIN MINUE .\n";
    cout << "\n=================================================\n";
    PerformTransactionMenueOption((enTransactionMenueOption)ReadTransactionMenueOption());
}

void ShowMinueScreen()
{
    system("cls");

    cout << "=========================================================\n";
    cout << "\t\t**MINE MINUE** " << endl;
    cout << "=========================================================\n";
    cout << "\t[1] SHOW CLIENT LEST .\n";
    cout << "\t[2] ADD NEW CLIENT .\n";
    cout << "\t[3] Delet Client .\n";
    cout << "\t[4] UPDATE CLIENT .\n";
    cout << "\t[5] FIND CLIENT .\n";
    cout << "\t[6] TRANSACTION .\n";
    cout << "\t[7] EXIT .\n";

    PerfromMainMenueOption((enMainMenueOption)ReadMainMinueOption());
}
int main()
{
    ShowMinueScreen();
    return 0;
}