#include <bits/stdc++.h>
#include<fstream>
#include<windows.h>
using namespace std;
#define V 1000
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
int rGraph[V][V];
const int tprofessor=1000;
int professor=25;
int load=10;
const int tcourse=10000;
int course_section[tcourse]={0};
int course=11;

//vector<string> professors={"Pawan Upadhyay","Shikha Pandey","Jyoti","Suma Dawn","Tribhuwan K. Tewari","Taj Alam","Vivek Kumar Singh","Sherry Garg"
//,"Bharat Gupta","Shikha Jain","Nitish Andola","Hema N","Dhanalakshmi","Ankita Wadhwa","Amarjeet Kaur","Krishna Sundari","Garima Mathur"
//,"Ekta Bhatt","Rachana","Smriti Gaur","Sonam Chawla","Shazia","Sujata Mohanty","Neeraj Wadhwa","Chakresh Jain"};

map<string,int>m;
vector<vector<int>>total;
int limit =39;


int numP()
{
    ifstream indata;
    indata.open("noofprof.txt");
    if(!indata){
    cerr << "Error: file could not be opened" << endl;
    exit(1);
    }
    int n;
    indata>>n;
    indata.close();
    return n;
}
int numC(){
     ifstream indata2;
    indata2.open("noofcourses.txt");
    if(!indata2){
    cerr << "Error: file could not be opened" << endl;
    exit(1);
    }
    int n2;
    indata2>>n2;
    indata2.close();
    return n2;
}
void updateP()
{
    int n=numP();
    ofstream outdata;
    outdata.open("noofprof.txt");
    outdata<<n+1;
    outdata.close();

}
void updateC()
{
    int n2=numC();
    ofstream outdata2;
    outdata2.open("noofcourses.txt");
    outdata2<<n2+1;
    outdata2.close();
}



string printKey(map<string, int>& Map,int K)
{

    for (auto& it : Map) {
        if (it.second == K) {
            return it.first ;
        }
    }

}

vector<int> f (string profn)
{
    string s1=".txt";
    profn.append(s1);
    string filename(profn);
    ifstream input_file(filename);
    if(!input_file.is_open())
    {
        cout<<"can't";
    }
    string subj;
    int i=0;
    auto itr=m.begin();
    vector<int>v(course,0);
    while(getline(input_file,subj))
    {
        //SetConsoleTextAttribute(h,11);
       // cout<<" "<<subj<<endl;
      itr=m.find(subj);
      v[itr->second]=1;
    }
    input_file.close();
    return v;

}



bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < limit; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {

				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return false;
}

int fordFulkerson(int graph[V][V], int s, int t)
{
	int u, v;
	for (u = 0; u < limit; u++)
		for (v = 0; v < limit; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V];

	int max_flow = 0;
	while (bfs(rGraph, s, t, parent)) {
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}


void course_distribute(map<string,int>m)
{
    string filename("faculty.txt");
    ifstream input_file(filename);
    if(!input_file.is_open())
    {
        cout<<"err";
    }
    string pf;
    int i=0;
    while(getline(input_file,pf))
    {
        //cout<<" "<<pf<<endl;
        vector<int>v1=f(pf);
        total.push_back(v1);
        int sum=0;
        int last_index=-1;

        for(int j=0;j<course;j++)
        {

            sum+=v1[j];
            if(v1[j]==1)
            {
                last_index=j;
            }
        }
        for(int j=0;j<course;j++)
        {
            int s=0;
            if(v1[j]==1)
            {

                course_section[j]+=(load/sum);
                s+=load/sum;
                if(j==last_index)
                {
                    course_section[j]+=(load-s);
                }

            }
        }
    }
    cout<<"\n\tNumber of course sections per subject:"<<endl;
    SetConsoleTextAttribute(h,13);

    int n=0;
    for(int i=0;i<course;i++) {
            string str= printKey(m,i);
        cout << '\t' << str << ":"<<setw(50-str.length()) << course_section[i]<< '\n';
    }
    cout << endl;
    input_file.close();

}
int graph[V][V]={0};
void graph_make()
{
    int p=0;
    for(int i=0;i<limit;i++)
    {
        if(p<professor)
        {
           graph[0][p+1]=load;
           p++;
        }
        else
        {
            break;
        }

    }
    int c=0;
    for(int i=0;i<limit;i++)
    {
        if(c<course)
        {
           graph[p+c+1][limit-1]=course_section[c];
           c++;
        }
        else
        {
            break;
        }
    }
    for(int i=1;i<limit-course-1;i++)
    {
        for(int j=professor+1;j<limit-1;j++)
        {
            if(total[i-1][j-professor-1]==1)
            {
                graph[i][j]=INT_MAX;
            }
        }

    }


}
int main()
{
    system("COLOR 09");

    const char *longString = R""""(

     _____                _                   __                 _     _           _                                  _
    /__   \___  __ _  ___| |__   ___ _ __    / /  ___   __ _  __| |   /_\  ___ ___(_) __ _ _ __  _ __ ___   ___ _ __ | |_
      / /\/ _ \/ _` |/ __| '_ \ / _ \ '__|  / /  / _ \ / _` |/ _` |  //_\\/ __/ __| |/ _` | '_ \| '_ ` _ \ / _ \ '_ \| __|
     / / |  __/ (_| | (__| | | |  __/ |    / /__| (_) | (_| | (_| | /  _  \__ \__ \ | (_| | | | | | | | | |  __/ | | | |_
     \/   \___|\__,_|\___|_| |_|\___|_|    \____/\___/ \__,_|\__,_| \_/ \_/___/___/_|\__, |_| |_|_| |_| |_|\___|_| |_|\__|
                                                                                     |___/

    )"""";
    cout<<longString;
    char y;
    cout<<" Do you want to add Professor info? (y/n): ";
    cin>>y;
    if(y=='y')
    {
        string pn,subject;
        cout<<" Enter Professor name:";
        cin>>pn;
        ofstream foutput;
        ifstream finput;
        finput.open ("faculty.txt");
        foutput.open ("faculty.txt",ios::app);
        if(finput.is_open())
           foutput<<endl<<pn;

           updateP();


        finput.close();
        foutput.close();
        string s2=".txt";
        pn.append(s2);
        string filename(pn);
        ofstream MyFile(filename);
        int ps;
        cout<<" Enter no. of preffered subjects: ";
        cin>>ps;
        cout<<" Enter subject :";
        string filename1("courses.txt");
            ifstream input_file(filename1);
            if(!input_file.is_open())
            {
                return EXIT_FAILURE;
            }
        string sub;
        for(int k=0;k<ps;k++)
        {   fflush(stdin);
            getline(cin,subject);
            MyFile <<subject<<endl;
            int f=0;
            while(getline(input_file,sub))
            {
                if(sub==subject)
                    {   input_file.close();
                        f=1;
                        break;}
            }
            input_file.close();
            if (f==0)
            {
                ofstream foutput1;
                ifstream finput1;
                finput1.open ("courses.txt");
                foutput1.open ("courses.txt",ios::app);
                if(finput1.is_open())
                   SetConsoleTextAttribute(h,11);
                   foutput1<<endl<<subject;
                   updateC();
                finput1.close();
                foutput1.close();
            }

        }
        MyFile.close();

    }
    limit=numP()+numC()+2;
    professor=numP();
    course=numC();
    string filename("courses.txt");
    ifstream input_file(filename);
    if(!input_file.is_open())
    {
        return EXIT_FAILURE;
    }
    string sub;
    int i=0;
    while(getline(input_file,sub))
    {
        m.insert(pair<string,int>(sub,i));
        i++;
    }

    map<string,int>::iterator itr;
    input_file.close();
    course_distribute(m);
	graph_make();
    cout<<"Professor-wise course allocation:"<<endl;
    int x=fordFulkerson(graph, 0, limit-1);

     string filename1("faculty.txt");
    ifstream input_file1(filename1);
    if(!input_file1.is_open())
    {
        return EXIT_FAILURE;
    }
    string proff;

     for(int i=1;i<limit-course-1;i++)
    {
        getline(input_file1,proff);
        SetConsoleTextAttribute(h,11);
        cout<<"Professor "<<proff<<endl;
        int count=1;
        for(int j=professor+1;j<limit-1;j++)
        { SetConsoleTextAttribute(h,10);
            if(graph[i][j]-rGraph[i][j]>0)
            {
                cout<<count++<<") Course "<<printKey(m,j-professor-1)<<" and No of sections :"<<graph[i][j]-rGraph[i][j]<<endl;
            }
        }
        cout<<endl;
    }
      input_file1.close();

	return 0;
}
