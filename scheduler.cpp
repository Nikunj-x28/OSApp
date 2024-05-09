#include<bits/stdc++.h>
using namespace std;
void gant_chart(map<pair<int,pair<int,int>>,int> &gc_helper){
        vector<string> gant_chart_prc;
        vector<string> gant_chart_time;
        for(auto &it:gc_helper){
            string x=to_string(it.first.first);
            if(x.size()==1) x="0"+x;
            string y=to_string(it.first.second.first);
            if(y.size()==1) y="0"+y;
            gant_chart_prc.push_back("|Process : "+to_string(it.first.second.second)+"|");
            gant_chart_time.push_back("|"+x+"         "+
            y+"|");
        }
        for(auto &it:gant_chart_time) cout<<it;
        cout<<"\n";
        for(auto &it:gant_chart_prc) cout<<it;
        cout<<"\n";
}
void cpu_performance(vector<int> &wait,vector<pair<int,int>> &v,int &idleTime,int &n){
        vector<int> turnaround;
        for (int i = 0; i <n; i++)
        {
            turnaround.push_back(wait[i]+v[i].second);
        }
        float sumwait=0,sumturn=0;
        for (int i = 0; i <n; i++)
        {
            sumwait+=wait[i];
            sumturn+=turnaround[i];
        }
        cout<<"Average wait time is "<<sumwait/n<<"\n";
        cout<<"Average turnaround time is "<<sumturn/n<<"\n";
        cout<<"Total CPU idle time is :"<<idleTime<<"\n";
        cout<<"------------------------------------------------------------------\n";
}
void fifo(){
        cout<<"------------------------------------------------------------------\n";
        cout<<"Enter the number of processes\n";
        int n; cin>>n;
        vector<pair<int,int>> v;
        vector<int> wait;
        cout<<"Enter the arrival times and burst times\n";
        cout<<"AT BT\n";
        for (int i = 0; i < n; i++)
        {
            int x,y;
            cin>>x>>y;
            v.push_back({x,y});
        }
        sort(v.begin(),v.end());
        cout<<"The processes will be referenced as follows\n";
        for(int i=0;i<n;i++){
            cout<<"Process :"<<i+1<<" AT="<<v[i].first<<" "<<" BT="<<v[i].second<<"\n";
        }
        cout<<"\n";
        wait.push_back(0);
        int idleTime=0;
        idleTime+=v[0].first;
        int time=v[0].first+v[0].second; // time tells at what moment cpu will be free again
        map<pair<int,pair<int,int>>,int> gc_helper;
        int start=v[0].first;
        for (int i = 1; i<n; i++)
        {
            if(v[i].first>=time){
                gc_helper[{start,{time,i}}]++;
                wait.push_back(0);
                idleTime+=v[i].first-time;
                start=v[i].first;
                time=v[i].second+v[i].first;
            }
            else{
                gc_helper[{start,{time,i}}]++;
                wait.push_back(time-v[i].first);
                start=time;
                time+=v[i].second;
            }
        }
        gc_helper[{start,{time,n}}]++;
        gant_chart(gc_helper);
        cpu_performance(wait,v,idleTime,n);
}
void sjf(){
   cout<<"Is the process preemptive? (Enter yes or no)\n";
   string ans;cin>>ans;
   for(auto &it:ans) it=tolower(it);
   if(ans=="yes"){
        cout<<"------------------------------------------------------------------\n";
        cout<<"Enter the number of processes\n";
        int n; cin>>n;
        vector<pair<int,int>> v;
        cout<<"Enter the arrival times and burst times\n";
        cout<<"AT BT\n";
        for (int i = 0; i < n; i++)
        {
            int x,y;
            cin>>x>>y;
            v.push_back({x,y});
        }
        sort(v.begin(),v.end());
        cout<<"The processes will be referenced as follows\n";
        for(int i=0;i<n;i++){
            cout<<"Process :"<<i+1<<" AT="<<v[i].first<<" "<<" BT="<<v[i].second<<"\n";
        }
        cout<<"\n";
        map<pair<int,pair<int,int>>,int> gc_helper;
        int idleTime =0;
        vector<int> wait(n,0);
        vector<int> burst;
        for(auto &q:v){
            burst.push_back(q.second);
        }
        int process=-1;
        int start=0;
        int finish=0;
        int time=0;
        while(finish<n)
        {  
            int smallestTime=INT_MAX;
            int next_process=-1;
            for (int j = 0; j<n ;j++)
            {
                if(v[j].first>time) break;
                else{
                    if(v[j].second==0) continue;
                    if(v[j].second<smallestTime){
                        smallestTime=v[j].second;
                        next_process=j;
                    }
                }
            }
            if(next_process!=-1){
                if(process==-1){
                    process=next_process;
                    start=time;
                }
                else{
                    if(process!=next_process){
                        gc_helper[{start,{time,process+1}}];
                        start=time;
                        process=next_process;
                    }
                }
                v[process].second--;
                for (int j = 0; j<v.size(); j++)
                {   if(j==process or v[j].second==0) continue;
                    if(v[j].first>time) break;
                    else{
                        wait[j]++;
                    }
                }
                if(v[process].second==0) {
                    finish++;
                    gc_helper[{start,{time+1,process+1}}];
                    process=-1;
                }
            }
            else{
                idleTime++;
            }  
            time++;   
        }
        for(int i=0;i<n;i++) v[i].second=burst[i];
        gant_chart(gc_helper);
        cpu_performance(wait,v,idleTime,n);
   }
   else if(ans=="no"){
        cout<<"------------------------------------------------------------------\n";
        cout<<"Enter the number of processes\n";
        int n;
        cin>>n;
        vector<pair<int,int>> v;
        cout<<"Enter the arrival times and burst times\n";
        cout<<"AT BT\n";
        for (int i = 0; i < n; i++)
        {
            int x,y;
            cin>>x>>y;
            v.push_back({x,y});
        }
        sort(v.begin(),v.end());
        cout<<"The processes will be referenced as follows\n";
        for(int i=0;i<n;i++){
            cout<<"Process :"<<i+1<<" AT="<<v[i].first<<" "<<" BT="<<v[i].second<<"\n";
        }
        cout<<"\n";
        int idleTime =0;
        vector<int> wait(n,0);
        int time=v[0].first+v[0].second;
        wait[0]=0;
        idleTime+=v[0].first;
        map<pair<int,pair<int,int>>,int> gc_helper;
        int start=v[0].first;
        vector<int> done(n,0);
        done[0]=1;
        int process=0;
        for (int i=1; i<n ; i++)
        {
            gc_helper[{start,{time,process+1}}]++;
            int jobTime=INT_MAX;
            bool found=false;
            for(int j=1;j<n;j++){
                if(!done[j]){
                    if(v[j].first<=time){
                        if(v[j].second<jobTime) {
                            jobTime=v[j].second;
                            process=j;
                            found=true;
                        }
                    }
                    else{
                        if(!found) process=j;
                        break;
                    }
                }
            }
            done[process]=1;
            if(v[process].first<=time){
                start=time;
                wait[process]=time-v[process].first;
                time+=v[process].second;
            }
            else{
                start=v[process].first;
                wait[process]=0;
                idleTime+=v[process].first-time;
                time=v[process].first+v[process].second;
            }
        }
        gc_helper[{start,{time,process+1}}]++;
        gant_chart(gc_helper);
        cpu_performance(wait,v,idleTime,n);
   }
   else{
    cout<<"You have entered a wrong input (exiting)\n";
   }
}
void priority(){
    cout<<"Is the process preemptive? (Enter yes or no)\n";
    string ans;cin>>ans;
    for(auto &it:ans) it=tolower(it);
    if(ans=="yes"){
        cout<<"------------------------------------------------------------------\n";
        cout<<"Enter the number of processes\n";
        int n; cin>>n;
        vector<pair<int,pair<int,int>>> v;
        cout<<"Enter the arrival times , priority and  burst times\n";
        // assuming lower numbers denote higher priority.
        cout<<"AT P BT\n";
        for (int i = 0; i < n; i++)
        {
            int x,y,z;
            cin>>x>>y>>z;
            v.push_back({x,{y,z}});
        }
        sort(v.begin(),v.end());
        cout<<"The processes will be referenced as follows\n";
        for(int i=0;i<n;i++){
            cout<<"Process :"<<i+1<<" AT="<<v[i].first<<" "<<" Priority="<<v[i].second.first<<" "<<
            " BT="<<v[i].second.second<<"\n";
        }
        cout<<"\n";
        map<pair<int,pair<int,int>>,int> gc_helper;
        int idleTime =0;
        vector<int> wait(n,0);
        vector<int> burst;
        for(auto &q:v){
            burst.push_back(q.second.second);
        }
        int process=-1;
        int start=0;
        int finish=0;
        int time=0;
        while(finish<n)
        {  
            int mostPriority=INT_MAX;
            int next_process=-1;
            for (int j = 0; j<n ;j++)
            {
                if(v[j].first>time) break;
                else{
                    if(v[j].second.second==0) continue;
                    if(v[j].second.first<mostPriority){
                        mostPriority=v[j].second.first;
                        next_process=j;
                    }
                }
            }
            if(next_process!=-1){
                if(process==-1){
                    process=next_process;
                    start=time;
                }
                else{
                    if(process!=next_process){
                        gc_helper[{start,{time,process+1}}];
                        start=time;
                        process=next_process;
                    }
                }
                v[process].second.second--;
                for (int j = 0; j<n; j++)
                {   if(j==process or v[j].second.second==0) continue;
                    if(v[j].first>time) break;
                    else{
                        wait[j]++;
                    }
                }
                if(v[process].second.second==0) {
                    finish++;
                    gc_helper[{start,{time+1,process+1}}];
                    process=-1;
                }
            }
            else{
                idleTime++;
            }  
            time++;   
        }
        vector<pair<int,int>> temp(n);
        for(int i=0;i<n;i++) temp[i].second=burst[i];
        gant_chart(gc_helper);
        cpu_performance(wait,temp,idleTime,n);
    }
    else if(ans=="no"){
        cout<<"------------------------------------------------------------------\n";
        cout<<"Enter the number of processes\n";
        int n; cin>>n;
        vector<pair<int,pair<int,int>>> v;
        cout<<"Enter the arrival times , priority and  burst times\n";
        // assuming lower numbers denote higher priority.
        cout<<"AT P BT\n";
        for (int i = 0; i < n; i++)
        {
            int x,y,z;
            cin>>x>>y>>z;
            v.push_back({x,{y,z}});
        }
        sort(v.begin(),v.end());
        cout<<"The processes will be referenced as follows\n";
        for(int i=0;i<n;i++){
            cout<<"Process :"<<i+1<<" AT="<<v[i].first<<" "<<" Priority="<<v[i].second.first<<" "<<
            " BT="<<v[i].second.second<<"\n";
        }
        cout<<"\n";
        int idleTime =0;
        vector<int> wait(n,0);
        int time=v[0].first+v[0].second.second;
        wait[0]=0;
        idleTime+=v[0].first;
        map<pair<int,pair<int,int>>,int> gc_helper;
        int start=v[0].first;
        vector<int> done(n,0);
        done[0]=1;
        int process=0;
        for (int i=1; i<n ; i++)
        {
            gc_helper[{start,{time,process+1}}]++;
            int jobPriority=INT_MAX;
            bool found=false;
            for(int j=1;j<n;j++){
                if(!done[j]){
                    if(v[j].first<=time){
                        if(v[j].second.first<jobPriority) {
                            jobPriority=v[j].second.first;
                            process=j;
                            found=true;
                        }
                    }
                    else{
                        if(!found) process=j;
                        break;
                    }
                }
            }
            done[process]=1;
            if(v[process].first<=time){
                start=time;
                wait[process]=time-v[process].first;
                time+=v[process].second.second;
            }
            else{
                start=v[process].first;
                wait[process]=0;
                idleTime+=v[process].first-time;
                time=v[process].first+v[process].second.second;
            }
        }
        gc_helper[{start,{time,process+1}}]++;
        gant_chart(gc_helper);
        vector<pair<int,int>> temp;
        for(auto &it:v){
            temp.push_back({it.first,it.second.second});
        }
        cpu_performance(wait,temp,idleTime,n);
    }
    else{
        cout<<"You have entered a wrong input (exiting)\n";
    }
}
void ro_robin(){
    cout<<"------------------------------------------------------------------\n";
    cout<<"Enter number of processes: ";
    int n; cin>>n;
    cout<<"Enter Time Quantum for processes: ";
    int tq;cin>>tq;
    vector<int> wait(n,0);
    vector<pair<int,int>> v;
    cout<<"Enter the arrival times and burst times\n";
    cout<<"AT BT\n";
    for (int i = 0; i < n; i++)
    {
        int x,y;
        cin>>x>>y;
        v.push_back({x,y});
    }
    sort(v.begin(),v.end());
    cout<<"The processes will be referenced as follows\n";
    for(int i=0;i<n;i++){
        cout<<"Process :"<<i+1<<" AT="<<v[i].first<<" "<<" BT="<<v[i].second<<"\n";
    }
    cout<<"\n";
    vector<int> burst;
    map<pair<int,pair<int,int>>,int> gc_helper;
    for(auto &x:v){
        burst.push_back(x.second);
    }
    int idleTime=v[0].first;
    int finish=0;
    int time=0;
    int curr=0;
    while(finish<n){
        if(v[curr].first<=time){
            int newtime=time+min(tq,v[curr].second);
            for(int i=0;i<n;i++){
                if(v[i].first>newtime) break;
                else{
                    if(v[i].second>0 and i!=curr) wait[i]+=newtime-time+1;
                }
            }
            gc_helper[{time,{newtime,curr+1}}];
            if(v[curr].second<=tq) {
                v[curr].second=0;
                finish++;
            }
            else {
                v[curr].second-=tq;
            }
            time=newtime;
            int nextcurr=(curr+1)%n;
            if(finish==n) break;
            while(v[nextcurr].first>time or v[nextcurr].second==0){
                if(v[nextcurr].first>time){
                    for(int i=0;i<nextcurr;i++){
                        if(v[i].second!=0){
                            nextcurr=i;
                            break;
                        }
                    }
                    break;
                }
                else nextcurr=(nextcurr+1)%n;
            }
            curr=nextcurr;
        }
        else {
            idleTime+=tq;
            time+=tq;
        }
        
    }
    for(int i=0;i<n;i++) v[i].second=burst[i];
    gant_chart(gc_helper);
    cpu_performance(wait,v,idleTime,n);
}
void runScheduler(int sch_type){
    switch(sch_type){
        case 1: cout<<"Running the FIFO scheduler.....\n";
                fifo();
                break;
        case 2: cout<<"Running the SJF scheduler.....\n";
                sjf();
                break;
        case 3: cout<<"Running the Priority scheduler.....\n";
                priority();
                break;
        case 4: cout<<"Running the round robin scheduler.....\n";
                ro_robin();
                break;
        case 5: cout<<"Ending the operations..\n";
                break;
        default:cout<<"OOps you pressed a wrong input \n";
                break;
    }
}
int main(){
    // driver menu
    bool flag=true;
    while(flag){
        cout<<"Welcome to a simulation of the Process Schedulers\n";
        cout<<"Press 1 for First in First Out Scheduler\n";
        cout<<"Press 2 for Shortest Job First Scheduler\n";
        cout<<"Press 3 for Priority based Scheduler\n";
        cout<<"Press 4 for Round Robin Scheduler\n";
        cout<<"Press 5 to exit\n";
        cout<<"\n";
        int schedulerType;
        cin>>schedulerType;
        runScheduler(schedulerType);
        if(schedulerType==5) flag=false;
    }
    return 0;
}

// cd Schedulers 
// g++ scheduler.cpp