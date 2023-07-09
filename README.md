## MySQL C++ connector LAB assignment

To be able to compile the code and execute the commands, there has to be
a connection with the localhost using a local password.

1- Change the file password.h with your own password to be able to connect to the database.

2- Change the username with yours, if you don't have a local username set. Set it with the following commands after 
   connecting to your database locally

```
sudo mysql or mysql -u root -p
CREATE USER 'the_name_you_want_for_your_user'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON * . * TO 'your_preffered_user_name'@'%%'; 


```

3 - and create a database with 

```
CREATE DATABASE management_database; 

```


4 - Download the required packages with
```
sudo apt-get install libmysqlcppconn-dev
```


5 - Create an executable and run it with 
```
g++ -Wall -I/usr/include/cppconn -o connector_ex connector.cpp -L/user/lib -lmysqlcppconn

./connector_ex

```

    
Since it's a small project, I have not used CMake and advanced version control system tools for the assignment. 
    



