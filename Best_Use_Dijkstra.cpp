class Solution {
public:
    
    void shortestPath(int src,int n,vector<long long>&dist, vector<vector<pair<int,int>>>&graph){
        
        priority_queue<pair<long long,int>,vector<pair<long long ,int>>,greater<pair<long long,int>>>pq;
        dist[src]  = 0;
        vector<bool>visited(n,0);
        pq.push({0,src});
        
        while(!pq.empty()){
           auto u = pq.top().second;
           auto distance = pq.top().first;
            pq.pop();
            visited[u] = true;
            if(dist[u] != distance)
                continue;
           
            
            for(auto &next:graph[u]){
                auto w = next.first;
                auto v = next.second;
                
                if(!visited[v] && dist[v] > distance + w){
                    dist[v] = distance + w;
                    pq.push({dist[v],v});
                }
            }
        }
    
    }
    
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        //vector lookup is faster than map lookup becuase of O(1), in map lookup O(log(v) time is taken
        
        vector<vector<pair<int,int>>>graphforward(n);
        vector<vector<pair<int,int>>>graphreverse(n);
        
        //To get saved from overflow initialized max_val as some low val from LLONG_MAX
        long long max_val = 10000000000, res = LLONG_MAX;
          
        for(auto &edge:edges){
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            graphforward[u].push_back({w,v});
            graphreverse[v].push_back({w,u});
        }
        //distance vector from src1
        vector<long long>dist1(n,max_val);
        shortestPath(src1,n,dist1,graphforward);
        
        //distance vector from src2
        vector<long long>dist2(n,max_val);
        shortestPath(src2,n,dist2,graphforward);
        
        //distance vector from dest to all nodes
        vector<long long>distdest(n,max_val);
        shortestPath(dest,n,distdest,graphreverse);
        
        if(distdest[src1] == max_val || distdest[src2] == max_val)
            return -1;
        
        for(int i = 0;i<n;i++){
            res = min(res,distdest[i] + dist1[i] + dist2[i]);
        }
        
        return res;
    }
};