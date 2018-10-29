
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<cmath>
#include<math.h>
#include<iomanip>
#include <cstdlib>
using namespace std;

class Vector{


	int *contents;
	int length=0;
	int load_factor=2;
	int capacity=0;
	double shrinkPercent=30;
	 double fullPercent=80;

public:
	Vector()
	{
		length=0;
	}

	Vector(int n,int x)
	{

		contents=new int[n];
		length=n;
		capacity=n;
		for(int i=0;i<length;i++)
		{
			contents[i]=x;
		}

	}
	int &operator[] (int i)
	{

		if(i<length)
			return contents[i];
		
		cout<<"accessing out of index.Seg Fault";
		exit(1)	;		 
	
			 
	}
	int capacityOf()
	{
		return capacity;
	}
	int size()
	{
		return length;

	}	
	int front()
	{
		return contents[0];
	} 
	int back()
	{
		return contents[length-1];
	}

	int push_back(int x)
	{


		
		if(capacity==0){
			contents=new int[10];
			capacity=10;
			contents[length]=x;
			contents[length];
			length=length+1;
			
		}
		else
		{
		

			double fillPercentage=((double)length/(double)capacity)*100.0;
			cout<<"fillPercentage"<<fillPercentage<<"\n";
			cout<<"Full percentage"<<fullPercent<<"\n";
			
			if(fillPercentage>=fullPercent)
			{
				cout<<"resizing";
				int *newArray=new int[capacity*load_factor];

				for(int i=0;i<length;i++)
				{
					newArray[i]=contents[i];
				
				}
				contents=newArray;

				capacity=capacity*load_factor;
			}
			contents[length]=x;
			length=length+1;
			

		}

	}
	int pop_back()
	{
		if(length-1>0){
		int back=contents[length-1];
		length=length-1;
		double fillPercentage=((double)length/(double)capacity)*100;
		cout<<"fillPercentage"<<fillPercentage<<"\n";
		cout<<"Full percentage"<<shrinkPercent<<"\n";




		if(fillPercentage<=shrinkPercent)
		{
			cout<<"shrinking";
			int *newArray=new int[capacity/load_factor];

			for(int i=0;i<length;i++)
			{
				newArray[i]=contents[i];
			}
			contents=newArray;

		
		}
		return back;
		}
		else
		{	
				cout<<"Nothing to delete";
				exit(1);
		}
		
			

		
	}
	int insert(int pos,int element)
	{

			if(pos>length || pos <0)
			{
				cout<<"Cannot insert here";
				return -1;
			}
			if(pos==0 && capacity==0)
			{
				push_back(element);
				return 1;
			}



			double fillPercentage=((double)length/(double)capacity)*100;

			if(fillPercentage>=fullPercent)
			{
				
				int *newArray=new int[capacity*load_factor];

				for(int i=0;i<length;i++)
				{
					newArray[i]=contents[i];
				}
				contents=newArray;



			}

			for(int i=pos+1;i<=length;i++)
			{
				
				contents[i+1]=contents[i];
			}
			contents[pos]=element;
			length=length+1;


	}
	int erase(int pos)
	{

		if(length==0)
		{
			cout<<"Nothing to erase";
			return -1;
		}


		for(int i=pos;i<=length;i++)
			{
				contents[i]=contents[i+1];
			}
		
			length=length-1;
			
	double fillPercentage=((double)length/(double)capacity)*100;
		if(fillPercentage<=shrinkPercent)
		{
			int *newArray=new int[capacity/load_factor];

			for(int i=0;i<length;i++)
			{
				newArray[i]=contents[i];
			}
			contents=newArray;
			capacity=length;
		}
		







	}

	void display()
	{

		for(int i=0;i<length;i++)
		{
			cout<<contents[i]<<" ";
		}
	}


	

};

int main(){
Vector v;
cout<<v.capacityOf()<<" ";
 v.push_back(1);
v.push_back(1);
v.push_back(1);
v.push_back(1);
v.push_back(1);
v.push_back(1);
v.push_back(1);
v.push_back(1);
v.push_back(1);
v.pop_back();
v.pop_back();
v.pop_back();
v.pop_back();
v.pop_back();
v.pop_back();

//v.push_back(1);
cout<<v.capacityOf();
cout<<" "<<v.size();




return 0;
}
