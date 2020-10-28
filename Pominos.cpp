#include<bits/stdc++.h>
using namespace std;
const string sizes[] = {"Regular", "Medium" , "Large"};
const string crusts[] = {"New Hand Tossed" , "Fresh Pan" , "Cheese Burst", "Wheat Thin Crust"};
const string veg_pizza_options[] = {"Margherita" , "Double Cheese Margherita" , "Farm House" , "Peppy Paneer" , "Mexican Green Wave",
					"Deluxe Veggie"	, "Veg Extravaganza" , "CHEESE N CORN"};
const string nonveg_pizza_options[] = { "PEPPER BARBECUE CHICKEN" , "CHICKEN SAUSAGE" , "Chicken Golden Delight",
	"Non Veg Supreme" , "Chicken Dominator" , "PEPPER BARBECUE & ONION" , "CHICKEN FIESTA" , "Indi Chicken Tikka"}; 
class Pizza {
	private:
		static int order;
		long int order_time;
		int order_burst_time;
		int pizza_size;
		int pizza_crust;
		int pizza_option;
		int order_number;
		bool cancelled;
		int unique_key;
	public:
		void get_remaining_time()
		{
			if(!cancelled)
			{
				long int now = time(0);
				if(now - order_time >= this->order_burst_time) cout<<"Your pizza is ready .. Please collect your pizza from the counter.."<<endl;
				else cout<<" Remaining time is : "<< (this->order_burst_time + order_time - now)/ 60<<" minutes"<<endl;
			}
			else cout<<" Order cancelled already :-( "<<endl;
		}
		Pizza(int p_size , int p_crust, int veg,int option) : pizza_size(p_size) , pizza_crust(p_crust) , pizza_option(option){
			order++;
			order_number = order;
			order_time = time(0);
			order_burst_time = (rand() % 25 + 20) * 60;
			cancelled = false;
			unique_key = rand();
			cout<<"Your order number : "<<order_number<<endl;
			cout<<"Your unique key : "<<unique_key<<endl;
			cout<<"Your pizza choice : ";
			if(veg==1) cout<<veg_pizza_options[pizza_option-1]<<endl;
			else cout<<nonveg_pizza_options[pizza_option-1]<<endl;
			cout<<"Estimated time : "<<order_burst_time / 60<<endl;
		}
		void cancel_order()
		{
			long int now = time(0);
			long int remtime = order_time + order_burst_time - now ; 
			if(remtime / 60 <= 10)
			{
				cout<<"Sorry Sir/Ma\'am , since your pizza is almost ready it can\'t be cancelled now"<<endl;
			}
			else
			{
				cancelled = true;
				cout<<"Order cancelled successfully.. We hope to serve you soon..";
			}
		}
		~Pizza()
		{
			cout<<this->pizza_option<<" destroyed"<<endl;
		}
		friend bool isvalidorder(int,int,vector<Pizza*> &);
};

int Pizza::order = 0;
bool isvalidorder(int ono , int ukey , vector<Pizza*> &orders)
{
	if(ono > orders.size()) return false;
	if(orders[ono-1]->unique_key != ukey) return false;
	return true;
}
void print_options()
{
	cout<<endl<<endl;
	cout<<" 1. New Pizza Order\n 2. Enquire Pizza remaining time\n 3. Cancel Order\n 4. Exit store\n";
}
int main()
{
	vector<Pizza *> orders;
	Pizza *newpizza;
	system("Color 70");
	cout<<endl<<endl;
	for(int i=0 ; i<=210  ; i++) cout<<"=";
	cout<<endl;
	for(int i=0;i<90;i++) cout<<" ";
	cout<<"Welcome to POMINO\'S"<<endl<<endl;
	for(int i=0 ; i<=210  ; i++) cout<<"=";
	cout<<endl;
	while(1)
	{	
		print_options();
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Select size: \n 1. Regular\n 2. Medium \n 3. Large\n";
				int size;
				cin>>size;
				cout<<"Select crust :\n 1. New Hand Tossed\n 2. Fresh Pan\n 3. Cheese Burst\n 4. Wheat Thin Crust\n";
				int crust;
				cin>>crust;
				int option , veg;
				cout<<"Choose your pizza :\n 1. Veg options \n 2. Non veg options"<<endl;
				cin>>veg;
				if(veg==1) 
				{
					cout<<"Veg pizza menu : "<<endl;
					for(int i=0;i<8;i++)
						cout<<""<<i+1<<". "<<veg_pizza_options[i]<<endl;
				}
				else if(veg==2)
				{
					cout<<"Non-Veg pizza menu : "<<endl;
					for(int i=0;i<8;i++)
						cout<<""<<i+1<<". "<<nonveg_pizza_options[i]<<endl;
				}
				else
				{
					cout<<"Invalid choice .. "<<endl;
					break;
				}
				cin>>option;
				if(size <1 || size > 3 || crust < 1 || crust > 4 || option < 1 || option > 8)
				{
					cout<<"Please choose valid options"<<endl;
					break;
				}
				newpizza = new Pizza(size,crust,veg,option);
				orders.push_back(newpizza);
				break;
			case 2:
				cout<<"Enter your order number"<<endl;
				int ono , ukey;
				cin>>ono;
				cout<<"Enter your unique key\n";
				cin>>ukey;
				if(isvalidorder(ono,ukey,orders))
					orders[ono-1]->get_remaining_time();
				else
				{
					cout<<"Invalid order credentials.."<<endl;
				}
				break;
			case 3:
				cout<<"Enter your order number"<<endl;
				cin>>ono;
				cout<<"Enter your unique key\n";
				cin>>ukey;
				if(isvalidorder(ono,ukey,orders))
					orders[ono-1]->cancel_order();
				else
				{
					cout<<"Invalid order credentials.."<<endl;
				}
				break;
			case 4:
				for(int i=0;i<(int) orders.size() ;i++) delete orders[i];
				return 0; 
			default:
				cout<<"Invalid selection"<<endl;
		}
	}
	return 0;
}
