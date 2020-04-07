#include<iostream>
#include <math.h>
using namespace std;



void enqueue (string name, int AT, int BT);
void dequeue ();
void bubbleSort ();       //Sort according to burst time
int findMaxArrivalTime (); //if you want to see when was the last complaint was filed?
void SJF ();         //Driver method to take input from user
void display ();      //Show complete records
void action ();          //Perfrom Shortest Job First
int counte ();       //Count total no of complaint in the system
int findMinArrivalTime ();
int sumOfBurstTimes ();
void bubbleSortArrival ();
void findTurnAroundTime ();
void findWaitingTime ();
void findCompletionTime();
void roundRobinAction();
int findBurstTime(int c);
void Sort ();
void sjf();
void roundRobin();



struct Node
{
    string processName;  //Name of customer
    int arrivalTime;     //When complaint was arrived
    int burstTime;       //When complaint agent will be assigned to complaint
    int completionTime; //When complaint WILL BE COMPLETED
    int waitingTime; //how much more time  is required till complaint completionTime
    int turnAroundTime;// Amount of required to fulfill the request
    Node *next;

};



Node *front;
Node *rear;
Node *temp=NULL;




int main(){
    int choice;
    cout<<"\t***COMPLAINT MANAGER***\n";
    cout<<"1.register complaint\n"<<"0.Exit\n";
    cin>>choice;

    if(choice==1){
        int justToRunLoop = 335;   //0 to exit
        while (justToRunLoop!=0){
            /* code */

            string name;
            int arrival, burst,x;


            cout << "\nenter customer name " << endl;
            cin >> name;
            cout << "Time when complaint was filed \n";
            cin >> arrival;
            cout<< "\nwhich service is causing problem?\n1.phone\n2.TV\n3.Internet\n";
            cin>>x;
            burst=findBurstTime(x);
            enqueue (name, arrival, burst);
            cout << "\nDo you want to insert another record?";
            cin >> justToRunLoop;
        }
    }

    if(choice==0){
        cout<<"thank you.";
    }
    int sch=0;
    cout<<"\nWhich Scheduler would you like to use?\n1.Round Robin\t2.Shortest job First\n";
    cin>>sch;
    if(sch==1){
        roundRobin();
    }
    else if(sch==2){
        sjf();
    }




}

void sjf()
{
    Sort ();
    cout << "\nsorted\n";
    findWaitingTime ();
    findTurnAroundTime();
    findCompletionTime();
    display();
    action();

}

void roundRobin(){
    Sort();
    cout << "\nsorted\n";
    findTurnAroundTime();
    findWaitingTime ();
    findCompletionTime();
    display();
    roundRobinAction();
    
}

void enqueue (string name, int AT, int BT)
{
    struct Node *newNode = new Node;
    newNode->processName = name;
    newNode->arrivalTime = AT;

    newNode->burstTime = BT;
    newNode->next = NULL;


    if (front==NULL)
    {
        front = newNode;
        rear = front;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

void bubbleSort(){
    struct Node *i, *j;
    for (i=front; i->next!=front; i = i->next)
    {
        for (j = i; j->next != front; j = j->next)
        {
            Node *k=j->next;
            if (k->burstTime < j->burstTime)
            {
                if(j==front){
                    front=k;
                    temp=k->next;
                    k->next=j;
                    j->next=temp;
                }

                else{
                    temp=k->next;
                    k->next=j;
                    j->next=temp;

                }
            }
        }
    }
}

void
Sort ()
{
    struct Node *i, *j;
    Node *temp;
    for (i = front; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->burstTime > j->burstTime)
            {
                temp = i;
                i = j;
                j = temp;
            }
        }
    }
}


void action ()
{


    //int lims=findMaxArrivalTime();
    //int i=0;
    Node *temp, *i, *j;
    for (temp = front; temp != NULL; temp = temp->next)
    {
        if (temp->burstTime < temp->next->burstTime)
            dequeue ();
        else if (temp->burstTime == temp->next->burstTime)
        {
            if (temp->arrivalTime < temp->next->arrivalTime)
                dequeue ();
            else if (temp->arrivalTime > temp->next->arrivalTime)
            {
                i = temp;
                temp = i->next;
                i->next = i;
            }

        }
        dequeue ();
        display();
    }

}

void
display ()
{

    cout<<"\nCustomer Name\t";
    cout<<" ArrivalTime\tAssignment Time\tCompeletion Time\tWaiting Time\tRequired Time\n\n";
    struct Node *temp;
    for (temp = front; temp != NULL; temp = temp->next)

        cout<<temp->processName<<"\t\t"<<temp->arrivalTime<<"\t\t"<<temp->burstTime<<"\t\t"<<temp->completionTime<<"\t\t\t"<<temp->waitingTime<<"\t\t\t"<<temp->turnAroundTime<<endl;



}

void
dequeue ()
{

    Node *newNode;
    newNode = front;
    if (front == NULL)
        cout << "\n No complaint exists in system\n";
    else
    {
        cout << "\n Customer " << newNode->processName;
        cout<< "  complaint has been  executed\n";
        front = front->next;
        delete newNode;

    }
}


void
bubbleSortArrival ()
{
    struct Node *i, *j;
    Node *temp;
    for (i = front; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (i->arrivalTime > j->arrivalTime)
            {
                temp = i;
                i = j;
                j = temp;
            }
        }
    }


}

int
findMaxArrivalTime ()
{
    Node *temp;
    int max = 0;
    for (temp = front; temp != NULL; temp = temp->next)
    {
        if (temp->arrivalTime > max)
            max = temp->arrivalTime;
    }
    return max;
}

int
findMinArrivalTime ()
{
    Node *temp;
    int min = 0;
    for (temp = front; temp != NULL; temp = temp->next)
    {
        if (temp->arrivalTime < min)
            min = temp->arrivalTime;
    }
    return min;
}

int
sumOfBurstTimes ()
{
    Node *temp;
    int r = 0;
    for (temp = front; temp != NULL; temp = temp->next)
        r = r + temp->burstTime;
    return r;


}


int
counte ()
{
    Node *temp;
    int c = 0;
    for (temp = front; temp != NULL; temp = temp->next)
        c++;
    return c;

}


void findWaitingTime ()
{



    int i = 0;
    //Node *temp = front;
    Node *tt = front;

    int c = counte ();

    tt->waitingTime = 0;

    while (i != c-1)
    {

        tt->next->waitingTime = abs(tt->burstTime - tt->waitingTime);
        i++;
        tt = tt->next;

    }

}



void
findTurnAroundTime ()
{

    int i = 0;
    Node *temp = front;
    int c = counte ();

    i++;
    while (i != c)
    {
        temp->turnAroundTime=abs(temp->burstTime+temp->waitingTime);

        i++;
        temp = temp->next;

    }
}




void findCompletionTime()
{
    int i = 0;
    Node *temp = front;
    int c = counte();
    while(i!=c)
    {
        temp->completionTime =abs( temp->turnAroundTime + temp->arrivalTime);
        i++;
        temp=temp->next;
    }

}

void roundRobinAction(){
    Node *temp = NULL;
    for (temp = front; temp != NULL; temp = temp->next){
        if(temp->burstTime > 2){
            temp->burstTime -= 2;
            temp->completionTime += 2;
        }
        else{
            dequeue();
        }
    }
    cout<<"There are no Complaints Remaining in the System.\n";
}

int findBurstTime(int c){
    string complaints[3]={"phone","tv","internet"};
    int complaint_BT[3]={5,10,15};
    return complaint_BT[c-1];

}
