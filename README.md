
# Binary Files Based SQL database

## Description: 
- This is an simplify version of an SQL database with the abiltiy to add, search, and filter data using a binary files
- Does not include the ability to remove data - will have to implement it in the future

## Allowed Commands:
- It is easier to have some examples command and explains them than listing them out
  - "make table employee fields last, first, dep, salary, year"
    - This create the database for employees that have fields of last, first name, the department, salary, and year they joined the company
    - Keywords "make table" is require to start creating the database 
    - employee in this case is the database name, and words after the fields keyword are the different information that each data will have
  - "insert into employee values Blow, Joe, CS, 100000, 2018"
    - This is used to insert datas into the employee database
    - It important to have the keywords "insert into" or else the commands will not work properly
    - This will insert an employee name Joe Blow in the CS department that joined in 2018 with a salary of 100,000
  - "select * from employee"
    - The "select" keyword will retrieve the data from the database
    - Select * will retrieve every data from the indicated database using the keywords "from" followed by the database name
  - "select last, first, age from employee"
    - This is used to retrieve fields last, first, and age from the employee database
    - It'll will retrieve all the datas but will only show the three fields indicated
  - "select * from student where (major=CS or major=Art)"
    - This is used to retrieve all data and all fields where students have their major = CS or major = Art
    - "where" keywords is used to indicate that you are filtering the data using the fields and the value associated in that fields
    - all available keywords for filtering is:
      - "or": used to filter data between one conditions or another
      - "and": used to filter data where the information has to match both conditions
      - "=": used to filter if any data containings fields equal to a certain value
      - ">, <, <=, >=": used to filter any data in a specific fields is greater than/less than a certain value
      - parenthesis is used to extent the conditions and it should work like a normal parenthesis



# Reflections:

- Any thoughts you may have and would like to share.

# **Example Output**
<pre>
<br/><br/><br/><br/>
  >make table employee fields  last,       first,         dep,      salary, year
basic_test: table created.

>make table employee fields  last,       first,         dep,      salary, year
>insert into employee values Blow,       Joe,           CS,       100000, 2018
>insert into employee values Blow,       JoAnn,         Physics,  200000, 2016
>insert into employee values Johnson,    Jack,          HR,       150000, 2014
>insert into employee values Johnson,    "Jimmy",     Chemistry,140000, 2018
>make table student fields  fname,          lname,    major,    age
>insert into student values Flo,            Yao,        Art,    20
>insert into student values Bo,                      Yang,      CS,             28
>insert into student values "Sammuel L.", Jackson,      CS,             40
>insert into student values "Billy",         Jackson,   Math,   27
>insert into student values "Mary Ann",   Davis,        Math,   30



>select * from employee
basic_test: records selected: |0| |1| |2| |3| 

table:
Table name: sample, records: 4
record     last       first         dep      salary        year
     0        Blow         Joe          CS      100000        2018
     1        Blow       JoAnn     Physics      200000        2016
     2     Johnson        Jack          HR      150000        2014
     3     Johnson       Jimmy   Chemistry      140000        2018


>select last, first, age from employee
basic_test: records selected: |0| |1| |2| |3| 

table:
Table name: temp, records: 4
record     last       first         age
     0        Blow         Joe        Blow
     1        Blow       JoAnn        Blow
     2     Johnson        Jack     Johnson
     3     Johnson       Jimmy     Johnson


>select last from employee
basic_test: records selected: |0| |1| |2| |3| 

table:
Table name: temp, records: 4
record     last
     0        Blow
     1        Blow
     2     Johnson
     3     Johnson


>select * from employee where last = Johnson
basic_test: records selected: |2| |3| 

table:
Table name: temp, records: 2
record     last       first         dep      salary        year
     0     Johnson        Jack          HR      150000        2014
     1     Johnson       Jimmy   Chemistry      140000        2018


>select * from employee where last=Blow and major="JoAnn"
basic_test: records selected:

table:
Table name: temp, records: 0
record     last       first         dep      salary        year


>select * from student
basic_test: records selected: |0| |1| |2| |3| |4| 

table:
Table name: sample, records: 5
record    fname       lname       major         age
     0         Flo         Yao         Art          20
     1          Bo        Yang          CS          28
     2  Sammuel L.     Jackson          CS          40
     3       Billy     Jackson        Math          27
     4    Mary Ann       Davis        Math          30


>select * from student where (major=CS or major=Art)
basic_test: records selected: |0| |1| |2| 

table:
Table name: temp, records: 3
record    fname       lname       major         age
     0         Flo         Yao         Art          20
     1          Bo        Yang          CS          28
     2  Sammuel L.     Jackson          CS          40


>select * from student where lname>J
basic_test: records selected: |0| |1| |2| |3| 

table:
Table name: temp, records: 4
record    fname       lname       major         age
     0         Flo         Yao         Art          20
     1          Bo        Yang          CS          28
     2  Sammuel L.     Jackson          CS          40
     3       Billy     Jackson        Math          27


>select * from student where lname>J and (major=CS or major=Art)
basic_test: records selected: |0| |1| |2| 

table:
Table name: temp, records: 3
record    fname       lname       major         age
     0         Flo         Yao         Art          20
     1          Bo        Yang          CS          28
     2  Sammuel L.     Jackson          CS          40


>select * from student where fname = Flo and lname = Yao or major = CS
basic_test: records selected: |0| |1| |2| 

table:
Table name: temp, records: 3
record    fname       lname       major         age
     0         Flo         Yao         Art          20
     1          Bo        Yang          CS          28
     2  Sammuel L.     Jackson          CS          40

----- END TEST --------
****************************************************************************

                CREATE AND INSERT

****************************************************************************

---- employee table ----------

[0] make table employee fields  last,           first,                  dep
[1] insert into employee values Blow,           Joe,                    CS
[2] insert into employee values Johnson,        "Jimmy",                Chemistry
[3] insert into employee values Yang,           Bo,                     CS
[4] insert into employee values "Jackson",      Billy,                  Math
[5] insert into employee values Johnson,        Billy,                  "Phys Ed"
[6] insert into employee values "Van Gogh",     "Jim Bob",              "Phys Ed"
[7] select * from employee
Table name: sample, records: 6
record     last       first         dep
     0        Blow         Joe          CS
     1     Johnson       Jimmy   Chemistry
     2        Yang          Bo          CS
     3     Jackson       Billy        Math
     4     Johnson       Billy     Phys Ed
     5    Van Gogh     Jim Bob     Phys Ed

----- student table ----------

[8] make table student fields   fname,                  lname,          major,                          age
[9] insert into student values  Flo,                    Yao,            CS,                             20
[10] insert into student values         "Flo",                  "Jackson",      Math,                           21
[11] insert into student values         Calvin,                 Woo,            Physics,                        22
[12] insert into student values         "Anna Grace",   "Del Rio",      CS,                                     22
[13] select * from student
Table name: sample, records: 4
record    fname       lname       major         age
     0         Flo         Yao          CS          20
     1         Flo     Jackson        Math          21
     2      Calvin         Woo     Physics          22
     3  Anna Grace     Del Rio          CS          22

****************************************************************************

                SIMPLE SELECT 

****************************************************************************

[14] select * from student
Table name: sample, records: 4
record    fname       lname       major         age
     0         Flo         Yao          CS          20
     1         Flo     Jackson        Math          21
     2      Calvin         Woo     Physics          22
     3  Anna Grace     Del Rio          CS          22

------- simple strings -------------------

[15] select * from student where lname = Jackson
Table name: temp, records: 1
record    fname       lname       major         age
     0         Flo     Jackson        Math          21

----- quoted strings ---------------------

[16] select * from student where lname = "Del Rio"
Table name: temp, records: 1
record    fname       lname       major         age
     0  Anna Grace     Del Rio          CS          22

-------- non-existing string ------------------

[17] select * from student where lname = "Does Not Exist"
Table name: temp, records: 0
record    fname       lname       major         age

****************************************************************************

                RELATIONAL OPERATORS:

****************************************************************************

.................

:Greater Than   :

.................

[18] select * from student where lname > Yang
Table name: temp, records: 1
record    fname       lname       major         age
     0         Flo         Yao          CS          20

. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .

[19] select * from student where age > 50
Table name: temp, records: 0
record    fname       lname       major         age

. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .

[20] select * from student where age  > 53
Table name: temp, records: 0
record    fname       lname       major         age

. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .

[21] select * from student where age > 54
Table name: temp, records: 0
record    fname       lname       major         age

.................

:Greater Equal  :

.................

[22] select * from student where lname >= Yang
Table name: temp, records: 1
record    fname       lname       major         age
     0         Flo         Yao          CS          20

. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .

[23] select * from employee where last >= Jack
Table name: temp, records: 5
record     last       first         dep
     0     Johnson       Jimmy   Chemistry
     1        Yang          Bo          CS
     2     Jackson       Billy        Math
     3     Johnson       Billy     Phys Ed
     4    Van Gogh     Jim Bob     Phys Ed

.................

:Less Than      :

.................

. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .

[24] select * from student where lname < Jackson
Table name: temp, records: 1
record    fname       lname       major         age
     0  Anna Grace     Del Rio          CS          22

. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .

[25] select * from student where age  < 20
Table name: temp, records: 0
record    fname       lname       major         age

. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[26] select * from student where age  < 19
Table name: temp, records: 0
record    fname       lname       major         age

.................

:Less Equal     :

.................

[27] select * from student where lname <= Smith
Table name: temp, records: 2
record    fname       lname       major         age
     0         Flo     Jackson        Math          21
     1  Anna Grace     Del Rio          CS          22

. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .

[28] select * from employee where last <= Peach
Table name: temp, records: 4
record     last       first         dep
     0        Blow         Joe          CS
     1     Johnson       Jimmy   Chemistry
     2     Jackson       Billy        Math
     3     Johnson       Billy     Phys Ed

****************************************************************************

                LOGICAL OPERATORS

****************************************************************************

.................

:AND            :

.................

[29] select * from student where fname = "Flo" and lname = "Yao"
Table name: temp, records: 1
record    fname       lname       major         age
     0         Flo         Yao          CS          20

.................

:OR            :

.................

[30] select * from student where fname = Flo or lname = Jackson
Table name: temp, records: 2
record    fname       lname       major         age
     0         Flo         Yao          CS          20
     1         Flo     Jackson        Math          21

.................

:OR AND         :

.................

[31] select * from student where fname = Flo or major = CS and age <= 23
Table name: temp, records: 3
record    fname       lname       major         age
     0         Flo         Yao          CS          20
     1         Flo     Jackson        Math          21
     2  Anna Grace     Del Rio          CS          22

.................

:AND OR AND     :

.................

[32] select * from student where age <30 and major=CS or major = Physics and lname = Jackson
Table name: temp, records: 2
record    fname       lname       major         age
     0         Flo         Yao          CS          20
     1  Anna Grace     Del Rio          CS          22

.................

:OR AND OR      :

.................

[33] select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson
Table name: temp, records: 3
record    fname       lname       major         age
     0         Flo         Yao          CS          20
     1         Flo     Jackson        Math          21
     2  Anna Grace     Del Rio          CS          22

SQL: DONE
</pre>


