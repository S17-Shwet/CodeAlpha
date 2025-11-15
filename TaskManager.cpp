#include<iostream>
#include<vector>
#include<fstream>
#include<string>


using  namespace std;

//class representing a Task

class Task
{
	public:
		string title;
		string category;
		bool isCompleted;
		
//	Constructor
Task(string t,string c,bool completed=false)
{
	title=t;
	category=c;
	isCompleted=false;
}
};

// task manager class that handles all functionalities
class TaskManager
{
	private:
		vector<Task> tasks;
		string filename="tasks.txt";
		
	public:
    //load tasks from file when program starts
    
    void loadFromFile()
    {
    	ifstream inFile(filename);
    	
    	if(inFile)
    	{
    		cout<<"No previous task file found.Starting fresh.\n";
		    return;
		}
		tasks.clear();
		
		string title,category;
		bool completed;
		
		while(inFile >> ws && getline(inFile,title))
		{
			getline(inFile,category);
			inFile>> completed;
			inFile.ignore();//ignore new line
			tasks.push_back(Task(title,category,completed));
			
		}
		inFile.close();
		
	}


void saveToFile()
{
	ofstream outFile(filename);
	for(auto &task: tasks)
	{
		outFile<<task.title<<"\n"<<task.category<<"\n"<<task.isCompleted<<"\n";
	}
	outFile.close();
}

//+ Add a new task
void addTask()
{
	string title,category;
	cout<<"Enter task title: ";
	getline(cin>> ws,title);
	cout<<"Enter task category (e.g., Work, Study, Personal):";
	getline(cin, category);
	
	tasks.push_back(Task(title,category));
	cout<< "Task added successfully !\n";
}

void markCompleted()
{
	viewPendingTasks();
	int index;
	cout<<"Enter the task number to mark as completed: ";
	cin>>index;
	
	if(index < 1 || index > (int)tasks.size())
	{
		cout<<"Invalid task number!\n";
		return;
	}
	//convert index to 0 based
	tasks[index-1].isCompleted=true;
	cout<<"Task marked as completed!\n";

}
	
//	view all tasks (pending+completed)

void viewAllTasks()
{
	if(tasks.empty())
	{
		cout<<"No tasks available.\n";
		return;
	}
	cout<<"\n All Tasks:\n";
	for(int i=0;i<(int)tasks.size();++i)
	{
		cout<<i + 1<<". "<<tasks[i].title<<" ["<<tasks[i].category<<"] - "<<(tasks[i].isCompleted ? "Completed" : "Pending ")<<endl;
		
	}
}
//view only pending tasks

void viewPendingTasks()
{
	cout<<"\n Pending Tasks:\n";
	bool found=false;
	for(int i=0;i<(int)tasks.size();++i)
	{
		if(!tasks[i].isCompleted)
		{
			cout<< i + 1 << ". "<<tasks[i].title<<" [" << tasks[i].category << "]\n";
			found=true;
		}
	}
	
	if(!found) cout<<"No pending tasks!\n";
}

//view only completed tasks
void viewCompletedTasks()
{
	cout<<"\n Completed Tasks: \n";
	bool found=false;
	for(int i=0;i<(int)tasks.size();i++)
	{
		if(tasks[i].isCompleted)
		{
			cout<< i + 1<<". "<<tasks[i].title<<" ["<<tasks[i].category<< "]\n";
			found=true;
		}
	}
	if(!found) cout<<"No completed tasks yet!\n";
}

};


int main()
{
	TaskManager manager;
	
	manager.loadFromFile();
	
	int choice;
	
	do{
		cout<<"\n=== TASK MANAGER MENU ===\n";
		cout<<"1. Add Task\n";
		cout<<"2. Mark Task as Completed\n";
		cout<<"3. View All Tasks\n";
		cout<<"4. View Pending Tasks\n";
		cout<<"5. View Complted Tasks\n";
		cout<<"6. Exit\n";
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		
		switch(choice)
		{
			case 1: manager.addTask();break;
			case 2: manager.markCompleted();break;
			case 3: manager.viewAllTasks();break;
			case 4: manager.viewPendingTasks();break;
			case 5: manager.viewCompletedTasks();break;
			case 6: 
			     manager.saveToFile();
			     cout<<"Tasks saved. Exiting...\n";
			     break;
			   default:
			     cout<<"Invalid choice! Tryagain.\n";  
			
		}
	}
	while(choice != 6);
	
	return 0;
}










