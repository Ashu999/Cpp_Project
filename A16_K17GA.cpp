//project

#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <limits>
using namespace std;

class item_g
{
protected:
    char iname[20];
    int inumber;
    float iprice;
    int iquant;
    float itaxcent;
    float inet_1;
    float inet;
    struct date
    {
        int dd,mm,yy;
    }mfdate;

public:
    static int counter;
   // static int total;
    void get_inumber(int inum)
    {
        inumber = inum;
    }
    void get_iname()
    {
        cout<<endl<<"Enter the Name of item :";
        cin>>iname;
    }
    void get_mfd()
    {
        cout<<endl<<"Enter the Manufacturing date(dd-mm-yy) :";
        cin>>mfdate.dd>>mfdate.mm>>mfdate.yy;
    }
    void get_iprice()
    {
        cout<<endl<<"Enter the Price of item :";
        cin>>iprice;
    }
    void get_iquant()
    {
        cout<<endl<<"Enter the quantity of item :";
        cin>>iquant;
    }
    void get_itaxcent()
    {
        cout<<endl<<"Enter the Tax percentage :";
        cin>>itaxcent;
    }
    void cal_inet_1()
    {
        inet_1=(iprice+(iprice*(itaxcent/100)));                //for each item
    }
    void cal_inet()
    {
        inet=iquant*(iprice+(iprice*(itaxcent/100)));      //for n items of same type
    }
    static void keep_count(int c)                          //static member function
    {
        counter = c;
    }
};

class item_s : public item_g
{
    public:
    void show_inumber()
    {
        cout<<endl<<"Item no. :"<<inumber;
    }
    void show_iname()
    {
        cout<<endl<<"Name of item :"<<iname;
    }
    void show_mfd()
    {
        cout<<endl<<"Manufacturing date(dd-mm-yy) :"<<mfdate.dd<<"-"<<mfdate.mm<<"-"<<mfdate.yy;
    }
    void show_iprice()
    {
        cout<<endl<<"Price :"<<iprice<<"Rs.";
    }
    void show_iquant()
    {
        cout<<endl<<"Quantity :"<<iquant;
    }
    void show_itaxcent()
    {
        cout<<endl<<"Tax percentage :"<<itaxcent<<"%";
    }
    void show_inet_1()
    {
        cout<<endl<<"Net price :"<<inet_1<<"Rs.";
    }
    void show_inet()
    {
        cout<<endl<<"Net price :"<<inet<<"Rs.";
    }
    int send_inet()                                   //total = total + (p+i)->inet;
    {
        return inet;
    }

    void show_all_header()
    {
        cout<<endl<<"Item No."<<"  "<<"Name"<<"  "<<"Date of Mfg"<<"  "<<"Price"<<"  "<<"Tax Percentage"<<"  "<<"Net Price";
    }

    void show_all()
    {
        cout<<"  "<<inumber<<"        "<<iname<<"    "<<mfdate.dd<<"-"<<mfdate.mm<<"-"<<mfdate.yy<<"      "<<iprice<<"       "<<itaxcent<<"             "<<inet_1;
    }

    void show_single()
    {
        cout<<endl<<endl<<"       Item No. :"<<inumber;
        cout<<endl<<endl<<"       Name :"<<iname;
        cout<<endl<<endl<<"       Date of Mfg :"<<mfdate.dd<<"-"<<mfdate.mm<<"-"<<mfdate.yy;
        cout<<endl<<endl<<"       Price :"<<iprice<<"Rs.";
        cout<<endl<<endl<<"       Applied Tax (%) :"<<itaxcent<<"%";
    }

};

int item_g::counter=0;    //static data member.
//int item_g::total;

int main()
{
    item_s *ptr, *ptr2;
    int x=0,i;
    int i_no,z, total=0;
    ifstream fob_read;
    ofstream fob_write;
    ifstream counter_get;
    ofstream counter_store;

home:                           //get counter
    counter_get.open("counter.txt");
    counter_get>>x;
    counter_get>>item_g::counter;
    counter_get.close();

   ptr2 = ptr = new item_s[x];

    fob_read.open("data.dat");
    for(i=0;i<x;i++)          //to read
    {
        fob_read.read((char*)(ptr+i),sizeof(item_s));
    }
    fob_read.close();

    int choice;

    system("cls");
    cout<<"            ################ Super Market Billing ################"<<endl;
    cout<<"                             --------------------                "<<endl<<endl;
    cout<<"                          1. Bill Report"<<endl<<endl;
    cout<<"                          2. Add, Remove or Edit items"<<endl<<endl;
    cout<<"                          3. Show item details"<<endl<<endl;
    cout<<"                          4. Exit"<<endl<<endl;
    cout<<"                          Enter your choice: ";
    cin>>choice;
                                                                       //limit header
while(cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    goto home;
}
    switch(choice)
    {
        case 1:
        system("cls");
        if(x==0)
    {
        cout<<"No data file found";
        getch();
        goto home;
    }
    else
    {

        cout<<"            ################ Billing Details ################"<<endl<<endl;

        ptr -> show_all_header();
        fob_read.open("data.dat");
    for(i=0;i<x;i++)                              //to read
    {
        fob_read.read((char*)(ptr+i),sizeof(item_s));
    }
    fob_read.close();

    for(i=0;i<x;i++)                 //setting up net price for each item
    {
        (ptr+i) -> cal_inet_1();
    }

    for(i=0;i<x;i++)               //to print
    {
        cout<<endl;
        (ptr+i) -> show_all();
        cout<<endl<<endl;
    }

cout<<endl<<"      Press 7 to add items to cart";
cout<<endl<<endl<<"      Press any other key to go back";
cout<<endl<<endl<<"   Your Choice: ";
cin>>z;
if(z==7)
    {
        more:
bk4:
        cout<<endl<<"      Enter the item no.: ";
    cin>>i_no;
    i_no=i_no-1;

    if(!(i_no >= 0 && i_no < x))      //out of bounds check
     {
         cout<<"Out of Bounds";
         getch();
         goto bk4;
     }

    cout<<endl;
    (ptr+i_no) -> get_iquant();
    (ptr+i_no) -> cal_inet();
    total = total + (ptr+i_no) -> send_inet();
    cout<<endl<<endl<<"    Press 7 to add more items ELSE Any other no. to Get Total";
    cout<<endl<<endl<<"        Your Choice:";
    cin>>z;
    if(z==7)
    {
        goto more;
    }
    else
    {
        cout<<endl<<endl<<"                        Price to pay = "<<total<<" Rs."<<endl;
        cout<<endl<<endl<<"                    press any key to go back: ";
        getch();
        goto home;
    }
    }
else if(z!=7)
{
 goto home;
}
    }

break;
        case 2:

    system("cls");
    cout<<"            ################ Add Edit Delete ################"<<endl;
    cout<<"                           ------------------                "<<endl<<endl;
    cout<<"                          1. Add Item(s)"<<endl<<endl;
    cout<<"                          2. Edit Item Details"<<endl<<endl;
    cout<<"                          3. Delete Item"<<endl<<endl;
    cout<<"                          0. Go back"<<endl<<endl;
    cout<<"                          Enter your choice: ";

cin>>choice;
        switch(choice)
        {
    case 0:
        {
            system("cls");
            goto home;
        }
break;

    case 1:
        {
            system("cls");

    fob_read.open("data.dat");
    if(!fob_read)
    {
        cout<<"            ################ Add Item(s) ################"<<endl<<endl;

    cout<<endl<<"      Enter the no. of items you want to add: ";
    cin>>x;
    ptr = new item_s[x];

    for(i=0;i<x;i++)              //to get
    {
        cout<<endl<<endl<<"        Enter data for item "<<i+1<<endl;
        cout<<"----------------------------------------------"<<endl;
        (ptr+i) -> get_inumber(i+1);
        (ptr+i) -> get_iname();
        (ptr+i) -> get_mfd();
        (ptr+i) -> get_iprice();
        (ptr+i) -> get_itaxcent();
        cout<<endl;
    }

        fob_write.open("data.dat");
    for(i=0;i<x;i++)                //to write
    {
        fob_write.write((char*)(ptr+i),sizeof(item_s));
    }
    fob_write.close();
                                              //position count
    item_g::keep_count(i);
                                               //store counter
    counter_store.open("counter.txt");
    counter_store<<item_g::counter;
    counter_store.close();
    }
    else
    {
                //get counter
    counter_get.open("counter.txt");
    counter_get>>item_g::counter;
    counter_get>>x;
    counter_get.close();

        fob_read.open("data.dat");
    for(i=0;i<x;i++)                  //to read
    {
        fob_read.read((char*)(ptr+i),sizeof(item_s));
    }
    fob_read.close();

    for(i=0;i<x;i++)                   //here
    {
         *(ptr2+i) = *(ptr+i);
    }

x=0;
    cout<<"            ################ Add Item(s) ################"<<endl<<endl;
    cout<<endl<<endl<<"      Enter the no. of items you want to add: ";
    cin>>x;
    x = x + item_g::counter;
    ptr = new item_s[x];   //old size + new size

     for(i=0; i<item_g::counter ;i++)               //here2
     {
      *(ptr+i) = *(ptr2+i);
     }
  ptr2 = new item_s[x];
    for(i==(item_g::counter);i<(x);i++)    //to get
    {
        cout<<endl<<endl<<"        Enter data for item "<<i+1<<endl;
        cout<<"----------------------------------------------"<<endl;
        (ptr+i) -> get_inumber(i+1);
        (ptr+i) -> get_iname();
        (ptr+i) -> get_mfd();
        (ptr+i) -> get_iprice();
        (ptr+i) -> get_itaxcent();
        cout<<endl;
    }
    fob_write.open("data.dat");
    for(int i=0;i<x;i++)    //to write
    {
        fob_write.write((char*)(ptr+i),sizeof(item_s));
    }
    fob_write.close();
    }
    item_g::counter = x;   //updating counter
    counter_store.open("counter.txt");
    counter_store<<item_g::counter;
    counter_store.close();

            cout<<endl<<endl<<"Item(s) Added Successfully.";
            cout<<endl<<endl<<"Press any key to go back..";
            getch();
            goto home;
        }
break;

    case 2:
        {    //editing
            system("cls");
if(x==0)
    {
        cout<<"No data file found";
    }
    else
    {
        cout<<"            ################ Edit Item ################"<<endl<<endl;
        int ed_no;
bk3:
        cout<<endl<<"    Enter the Item no. that you want to edit: ";
    cin>>ed_no;
        ed_no = ed_no-1;   //position

        if(!(ed_no >= 0 && ed_no < x))      //out of bounds check
     {
         cout<<"Out of Bounds";
         getch();
         goto bk3;
     }


    fob_read.seekg(0);
    fob_read.open("data.dat");  //to read
    for(i=0;i<x;i++)
    {
        fob_read.read((char*)(ptr+i),sizeof(item_s));
    }
    fob_read.close();

    (ptr+ed_no) -> get_inumber(ed_no+1);
    (ptr+ed_no) -> get_iname();
    (ptr+ed_no) -> get_mfd();
    (ptr+ed_no) -> get_iprice();
    (ptr+ed_no) -> get_itaxcent();

    fob_write.open("data.dat");
    for(i=0;i<x;i++)                //to write
    {
        fob_write.write((char*)(ptr+i),sizeof(item_s));
    }
    fob_write.close();
    cout<<endl<<endl<<"Item Edited Successfully.";
    }

            cout<<endl<<endl<<"Press any key to go back..";
            getch();
            goto home;
        }
break;
    case 3:
        {  //delete
            system("cls");
if(x==0)
    {
        cout<<"No data file found";
    }
    else
    {
        cout<<"            ################ Delete Item ################"<<endl<<endl;
            fob_read.open("data.dat");
    for(int i=0;i<x;i++)                  //to read
    {
        fob_read.read((char*)(ptr+i),sizeof(item_s));
    }
    fob_read.close();

    int del_no;
bk2:
        cout<<endl<<"   Enter the Item no. to Delete it :";
    cin>>del_no;
    del_no=del_no-1;     //position

    if(!(del_no >= 0 && del_no < x))      //out of bounds check
     {
         cout<<"Out of Bounds";
         getch();
         goto bk2;
     }


    *(ptr+del_no) = *(ptr+(x-1));
    (ptr+del_no)-> get_inumber(del_no+1);

    fob_write.open("data.dat");
    for(int i=0;i<(x-1);i++)           //to write
    {
        fob_write.write((char*)(ptr+i),sizeof(item_s));
    }
    fob_write.close();

    counter_get.open("counter.txt");          //updating counter
    counter_get>>item_g::counter;
    counter_get.close();
    item_g::counter = item_g::counter - 1;
    counter_store.open("counter.txt");
    counter_store<<item_g::counter;
    counter_store.close();


            cout<<endl<<endl<<"Item Deleted Successfully.";
    }
            cout<<endl<<endl<<"Press any key to go back..";
            getch();
            goto home;
        }
break;
    default:
        {
            system("cls");
            goto home;
        }

    }

break;
    case 3:
        {  //details
            system("cls");

            fob_read.open("data.dat");
if(x==0)
    {
        cout<<"No data file found";
    }
    else
    {
        cout<<"            ################ Item Details ################"<<endl<<endl;
        int  dtail_no;
bk1:
         cout<<endl<<"       Enter the Item no. to get it's details: ";
     cin>>dtail_no;
     dtail_no = dtail_no - 1;    //position

     if(!(dtail_no >= 0 && dtail_no < x))      //out of bounds check
     {
         cout<<"Out of Bounds";
         getch();
         goto bk1;
     }

     fob_read.open("data.dat");
    for(i=0;i<x;i++)    //to read
    {
        fob_read.read((char*)(ptr+i),sizeof(item_s));
    }
    fob_read.close();
    cout<<endl;
    (ptr+dtail_no) -> show_single();
    }


    cout<<endl<<endl<<"Press any key to go back..";
    getch();
    goto home;
        }
break;
    case 4:
        {
            delete ptr,ptr2;
            cout<<endl<<"                        Exiting..";
            getch();
            return 0;
        }
    default:
        {
            goto home;
        }
}
    getch();
}
