#include "split_service.h"
#include<fstream>
#include <sstream>

int main()
{
   SplitService *ser = new SplitService(4);

   User *U1 = new User(0, "u1", "Susmita", "sm@com", "11890");
   ser->set_user_table("u1", U1);

   User *U2 = new User(1, "u2", "Ayan", "ay@com", "11890");
   ser->set_user_table("u2", U2);

   User *U3 = new User(2, "u3", "Moumita", "mm@com", "11890");
   ser->set_user_table("u3", U3);

   User *U4 = new User(3, "u4", "Subhayan", "sb@com", "11890");
   ser->set_user_table("u4", U4);

   fstream input;
   input.open("input.txt");

   string line;
   while (getline(input, line))
   {
      stringstream s(line);
      string c;
      s >> c;
      if (c == "SHOW")
        {
           string show_arg;
           s >> show_arg;
           if (show_arg == "")
             {
                ser->SHOW_ALL();
             }
           else
             {
                ser->SHOW(show_arg, 0);
             }
        }
      else if (c == "EXPENSE")
        {
           int num = 0;
           string payer;
           vector <string> users;
           string type;
           int total;
           s >> payer;
           s >> total;
           s >> num;
           for (int i = 0; i < num; i++)
           {
              string u;
              s >> u;
              users.push_back(u);
           }
           s >> type;
           if (type == "EQUAL")
           {
              ser->EXPENSE_EQUAL(total, payer, users);
           }
           else if (type == "EXACT")
           {
              vector <int> amounts;
              for (int i = 0; i<num; i++)
              {
                 int amount;
                 s >> amount;
                 amounts.push_back(amount);
              }
              ser->EXPENSE_EXACT(total, payer, users, amounts);
           }
           else if (type == "PERCENT")
           {
              vector <float> percents;
              for (int i = 0; i<num; i++)
              {
                 float percent;
                 s >> percent;
                 percents.push_back(percent);
              }
              ser->EXPENSE_PERCENT(total, payer, users, percents);
           }
           else
             cout << "INVALID TYPE" << endl;
        }
      else
        {
           cout << "INVALID OPERTAION " << endl;
        }
   }

   input.close();
   return 0;
}
