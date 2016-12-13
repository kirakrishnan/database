/*
	
Name:    Aravinda Krishnan V
Zid:         z1760288
Section:  CSCI 566-0003
TA:          Robert Durham

*/

#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <mysql.h>

using namespace std;

	MYSQL  *conn,mysql;
	MYSQL_RES *res;  
	MYSQL_ROW row;   
	
	string p1,p2;
	int query_state;
	
void author(){
	cout << "Enter the author name" << endl;
	string input = "";
	cin.ignore();
	getline (cin,input);
	cout << "The books written by "+input+" are:" << endl;
	p1= "select * from Book where Bookcode in (select BookCode from Wrote where AuthorNum=(select AuthorNum from Author where AuthorLast='"+input+"'));";
	query_state=mysql_query(conn,p1.c_str());
	if(query_state !=0)
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	res = mysql_store_result(conn);
	if((row = mysql_fetch_row(res)) == NULL){
		cout << "There are no books written by author "+input << endl;
		return;
	}
	cout << "\tBookCode\tTitle\tpublisher code\tType\tprice \tpaperback" << endl;
	cout << "\t" << row[0] <<"\t" << row[1] <<"\t" << row[2] <<"\t" << row[3] <<"\t" << row[4] <<"\t" << row[5] << endl;
	while ((row = mysql_fetch_row(res)) != NULL){
		cout << "\t" << row[0] <<"\t" << row[1] <<"\t" << row[2] <<"\t" << row[3] <<"\t" << row[4] <<"\t" << row[5] << endl;
	}
	mysql_free_result(res);
}

void publisher(){
	cout << "Enter the publisher name" << endl;
	string input = "";
	cin.ignore();
	getline (cin,input); // >> input;
	cout << "The books published by "+input+" are:" << endl;
	p2= "select * from Book where PublisherCode=(select PublisherCode from Publisher where PublisherName='"+input+"');";
	query_state=mysql_query(conn,p2.c_str());
	if(query_state !=0)
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	res = mysql_store_result(conn);
	if((row = mysql_fetch_row(res)) == NULL){
		cout << "There are no books published by "+input << endl;
		return;
	}
	cout << "\tBookCode\tTitle\tpublisher code\tType\tprice \tpaperback" << endl;
	cout << "\t" << row[0] <<"\t" << row[1] <<"\t" << row[2] <<"\t" << row[3] <<"\t" << row[4] <<"\t" << row[5] << endl;
	while ((row = mysql_fetch_row(res)) != NULL){
		cout << "\t" << row[0] <<"\t" << row[1] <<"\t" << row[2] <<"\t" << row[3] <<"\t" << row[4] <<"\t" << row[5] << endl;
	}
	mysql_free_result(res);
}


int main (int argc, char *argv[])
{
	const char *server="courses";
	const char *user="z1760288";
	const char *password="19920820";
	const char *database="henrybooks";
	int j=0;
	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql, server, user, password, database, 0, 0, 0);
	 // Connect to database
	if (conn == NULL)
	{
		cout << mysql_error(&mysql) << endl;
		exit(1);
	}
	
	while(j != 3)
	{
		cout << "choose one of the options from below:\n";
		cout << " 1) Author name as input\n";
		cout << " 2) Publisher as input\n";
		cout << " 3) To Quit\n";
		cin >> j;
		if(j == 1){
			author();
		}
		else if ( j == 2){
			publisher();
		}
		else if ( j == 3){
			mysql_close(conn);
			exit(0);
		}
	}
 
return 0;
}
