#include <bits/stdc++.h>
using namespace std;

float INF = std::numeric_limits<float>::infinity();

float D=100.2;

template <class T>
void printVector(vector<T>V){
  for (int i = 0; i <V.size() ; ++i) {
    cout<<V[i]<<", ";
  }
  cout<<endl;
}


template<class T>
T dEuclidiana(T*a,T*b){
  return abs(a[0]-b[0])+abs(a[1]-b[1]);
}

template<class T>
T dEuclidianaManhatan(T*a,T*b){
  return (abs(a[0]-b[0])+abs(a[1]-b[1]))*D;
}

template<class T>
T dEuclidiana2(T*a,T*b){
  T Dx=abs(a[0]-b[0]);
  T Dy=abs(a[1]-b[1]);
  return D*(sqrt((Dx*Dx)+(Dy*Dy)));
}

template<class T>
T dEuclidiana3(T*a,T*b){
  T Dx=abs(a[0]-b[0]);
  T Dy=abs(a[1]-b[1]);
  return D*((Dx*Dx)+(Dy*Dy));
}

template<class T>
T breakTies(T*a,T*b,T*c){
  T dx1=c[0]-b[0];
  T dy1=c[1]-b[1];
  T dx2=a[0]-b[0];
  T dy2=a[1]-b[1];
  return abs((dx1*dy2)-(dx2*dy1));
}

template<class T>
T diagonalDistance(T*a,T*b){
  return max(abs(a[0]-b[0]),abs(a[1]-b[1]))*D;
}

struct Graph{
  int V;
  list< pair<int,float> >*adj;
  vector<float*>coord;
  Graph(int V){
    this->V=V;
    adj=new list<pair<int,float> >[V];
    coord.resize(V);
  }
  void addNode(int pos,float x,float y){
    float *p=new float[2];
    p[0]=x;
    p[1]=y;
    coord[pos]=p;
  }
  
  void addEdge(int u,int v,float w){
    adj[u].push_back(make_pair(v,w));
    //    adj[v].push_back(make_pair(u, w));
  }
  void print(){
    for (int i = 0; i <V; ++i) {
      cout<<i<<" ["<<coord[i][0]<<"]["<<coord[i][1]<<"]: "<<endl;
      list<pair<int,float> >::iterator j;
      for (j = adj[i].begin(); j !=adj[i].end(); j++) {
	cout.width(2);
	cout<<"-"<<(*j).second<<"-> "<<(*j).first<<endl;
      }
    }
  }


  
  
  void aStar(int a,int b){
    vector<float*>score(V);//0:F(G+H),1:G Peso, 2:Heuristic,3:Estado (1:OpenList,2:CloseList)
    priority_queue< pair<float,int>,vector<pair<float,int> >,greater< pair<float,int> > >openList;
    int path[V];
    openList.push(make_pair(0,a));
    score[a]=new float[4];
    score[a][0]=score[a][1]=score[a][2]=score[a][3]=0;
    while(openList.size()>0){
      int temp=openList.top().second;
      openList.pop();
      score[temp][3]=2;
      list<pair<int,float> >::iterator vecino;
      for (vecino = adj[temp].begin(); vecino !=adj[temp].end(); vecino++) {
	int tempN=(*vecino).first;
	float F,G,H;
	float pesoTempN=(*vecino).second;
	G=pesoTempN+score[temp][1];
	//H=(dEuclidiana(coord[tempN],coord[b]));//Basica
	//H=(dEuclidianaManhatan(coord[tempN],coord[b]))+breakTies(coord[a],coord[b],coord[tempN]);//Mejor
	//H=(dEuclidiana2(coord[tempN],coord[b]));//Mucho mejor
	//H=(dEuclidiana2(coord[tempN],coord[b]))+breakTies(coord[a],coord[b],coord[tempN]);//Mucho mejor pero no tanto	  
	//H=diagonalDistance(coord[tempN],coord[b])+breakTies(coord[a],coord[b],coord[tempN]);
	H=dEuclidiana3(coord[tempN],coord[b])+breakTies(coord[a],coord[b],coord[tempN]);
	F=G+H;
	if(score[tempN]!=NULL){	  
	  if(score[tempN][3]==1){
	    if(H<score[tempN][2]){
	      score[tempN][0]=F;
	      score[tempN][1]=G;
	      score[tempN][2]=H;
	      path[tempN]=temp;
	      openList.push(make_pair(H,tempN));
	    }
	  }
	}
	else{
	  openList.push(make_pair(H,tempN));
	  float*scoreTemp=new float[4];
	  scoreTemp[0]=F;
	  scoreTemp[1]=G;
	  scoreTemp[2]=H;
	  scoreTemp[3]=1;
	  path[tempN]=temp;
	  score[tempN]=scoreTemp;
	}
	if(tempN==b){	
	  break;
      }

      }
    }
    
    /*       
    if(closeList[closeList.size()-1]==b){
      vector<int>camino;
      int bTemp=b;
      while(bTemp!=-1){
	//cout<<"btemo "<<bTemp<<endl;
	camino.push_back(bTemp);
	bTemp=path[bTemp];
      }
      for(int x=camino.size();x>0;x--)
	cout<<camino[x-1]<<",";
      cout<<endl;
    }
    
    else
      cout<<"No hay camino"<<endl;
    */
  }

  void dijkstra(int s,int f,int *path){
    priority_queue< pair<float,int>,vector<pair<float,int> >,greater< pair<float,int> > >pq;
    vector<float>dist(V,INF);
    
    pq.push(make_pair(0,s));
    dist[s]=diagonalDistance(coord[s],coord[f]);
    pq.push(make_pair(dist[s],s));
    path[s]=-1;
    path[f]=-1;
    while(!pq.empty()){
      int u=pq.top().second;
      pq.pop();
      list<pair<int,float> >::iterator i;
      for (i=adj[u].begin(); i!=adj[u].end() ;i++){
	int v=(*i).first;
	float distancia=diagonalDistance(coord[v],coord[f]);	
	if(dist[u]>distancia){
	  dist[v]=distancia;
	  pq.push(make_pair(dist[v],v));
	  path[v]=u;
	}
	if(v==f)
	  break;
   
      }
    }
    //cout<<"Distancia :"<<endl;
    //for (int i = 0; i < V; ++i) {
    //  cout<<"i:"<< i<< " dist:"<<dist[i]<<endl;

    //}

    //printVector(path);
    //printVector(dist);
    //return path;
  }


  
  void dijkstra2(int s,int f){
    priority_queue< pair<float,int>,vector<pair<float,int> >,greater< pair<float,int> > >pq;
    vector<float>dist(V,1);
    vector<int>visit(V,1);
    vector<int>path;
    dist[s]=diagonalDistance(coord[s],coord[f]);
    pq.push(make_pair(dist[s],s));
    while(!pq.empty()){
      int u=pq.top().second;
      path.push_back(u);
      pq.pop();
      visit[u]=0;
      if(u==f)
	  break;
      list<pair<int,float> >::iterator i;
      for (i=adj[u].begin(); i!=adj[u].end() ;i++){
	int v=(*i).first;
	float distancia=diagonalDistance(coord[v],coord[f]);	
	if(dist[u]>distancia and visit[v]==1){
	  dist[v]=distancia;
	  pq.push(make_pair(dist[v],v));
	}
	
      }
    }
    //printVector(path);
   
  }
  

  void printCaminoD(int a,int b){
    //int* path=new int[V];
    int *path=new int[V];
    dijkstra(a,b,path);
    for(int x=0;x<V;x++){
      cout<<path[x]<<" ,";
    }
    cout<<endl;
    vector<int>camino;
    int bTemp=b;
    if(path[b]==-1)
      cout<<"-1"<<endl;
    else{
      camino.push_back(a);
      while (path[bTemp]!=a){
	camino.insert(camino.begin()+1,path[bTemp]);
	bTemp=path[bTemp];
      }
      camino.push_back(b);

    }
    //printVector(camino);
  }  
};




int main(){
  /*  int tam=10;
  Graph Grafo(tam);
  float coordInicio[tam*2]={0,0,5,0,1,3,4,3,0,6,2,6,6,6,1,8,5,8,6,9};
  int j=0;
  for(int x=0;x<tam;x++){
    Grafo.addNode(x,coordInicio[j],coordInicio[j+1]);
    j=j+2;
  }
  Grafo.addEdge(0,1,10.0);
  Grafo.addEdge(0,2,20.0);
  Grafo.addEdge(0,4,20.0);
  Grafo.addEdge(2,4,80.0);
  Grafo.addEdge(2,1,5.0);
  Grafo.addEdge(2,5,6.0);
  Grafo.addEdge(1,3,15.0);
  Grafo.addEdge(1,6,10.0);
  Grafo.addEdge(3,5,7.0);
  Grafo.addEdge(5,6,1.0);
  Grafo.addEdge(5,7,6.0);
  Grafo.addEdge(5,8,20.0);
  Grafo.addEdge(6,8,3.0);
  Grafo.addEdge(7,8,12.0);
  */
  //Grafo.aStar(0,9);
  //Grafo.print();

  int nv, ne, u, v;
  float w;
  cin >> nv >> ne;
  
  Graph g(nv);
  
  float x,y;
  for(int a=0;a<nv;a++){
    cin >> x >> y; 
    g.addNode(a, x, y);
  }
  //printCoord(g.coord);
  for(int a=0;a<ne;a++){
    cin >> u >> v >> w;
    g.addEdge(u, v, w);
  }
  int *path=new int[nv];
  //g.aStar(0,nv-1);
  clock_t begin = clock();
  vector<int>Inicio,Fin;
  for(int pos=0;pos<100;pos++){
    Inicio.push_back(10);
    Fin.push_back(200);
  }
  cout<<"Inicio"<<endl;
  for(int count=0;count<100;count++){
    g.dijkstra2(Inicio[count],Fin[count]);
  }
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"en seg: "<<elapsed_secs<<endl;

   return 0;
}
