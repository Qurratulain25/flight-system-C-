#include<conio.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<unistd.h>
#include<time.h>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#include"payment.h"
#include<stdio.h>

using namespace std;
bool IsloggedIn()
{
	string cnic,password,id,pass;
	int ch;
	cout<<"Enter cnic:";
	cin>>cnic;
	cout<<"Enter Password:";
	ch = getch();
	while(ch!=13)
		{
		password.push_back(ch);
		cout<<"*";
		ch = getch();
		}
	cout<<endl;
	
	ifstream read("Passenger.txt");
	
	//getline(read,id);
	//getline(read,pass);
	
	while(read.eof())
	{
	if(id==cnic && pass==password)
	
		return true;
	
	else
	
		return false;
		
	}
	
}
const char l_destination[5][20]={"LAHORE","ISLAMABAD","KARACHI","PESHAWAR","QUETTA"};	//local Destination
const char i_destination[11][20]={"LONDON","BERLIN","DUBAI","RIYADH","BEIJING","PARIS","CANBERRA","TOKYO","WASHINGTON","DELHI","ISLAMABAD" }; //International Destination

class Passenger
{
	private:
		const int bseats;
		const int eseats;
	protected:
		string firstname,lastname, phone, mealtype, passport, Cnic;
		int bus, eco, datedep, payment;
		char origin[30];
		char destination[30];
	public:		
		Passenger(string f_name, string l_name, string phone_no, string cnic, string pass_no="N/A", int dd=000000): bseats(10), eseats(50)
		{
			datedep=dd;
			firstname=f_name;
			lastname=l_name;
			Cnic=cnic;
			phone=phone_no;
			passport=pass_no;
			bus = bseats;
			eco = eseats;
		}
		
		virtual bool ldest()=0;
		virtual bool idest(string pass)=0;
		virtual void seats()=0;
	//	virtual void select_flight()=0;
	//	virtual void Meals()=0;
		virtual void Registration()=0;
		virtual bool display()=0;
	//	virtual void drive()=0;	
};

class Booking : public Passenger
{
	protected:
		int i,j,n,m,k,NoOfSeats,choice;
	public:
		
		Booking(string f,string l,string num,string cnic,string pass,int dd):Passenger(f,l,cnic,num,pass,dd)
		{
			n=0;
			m=0;
		}
		
	bool ldest()
	{
		
		cout<<endl<<"These are the local destinations where we are flying: \n";
		for(i=0;i<5;i++)
		{
			for(j=0;j<20;j++)
			{
				cout<<l_destination[i][j];
			}
			cout<<"\n";
		}

		again:
		cout<<endl<<"Enter your origin(using BLOCK letters): ";
		cin>>origin;
		cout<<endl<<"Enter your destination(using BLOCK letters): ";
		cin>>destination;
		if(strcmp(origin,destination)==0)
		{
			cout<<"Invalid Origin and Destination Enter again\n";
			goto again;
		}
		else
		{
			for(i=0;i<5;i++)
			{
				if(strcmp(l_destination[i],origin)==0)
					n++;
			}
			for(j=0;j<5;j++)
			{
				if(strcmp(l_destination[j],destination)==0)
					m++;
			}
			if(m==1&&n==1)
			{
				payment = lpayment(origin, destination);
				cout<<endl<<"Price: "<<payment<<" Pkr/seat + 5% TAX"<<endl;
				return true;
			}
			else 
				return false;
			
		}
	}
	
		bool idest(string pass)
	{
		passport = pass;
		cout<<endl<<"These are the international destinations where we are flying: \n";
		for(i=0;i<11;i++)
		{
			for(j=0;j<20;j++)
			{
				cout<<i_destination[i][j];
			}
			cout<<"\n";
		}
		again:
		cout<<endl<<"Enter your origin(using BLOCK letters): ";
		cin>>origin;
		cout<<endl<<"Enter your destination(using BLOCK letters): ";
		cin>>destination;
		if(strcmp(origin,destination)==0)
		{
			cout<<"Invalid Origin and Destination Enter again\n";
			goto again;
		}
		else
		{
			for(i=0;i<11;i++)
			{
				if(strcmp(i_destination[i],origin)==0)
					n++;
			}
			for(j=0;j<11;j++)
			{
				if(strcmp(i_destination[j],destination)==0)
					m++;
			}
			if(m==1&&n==1)
			{
				payment = ipayment(origin, destination);
				cout<<endl<<"Price: "<<payment<<" Pkr/seat + 10% TAX"<<endl;
				return true;
			}
			else 
				return false;
		}
	}

		
		void seats()
		{
			bus_eco:
				if(bus>0&&eco>0)
				{
					cout<<endl<<"1.Business Class\n2.Economy Class\n";
					k = getch();
					switch(k)
					{
						case 49:
						{
							cout<<endl<<"Business Class";
							cout<<endl<<"Enter the number of seats: ";
							cin>>NoOfSeats;
							payment=(payment*NoOfSeats);
							if(NoOfSeats<=bus)
							{
								cout<<endl<<"Seats are available.\n\n";
								bus=bus-NoOfSeats;
							}
							else
							{
								cout<<endl<<"Seats are not available.\n\n";
								cout<<"we have only "<<bus<<" seats available.\n"<<endl;
								cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
								k = getch();
								if(k==49)
								{
									NoOfSeats = bus;
									payment=(payment*NoOfSeats);
								 	cout<<"Seats are booked\n\n";
								 	bus=0;
								}
								else
								{
									cout<<endl<<"See you again.\n";
									exit(0);
								}
							}
							break;
						}
						
					case 50:
						{
							cout<<endl<<"Economy Class";
							cout<<endl<<"Enter the number of seats: ";
							cin>>NoOfSeats;
							payment=(payment*NoOfSeats);
							if(NoOfSeats<=eco)
							{
								cout<<endl<<"Seats are available.\n\n";
								eco=eco-NoOfSeats;
							}
							else
							{
								cout<<endl<<"Seats are not available.\n\n";
								cout<<"we have only "<<eco<<" seats available.\n"<<endl;
								cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
								k = getch();
								if(k==49)
								{
									NoOfSeats = eco;
									payment=(payment*NoOfSeats);
									cout<<endl<<"Seats are booked\n\n";
									eco=0;
								}
								else
								{
									cout<<endl<<"See you again.\n";
									exit(0);
								}
							}
							break;
						}
					
					default:
						{
							cout<<"Error!\n";
							goto bus_eco;
						}
				}
			}
			else
			{
				cout<<endl<<"Sorry no seats available\nHave a nice day!";
				exit(0);
			}
		}
		void Registration()
		{
			int tkt;
			srand (time(NULL));
			tkt = rand()%1000;
			if(k==49)
			{
				ofstream outfile;
				outfile.open("flight.txt");
				outfile<<"|TICKET INFORMATION:"<<endl<<endl
				<<"Name: "<<firstname<<" "<<lastname<<endl
				<<"Phone: "<<Cnic<<endl
				<<"CNIC: "<<phone<<endl
				<<"Passport Number: "<<passport<<endl
				<<"Origin: "<<origin
				<<endl<<"Destination: "<<destination
				<<endl<<"Number of Seats: "<<NoOfSeats
				<<endl<<"Class: Business"
				<<endl<<"Date of departure: "<<datedep
				<<endl<<"Time: 4.00 PM"
				<<endl<<"Ticket: HF"<<tkt
				<<endl<<"Bill(in pakistani rupees): "<<payment<<"/-"<<endl;				
				outfile.close();
			}
			else if(k==50)
			{
				ofstream outfile;
				outfile.open("flight.txt");
				outfile<<"|TICKET INFORMATION:"<<endl<<endl
				<<"Name: "<<firstname<<" "<<lastname<<endl
				<<"Phone: "<<Cnic<<endl
				<<"CNIC: "<<phone<<endl
				<<"Passport Number: "<<passport<<endl
				<<"Origin: "<<origin
				<<endl<<"Destination: "<<destination
				<<endl<<"Number of Seats: "<<NoOfSeats
				<<endl<<"Class: Economy"
				<<endl<<"Date of departure: "<<datedep
				<<endl<<"Time: 4.00 PM"
				<<endl<<"Ticket: HF"<<tkt
				<<endl<<"Bill(in pakistani rupees): "<<payment<<"/-"<<endl;
				outfile.close();
			}
		} 
		
		bool display()
		{
			bool ans;
			system("cls");
			string temp;
			ifstream infile;
			infile.open("flight.txt");
			while(!infile.eof())
			{
				getline(infile,temp);
				cout<<temp<<endl;
			}
			ans = confirm();
			return ans;
		}
		
		bool confirm()
		{
			char ch;
			confirm:
			cout<<endl<<endl<<"Do you wish to confirm your ticket?(y/n): ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl<<"|STATUS CONFIRMED";
				ofstream outfile;
				outfile.open("flight.txt",ios::app);
				outfile<<endl<<"|STATUS CONFIRMED";
				outfile.close();
				return true;
			}
			else if(ch=='N'||ch=='n')
			{
				ofstream outfile;
				outfile.open("flight.txt",ios::app);
				outfile<<endl<<"|BOOKING CANCELLED";
				cout<<endl<<endl<<"|BOOKING CANCELLED"
				<<endl<<"Going back to main page";
				sleep(3);
				outfile.close();
				return false;
			}
			else
			{
				cout<<endl<<"ERROR!!!";
				goto confirm;
			}
		}
};
class flightSchedule
{
	protected:
		
		char ch, f_i[10],tojai[7],tojdi[7];
	public:
		int flight()
		{
			int src,dest;
        cout << "1.LAHORE(1) \t2.ISLAMABAD(2) \t3.KARACHI(3) \t4.PESHAWAR(4) \t5.QUETTA(5)" << endl << endl;
        cout << "\tEnter Source" << endl;
        cin >> src;
        cout << "\tEnter destination" << endl;
        cin >> dest;
        if((src==1 && dest==2) || (src==2 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t7:45\t\t9:25\t\tPKR20000\tRefundable\t1h 40m\n";
            cout << "2.Falcon(2)\t11:25\t\t01:45\t\tPKR20000\tRefundable\t1h 40m\n";
            cout << "3.Jet Speed(3)\t03:45\t\t05:25\t\tPKR20000\tRefundable\t1h 40m\n";
        }

        else if((src==1 && dest==3) || (src==3 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:40\t\tPKR18000\tRefundable\t1h 40m\n";
            cout << "2.Falcon(2)\t11:40\t\t01:00\t\tPKR18000\tRefundable\t1h 40m\n";
            cout << "3.Jet Speed(3)\t03:00\t\t4:40\t\tPKR18000\tRefundable\t1h 40m\n";
        }

        else if((src==1 && dest==4) || (src==4 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:15\t\tPKR10000\tRefundable\t1h 15m\n";
            cout << "2.Falcon(2)\t11:15\t\t12:30\t\tPKR10000\tRefundable\t1h 15m\n";
            cout << "3.Jet Speed(3)\t02:30\t\t03:45\t\tPKR10000\tRefundable\t1h 15m\n";
        }
        
        else if((src==1 && dest==5) || (src==5 && dest==1))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:20\t\tPKR10000\tRefundable\t1h 20m\n";
            cout << "2.Falcon(2)\t11:20\t\t12:40\t\tPKR10000\tRefundable\t1h 20m\n";
            cout << "3.Jet Speed(3)\t02:40\t\t04:00\t\tPKR10000\tRefundable\t1h 20m\n";
        }

        else if((src==2 && dest==3) || (src==3 && dest==2))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:55\t\tPKR20000\tRefundable\t1h 55m\n";
            cout << "2.Falcon(2)\t12:00\t\t02:55\t\tPKR20000\tRefundable\t1h 55m\n";
            cout << "3.Jet Speed(3)\t05:00\t\t07:55\t\tPKR20000\tRefundable\t1h 55m\n";
        }

        else if((src==2 && dest==4) || (src==4 && dest==2))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:20\t\tPKR10000\tRefundable\t1h 20m\n";
            cout << "2.Falcon(2)\t11:20\t\t12:40\t\tPKR10000\tRefundable\t1h 20m\n";
            cout << "3.Jet Speed(3)\t02:40\t\t04:00\t\tPKR10000\tRefundable\t1h 20m\n";
        }
        
        else if((src==2 && dest==5) || (src==5 && dest==2))//condition
        {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:20\t\tPKR10000\tRefundable\t1h 20m\n";
            cout << "2.Falcon(2)\t11:20\t\t12:40\t\tPKR10000\tRefundable\t1h 20m\n";
            cout << "3.Jet Speed(3)\t02:40\t\t04:00\t\tPKR10000\tRefundable\t1h 20m\n";
        }
        
        else if((src==3 && dest==4) || (src==4 && dest==3))//condition
         {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:40\t\tPKR18000\tRefundable\t1h 40m\n";
            cout << "2.Falcon(2)\t11:40\t\t01:00\t\tPKR18000\tRefundable\t1h 40m\n";
            cout << "3.Jet Speed(3)\t03:00\t\t4:40\t\tPKR18000\tRefundable\t1h 40m\n";
        }
        
        else if((src==3 && dest==5) || (src==5 && dest==3))//condition
         {
            cout << "\t \t \tFlights Found" << endl << endl;
            cout << "Airline:\tDeparture:\tArrival:\tPrice:\t\tCategory:\tTime:\n";
            cout << "1.Eagle(1)\t08:00\t\t09:15\t\tPKR10000\tRefundable\t1h 15m\n";
            cout << "2.Falcon(2)\t11:15\t\t12:30\t\tPKR10000\tRefundable\t1h 15m\n";
            cout << "3.Jet Speed(3)\t02:30\t\t03:45\t\tPKR10000\tRefundable\t1h 15m\n";
        }
        else if(src==dest)//condition
        {
            cout << "\nDestination can't be same.\nTry again\n\n\n" << endl;
           // return j_detail();
        }
        else
        {
            cout <<"\nWrong input entered\nTry again\n\n\n" << endl;
           // return j_detail();
        }
      	
			
			}
		
	int select_flight()
    {
    	int choicei;
        cout << "\nEnter your choice" << endl;
        cin >> choicei;
        switch(choicei)
        {
        case 1:
            cout << "\nFlight selected:" <<endl;
            cout << "Speed" << endl;
           // strcpy(f_i,"Speed");
            //cout << "Departure Time: 10:00" << endl;
            //cout << "Arrival Time: 14:05" << endl;
            //strcpy(tojdi,"10:00");
            //strcpy(tojai,"14:05");
            break;
        case 2:
               cout << "\nFlight selected:" << endl;
               cout << "Zoom" << endl;
              // strcpy(f_i,"Zoom");
               //cout << "Departure Time: 14:00" << endl;
               //cout << "Arrival Time: 18:05" << endl;
               //strcpy(tojdi,"14:00");
                //strcpy(tojai,"18:05");
                break;
        case 3:
            cout << "\nFlight selected:" << endl;
            cout << "Fly Away" << endl;
          //  strcpy(f_i,"Fly Away");
           // cout << "Departure Time : 18:00" << endl;
            //cout << "Arrival Time: 22:05" << endl;
            //strcpy(tojdi,"18:00");
            //strcpy(tojai,"22:05");
            break;
        default:
            cout << "Wrong input entered" << endl;
            return select_flight();
        }
    }
};
class routes{
	public:
		bool print()
		{
			int i,j;
			char ch;
			cout<<"\n\n\n\n\tFollowing are the international flights available"<<endl;
			for(i=0;i<11;i++)
			{
				cout<<endl;
				for(j=0;j<11;j++)
				{
					if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<i_destination[i]<<" to "<<i_destination[j]<<endl;
					}
					
				}
			}
			cout<<"\n\n\n\n\tFollowing are the local flights available"<<endl;
			for(i=0;i<5;i++)
			{
				cout<<endl;
				for(j=0;j<5;j++)
				{
						if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<l_destination[i]<<" to "<<l_destination[j]<<endl;
					}
				}
			}
			cout<<endl<<"Do you have an account? (y/n) ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl;
				return true;
			}
			else
				return false;
		}
		
};

class Login
{
	public:
		bool print()
		{
		string cnic;
		string password,password1;
		int ch1,ch2;
		char ch;
		int choice;
		cout << "1 : Don't have an account? Sign up \n2 : Already have an account?Sign in\n";
   		cin >> choice;
   		if (choice==1)
    		{
    			cout<<"Enter CNIC :"<<endl;
				cin>>cnic;
				cout<<"Enter Password: "<<endl;
				ch1 = getch();
				while(ch1!=13)
					{
						password.push_back(ch1);
						cout<<"*";
						ch1 = getch();
					}
					cout<<endl;
				cout<<"Re-enter the password: "<<endl;
				ch2 = getch();
				while(ch2!=13)
					{
						password1.push_back(ch2);
						cout<<"*";
						ch2 = getch();
					}
					cout<<endl;
				if(password==password1)
					{
						cout<<"Your details are saved"<<endl;
						system("pause");
					}
				else
					{
						cout<<"Password Mismatched"<<endl;
					}
			//File Handling		
				ofstream outfile;
				outfile.open("Passenger.txt",ios::app);
			//	outfile<<"|Passenger INFORMATION:"<<endl<<endl;
			  	outfile<<cnic<<endl;
			  	outfile<<password<<endl;
			  	outfile.close();
				  
			cout<<endl<<"Do you want to book a flight(y/n) ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl;
				return true;
			}
			else
				return false;	
			
			}
		else if(choice==2)
		{
			bool status = IsloggedIn();
			
			if(!status)
			{
			cout<<"Incorrect Information"<<endl;
			system("PAUSE");
			return 0;
			}
			else
			{
			cout<<"Login Successfull"<<endl;
			//system("PAUSE");
			//return 1;
			
			cout<<endl<<"Do you want to book a flight(y/n) ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl;
				return true;
			}
			else
				return false;	
			
			
			}	
		}
	}
};

class Manage
{
	private:
		string temp,y,z,c2;
		int option;
	public:
		int change()
		{	
			int i=0;
			
			ifstream file("flight.txt");
			if(file.is_open())
			{
			cout<<endl<<"Enter your Ticket Number or Press 0 to exit\nTicket Number: ";
			cin>>temp;
			if(temp=="0")
				return 1;
			string v("Ticket: "+temp);
			
			while(!file.eof())
			{
				getline(file,y);
				if(y==v)
				{
					file.seekg(0,ios::beg);
					while(!file.eof())
					{
						getline(file,temp);
						cout<<temp<<endl;
					}
					cout<<endl<<endl<<"1.Change date\n2.Cancel the flight\n3.Go Back\n";
					option = getch();
					switch(option)
					{
						case 49:
						{
							file.seekg(0,ios::beg);
							ofstream ofile("temp.txt");
							cout<<endl<<"Enter the new date of departure(DDMMYYYY): ";
							cin>>c2;
							string c1("New Date: "+c2);
							while(!file.eof())
							{
								getline(file,y);
								if(i==11)
								{
									i++;
									ofile<<c1<<endl;
								}
								else
								{
									i++;
									ofile<<y<<endl;
								}
							}
							file.close();
							ofile.close();
							ofstream outfile;
							outfile.open("flight.txt");
							ifstream readfile("temp.txt");
							while(!readfile.eof())
							{
								getline(readfile,y);
								outfile<<y<<endl;
							
							}
							outfile.close();
							readfile.close();
							remove("temp.txt");
							cout<<endl<<"Date Changed!";
							return 1;
							break;
						}
					
						case 50:
						{
							file.close();
							ofstream ofli;
							ofli.open("flight.txt",ios::trunc);
							ofli.close();
							remove("flight.txt");
							system("cls");
							cout<<endl<<"Booking cancelled!\n\n";
							return 1;
							break;
						}
						case 51:
							system("cls");
							return 1;
					}
				}
			}
		}
		else if(!file.is_open())
		{
			cout<<endl<<endl<<"unable to find any record"<<endl;
			cout<<endl<<"going back to main page\n\n";
			file.close();
			return 1;
		}
	}
};
int main()
{
	cout<<endl<<"\n\n\n\tWelcome to New Pak Airline"<<endl;
	string cnic, password, password1, f_name, l_name, pass_no,phone_no;
	int choice,datedep, date, month, year;
	bool ans;
	char ch;
	
	back2:
	cout<<endl<<"Press 1 for Login"
	<<endl<<"Press 2 for Ticket Reservation"
	<<endl<<"Press 3 for Routes"
	<<endl<<"Press 4 for Ticket Management"
	<<endl<<"Press 5 for Flight Schedule"
	<<endl<<"Press 0 for Exit\n";
	cin>> choice;
	system("cls");
	
	switch(choice)
	{
		case 1:
			{
				my1:
				cout<<">>>>>>>>>>Login<<<<<<<<<<<\n";
					Login l;
					ans = l.print();
					if(ans==true)
						goto my;
					else if(ans==false)
					{
						cout<<endl;
						system("cls");
						goto back2;
					}
					break;
			}
		case 2:
			{
				my:
				cout<<">>>>>>>>>>Passenger Details<<<<<<<<<<<\n";
				Passenger *p;
				cout<<"Enter Your First Name: ";
				cin>>f_name;
				cin.ignore();
				cout<<"Enter Your Last Name: ";
				getline(cin,l_name);
				cout<<"Enter Your CNIC (without -): ";
				getline(cin,cnic);
				cout<<"Enter Your Phone Number (without -): ";
				cin>>phone_no;
				date:
				cout<<"Enter date of departure(DDMMYYYY): ";
				cin>>datedep;
				
				Booking obj1(f_name,l_name,phone_no,cnic,pass_no,datedep);
				p = &obj1;
				back:
				cout<<endl<<"1.Local Destination\n2.International Destination\n3.Back\n4.Exit\n";
				cin>> choice;
				
				if(choice==1)
				{
					
					if(p->ldest()==false)
					{
						cout<<endl<<"We donot fly to this place\nPlease Choose again\n";
						goto back;
					}
					else
					{
						cout<<endl<<"Yes we do fly\n";
						
						flightSchedule fs;
						system("cls");
						fs.flight();
						fs.select_flight();
					//	p->select_flight();
						p->seats();
						p->Registration();
						system("cls");
						ans = p->display();
						if(ans==false)
						{
							system("cls");
							goto back2;
						}
						else if(ans==true)
						{
							cout<<endl<<"Thanks for Flying With Us"<<endl;
						}
					}
				}
				else if(choice==2)
				{
					cout<<endl<<"Enter Your Passport Num(Without \"-\"): ";
					cin>>pass_no;
					ans = p->idest(pass_no);
					if(ans==false)
					{
						cout<<endl<<"We donot fly to this place\n";
						goto back;
					}
					else
					{
						cout<<endl<<"Yes we do fly\n";
						p->seats();
					//	ptr->Meals();
						p->Registration();
						system("cls");
						ans = p->display();
						if(ans==false)
						{
							system("cls");
							goto back2;
						}
						else if(ans==true)
						{
							cout<<endl<<"Thanks for Flying With Us"<<endl<<endl;
						}
					}
				}
				else if(choice==3)
				{
					system("cls");
					goto back2;
				}
				else
					exit(0);
				break;
			}
			case 3:
				{
					cout<<">>>>>>>>>>ROUTES<<<<<<<<<<<\n";
					routes r;
					ans = r.print();
					if(ans==true)
						goto my1;
					else if(ans==false)
					{
						cout<<endl;
						system("cls");
						goto back2;
					}
					break;
				
				}
			case 4:
				{
					cout<<">>>>>>>>>>Manage<<<<<<<<<<<\n";
					Manage m;
					chnge:
					choice= m.change();
					if (choice==1)
					{
						sleep(2);
						system("cls");
						goto back2;
					}
					else
					{
						cout<<"No record found\n";
						goto chnge;
					}
						
					break;
				}
			case 5:
				{
						cout<<">>>>>>>>>>Flight Schedule<<<<<<<<<<<\n";
						flightSchedule fs;
					//	system("cls");
						fs.flight();
						cout<<endl;
						cout<<"To book a flight, go to Login form."<<endl;
						system("Pause");
						goto back2;
						
					break;
				}
	}
}

