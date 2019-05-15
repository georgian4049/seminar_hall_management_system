#include<string>
#include<iostream>
#include<cstring>
#include<fstream>
#include <stdlib.h>
#include <array> 
#include<iomanip>

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


char fname1[30]="seminar_hall_1.txt";
char fname2[30]="seminar_hall_2.txt";
char fname3[30]="seminar_hall_3.txt";
char fname4[30]="seminar_hall_4.txt";
char fname5[30]="seminar_hall_5.txt";
char fname6[30]="seminar_hall_6.txt";
char fname7[30]="RajLaxhmin_seminar_hall.txt";
char fname8[30]="auditorium.txt";
struct record
{
	char date[15],time[15],branch[10],discription[100];
	int id;
}; 
class seminar1
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify(int a);
};
void seminar1::pack(record r)
{
	fstream fp;
	fp.open(fname1,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	cout.flush();
	fp.close();
}
record seminar1::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
        r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar1::writedata(int a)
{
	fstream fo;
	int j;
	record r;
	r.id=a;
	int count=0;
	record s;
	char date_list[100][15];
	char time_list[100][15];
	int starttime[20],endtime[20];
	int i=0;
	fo.open("seminar_hall1.dat",ios::in|ios::binary);
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
	
	
	cout<<"\ntime slots taken on this dates are\n";
	for(j=0;j<i;j++)
	{
		if(strcmp(date_list[j],r.date)==0)
		{
			cout<<j+1<<"."<<"\t"<<time_list[j]<<"\n";
			
		}
	}


	int flag=0;
	while(flag==0)
	{
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	int starttime1,endtime1;
	sscanf(r.time,"%d-%d",&starttime1,&endtime1);
	if(starttime1<8 || starttime1>16 || endtime1>16 || endtime1<8 || starttime1==endtime1)
	{
		cout<<"thats not working time. try again \n";
	}

	if(j==0)
	{  
		flag=1;
		


	}

	else{
		count=0;
		for(int k=0;k<i;k++)
		{
			if((starttime[k]<starttime1 && endtime[k]<endtime1) ||(starttime[k]>starttime1 && endtime[k]>endtime1))
			{
				
			count=count+1;
			}
			else
			{
				count=count-1;
			}
			
		}
		if(count>0)
		{
			flag=1;
		}

	}

}
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	fstream f;
	f.open("seminar_hall1.dat",ios::app|ios::binary);
	f.write((char*)&r,sizeof(r));
	cout.flush();
	f.close();
}
void seminar1::display()
{
/*	fstream fp;
	char buff[45];
	record r;
	fp.open(fname1,ios::in);
	if(!fp)
	{
		cout<<"\ncan not open file";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)

		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
	*/

	fstream f;
	record r;
	char date_list[100][15];
	char time_list[100][15];
	int i=0;
	int c=1;
	f.open("seminar_hall1.dat",ios::in|ios::binary);
	if(!f){
		cout<<"no records found";
	}
	else{
	cout << '|' << setw(4) << "s.no" << '|'<< setw(15) << "date" << '|'<< setw(10) << "time" << '|'<< setw(10) << "branch" << '|'<< setw(15) << "description" << '|'<< setw(10) << "id" << '|' << endl;
	while(1){
	f.read((char*)&r,sizeof(r));
	if(!f.eof())
{	cout.flush();
	cout << '|' << setw(4) << c++ << '|'<< setw(15) << r.date << '|'<< setw(10) << r.time << '|'<< setw(10) << r.branch << '|'<< setw(15) << r.discription << '|'<< setw(10) << r.id << '|' << endl;
	
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

void seminar1::modify(int a)
{
	fstream f;
	record r;
	int j=0;
	char date_list[100][15];
	char time_list[100][15];
	char times_slots[100][15];
	char description[100][15];
	char branch[100][15];

	int id[100];
	int i=0;
	f.open("seminar_hall1.dat",ios::in|ios::binary);
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
	i--;
int count=0;
cout<<i;


char date_to_modify[15];
	cout<<"\n\t\t\tenter date you want to modify:\t";
	cout<<endl;
	cin>>date_to_modify;
	int a=0;
	for(j=0;j<i;j++)
	{
		if(strcmp(date_list[j],date_to_modify)==0 && id[i]==a)
		{  
			strcpy(times_slots[count],time_list[j]);
			count++;

		}
	}
	
	if(count==0)
	{
		cout<<"\t\t--------you didnot book seminar hall on this day-------- ";
	}
	else
	{   cout<<"\n\t\t\t\tyou booked seminar hall on:";
		for(int cc=0;cc<count;cc++)
			{
		cout<<"\n\t\t\t\t"<<times_slots[cc];
		cout<<endl;
			}

	}







	//time modification-------------------------------------------------------------
	/*char time_to_modify[5];
	char description_to_modify[15];
	char new_time[5];
	char new_description[15];
	char ch;
	cout<<"\n\t\t\t\tdo you want to modify time slot . Type Y/N :\t";
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	cout<<"\n\t\t\t\tenter time to modify";
	cin>>time_to_modify;
	cout<<"\n\t\t\t\tenter new time slot";
	cin>>new_time;

	for(int j=0;j<i;j++)
	{
		if(strcmp(time_list[j],time_to_modify)==0 && id[j]==a)
		{
			strcpy(time_list[j],new_time);
			cout<<"\n------------------------------------------------time modified sucessfully------------------------------------------------\n";
		}
	}
	}
	else if(ch=='n' || ch=='N')
	{
		cout<<"\n\t\t\t\t You choosed no";
	}
	else{
		cout<<"\n\t\t\t\t\t Thats wrong choice ";
	}
//description modification---------------------------------------------------------------
	cout<<"\n\t\t\t\tdo you want to modify description . Type Y/N :\t";
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	cout<<"\n\t\t\t\tenter time slot where you want  to modify";
	cin>>time_to_modify;
	char new_description[15];
	for(int j=0;j<i;j++)
	{
		if(strcmp(time_list[j],time_to_modify)==0 && id[j]==a)
		{
			cout<<"\ndescription is :"<<" "<<description[j];
			cout<<"\nenter new description:";
			cin>>new_description;
			strcpy(description[j],new_description);
			cout<<"\n------------------------------------------------description modified sucessfully------------------------------------------------\n";
		}
	}
	}
	
	else if(ch=='n' || ch=='Y')
	{
		cout<<"\n\t\t\t\t You choosed no";
	}
	else{
		cout<<"\n\t\t\t\t\t Thats wrong choice ";
	}
	record r_array[10];
	for(int c=0;c<i;c++)
	{
		strcpy(r_array[c].date,date_list[c]);
		strcpy(r_array[c].time,time_list[c]);
		strcpy(r_array[c].discription,description[c]);
		strcpy(r_array[c].branch,branch[c]);
		r_array[c].id=id[c];

	}

f.close();
fstream f,fo;
	f.open("seminar_hall1.dat",ios::out|ios::binary);
	f.write((char*)&r_array,sizeof(record));
	f.close();
	fo.open("seminar_hall1.dat",ios::app|ios::binary);
for(int c=1;c<i;c++)
{
	fo.write((char*)&r_array[c],sizeof(record));
	cout.flush();

}
	fo.close();

*/
	f.close();




}
}
void seminar1::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname1,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}

class seminar2
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar2::pack(record r)
{
	fstream fp;
	fp.open(fname2,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar2::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar2::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar2::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname2,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar2::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname2,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname2,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar2::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname2,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}
class seminar3
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar3::pack(record r)
{
	fstream fp;
	fp.open(fname3,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar3::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar3::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar3::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname3,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar3::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname3,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname3,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar3::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname3,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}
class seminar4
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar4::pack(record r)
{
	fstream fp;
	fp.open(fname4,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar4::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar4::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar4::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname4,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar4::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname4,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname4,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar4::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname4,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}

class seminar5
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar5::pack(record r)
{
	fstream fp;
	fp.open(fname5,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar5::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar5::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar5::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname5,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar5::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname5,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname5,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar5::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname5,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}
class seminar6
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar6::pack(record r)
{
	fstream fp;
	fp.open(fname6,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar6::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar6::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar6::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname6,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar6::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname6,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname6,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar6::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname6,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}
class seminar7
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar7::pack(record r)
{
	fstream fp;
	fp.open(fname7,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar7::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar7::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar7::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname7,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar7::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname7,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname7,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar7::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname7,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}
class seminar8
{
public: void pack(record r);
		record unpack(char a[]);
		void writedata(int a);
		void display();
		void search();
		void modify();
};
void seminar8::pack(record r)
{
	fstream fp;
	fp.open(fname8,ios::out|ios::app);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	char buff[45];
	strcpy(buff,r.date);
	strcat(buff,"|");
	strcat(buff,r.time);
	strcat(buff,"|");
	strcat(buff,r.branch);
	strcat(buff,"|");
	strcat(buff,r.discription);
	strcat(buff,"|*");
	fp<<buff<<endl;
	fp.close();
}
record seminar8::unpack(char buff[])
{
	record r;
	int i=0,j=0;
	while(buff[j]!='|')
		r.date[i++]=buff[j++];
	r.date[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.time[i++]=buff[j++];
	r.time[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.branch[i++]=buff[j++];
	r.branch[i]='\0';
	i=0;
	j++;
	while(buff[j]!='|')
		r.discription[i++]=buff[j++];
	r.discription[i]='\0';
	return(r);
}
void seminar8::writedata(int a)
{
	record r;
	r.id=a;
	cout<<"\nEnter Date (DD/MM/YYYY):";
	cin>>r.date;
	cout<<"\nEnter Time Slot (From - To):";
	cin>>r.time;
	cout<<"\nEnter Branch:";
	cin>>r.branch;
	cout<<"\nEnter Discription:";
	cin>>r.discription;
	pack(r);
}
void seminar8::display()
{
	fstream fp;
	char buff[45];
	record r;
	fp.open(fname8,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\n#\tDate\tTime Slot\tBranch\tDiscription\n";
	int c=1;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())break;
		r=unpack(buff);
		cout<<c++<<"\t"<<r.date<<"\t"<<r.time<<"\t"<<r.branch<<"\t"<<r.discription<<endl;

	}
	fp.close();
	return;
}
void seminar8::modify()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s[100];
	fp.open(fname8,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be modified:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s[i]=unpack(buff);
		i++;
	}
	for(j=0;j<i;j++)
	{
		if(strcmp(s[j].date,date)==0)
		{
			cout<<"\nvalues of the record are:\n";
			cout<<"\nDate:"<<s[j].date;
			cout<<"\nTime Slot:"<<s[j].time;
			cout<<"\nBranch:"<<s[j].branch;
			cout<<"\nDiscription:"<<s[j].discription;
			cout<<"\nenter the new values:\n";
			cout<<"\nDate:";
			cin>>s[j].date;
			cout<<"\nTime Slot:";
			cin>>s[j].time;
			cout<<"\nBranch:";
			cin>>s[j].branch;
			cout<<"\nDiscription:";
			cin>>s[j].discription;
			break;
		}
	}
	if(j==i)
	{
		cout<<"\nrecord not found";
		return;
	}
	fp.close();
	fstream fd;
	fd.open(fname8,ios::out|ios::trunc);
	if(!fd)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	for(j=0;j<i;j++)
		pack(s[j]);
	fd.close();
}
void seminar8::search()
{
	fstream fp;
	char date[15],buff[45];
	int i,j;
	record s;
	fp.open(fname8,ios::in);
	if(!fp)
	{
		cout<<"\ncould not open file. not yet booked \n";
		exit(0);
	}
	cout<<"\nenter the Date (DD/MM/YYYY) to be searched:";
	cin>>date;
	i=0;
	while(1)
	{
		fp.getline(buff,45,'*');
		if(fp.eof())
			break;
		s=unpack(buff);
		if(strcmp(s.date,date)==0)
		{
			cout<<"\nrecord found\n";
			cout<<"\nDate:"<<s.date;
			cout<<"\nTime Slot:"<<s.time;
			cout<<"\nBranch:"<<s.branch;
			cout<<"\nDiscription:"<<s.discription;
			return;
		}
	}
	cout<<"\nrecord not found";
	return;
}

void login(int a)
{	
int hall;

	seminar1 obj1;
	seminar2 obj2;
	seminar3 obj3;
	seminar4 obj4;
	seminar5 obj5;
	seminar6 obj6;
	seminar7 obj7;
	seminar8 obj8;
int ch;

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
		case 1: obj1.writedata(a);
			break;
		case 2: obj1.display();
			break;
		case 3: obj1.search();
			break;
		case 4: obj1.modify(a);
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
		case 1: obj2.writedata(a);
			break;
		case 2: obj2.display();
			break;
		case 3: obj2.search();
			break;
		case 4: obj2.modify();
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
		case 1: obj3.writedata(a);
			break;
		case 2: obj3.display();
			break;
		case 3: obj3.search();
			break;
		case 4: obj3.modify();
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
		case 1: obj4.writedata(a);
			break;
		case 2: obj4.display();
			break;
		case 3: obj4.search();
			break;
		case 4: obj4.modify();
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
		case 1: obj5.writedata(a);
			break;
		case 2: obj5.display();
			break;
		case 3: obj5.search();
			break;
		case 4: obj5.modify();
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
		case 1: obj6.writedata(a);
			break;
		case 2: obj6.display();
			break;
		case 3: obj6.search();
			break;
		case 4: obj6.modify();
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
		case 1: obj7.writedata(a);
			break;
		case 2: obj7.display();
			break;
		case 3: obj7.search();
			break;
		case 4: obj7.modify();
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
		case 1: obj8.writedata(a);
			break;
		case 2: obj8.display();
			break;
		case 3: obj8.search();
			break;
		case 4: obj8.modify();
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





