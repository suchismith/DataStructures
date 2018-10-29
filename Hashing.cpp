#include<bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <string>
#include <typeindex>
#include <typeinfo>
using namespace std;
int sieve[1000100];


template <typename K, typename V>

class MapNode
{
 private:
   K  key;
   V value;
   MapNode<K,V> *next;
   
 public:
   MapNode(K key,V value)
   {
       this->key = key;
       this->value = value;
       this->next = NULL;
   }
   K getKey() const
   {

       return key;
   }
   V getValue() const
   {
       return value;
   }
   void setValue(V value)
   {
       this->value = value;
   }
   MapNode *getNext() const
   {
       return next;
   }
   void setNext(MapNode *next)
   {
       
       this->next = next;
   }

};

template <typename K, typename V>

class HashTable
{
 private:
    int current_size;
    int table_size;
    MapNode<K, V> **bucket;

 public:
   HashTable(int table_size)
   {
       generateSieve();
       current_size = 0;
       this->table_size = table_size;
       bucket = new MapNode<K, V> *[table_size];
       for(int i=0;i<table_size;i++)
       {
           bucket[i]=NULL;
       }
   }
    void generateSieve()
    {

        sieve[0]=0;
        sieve[1]=0;
       for(int i=2;i<10000;i++)
       {
           sieve[i]=1;
       }
        for(int i=2;i<10000;i++)
        {

            if(sieve[i]==1)
            {
                for(int j=i;i*j<10000;j++)
                {
                    //cout<<i*j<<"\n";
                    sieve[i*j]=0;
                }
            }
        }



    }

    int nextPrime(int k)
    {
        for(int i=k;i<1000000;i++)
        {
            if(sieve[i]==1)
            {
                return i;
            }
        }
        return -1;
    }

   void insertNode(MapNode<K, V> *node, MapNode<K, V> **new_bucket)
   {
       int hash_val=calculateHash(node->getKey());
       MapNode<K, V> *cur = new_bucket[hash_val];
       cout<<"new index"<<hash_val<<"\n";
       if (cur == NULL)
       {
        //    cout<<"inserted at new location"<<node->getKey()<<"\n";
            new_bucket[hash_val] = node;
       }
       else
       {
            // cout<<"inserted at new location after cchaining"<<node->getKey()<<"\n";
            node->setNext(cur);
            new_bucket[hash_val] = node;
       }




   }
    
    void deleteNode(K key)
    {
   
       int index = calculateHash(key);
       MapNode<K,V> *cur = bucket[index];
       cout<<"Delete Node"<<"\n";
       if (cur != NULL)
       {


           if(cur->getKey()==key)
            {

                if(cur->getNext()==NULL){
                    free(cur);
                    bucket[index]=NULL;
                   
                }
                else
                {
                    bucket[index]=cur->getNext();
                    free(cur);
                }
               
                 current_size-=1;
            }
            else
            {
                MapNode<K, V> *prev = cur;
                while (cur != NULL && cur->getKey() != key) 
                { 
                    prev = cur; 
                    cur = cur->getNext(); 
                } 
                if(cur==NULL)
                {
                     cout<<"Key not found";
                
                }
                 else
                 {
                     prev->setNext(cur->getNext());
                     current_size-=1;
                     free(cur);
                 }
            }
         } 
         else
         {
             cout<<"Key Not Found\n";
         }

    }


    void rehash()
    {

        MapNode<K, V> **newbucket;
        int oldsize=table_size;
        table_size*=2;
        table_size=nextPrime(table_size);
        newbucket=new MapNode<K, V> *[table_size];

        for(int i=0;i<table_size;i++)
        {      
            newbucket[i]=NULL;
        }

        for(int i=0;i<oldsize;i++)
        {
            cout<<i<<"\n";
            if(bucket[i]!=NULL)
            {  
               // cout<<"here"<<"\n";
               int index;
               MapNode<K,V> *ptr=bucket[i]; 
                          
                while(ptr!=NULL)
                {
                 //  cout<<"inserting"<<ptr->getKey()<<"\n";
                   MapNode<K, V> *node=new MapNode<K,V>(ptr->getKey(),ptr->getValue());

                   insertNode(node,newbucket);
                   
                    ptr=ptr->getNext();
                   
                }

            }
        
        }

        bucket=newbucket;
}



   void insert(MapNode<K,V> *node)
   {
    
    //    cout<<"table size"<<table_size;
     int index=calculateHash(node->getKey());
   
     current_size+=1;
     int load=((double)current_size/(double)table_size)*100;
     if(!search(node->getKey())){
       if(bucket[index]==NULL) {
          
            bucket[index]=node;
          //  cout<<"inserted"<<bucket[index]->getKey()<<"index"<<index<<"\n";
       
       }
        else
        {
          
            
            MapNode<K,V> *ptr;
            ptr=bucket[index];
            node->setNext(ptr);
            bucket[index]=node;
             ptr=bucket[index];

        }

      }
    
     if(load>70.0)
     {
         // cout<<"overload"<<"\n";
          rehash();  
     }

   }  

   bool search(K value)
   {
        int index=calculateHash(value);

        if(bucket[index]!=NULL)
        {
            
            MapNode<K,V> *ptr;
            ptr=bucket[index];
           
            while(ptr!=NULL)
            {   
               if(ptr->getKey()==value)
                {
                    return true;
                }
                ptr=ptr->getNext();
            }
           
            
        }
      return false;
   }

    int calculateHash(K key)
    {

        string key1;
        //checking if type is integer 
        type_index _typ_info_native(typeid(key));
        if(strstr(_typ_info_native.name(),"i"))
        {

                std::stringstream ss;
                ss << key;
                key1 = ss.str();


        }
        else
        {
            key1=key;
        }

        long long sum=0;
        for(int i=0;i<key1.length();i++)
        {
            sum+=key1[i]*pow(37,i);

        }
           
            sum=sum%table_size;
            return sum;


    }


   int getCurrentSize()
   {
       return current_size;
   }
   void setCurrentSize(int c_size)
   {
       current_size = c_size;
   }
   int getTableSize()
   {
       return table_size;
   }
   void setTableSize(int table_size)
   {
       this->table_size = table_size;
   }
};
int main()
{
    
    MapNode<string,int> *m1=new MapNode<string,int>("amit",10);
    MapNode<string,int> *m2=new MapNode<string,int>("suchi",11);
     MapNode<string,int> *m3=new MapNode<string,int>("neeraj",12);
    
   HashTable<string,int> *table1=new HashTable<string,int>(4);
   table1->insert(m1);
   table1->insert(m3);
   table1->insert(m2);
   
   //new
    // MapNode<int,int> *m1=new MapNode<int,int>(12,12);
    // MapNode<int,int> *m2=new MapNode<int,int>(13,13);
    // MapNode<int,int> *m3=new MapNode<int,int>(14,14);
    //  MapNode<int,int> *m3=new MapNode<int,int>(13,14);
    //   MapNode<int,int> *m3=new MapNode<int,int>(12,14);
    //    MapNode<int,int> *m3=new MapNode<int,int>(12,14);
    //     MapNode<int,int> *m3=new MapNode<int,int>(12,14);

   

    
   
    //   cout<<table1->getTableSize()<<"\n";
    //  for(int i=12;i<25;i++)
    // {   
    //      table1->insert(new MapNode<int,int>(i,i+1));
        
    // }
    //  HashTable<int,int> *table1=new HashTable<int,int>(2);
    // for(int i=12;i<25;i++)
    // {   
    //      table1->insert(new MapNode<int,int>(i,i+1));
        
    // }
   // table1->insert(new MapNode<int,int>(19,20));



//     MapNode<int,int> *m1=new MapNode<int,int>(12,12);
//     MapNode<int,int> *m2=new MapNode<int,int>(13,13);
   
//     MapNode<int,int> *m4=new MapNode<int,int>(14,14);
//     table1->insert(m1);
//     table1->insert(m2);
  
//     table1->insert(m4);

//     if(!table1->search(13))
//     {
//         cout<<"not found";
//     }
//     else
//         cout<<"found";
//    table1->deleteNode(13);
//     if(!table1->search(13))
//     {
//         cout<<"not found";
//     }
//     else
//         cout<<"found";

     if(table1->search("suchi"))
        cout<<"found";
    else
     cout<<"not found";
    table1->deleteNode("rajat");
    if(table1->search("amit"))
        cout<<"found";
    else
     cout<<"not found";

return 0;



}