#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "password.h"


using namespace sql;


int main()
{


try{
sql::mysql::MySQL_Driver *driver;
sql::Connection *con;
sql::Statement *statement;
sql::ResultSet *res;
sql::PreparedStatement *prep_stmt;



driver = sql::mysql::get_mysql_driver_instance();
con = driver->connect("tcp://127.0.0.1", "kaan", password);

// database to connect to 
con->setSchema("management_database");


statement = con->createStatement();
// inserting employees table to the database 
statement->execute("CREATE TABLE if not exists employees ( "
 "emp_no      INT UNSIGNED DEFAULT '0000' NOT NULL ,"           
"birth_date  DATE,"
"first_name  VARCHAR(14),"
"last_name   VARCHAR(16),"
 "gender      ENUM ('M','F'),"
"hire_date   DATE,"
"PRIMARY KEY (emp_no)"
");");

delete statement;

statement = con->createStatement();

statement->execute("CREATE TABLE if not exists departments ("
                   "dept_no   CHAR(4),"
                   "dept_name VARCHAR(40)," 
                   "PRIMARY KEY (dept_no),"
                   "UNIQUE KEY (dept_name)"
                   ");"
);

delete statement; 


statement = con->createStatement();

statement->execute("CREATE TABLE if not exists salaries ("
                   "emp_no  INT,"
                   "salary  INT," 
                   "from_date   DATE,"
                   "to_date     DATE,"
                   "KEY     (emp_no),"
                   "FOREIGN KEY (emp_no) REFERENCES employees (emp_no) ON DELETE CASCADE,"
                   "PRIMARY KEY (emp_no, from_date)"
                   ");"                                
);
delete statement; 

statement = con->createStatement();

statement->execute("CREATE TABLE if not exists titles ("
                   "emp_no  INT,"
                   "title VARCHAR(50),"
                   "from_date DATE," 
                   "to_date  DATE,"
                   "KEY (emp_no),"
                   "FOREIGN KEY (emp_no) REFERENCES employees (emp_no) ON DELETE CASCADE,"
                   "PRIMARY KEY (emp_no, title, from_date)"
                   ");"
);

delete statement; 

statement = con->createStatement();

statement->execute("CREATE TABLE if not exists dept_emp ("
                   "emp_no  INT,"
                   "dept_no CHAR(4),"
                   "from_date DATE,"
                   "to_date  DATE,"
                   "KEY (emp_no),"
                   "KEY (dept_no),"
                   "FOREIGN KEY (emp_no) REFERENCES employees (emp_no) ON DELETE CASCADE,"
                   "PRIMARY KEY  (emp_no, from_date)"
                    ");"
);

delete statement; 

statement = con->createStatement();

statement->execute(
  "CREATE TABLE if not exists dept_manager(" 
  "dept_no   CHAR(4),"
   "emp_no       INT,"
   "from_date    DATE,"
   "to_date      DATE,"
   "KEY         (emp_no),"
   "KEY         (dept_no),"
   "FOREIGN KEY (emp_no)  REFERENCES employees (emp_no)    ON DELETE CASCADE,"
   "FOREIGN KEY (dept_no) REFERENCES departments (dept_no) ON DELETE CASCADE,"
   "PRIMARY KEY (emp_no, dept_no)"
  ");"
);


delete statement; 


statement = con->createStatement();




// insertion 
statement->execute("INSERT IGNORE INTO  employees (emp_no, birth_date, first_name, last_name, gender, hire_date)"
                                  "VALUES(1, '1995-01-24', 'kaan', 'karaalioglu', 'M', '2023-06-17');"
);


statement->execute("INSERT IGNORE INTO employees (emp_no, birth_date, first_name, last_name, gender, hire_date)"
                                  "VALUES(2, '1999-07-15', 'nisa', 'karaalioglu', 'F', '2022-06-17')"); 


statement->execute("INSERT IGNORE INTO employees (emp_no, birth_date, first_name, last_name, gender, hire_date)"
                                  "VALUES(3, '1965-07-15', 'John', 'Doe', 'M', '2021-03-17')"); 

statement->execute("INSERT IGNORE INTO employees (emp_no, birth_date, first_name, last_name, gender, hire_date)"
                                  "VALUES(4, '1969-07-15', 'Haylee', 'Arnold', 'F', '2020-03-17')"); 


// inserting into departments 
statement->execute("INSERT IGNORE INTO departments (dept_no, dept_name)"
                                  "VALUES('0001', 'London')");


statement->execute("INSERT IGNORE INTO departments (dept_no, dept_name)" //--------------------------------------->INSERT
                                  "VALUES('0002', 'New York')");

statement->execute("INSERT IGNORE INTO departments (dept_no, dept_name)"
                                  "VALUES('0003', 'Beijing')");

statement->execute("INSERT IGNORE INTO departments (dept_no, dept_name)"
                                  "VALUES('0004', 'Tokyo')");


///*


//// insert into salaries 
//// by intention, i made a mistake inserting a data in table 

//statement->execute("INSERT IGNORE INTO salaries (emp_no, salary, from_date, to_date)"
                                  //"VALUES(1, 5000, '17-06-2023', '17-06-2023')");
///*
//// with update statement, we can correct the dates 
//statement->execute("UPDATE salaries " ---------------------------------------------------->UPDATE
                   //"SET "
                   //"from_date = '2023-06-17', "
                   //"to_date = '2023-07-17' "
                   //"WHERE "
                   //"emp_no = 1;"
//);
//*/ 

///*
//statement->execute("DELETE FROM salaries " ----------------------------------------------> DELETE 
                   //"WHERE "
                   //"emp_no = 1 AND salary = 5000;"
//);
//*/

statement->execute("INSERT IGNORE INTO salaries (emp_no, salary, from_date, to_date)"
                                  "VALUES(1, 5000, '2023-06-17', '2023-07-17')");



statement->execute("INSERT IGNORE INTO salaries (emp_no, salary, from_date, to_date)"
                                  "VALUES(2, 7000, '2023-06-17', '2023-07-17')");

statement->execute("INSERT IGNORE INTO salaries (emp_no, salary, from_date, to_date)"
                                  "VALUES(3, 9000, '2023-06-17', '2023-07-17')");


statement->execute("INSERT IGNORE INTO salaries (emp_no, salary, from_date, to_date)"
                                  "VALUES(4, 11000, '2023-06-17', '2023-07-17')");



statement->execute("INSERT IGNORE INTO titles (emp_no, title, from_date, to_date)"
                                  "VALUES(1, 'software engineer', '2023-06-17', CURDATE())");

statement->execute("INSERT IGNORE INTO titles (emp_no, title, from_date, to_date)"
                                  "VALUES(2, 'Project Manager', '2022-06-17', CURDATE())");

statement->execute("INSERT IGNORE INTO titles (emp_no, title, from_date, to_date)"
                                  "VALUES(3, 'CEO', '2021-03-17', CURDATE())");

statement->execute("INSERT IGNORE INTO titles (emp_no, title, from_date, to_date)"
                                  "VALUES(4, 'Founder', '2020-03-17', CURDATE())");


res = statement->executeQuery("SELECT * FROM employees");


while(res->next()) // -------------------------------------------------------->>> SELECTION 
{
  int id = res->getInt("emp_no"); 
  std::string birth_date = res->getString("birth_date");
  std::string first_name  = res->getString("first_name");
  std::string last_name  = res->getString("last_name");
  std::string gender = res->getString("gender");
  std::string hire_date = res->getString("hire_date");

  std::cout << id << " " << birth_date << " " << first_name << " " << last_name << " " << gender << " " << hire_date << std::endl; 


}

delete statement; 

}
catch(sql::SQLException &e)
{
 std::cout << "# ERR: SQLException in " << __FILE__;
std::cout << "(" << __FUNCTION__ << ") on line " \
     << __LINE__ << std::endl;
  std::cout << "# ERR: " << e.what();
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() << \
     " )" << std::endl;
}

return 0;

}