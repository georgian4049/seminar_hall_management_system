//author::ayush shekhar,cadet4049,github.com/georgian4049

#include<string>
#include<iostream>
#include<cstring>
#include<fstream>
#include <stdlib.h>
#include <array> 
#include<iomanip>


char official(int a)
{  
	if(a==11)
	{
		std::cout<<"HOD ISE";
	}

	if(a==12)
	{
		std::cout<<"HOD CSE";
	}

	if(a==13)
	{
		std::cout<<"HOD MECH";
	}

	if(a==14)
	{
		std::cout<<"HOD CIV";
	}

	if(a==15)
	{
	
		std::cout<<"HOD AERO";
	}

	if(a==2)
	{
		std::cout<<"VICE-PRINCIPAL";
	}

	if(a==3)
	{
		std::cout<<"PRINCIPAL";
	}if(a==4)

	{
		std::cout<<"CHAIRMAN";
	}
return '.' ;
}



using namespace std;
//checking date
int checkDate(int month, int day, int year)
{
    int status=0; 
     if ((month < 1) || (month > 12))
    {
        return 0;
    }

    if ((month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12) && ( day<=31 || day>=1) )
    {
        status = 1; 
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day<=30 || day>=1) )
    {
        status = 1; 
    }
    else if ((month == 2) && (year % 4 == 0) && (day<=29 || day>=1))
    {
        status = 1; 
    }
    else if ((month == 2) && (year % 4 != 0) && (day<=28 || day>=1) )
    {
        status = 1; 
    }
    else if ((year < 999) || (year > 10000))
    {
        status = 1;
    }
   
    return status;
};

int split(char date[10])
{
	 int d,m,y;
    sscanf(date,"%d/%d/%d",&d,&m,&y);
    sscanf(date,"%d-%d-%d",&d,&m,&y);
    if(checkDate(m,d,y))
    	{	
    		return 1;
    	}
    	else
    	{
    		return 0;
    	}
    }


char fname1[30]="seminar_hall_1.dat";
char fname2[30]="seminar_hall_2.dat";
char fname3[30]="seminar_hall_3.dat";
char fname4[30]="seminar_hall_4.dat";
char fname5[30]="seminar_hall_5.dat";
char fname6[30]="seminar_hall_6.dat";
char fname7[30]="RajLaxhmin_seminar_hall.dat";
char fname8[30]="auditorium.dat";

struct record
{
	char date[15],time[15],branch[10],discription[100];
	int id;
}; 

//message
struct record_msg
{
	char date[15],time[15],branch[10],discription[100];
	int id_to,id_by;
}; 
int message(char date_list[15],char time_list[15],char branch[10],char description[100],int id_to,int id_by)
{
	record_msg r;
	strcpy(r.date,date_list);
	strcpy(r.time,time_list);
	strcpy(r.branch,branch);
	strcpy(r.discription,description);
	r.id_to=id_to;
	r.id_by=id_by;
 fstream mod;
mod.open("message.dat",ios::app|ios::binary);
	mod.write((char*)&r,sizeof(r));
	return 0;
}


class seminar1
{
public: void writedata(int a,char file_name[30]);
		void display(char file_name[30]);
		void search(char file_name[30]);
		void modify(int a,char file_name[30]);
};

int time_checker(int starttime1,int endtime1,int i,int *starttime,int *endtime)
{	
	if(starttime1<8 || starttime1>16 || endtime1>16 || endtime1<8 || starttime1==endtime1 || endtime1<starttime1)
	{
		cout<<"thats not working time. try again \n";
		return 0;
	}
	else{
		int cou=0;
		for(int k=0;k<i;k++)
		{
			if(!((starttime1<starttime[k] && endtime1<=starttime[k]) || (starttime1>=endtime[k] && endtime1>endtime[k]) ))
			{
				
				cou++;
				

			}

			
		}
		if(cou>0)
		{
			cout<<"\nseminar hall will be busy during this time slot\n";
			return 0;
		}
		else
			{
				return 1;
			}
		}
return 0;
}


void seminar1::writedata(int a,char file_name[30])
{
	fstream fo;
	int j;
	record r;
	int tot_slots_count=0;
	r.id=a;
	int count=0;
	int starttime1,endtime1;
	record s;
	char date_list[100][15];
	char time_list[100][15];
	int starttime[20],endtime[20];
	int i=0;
	fo.open(file_name,ios::in|ios::binary);
	if(fo)
	{
	while(1){

	fo.read((char*)&s,sizeof(s));
	if(fo.eof())
	{
		break;
	}
	strcpy(date_list[i],s.date);
	strcpy(time_list[i],s.time);
	
	sscanf(time_list[i],"%d-%d",&starttime[i],&endtime[i]);

	i++;

	}
	}
	fo.close();
	

	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	
	
	cout<<"\ntime slots taken on this dates are:";
	for(j=0;j<i;j++)
	{	
		if(strcmp(date_list[j],r.date)==0)
		{
			cout<<"\n"<<j+1<<"."<<"\t"<<time_list[j]<<"\n";
			tot_slots_count++;
			
		}
	}
	if(tot_slots_count==0)
	{
		cout<<"\t no time slots booked";
	}
	else {
		do
	{
	cout<<"\nEnter Time Slot (From - To):\t";
	cin>>r.time;

	sscanf(r.time,"%d-%d",&starttime1,&endtime1);
	
}while(!(time_checker(starttime1,endtime1,i,starttime,endtime)));

}


	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	fstream f;
	f.open(file_name,ios::app|ios::binary);
	f.write((char*)&r,sizeof(r));
	cout.flush();
	f.close();
}
void seminar1::display(char file_name[30])
{
	fstream f;
	record r;
	char date_list[100][15];
	char time_list[100][15];
	int i=0;
	int c=1;
	f.open(file_name,ios::in|ios::binary);
	if(!f){
		cout<<"no records found";
	}
	else{
	cout << '|' << setw(4) << "s.no" << '|'<< setw(15) << "date" << '|'<< setw(10) << "time" << '|'<< setw(10) << "branch" << '|'<< setw(15) << "description" << '|'<< setw(16) << "id" << '|' << endl;
	while(1){
	f.read((char*)&r,sizeof(r));
	if(!f.eof())
{	cout.flush();
	cout << '|' << setw(4) << c++ << '|'<< setw(15) << r.date << '|'<< setw(10) << r.time << '|'<< setw(10) << r.branch << '|'<< setw(15) << r.discription << '|'<< setw(16) << official(r.id) << '|' << endl;
	
		strcpy(date_list[i],r.date);
		strcpy(time_list[i],r.time);
		i++;
	}

	else{
		break;
	}
}
	f.close();
}
}	

void seminar1::modify(int a,char file_name[30])
{
	fstream f;
	record r;
	int j=0;
	int my_count=0;
	int time_cnt=0;
	char date_list[100][15];
	char time_list[100][15];
	char description[100][100];
	char branch[100][10];
	char new_date[15];
	char new_time[15];
	char new_description[100];
	char new_branch[10];
	char date_check[15];
	char time_check[15];
int count_booking_time=0;
	int id[100];
	int i=0;
	f.open(file_name,ios::in|ios::binary);
	if(!f){
		cout<<"no records found";
	}
	else{
	
	while(!f.eof()){
	f.read((char*)&r,sizeof(r));
		strcpy(date_list[i],r.date);
		strcpy(time_list[i],r.time);
		strcpy(description[i],r.discription);
		strcpy(branch[i],r.branch);
		id[i]=r.id;
		i++;
	}
i=i-1;
for(int k=0;k<i;k++)
{
	if(id[k]==a)
	{
		my_count++;
}
}
if(my_count==0)
{
	cout<<"you have not booked seminar hall yet";
}

	else
	{

cout<<"\n\t\t\t\t you have booked seminar hall  as follows:\n";
cout<<"Date\t\t"<<"time\t\t"<<"description\t\t"<<"branch\t\t\n";
int c=1;
cout << '|' << setw(4) << "s.no" << '|'<< setw(15) << "date" << '|'<< setw(10) << "time" << '|'<< setw(10) << "branch" << '|'<< setw(15) << "description" << '|'<< setw(16) << "id" << '|' << endl;

for(int k=0;k<i;k++)
{
	if(id[k]==a)
	{
	cout << '|' << setw(4) << c++ << '|'<< setw(15) << date_list[k] << '|'<< setw(10) <<time_list[k] << '|'<< setw(10) << branch[k] << '|'<< setw(15) << description[k] << '|'<< setw(16) << official(id[k]) << '|' << endl;

}
}
	}

int count_booking;
char date_mod[15];
cout<<"\n\t\t\t\tenter the date you want to do modification:\t";
cin>>date_mod;
int c=1;
cout << '|' << setw(4) << "s.no" << '|'<< setw(15) << "date" << '|'<< setw(10) << "time" << '|'<< setw(10) << "branch" << '|'<< setw(15) << "description" << '|'<< setw(16) << "id" << '|' << endl;
	
for(int k=0;k<i;k++)
{
	if(strcmp(date_mod,date_list[k])==0)
	{
		cout << '|' << setw(4) << c++ << '|'<< setw(15) << date_list[k] << '|'<< setw(10) <<time_list[k] << '|'<< setw(10) << branch[k] << '|'<< setw(15) << description[k] << '|'<< setw(16) << official(id[k]) << '|' << endl;

}
}
char get_time[15];


	again_time_slot:cout<<"\n\t\t\t\tenter the times-lot you want to do modification:\t";
	cin>>get_time;
	
	for(int k=0;k<i;k++)
{


if(((a>10 && id[k]!=a )|| (a<id[k] && id[k]<10 ))&& strcmp(date_mod,date_list[k])==0 && strcmp(get_time,time_list[k])==0)
	{
		cout<<"\n\t\t\t\t you cannot modify this time\n";
		cout<<"\n\t\t\t\tto exit type y else n:\n";
		opt1:char optt;
		cin>>optt;
		if(optt=='y')
		{
			break;
		}
		else if(optt=='n')
		{
		goto again_time_slot;
		}
		else
		{
			cout<<"\n\t\t\t\tno such option\n";
			goto opt1;
		}

	
	}
/*
	if(time_cnt==0)
	{
		cout<<"\n\t\t\t\tno such time slot\n";
		cout<<"\n\t\t\t\tto exit type y else n:\n";
		opt:char optt;
		cin>>optt;
		if(optt=='y')
		{
			break;
		}
		else if(optt=='n')
		{
		goto again_time_slot;
		}
		else
		{
			cout<<"\n\t\t\t\tno such option\n";
			goto opt;
		}

	}
	*/
	if(((id[k]<=a && a<10)||(id[k]>10 && a<10)|| (id[k]==a))&& strcmp(date_mod,date_list[k])==0 && strcmp(get_time,time_list[k])==0)
	{
		cout<<"old date : \t ";
	cout<<date_list[k]<<"\n";
cout<<"old time:\t";
	cout<<time_list[k]<<endl;
	cout<<"old description:\t";
cout<<description[k]<<endl;
cout<<"old branch:\t";
cout<<branch[k]<<"\n\n";

update_failed: cout<<"new date : \t ";
	cin>>date_check;

cout<<"new time:\t";
	cin>>time_check;
	cout<<"new description:\t";
cin>>description[k];
cout<<"new branch:\t";
cin>>branch[k];
int c=1;
for(int j=0;j<i;j++)
{
	if((id[j]>a && id[j]<10) && strcmp(date_check,date_list[j])==0 && strcmp(time_check,time_list[j])==0)
	{
		cout<<"\n\t\t\t\tthis date/time slot is already taken by higher ups \n";
		cout << '|' << setw(4) << "s.no" << '|'<< setw(15) << "date" << '|'<< setw(10) << "time" << '|'<< setw(10) << "branch" << '|'<< setw(15) << "description" << '|'<< setw(16) << "id" << '|' << endl;
	cout << '|' << setw(4) << c++ << '|'<< setw(15) << date_list[j] << '|'<< setw(10) <<time_list[j] << '|'<< setw(10) << branch[j] << '|'<< setw(15) << description[j] << '|'<< setw(16) << official(id[j]) << '|' << endl;
goto update_failed;
		
	}

	else
	{	message(date_list[k],time_list[k],new_branch,new_description,id[j],a);
		strcpy(date_list[k],date_check);
		strcpy(time_list[k],time_check);
		id[k]=a;
		
	}
}
}

}
record rr[10];
for(int k=0;k<i;k++)
{
	strcpy(rr[k].date,date_list[k]);
		strcpy(rr[k].time,time_list[k]);
		strcpy(rr[k].discription,description[k]);
		strcpy(rr[k].branch,branch[k]);
		rr[k].id=id[k];
}

f.close();
fstream ff;
ff.open(file_name,ios::out|ios::binary);
ff.close();
fstream fff;
fff.open(file_name,ios::app|ios::binary);

for(int k=0;k<i;k++)
{
	fff.write((char*)&rr[k],sizeof(r));
}
fff.close();
}
}





void seminar1::search(char file_name[30])
{
	fstream f;
	record r;
	char date[15];
	cout<<"\n\t\t\t\tenter date you want to search :\t";
	cin>>date;

	char date_list[100][15];
	char time_list[100][15];
	char description[100][100];
	char branch[100][10];
	int id[100];

	int i=0;
	int c=1;
	f.open(file_name,ios::in|ios::binary);
	if(!f){
		cout<<"no records found";
	}
	else{
	while(1){
	f.read((char*)&r,sizeof(r));
	if(!f.eof())
{	if(strcmp(r.date,date)==0)
	{
		strcpy(date_list[i],r.date);
		strcpy(time_list[i],r.time);
		strcpy(branch[i],r.branch);
		strcpy(description[i],r.discription);
		id[i]=r.id;
	i++;
	}

	}

	else{
		break;
	}
}
if(i==0)
	{
		cout<<"\n\t\t\t\tno booking on this date";
	}
else
{
	cout << '|' << setw(4) << "s.no" << '|'<< setw(15) << "date" << '|'<< setw(10) << "time" << '|'<< setw(10) << "branch" << '|'<< setw(15) << "description" << '|'<< setw(16) << "id" << '|' << endl;
	
	for(int k=0;k<i;k++)
	{
		cout << '|' << setw(4) << c++ << '|'<< setw(15) << date_list[k] << '|'<< setw(10) <<time_list[k] << '|'<< setw(10) << branch[k] << '|'<< setw(15) << description[k] << '|'<< setw(16) << official(id[k]) << '|' << endl;

	}
}

	f.close();
}
}

void login(int a)
{	
int hall;

	seminar1 obj1;
	seminar1 obj2;
	seminar1 obj3;
	seminar1 obj4;
	seminar1 obj5;
	seminar1 obj6;
	seminar1 obj7;
	seminar1 obj8;
int ch;
//message display
fstream f;
	record_msg r;
	char date_list[100][15];
	char time_list[100][15];
	char description[100][100];
	char branch[100][10];
	int id;
	int i=0;
	int c=1;
	f.open("message.dat",ios::in|ios::binary);
	if(!f){
		cout<<"no message";
	}
	else{
	while(1){
	f.read((char*)&r,sizeof(r));
	if(!f.eof())
{	if(r.id_to==a)
	{

	cout<<"\n\n\tyour booking has been modified by :"<<official(r.id_by)<<" dated :"<<r.date<<" timed :"<<r.time<<"for branch:"<<r.branch<<"description :"<<r.discription<<endl;
	}
}

	else{
		break;
	}
}



	f.close();
}





	cout<<"Select Seminar Hall:\n"<<"\n-----------------------------------------------------------------------------------------\n";
	cout<<"1.Seminar Hall 1\n2.Seminar Hall 2\n3.Seminar Hall 3\n4.Seminar Hall 4\n5.Seminar Hall 5\n6.Seminar Hall 6\n7.Raj Laxhmi Seminar Hall\n8.Auditorium\n";
	cout<<"\n------------------------------------------------------------------------------------------\n";
	cin>>hall;
	switch(hall)
	{
	case 1:cout<<" \nSeminar Hall 1\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj1.writedata(a,fname1);
			break;
		case 2: obj1.display(fname1);
			break;
		case 3: obj1.search(fname1);
			break;
		case 4: obj1.modify(a,fname1);
			break;
		default: exit(0);
		}
	}
	break;
	case 2:
		cout<<" \nSeminar Hall 2\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj2.writedata(a,fname2);
			break;
		case 2: obj2.display(fname2);
			break;
		case 3: obj2.search(fname2);
			break;
		case 4: obj2.modify(a,fname2);
			break;
		default: exit(0);
		}
	}
	break;
	case 3: cout<<" \nSeminar Hall 3\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj3.writedata(a,fname3);
			break;
		case 2: obj3.display(fname3);
			break;
		case 3: obj3.search(fname3);
			break;
		case 4: obj3.modify(a,fname3);
			break;
		default: exit(0);
		}
	}
	break;
	case 4:cout<<" \nSeminar Hall 4\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj4.writedata(a,fname4);
			break;
		case 2: obj4.display(fname4);
			break;
		case 3: obj4.search(fname4);
			break;
		case 4: obj4.modify(a,fname4);
			break;
		default: exit(0);
		}
	}
	break;
	case 5:cout<<" \nSeminar Hall 5\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj5.writedata(a,fname5);
			break;
		case 2: obj5.display(fname5);
			break;
		case 3: obj5.search(fname5);
			break;
		case 4: obj5.modify(a,fname5);
			break;
		default: exit(0);
		}
	}
	break;
	case 6:cout<<" \nSeminar Hall 6\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj6.writedata(a,fname6);
			break;
		case 2: obj6.display(fname6);
			break;
		case 3: obj6.search(fname6);
			break;
		case 4: obj6.modify(a,fname6);
			break;
		default: exit(0);
		}
	}
	break;
	case 7:cout<<" \nSeminar Hall 7\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj7.writedata(a,fname7);
			break;
		case 2: obj7.display(fname7);
			break;
		case 3: obj7.search(fname7);
			break;
		case 4: obj7.modify(a,fname7);
			break;

		default: exit(0);
		}
	}
	break;
	case 8:cout<<" \nSeminar Hall 8\n"<<"\n-----------------------------------------------------------------------------------------\n";
		cout<<"1.write data\n2.display\n3.search\n4.modify\n5.exit:"<<"\n-----------------------------------------------------------------------------------------\n";

	while(1)
	{
		cout<<"\nenter your choice:";
		cin>>ch;
		switch(ch)
		{
		case 1: obj8.writedata(a,fname8);
			break;
		case 2: obj8.display(fname8);
			break;
		case 3: obj8.search(fname8);
			break;
		case 4: obj8.modify(a,fname8);
			break;
		default: exit(0);
		}
	}
	break;

	
	}
}

int main()
{   
	int ch;
	int hall;
	int type;
	char pass[10];
	char enterpass[10];
	char chairman[10]="chairman";
	char vp[10]="vp";
	char principal[10]="principal";
	
	cout<<"\n\t\t\t1. HOD\n";
	cout<<"\n\t\t\t2. VICE-PRINCIPAT\n";
	cout<<"\n\t\t\t3. PRINCIPAL\n";
	cout<<"\n\t\t\t4. CHAIRMAN\n";

	cout<<"\n";
	cout<<"\n\t\t\t"<<"enter your choice:\t";
	cin>>type;
	if(type==1)
	{
		cout<<"\n\t\t\t1. HOD ISE\n";
	cout<<"\n\t\t\t2. HOD CSE\n";
	cout<<"\n\t\t\t3. HOD MECH\n";
	cout<<"\n\t\t\t4. HOD CIV\n";
	cout<<"\n\t\t\t5. HOD AERO\n";
	cout<<"\n";
	cout<<"\n\t\t\t"<<"enter your choice:\t";
	cin>>ch;
	if(ch==1)
	{
		strcpy(pass,"hodise");
	}
	else if(ch==2)
	{
		strcpy(pass,"hodcse");
	}
	else if(ch==3)
	{
		strcpy(pass,"hodmech");
	}
	else if(ch==4)
	{
		strcpy(pass,"hodciv");
	}
	else if(ch==5)
	{
		strcpy(pass,"hodaero");
	}

	
	cout<<"\n\t\t\tenter password:\t";
	cin>>enterpass; 

	int id=(type*10)+ch;
	while(strcmp(enterpass,pass)!=0)
	{
		cout<<"\n\t\t\tenter correct password:\t";
		cin>>enterpass;
	}
	login(id);
	}
	else if(type==2)
	{
		cout<<"\n\t\t\tenter password:\t";
		cin>>enterpass; 
	while(strcmp(enterpass,vp)!=0)
	{
		cout<<"\n\t\t\tenter correct password:\t";
		cin>>enterpass; 
	}
	login(type);
	}
else if(type==3){
		cout<<"\n\t\t\tenter password:\t";
		cin>>enterpass; 	
	while(strcmp(enterpass,principal)!=0)
	{
		cout<<"\n\t\t\tenter correct password:\t";
		cin>>enterpass; 
	}
	login(type);
	}
	else if(type==4){
		cout<<"\n\t\t\tenter password:\t";
		cin>>enterpass; 
	while(strcmp(enterpass,chairman)!=0)
	{
		cout<<"\n\t\t\tenter correct password:\t";
		cin>>enterpass; 
	}
	login(type);
	}

	}





