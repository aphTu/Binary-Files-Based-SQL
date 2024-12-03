#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/table/table.h"
#include "../../includes/sql/sql.h"
using namespace std;
const vector<string> command_list = {

// /*00*/     "make table employee fields  last,       first,         dep,      salary, year",
// /*01*/     "insert into employee values Blow,       Joe,           CS,       100000, 2018",
// /*02*/     "insert into employee values Blow,       JoAnn,         Physics,  200000, 2016",
// /*03*/     "insert into employee values Johnson,    Jack,          HR,       150000, 2014",
// /*04*/     "insert into employee values Johnson,    \"Jimmy\",     Chemistry,140000, 2018",

/*05*/     "make table student fields  fname,          lname,    major,    age",
/*06*/     "insert into student values Flo,            Yao, 	Art, 	20",
/*07*/     "insert into student values Bo, 		     Yang, 	CS, 		28",
/*08*/     "insert into student values \"Sammuel L.\", Jackson, 	CS, 		40",
/*09*/     "insert into student values \"Billy\",	     Jackson, 	Math,	27",
/*10*/     "insert into student values \"Mary Ann\",   Davis,	Math,	30",
/*10*/     "insert into student values \"Mary Ann\",   Davi,	Math,	30",
/*10*/     "insert into student values \"Mary Ann\",   Da,	Math,	30",
            "insert into student values Johnson, \"Mary Ann\", \"Biology\"",
// /*11*/     "select * from employee",
// /*12*/     "select last, first, age from employee",
// /*13*/     "select last from employee",
// /*14*/     "select first from employee where year <= 2016 and dep = Physics and first = JoAnn and last = Blow and salary > 20000",
// /*15*/     "select * from employee where last=Blow and major=\"JoAnn\"",

/*16*/     "select * from student",

// // lower bound test
// /*17*/     "select * from student where (age <  20)",
// /*20*/     "select * from student where age < 25",
// /*20*/     "select * from student where age < 27",
// /*20*/     "select * from student where age < 30",
// /*20*/     "select * from student where age < 40",
// /*20*/     "select * from student where age < 0",

// /*20*/     "select * from student where age >= 20",
// /*20*/     "select * from student where age >= 25",
// /*20*/     "select * from student where age >= 27",
// /*20*/     "select * from student where age >= 30",
// /*20*/     "select * from student where age >= 40",
// /*20*/     "select * from student where age >= 70",

// //upper bound test
// /*17*/     "select * from student where (age > 20)",
// /*20*/     "select * from student where age > 25",
// /*20*/     "select * from student where age > 27",
// /*20*/     "select * from student where age > 30",
// /*20*/     "select * from student where age > 40",
// /*20*/     "select * from student where age > 60",

// /*20*/     "select * from student where age <= 20",
// /*20*/     "select * from student where age <= 25",
// /*20*/     "select * from student where age <= 27",
// /*20*/     "select * from student where age <= 30",
// /*20*/     "select * from student where age <= 40",
// /*20*/     "select * from student where age <= 80",


// /*18*/     "select * from student where (fname = \"Sammuel L.\" and fname = Billy) or (major = CS and major = Math) or age = 27",
// /*19*/     "select * from student where lname>J and (major=CS or major=Art)",
// /*20*/     "select * from student where age < 29",
// /*20*/     "select * from student where age >= 29",

/*21*/ "select * from student where (fname) = Billy and (age >= 20 or age < 40) or (lname = Davis and major = Math)",

"select * from student where ((fname = Billy or major = Math) and major = Art) and fname = Flo",

"select * from student where (fname = Billy and (lname = Jackson or major = CS) or major = Art and age = 20)"
};

const int MAKE_TABLE_COMMANDS = 11;
const int SELECT_COMMANDS = 20;
bool test_stub(bool debug = false)
{


  
 if (debug){

    // SQL sql;
    //  Table t;
    //  cout << ">" << command_list[0] << endl;
    //  sql.command(command_list[0]);
    //  cout << "basic_test: table created." << endl<<endl;

    //  for (int i = 0; i < command_list.size(); i++)
    //  {
    //       cout << ">" << command_list[i] << endl;
    //       cout<< "here is yo table \n" << sql.command(command_list[i]);
    //       cout << "basic_test: records selected: "<<sql.select_recnos() << endl;

    //  }
   vector<string> cmds = {
        "select * from student where major = CS or major = Art or fname = Flo and lname = Yao",
        "select * from student where (fname=Flo)",
        "select * from student where fname = Flo or (major > Art and lname < Z)",
        "select * from student where (fname = Flo) or (lname < Z)",
        "select * from student where (fname = Flo and lname = Yao or major = CS)",
        "select * from student where (fname = Flo and (lname = Yao or major = CS))",
        "select * from student where (fname = Flo and (lname <= Yao and (major = Art or age > 20)))",
        "select * from student where fname = Flo and lname = Yao",
        "select * from student where fname = Flo or (lname = Yao or major = CS)",
        "select * from student where (fname = Flo or lname = Yao) and major = CS",
        "select * from student where (fname = Flo or lname = Yao) and (major = CS or major = Art)",
        "select * from student where (fname = Flo or (lname = Yao and (major = CS or major = Art)))",
        "select * from student where fname = Flo or (lname = Yao and (major = CS or major = Art))",
        "select * from student where (fname = Flo and (lname = Yao or major = CS or major = Art))",
        "select * from student where (fname = Flo and lname = Yao or major = CS or major = Art)",
        "select * from student where (fname = Flo and lname = Yao)",
        "select * from student where (fname = Flo and (lname = Yao or major = CS))",
        "select * from student where (fname = Flo and (lname = Yao or lname = Jackson) or major = CS and age <= 30)",
        "select * from student where ((fname = Flo and lname = Yao) or lname = Jackson) or major = CS and age <= 30",
        "select * from student where (fname = Flo or (lname = Yao and (major = CS or major = Art)) or lname = Jackson)",
    };

    SQL sql;
    Table t;

    cout << endl
        << endl;
    for (int i = 0; i < cmds.size(); i++)
    {
        cout << "\n>" << cmds[i] << endl;
        if (debug)
            cout << sql.command(cmds[i]) << endl;
        else
            t = sql.command(cmds[i]);
        cout << "basic_test: records selected: " << sql.select_recnos() << endl;
    }

  }

// if (debug){
//     cout << "testB:: test-sql_interactive() entering test_sql_interactive" << endl;
//   }
//   SQL sql;
//   Table t;
//   char s[300];
//   // string s_str = s;
//   string s_str;
//   while(true)
//   {
//     cout<<">";
//     getline(cin, s_str);
//     // cout<<"s_str: "<<s_str<<"\n";
//     strcpy(s, s_str.c_str());
//     // cout<<"after strcpy s: "<<s;
//     //if bored write a tolower for string
//     if(s_str == "exit")
//       break;
//     Table temp = sql.command(s_str);
//     // if(sql.error_state())
//       // cout<<"sql is in error_state\n";
//     // else
//     // if(!sql.error_state())
//     // {
//     //   cout<<temp;
//     //   if(!temp.get_tablenames_table())
//     //     cout << "records selected from old table: "<<sql.select_recnos() << endl;
//     // }
//   }
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(true));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

