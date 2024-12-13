#include <iostream>
using namespace std;
struct Node{
    int data;
    Node*next;
    
    Node(int value){
        data=value;
        next=nullptr;
    }
};
int main()
{
    Node* head=new Node(10);
    Node* second=new Node(20);
    Node* third=new Node(30);
    
    head->next=second;
    second->next=third;
    
    Node* temp=head;
    while(temp!=nullptr)
    {
        cout<<"Values"<<temp->data<<" ->";
        temp=temp->next;
    }
    cout<<"nullptr"<<endl;

    return 0;
}