#include<bits/stdc++.h>
using namespace std;

unordered_map<int,vector<pair<int,int>>>graph;

void shortestPath(int src,int vertices,vector<vector<int>>&edges){
    for(auto vec:edges){
        int u = vec[0];
        int v = vec[1];
        int w = vec[2];
        graph[u].push_back({w,v});
        graph[v].push_back({w,u});
    }
    
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>dist(vertices,INT_MAX);
    pq.push({0,src});
    dist[src] = 0;
    //visited-vector for checking the nodes for which we already have finalized the distance
    vector<bool>visited(vertices,false);
    
    while(!pq.empty()){
        auto next = pq.top();
        pq.pop();
        int u = next.second;
        visited[u] = true;
        
        
        for(auto pa:graph[u]){
            int w = pa.first;
            int v = pa.second;
            if( !visited[v] && dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                
                //push the updated minimum distance
                pq.push({dist[v],v});
            }
        }
    }
    
    for(auto val:dist){
        cout<<val<<" ";
    }
}

int main(){
    vector<vector<int>>edges{{0,1,4},{0,7,8},{1,2,8},{1,7,11},{2,3,7},{2,8,2},{2,5,4},{3,4,9},{3,5,14},{4,5,10},{5,6,2},{6,7,1},{6,8,6},{7,8,7}};
    int vertices = 9;
    shortestPath(0,vertices,edges);
    
    return 0;
}